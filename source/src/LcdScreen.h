#ifndef LcdScreen_h
#define LcdScreen_h

#include <inttypes.h>
//#include <stdio.h> // for size_t
#include <stdarg.h>
#include "WString.h"

#include <LiquidCrystal.h>
#include "DataStore.h"

/*LCD_KeyPad_shield pins*/
#define LCD_RS 11 
#define LCD_ENABLE 10
#define LCD_PINS_D4 12
#define LCD_PINS_D5 13
#define LCD_PINS_D6 14
#define LCD_PINS_D7 15
//#define LCD_BLACKLIGHT 13
//#define LCD_KEYS PIN_A4

class LcdScreen
{
protected:
   const __FlashStringHelper *item0;
   const __FlashStringHelper *item1; 
public:
    virtual void show(LiquidCrystal *lcd);
    virtual void add();
    virtual void sub();
    virtual uint8_t ok();

    void addItem0(const __FlashStringHelper *it);
    void addItem1(const __FlashStringHelper *it);
};

class StaticLcdScreen:public LcdScreen
{
public:
    StaticLcdScreen(){
        item0 = NULL;
        item1 = NULL;
    };

    StaticLcdScreen(const __FlashStringHelper *it0, const __FlashStringHelper *it1){
        item0 = it0;
        item1 = it1;
    };
    
    

    void show(LiquidCrystal *lcd);
    void add(){
        return;
    };
    void sub(){
        return;
    };
    uint8_t ok(){
        return -1;
    };

};

class DinamicLcdScreen: public LcdScreen
{
protected:
    DataReal *data1, *data2;
    

    uint16_t *d0_1;
    uint16_t *d0_2;
    uint16_t *d1_1;
    uint16_t *d1_2;
public:
    DinamicLcdScreen(){
 
        item0 = NULL;
        item1 = NULL;
        d0_1 = d0_2 = d1_1 = d1_2 = NULL;
        data1 = data2 = NULL;
    };

    DinamicLcdScreen(const __FlashStringHelper *it0, const __FlashStringHelper *it1){
        item0 = it0;
        item1 = it1;
        d0_1 = d0_2 = d1_1 = d1_2 = NULL;
        data1 = data2 = NULL;
    };

    
    //динамические данные пкредаются как указатель .. ограничение - не более двух динамических значений на строку 
    void addData0(uint16_t *d1, uint16_t *d2);
    void addData1(uint16_t *d1, uint16_t *d2);
    void addData(DataReal *data1, DataReal *data2);
    
    void show(LiquidCrystal *lcd);
    void add(){
        return;
    };
    void sub(){
        return;
    };
    uint8_t ok(){
        return -1;
    };


};

class EditLcdScreen: public DinamicLcdScreen
{//Mode Number Switch - разновидности класса
    public:
        EditLcdScreen():DinamicLcdScreen(F("Edit data (%u)"),F("  <   %u   >")){

        };
        EditLcdScreen(const __FlashStringHelper *it0, const __FlashStringHelper *it1):DinamicLcdScreen(it0,it1){

        };


        void addData0(uint16_t *d1);
        void addData1(uint16_t *d1);
        void addData(DataEdit *data);
        void show(LiquidCrystal *lcd);
        void add();
        void sub();
        uint8_t ok();
};

class ModeLcdScreen: public LcdScreen{
    private:
        DataReal *data;
        const char **mode;
    public:

        ModeLcdScreen(const __FlashStringHelper *it0, const __FlashStringHelper *it1){
            item0 = it0;
            item1 = it1;
            data = NULL;
            mode = NULL;
        };
        
        void addData(DataEdit *data);
        void addMode(const char* mode);
        void show(LiquidCrystal *lcd);
        void add();
        void sub();
        uint8_t ok();
};


#endif