#ifndef ANALOGRW_H
#define ANALOGRW_H
//ADC_DAC_MODULE
//MCP3204 and DAC8830
//В модуле предусмотрены делители напряжения на каналах
// ch0 - делитель 1 - используется для измерения напряжения на датчике тока ACS712-20A 
// ch1 - делитель 10 - используется для измерения напряжения на выходе АБК 
// ch2 - делитель 10 - используется для измерения напряжения на нагрузке 
// ch3 - делитель 1 - используется для измерения напряжения на выходе внутреннего (для модуля) ЦАП (назначение не изменяется - реализовано в схеме) 

//опорное напряжение для "0" датчика тока 
#define DT_20 2500 

#include <SPI.h>

#define CS_A 4 // порт МК для выбора микросхемы АЦП
#define CS_D 2 // порт МК для выбора микросхемы ЦАП

#define RELE1 23
#define RELE2 22

#define ON_ 1 // порт МК для включения чопера TL4016 (ON - low; OFF - hight)

enum chanel{
    ch0, ch1, ch2, ch3
};



class AnalogRW{

private:

    //byte mutex;
    uint8_t kVref;
    uint16_t _DT;

    /* Объединение, предназначеное для передачи
    первого байта настройки АЦП */
    union{
        struct {
            char d2:1;
            char single_channel:1;
            char start_bit:1;
            char unused:5;
        } str;
        char chr;
    } adc_ctrl0;
    
    /* Объединение, предназначеное для передачи
    второго байта настройки АЦП */
    union{
        struct {
            char unused:6;
            char d0:1;
            char d1:1;
        } str;
        char chr;
    } adc_ctrl1;

public:
    uint8_t f_positive; //0 1 флаг указывающий направление тока 0 - разряд 1 - заряд

    AnalogRW();

    //inline void setDT(uint16_t dt){
    //    _DT = dt;
    //};

    void settingDT();

    // читает значение канала в миливольтах
    uint16_t readMCP3204(chanel ch);

    
    // читает среднее  из измеренных значение канала в миливольтах
    uint16_t averageMeasured(chanel ch);

    void sendDAC8830(uint16_t data);

    void settingADC8830();

    
    //int8_t getCurrentMult100(){};

    ///Возвращает напряжение в виде 1.25В = 125
    uint16_t getU_AKB();
    ///Возвращает напряжение в виде 1.25В = 125
    uint16_t getU_Load();

    /// Возвращает ток в цепи выставляе флаг POSITIVE
    /// значение ==> ток * 100 т.е. 1.25А = 125
    uint16_t getI_AKB();


    /// Устанавливает значение напряжения в миливольтах
    /// min = 0 mV, max = 4096 mV
    void setVoltage(uint16_t voltage);

    /// Отключает преобразователь напряжения DC-DC
    inline void onDC(){digitalWrite(ON_,LOW);};

    /// Включает преобразователь напряжения DC-DC
    inline void offDC(){digitalWrite(ON_,HIGH);};

    inline void releLoad(){
        digitalWrite(RELE1,LOW);
        digitalWrite(RELE2,HIGH);
    };

    inline void releZaryd(){
        digitalWrite(RELE2,LOW);
        digitalWrite(RELE1,HIGH);
    }
    inline void releOff(){
        digitalWrite(RELE2,HIGH);
        digitalWrite(RELE1,HIGH);
    }


};

#endif // ANALOGRW_H