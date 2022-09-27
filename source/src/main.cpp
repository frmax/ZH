#include <Arduino.h>
#include <AnalogRW.h>

#include "sma_filter.h"
#include "ProcessIU.h"
#include "DataStore.h"
#include "LcdScreen.h"
#include "LcdMenu.h"

AnalogRW *pMeter;
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_PINS_D4, LCD_PINS_D5, LCD_PINS_D6, LCD_PINS_D7);

LcdMenu menu;

//Create screen
StaticLcdScreen   *pScreenInfo;
DinamicLcdScreen  *pScreenMain;
EditLcdScreen     *pScreenEditI;
EditLcdScreen     *pScreenEditU;
ModeLcdScreen     *pScreenMode;
//DinamicLcdScreen  *pScreenAmper;

//Create data 1V = 100 and 1A=100
DataReal trueI(0);
DataReal trueRI(0);
DataReal trueU(0);
DataEdit limI(100,0,900,10); //(init data, min, max, step, ring=0)
DataEdit limU(1050,550,1600,10);
DataEdit mode(0,0,3,1,1);

//DataReal amperH(0);

uint64_t TimerNew,TimerPrev,GlobalSec = 0; // для таймера выполнения операций кнопок и оновления экрана
uint8_t  msec10,msec30,msec; // для подсчета 10 и 100 интервалов  по 10 мили секнд - т.е 1/10 и 1 секунда

uint16_t out = 0;

char status = '0';

uint8_t zarydRazdyd = 255;
uint16_t lastTrueI = 0;

void setup() {
  
  delay(100);
  lcd.begin(16, 2);
  pScreenInfo   = new StaticLcdScreen(F("  ZARYDNOE AKB  "),F("   VER. 0.01a   "));
  pScreenMain   = new DinamicLcdScreen(F("    WAITING...  "),F("%2u.%02uB  %2u.%02uA"));
  //pScreenMain   = new DinamicLcdScreen(F("    PROCESS...  "),F("%2u.%02uB  %2u.%02uA"));
  pScreenEditI  = new EditLcdScreen(F("Max tok(%2u.%02uA) "),F("  <  %2u.%02uA  >  "));
  pScreenEditU  = new EditLcdScreen(F("Max nap(%2u.%02uB) "),F("  <  %2u.%02uB  >  "));
  pScreenMode   = new ModeLcdScreen(F("Status (%4s )     "),F("   < %4s  >       "));

  //pScreenAmper = new DinamicLcdScreen(F("   AMPER*HOUR   "),F("%2u.%02uAh  %2u.%02uAh"));

  //pScreenMain->addData(&trueU,&trueI);
  pScreenMain->addData(&trueU,&trueI);
  pScreenEditI->addData(&limI);
  pScreenEditU->addData(&limU);

  pScreenMode->addData(&mode);
  pScreenMode->addMode("off");
  pScreenMode->addMode("on");
  pScreenMode->addMode("ktc");
  pScreenMode->addMode("nag");
  
  //pScreenAmper->addData(&amperH,&amperH);

  menu = LcdMenu(pScreenInfo);
  menu.addScreen(pScreenMain);
  //menu.addScreen(pScreenAmper);
  menu.addScreen(pScreenEditI);
  menu.addScreen(pScreenEditU);
  menu.addScreen(pScreenMode);

  pMeter = new AnalogRW();
  pMeter->releOff();//схема собирается на нагрузку от сетевого источника питания
  pMeter->settingDT();
  pMeter->setVoltage(100);
  pMeter->onDC();  
  //Вычисление среднего скользящего - НАЧАЛО
  for(int i = 0; i <32; i++){
    // На старте требуется накопить 32 измерения по одному за цикл и 
    Filtering(pMeter->getI_AKB(),&filter[0]);       // ток 
    Filtering(pMeter->readMCP3204(ch1),&filter[1]); // напряжение АКБ
    Filtering(pMeter->readMCP3204(ch2),&filter[2]); // напряжение на нагрузке
    
  }
  pMeter->offDC();


  Serial.begin(115200);
  Serial.println("status, out, voltage, curent");

  menu.show(&lcd);
  delay(2000);
  menu.nextMenu();

}

void loop() {

  // ch0 - ток
  // ch1 - напряжение на выходе (или АБК)
  // ch2 - напряжение на нагрузке (или выход )
  // ch3 - напряжение на управляющем канале FB

/*
//Временный код для проверки соответсвия с устанавливаемым значением напряжния и измереным
  t = t<4050?t:0;
  pMeter->setVoltage(t);
  trueI.setData(t);
  delay(20);
  trueU.setData(pMeter->readMCP3204(ch3));
  t+=100;
  //вычислить Kref = setVoltage / readMCP дописать функцию измрения с поправкой на коэфф.
  
*/

// Замер тока и напряжения и передача их на регулятор
trueI.setData(Filtering(pMeter->getI_AKB(),&filter[0]));
trueU.setData(Filtering(pMeter->readMCP3204(ch1),&filter[1]));


if(mode.getData()){

    //при старте заряда использовать функцию processUI и дождаться перехода на режим К 
    //если его нет по истеченю времени написать нет АКБ что 
    //будет также означать неисправный АКБ либо завышенный лимит тока заряда
    // Далее перейти на режим заряда по току processIU и при достижении режима U
    // перйти на функцию поддержания напряжения processUI и дожидаться тока близкого к 0.07A при срабатывании режима К перейти снова на режим заряда по току
    //mode = processIU(limU.getData(), limI.getData(), out, trueU.getData(),trueI.getData());
    
  if(zarydRazdyd){

    pMeter->releZaryd();
    pMeter->onDC();
         
    switch (status){
      case 'K':
      case 'I':
        status = processIU(limU.getData(), limI.getData(), out, trueU.getData(),trueI.getData());
        pScreenMain->addItem0(F("    PROCESS I   "));
        break;
      
      default:
        status = processUI(limU.getData(), limI.getData(), out, trueU.getData(),trueI.getData());
        pScreenMain->addItem0(F("    PROCESS U   "));
        break;
      }
    pMeter->setVoltage(out);
  }
  else{
    
    pMeter->releLoad();
    pMeter->onDC();
    //режим заряд разряд - разряд током текущего заряда/10 через равные промежутки времени?
      //разряд
              //U на нагрузке  I поддерж на нагрузке
    processRI(limU.getData(), lastTrueI, out, trueU.getData(),trueRI.getData());
    pMeter->setVoltage(out);
  }
} 

  
  


TimerNew = millis() % 1000 / 10; // 10 милисекунд выявляем остаток от деления на тысячу счетчика милис. Остаток будет кратен 10 милисекундам. То есть минимальный интервал используемый для выполнения каких-либо функций 10милисекунд.
if (TimerPrev != TimerNew) { // переменная TimerNew меняет свое значение раз в 10 милисекунд.  Для того чтобы выявить что это произошло  мы сравниваем ее с запомненным ранее значением
    TimerPrev = TimerNew;  // при несовпадении значения запомненного ранее и текущего значения переменных таймера контроллер понимает что прошли очередные 10 миллисекунд. Запомненное ранее значение обновляется текущим
   
   /*
   // посылаем данные в порт каждые 10ms
    Serial.print(status);
    Serial.print(", ");
    Serial.print(out);
    Serial.print(", ");
    Serial.print(trueU.getData());
    Serial.print(", ");
    Serial.println(trueI.getData());
   */ 

    msec10++;
    msec30++;
    msec++;

    if(msec10 >= 10){
      
      // trueI.setData(NoFiltering(&filter[0]));
      // trueU.setData(NoFiltering(&filter[1]));
        // обновляем экран

        menu.show(&lcd);
        msec10 = 0;
    }

    // 0.3 sec -- 300ms
    if(msec30 >= 30){
      menu.key();
      msec30 = 0;
      if(!mode.getData()){
        pMeter->offDC();
        pMeter->releOff();
        pScreenMain->addItem0(F("    WAITING...  "));
      }else if(mode.getData() == 3){
        lastTrueI = trueI.getData();
        pMeter->offDC();
        zarydRazdyd = 0;
      }
      
    }
    // 1 sec - 1000ms
    if(msec >=100){
      //amperH.add(trueI.getData()/100);
      //здесь меняем заряд на разряд при режиме КТЦ
      if(mode.getData() == 2){
        lastTrueI = trueI.getData()/10;
        pMeter->offDC();
        zarydRazdyd =~zarydRazdyd;
      }
      // ведем учет времени заряда добавляя секунду к счетчику прошедшего времени заряда
      msec = 0;
    }

  }

}