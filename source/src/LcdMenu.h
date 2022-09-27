#ifndef LcdMenu_h
#define LcdMenu_h

#include <Arduino.h>
#include "LcdScreen.h"

#define QMAX 8
#define LCD_KEYS PIN_A4
#define MAINSCREEN 1

enum {
    BUTTON_RIGHT = 100,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_SELECT,
    BUTTON_NONE
};


class LcdMenu{
    private:
   // простая очередь из массива
   LcdScreen *qLcd[QMAX];
   //uint8_t q_start;
   uint8_t q_end;
   uint8_t q_curr;
   uint8_t flag_key;
    protected:
    uint8_t getPressedButton();

    public:
    LcdMenu(){

    };

    LcdMenu(LcdScreen *screen);
    LcdMenu(StaticLcdScreen *screen);
    LcdMenu(DinamicLcdScreen *screen);
    LcdMenu(EditLcdScreen *screen);

    void addScreen(LcdScreen *screen);

    void setMenu(uint8_t id);
    void nextMenu();
    void backMenu();

    void key();//ввести press_key флаг сбрасываемый в show чтобы пропускать нажатия клавиш пока не отобразятся действие

    void show(LiquidCrystal *lcd);
};

#endif