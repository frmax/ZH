#include "displaylcd.h"

#define DIGIT(n) ('0' + (n))
#define DIGIMOD(n, f) DIGIT((n)/(f) % 10)
#define RJDIGIT(n, f) ((n) >= (f) ? DIGIMOD(n, f) : ' ')
#define MINUSOR(n, alt) (n >= 0 ? (alt) : (n = -n, '-'))

DisplayLCD::DisplayLCD() {

    keys = 0;
    cursorMenu = 0;
    
    lcd = new LiquidCrystal(LCD_RS, LCD_ENABLE, LCD_PINS_D4, LCD_PINS_D5, LCD_PINS_D6, LCD_PINS_D7);
    delay(500);
    //screen_byffer = new byte(LCD_WIDTH*LCD_HEIGHT);
    lcd->begin(LCD_WIDTH, LCD_HEIGHT);

    //lcd->createChar(1, bukva_P);      // Создаем символ под номером 1
    //lcd->createChar(2, bukva_I);      // Создаем символ под номером 2
    //lcd->print("\1"); // Выводим символ под номером 1
    //lcd->print("\2");
    //lcd->print("\1P\2BET M\2P"); // Выводим фразу "ПРИВЕТ МИР"

    

};


void DisplayLCD::Test(){

    lcd->setCursor(0,0);
    lcd->print("Battery charging");
    lcd->setCursor(0,1);
    //lcd->print("U=14.4B | I=4.5A");
    lcd->printf("U=%dB",500);

};

void DisplayLCD::Test(uint16_t v){


    // для на пряжения: данные приходят с измерителя в виде 1В = 100 6.78В = 678 
    // значит для получения целой части требуется приходящее значение разделить на 100

    uint8_t cV = v/100;
    uint8_t dV = v%100;

    lcd->setCursor(0,0);
    lcd->print("Battery charging");
    lcd->setCursor(0,1);
    lcd->printf("U=%2u.%-2uB",cV,dV);
    /*
    char conv[8] = { 0 };
    conv[2] = RJDIGIT(v, 1000);
    conv[3] = RJDIGIT(v, 100);
    conv[4] = '.';
    conv[5] = RJDIGIT(v, 10);
    conv[6] = DIGIMOD(v, 1);



    lcd->setCursor(0,0);
    lcd->print("Battery charging");
    lcd->setCursor(0,1);
    lcd->print("U=     B");
    lcd->setCursor(2,1);
    lcd->print(&conv[2]);
*/
};

void DisplayLCD::Test(uint16_t v1,uint16_t v2){

    char conv[8] = { 0 };
    conv[2] = RJDIGIT(v1, 1000);
    conv[3] = RJDIGIT(v1, 100);
    conv[4] = '.';
    conv[5] = RJDIGIT(v1, 10);
    conv[6] = DIGIMOD(v1, 1);

    lcd->setCursor(0,0);
    lcd->print("Battery charging");
    lcd->setCursor(0,1);
    lcd->print("U=     B  U=   B");
    lcd->setCursor(2,1);
    lcd->print(&conv[2]);

    conv[3] = RJDIGIT(v2, 1000);
    conv[4] = '.';
    conv[5] = RJDIGIT(v2, 100);
    conv[6] = RJDIGIT(v2, 10);
    //conv[6] = DIGIMOD(v2, 1);
    lcd->setCursor(12,1);
    lcd->print(&conv[3]);

};

void DisplayLCD::Test(uint16_t v1,float v2){

    char conv[8] = { 0 };
    conv[2] = RJDIGIT(v1, 1000);
    conv[3] = RJDIGIT(v1, 100);
    conv[4] = '.';
    conv[5] = RJDIGIT(v1, 10);
    conv[6] = DIGIMOD(v1, 1);

    lcd->setCursor(0,0);
    lcd->print("Battery charging");
    lcd->setCursor(0,1);
    lcd->print("U=     B  U=   B");
    lcd->setCursor(2,1);
    lcd->print(&conv[2]);

    uint16_t v3 = v2 *1000;

    conv[3] = RJDIGIT(v3, 1000);
    conv[4] = '.';
    conv[5] = RJDIGIT(v3, 100);
    conv[6] = RJDIGIT(v3, 10);
    //conv[6] = DIGIMOD(v2, 1);
    lcd->setCursor(12,1);
    lcd->print(&conv[3]);

};

void DisplayLCD::Menu(){

    if(cursorMenu == 0){
        lcd->createChar(1, bukva_Z);
        lcd->createChar(2, bukva_Ya);
        lcd->createChar(3, bukva_D);
        lcd->createChar(4, bukva_B);
        lcd->createChar(5, bukva_I);
        lcd->setCursor(0,0);
        lcd->print(F("  \1AP\2\3HOE AK\4  "));
        lcd->setCursor(0,1);
        lcd->print(F("  BEPC\5\2 0.01a  "));
        
        cursorMenu = 1;
    }


    if(cursorMenu == 1){
        lcd->setCursor(0,0);
        lcd->print("> ");
        //lcd->print(status);
        lcd->print(" ZARYD        ");
        //va_list list; 
        //va_start(list,status);
        //var v1 = (var)va_arg(list,int);
        //var v2 = (var)va_arg(list,int);
        lcd->setCursor(0,1);
        lcd->print("x ");
        //lcd->printf(F("U=%2u.%-2uB I=%2u.%-2uA"),v1/100,v1%100,v2/100,v2%100);
        lcd->printf(set.values[var::U].format,set.values[var::U].data/100,set.values[var::U].data%100);
        lcd->print(" ");
        lcd->printf(set.values[var::I].format,set.values[var::I].data/100,set.values[var::I].data%100);

        //va_end(list);
    }

    if(cursorMenu == 2){
        lcd->setCursor(0,0);
        lcd->print("  ");
       // va_list list; 
       // va_start(list,status);
       // var v1 = (var)va_arg(list,int);
       // var v2 = (var)va_arg(list,int);
        
        
        lcd->print(set.values[var::setI].name);
        lcd->print(F(" ("));
        lcd->printf(set.values[var::setI].format,set.values[var::setI].data/100,set.values[var::setI].data%100);
        lcd->print(F(")"));

        lcd->setCursor(0,1);
        lcd->print(F("x  < "));
        lcd->printf(set.values[var::setI].format,set.values[var::newI].data/100,set.values[var::newI].data%100);
        
        //set.values[v2].data +=10;
        //set.values[v2].data -=10;

        lcd->print(F(" >"));
        

       // va_end(list);       
    }

        if(cursorMenu == 3){
        lcd->setCursor(0,0);
        lcd->print("  ");
       // va_list list; 
       // va_start(list,status);
       // var v1 = (var)va_arg(list,int);
       // var v2 = (var)va_arg(list,int);
        
        
        lcd->print(set.values[var::setU].name);
        lcd->print(F(" ("));
        lcd->printf(set.values[var::setU].format,set.values[var::setU].data/100,set.values[var::setU].data%100);
        lcd->print(F(")"));

        lcd->setCursor(0,1);
        lcd->print(F("x  < "));
        lcd->printf(set.values[var::setU].format,set.values[var::newU].data/100,set.values[var::newU].data%100);
        
        //set.values[v2].data +=10;
        //set.values[v2].data -=10;

        lcd->print(F(" >"));
        

       // va_end(list);       
    }
};

void DisplayLCD::setSet(var v, uint8_t type, const __FlashStringHelper *name, const __FlashStringHelper *format,uint16_t data, uint16_t min, uint16_t max){
    set.values[v].type = type;
    set.values[v].name = name;
    set.values[v].format = format;
    set.values[v].data = data;
    set.values[v].min = min;
    set.values[v].max = max;
};

void DisplayLCD::setSet(var v, uint16_t data){
    set.values[v].data = data;
};

uint8_t DisplayLCD::getPressedButton(){
        
        int buttonValue = analogRead(LCD_KEYS); 
        if (buttonValue < 60) {
        return BUTTON_RIGHT;
        }
        else if (buttonValue < 200) {
        return BUTTON_UP;
        }
        else if (buttonValue < 400){
        return BUTTON_DOWN;
        }
        else if (buttonValue < 600){
        return BUTTON_LEFT;
        }
        else if (buttonValue < 800){
        return BUTTON_SELECT;
        }
        return BUTTON_NONE;
    };

void DisplayLCD::Key(){

    uint8_t newKey = getPressedButton();

    if(cursorMenu == 0) {
        return;
    }

    if(cursorMenu == 1){
        if(newKey == BUTTON_DOWN) cursorMenu = 2;
        return;
    }

    
    if(cursorMenu == 2){
        if(newKey == BUTTON_UP) cursorMenu = 1;
        if(newKey == BUTTON_DOWN) cursorMenu = 3;

    }

    if(cursorMenu == 3){
        if(newKey == BUTTON_UP) cursorMenu = 2;
        //if(newKey == BUTTON_DOWN) cursorMenu = 3;

    }

};
