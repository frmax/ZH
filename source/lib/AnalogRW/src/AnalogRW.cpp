#include "AnalogRW.h"

AnalogRW::AnalogRW(){

  f_positive = 1;

  adc_ctrl0.str.d2 = 0;
  adc_ctrl0.str.single_channel = 1;
  adc_ctrl0.str.start_bit = 1;
  adc_ctrl0.str.unused = 0;

  adc_ctrl1.str.unused = 0;
  adc_ctrl1.str.d0 = 0;
  adc_ctrl1.str.d1 = 0;

  // ch0 -> d0 = 0; d1 = 0; d2 = not using;
  // ch1 -> d0 = 1; d1 = 0; d2 = not using;
  // ch2 -> d0 = 0; d1 = 1; d2 = not using;
  // ch3 -> d0 = 1; d1 = 1; d2 = not using;

    pinMode(ON_, OUTPUT);
    digitalWrite(ON_,HIGH);// аналог функции offDC()
    
    pinMode(CS_A, OUTPUT);
    pinMode(CS_D, OUTPUT);
    SPI.begin();
    digitalWrite(CS_A,HIGH);
    digitalWrite(CS_D,HIGH);
    kVref = 1;

    _DT = DT_20;
    //settingADC8830();
    //mutex = true;

    //настройка выходов управления реле
    pinMode(RELE1, OUTPUT);
    pinMode(RELE2, OUTPUT);
    digitalWrite(RELE1,HIGH);
    digitalWrite(RELE2,HIGH);
};

uint16_t AnalogRW::readMCP3204(chanel ch){
  
  switch (ch)
  {
    case ch0:
      adc_ctrl1.str.d0 = 0;
      adc_ctrl1.str.d1 = 0;
      break;
    
    case ch1:
      adc_ctrl1.str.d0 = 1;
      adc_ctrl1.str.d1 = 0;
      break;
    
    case ch2:
      adc_ctrl1.str.d0 = 0;
      adc_ctrl1.str.d1 = 1;
      break;
    
    case ch3:
      adc_ctrl1.str.d0 = 1;
      adc_ctrl1.str.d1 = 1;
      break;
    
    default:
      adc_ctrl1.str.d0 = 0;
      adc_ctrl1.str.d1 = 0;
      break;
  }
  
  // выставляем линию sc_adc в ноль
  digitalWrite(CS_A,LOW);

  //SPI.beginTransaction(SPISettings(16000000,MSBFIRST,SPI_MODE0));

  SPI.transfer(adc_ctrl0.chr); // отсылаем первый байт настройки АЦП

  uint8_t tmp_high = SPI.transfer(adc_ctrl1.chr); // отсылаем второй байт настройк содержащий номер канала для выборки, и получаем в ответ первый байт результата
  uint8_t tmp_low = SPI.transfer(0x0); // отсылаем любой байт чтобы получить ответ- второй байт результата
  
  uint16_t tmp = (tmp_high & 0x0f) << 8; // четыре старших бита мусорные - удаляем их и свигаем байт в старший разряд слова
  tmp |= tmp_low; // в младший разряд слова помещаем второй байт результата ответа, тем самым формируя 2-х байтный результат оцифровки min = 0, max =0x0FFF
  // MCP3204 - напрямую измеряет напряжение ==> U = (значение измерения)*4096/Vref - значения напряжения в миливольтах
  // для схемы с Vref= 4,096В и делителем на 10 на входе измерительного канала ==> U = (значение измерения)*10 результат в mV или U =(значение измерения)/100 результат в V.
  // на входе измерительного канала тока отсутвует делитель, но попрежнему измеряется напряжение с датчика ==> I = (значение измерения) mВ или I = (значение измерения)/1000 результат в В
  // опорное напряжение для датчика тока выбрано 5В(перевести на 4.096).
  // чувствительность датчика тока 100mv на 1A- получается линенйная шкала соответвия тока напряжению(при 5В) 2500mV = 0mA 3000mV = 5000mA 2650mV = 1500mA 2400mV = -1000mA

  //SPI.endTransaction();

  // выставляем линию sc_adc в еденицу
  digitalWrite(CS_A,HIGH);

  return tmp;

};


uint16_t AnalogRW::averageMeasured(chanel ch){
  uint16_t aver = 0; // 16 бит вместит максимум 16 измерений без переполнения для значений с максимум 0x0FFF

  for(byte i=0; i<8;i++){
    aver += readMCP3204(ch);
  }

  aver = aver>>3;
  return aver;
};

void AnalogRW::sendDAC8830(uint16_t data){
  // выставляем линию sc_dac в ноль
  digitalWrite(CS_D,LOW);

  //SPI.beginTransaction(SPISettings(16000000,MSBFIRST,SPI_MODE0));
  
  SPI.transfer16(data);

  //SPI.endTransaction();

  // выставляем линию sc_dac в еденицу
  digitalWrite(CS_D,HIGH);
};

void AnalogRW::settingADC8830(){
  //настраеваем путем подачи на ЦАП максимального
  // уровня его измерения а также  минимально
  // при этом ЗУ должно работать на LOADING
  // исходя из этого установка коэффициента Vref

  sendDAC8830(0xFFFF);
  uint16_t tmp_kRef = averageMeasured(ch3);
  // 4.096 * 0xfff /65536
  // округляем (0xffff>>15) получаем значение напряжения на выходе ЦАП при подчи 0xffff
  // сравниваем со значения полученого из АЦП tmp_kRef и вводдим коэфициент 
  kVref = (0xffff>>15)/tmp_kRef;

};

void AnalogRW::setVoltage(uint16_t voltage){
  /* Напряжение задается в миливольтах
  * Значение напряжения не должно превышать Vref = 4096mV
  * для перевода желаемого к установке напряжения в значения кода
  * нужно напряжение умножить на 0xffff и разделить на 4096, а из него вычесть 1
  */
  uint16_t tmp = voltage<=0?0:(voltage << 4 ) - 1;
  sendDAC8830(tmp);
};

uint16_t AnalogRW::getU_AKB(){
  return readMCP3204(ch1);
};

uint16_t AnalogRW::getU_Load(){
  return readMCP3204(ch2);
};

uint16_t AnalogRW::getI_AKB(){

  uint16_t curent_= readMCP3204(ch0);
  
  //if (curent_ < DT_20){
  //  f_positive = 0;
  //  curent_ = DT_20 - curent_;
  //}else{
  //  f_positive = 1;
  //  curent_ -= DT_20;
  //}
  //curent_ = curent_ < DT_20 ? 0 : curent_ - DT_20;
  curent_ = curent_ < _DT ? _DT - curent_ : curent_ - _DT; 
  return curent_;
};

void AnalogRW::settingDT(){
  //вызывается в состоянии покоя
  uint32_t curent_ = 0;
  for(uint8_t i = 0; i<32; i++)
    curent_ += readMCP3204(ch0);
  _DT = (uint16_t)(curent_>>5);
};