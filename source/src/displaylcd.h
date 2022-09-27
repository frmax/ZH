#ifndef DISPLAYLCD_H
#define DISPLAYLCD_H

#include "LiquidCrystal.h"
#include "Wire.h"

#define LCD_WIDTH 16
#define LCD_HEIGHT 2

//LCD_KeyPad_shield pins
#define LCD_RS 11 //Register select H:data L:instruction
#define LCD_ENABLE 10
#define LCD_PINS_D4 12
#define LCD_PINS_D5 13
#define LCD_PINS_D6 14
#define LCD_PINS_D7 15
//#define LCD_BLACKLIGHT 13
#define LCD_KEYS PIN_A4

enum {
    BUTTON_RIGHT = 100,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_SELECT,
    BUTTON_NONE
};

 enum var {
    setU,
    setI,
    U,
    I,
    newI,
    newU,
    last
  };

 class Settings
 {
   public:
   

  typedef struct
  {
    uint8_t type;//0 - динамические данные не сохраняются; 1 - числа; 2 - flag.
    //uint16_t name;
    const __FlashStringHelper *name; // для заголовка
    const __FlashStringHelper *format; //для вывода самого значения
    uint16_t max;
    uint16_t min;
    uint16_t data;
    
  } __attribute__((packed)) _data;

  //_data setUs ={(uint8_t)1,"Max U zaryda",(uint16_t)600,(uint16_t)1600,(uint16_t)12000};

  _data values[var::last];

  uint16_t getData(var variable){
    return values[variable].data;
  }

 };


class DisplayLCD{
    
    private:
    Settings set;
    uint8_t cursorMenu;

    uint16_t keys;

    LiquidCrystal *lcd;
    //byte *screen_byffer;

    byte bukva_B[8]   = {B11110,B10000,B10000,B11110,B10001,B10001,B11110,B00000,}; // Буква "Б"
    byte bukva_G[8]   = {B11111,B10001,B10000,B10000,B10000,B10000,B10000,B00000,}; // Буква "Г"
    byte bukva_D[8]   = {B01111,B00101,B00101,B01001,B10001,B11111,B10001,B00000,}; // Буква "Д"
    byte bukva_ZH[8]  = {B10101,B10101,B10101,B11111,B10101,B10101,B10101,B00000,}; // Буква "Ж"
    byte bukva_Z[8]   = {B01110,B10001,B00001,B00010,B00001,B10001,B01110,B00000,}; // Буква "З"
    byte bukva_I[8]   = {B10001,B10011,B10011,B10101,B11001,B11001,B10001,B00000,}; // Буква "И"
    byte bukva_IY[8]  = {B01110,B00000,B10001,B10011,B10101,B11001,B10001,B00000,}; // Буква "Й"
    byte bukva_L[8]   = {B00011,B00111,B00101,B00101,B01101,B01001,B11001,B00000,}; // Буква "Л"
    byte bukva_P[8]   = {B11111,B10001,B10001,B10001,B10001,B10001,B10001,B00000,}; // Буква "П"
    byte bukva_Y[8]   = {B10001,B10001,B10001,B01010,B00100,B01000,B10000,B00000,}; // Буква "У"
    byte bukva_F[8]   = {B00100,B11111,B10101,B10101,B11111,B00100,B00100,B00000,}; // Буква "Ф"
    byte bukva_TS[8]  = {B10010,B10010,B10010,B10010,B10010,B10010,B11111,B00001,}; // Буква "Ц"
    byte bukva_CH[8]  = {B10001,B10001,B10001,B01111,B00001,B00001,B00001,B00000,}; // Буква "Ч"
    byte bukva_Sh[8]  = {B10101,B10101,B10101,B10101,B10101,B10101,B11111,B00000,}; // Буква "Ш"
    byte bukva_Shch[8]= {B10101,B10101,B10101,B10101,B10101,B10101,B11111,B00001,}; // Буква "Щ"
    byte bukva_Mz[8]  = {B10000,B10000,B10000,B11110,B10001,B10001,B11110,B00000,}; // Буква "Ь"
    byte bukva_IYI[8] = {B10001,B10001,B10001,B11001,B10101,B10101,B11001,B00000,}; // Буква "Ы"
    byte bukva_Yu[8]  = {B10010,B10101,B10101,B11101,B10101,B10101,B10010,B00000,}; // Буква "Ю"
    byte bukva_Ya[8]  = {B01111,B10001,B10001,B01111,B00101,B01001,B10001,B00000,}; // Буква "Я"
    byte bukva_Up[8]      = {B00000,B00100,B01110,B11111,B00000,B00000,B00000,B00000,}; // Стрелка вверх
    byte bukva_Down[8]    = {B00000,B00000,B00000,B00000,B11111,B01110,B00100,B00000,}; // Стрелка вниз
    byte bukva_Right[8]   = {B00000,B00100,B00110,B00111,B00110,B00100,B00000,B00000,}; // Стрелка вправо
    byte bukva_Left[8]    = {B00000,B00100,B01100,B11100,B01100,B00100,B00000,B00000,}; // Стрелка влево

    uint8_t getPressedButton();


    public:
    DisplayLCD();
    
    void setSet(var v, uint16_t data);
    void setSet(var v, uint8_t type, const __FlashStringHelper *name, const __FlashStringHelper *format,uint16_t data, uint16_t min, uint16_t max);

    void Test();
    void Test(uint16_t v);
    void Test(uint16_t v1,uint16_t v2);
    void Test(uint16_t v1,float v2);
    void Menu();
    void Key();

};



#endif // DISPLAYLCD_H