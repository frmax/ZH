#include "LcdMenu.h"

uint8_t LcdMenu::getPressedButton(){
        
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



LcdMenu::LcdMenu(LcdScreen *screen){
    flag_key = 0;
    q_curr = 0;
    q_end = 0;
    qLcd[q_end] = screen;
};

LcdMenu::LcdMenu(StaticLcdScreen *screen){
    flag_key = 0;
    q_curr = 0;
    q_end = 0;
    qLcd[q_end] = screen;
};

LcdMenu::LcdMenu(DinamicLcdScreen *screen){
    flag_key = 0;
    q_curr = 0;
    q_end = 0;
    qLcd[q_end] = screen;
};

LcdMenu::LcdMenu(EditLcdScreen *screen){
    flag_key = 0;
    q_curr = 0;
    q_end = 0;
    qLcd[q_end] = screen;
};



void LcdMenu::addScreen(LcdScreen *screen){

    qLcd[++q_end] = screen;
};

void LcdMenu::setMenu(uint8_t id){
    if(id > q_end) return;
    q_curr = id;
};

void LcdMenu::nextMenu(){
    setMenu(q_curr+1);
};

void LcdMenu::backMenu(){
    setMenu(q_curr-1);
};

void LcdMenu::show(LiquidCrystal *lcd){
    qLcd[q_curr]->show(lcd);
    flag_key = 0;
};

void LcdMenu::key(){
    if(flag_key) return;
    uint8_t keys = getPressedButton();
    flag_key = 1;
    switch (keys)
    {
    case BUTTON_UP:
        backMenu();
        break;
    case BUTTON_DOWN:
        nextMenu();
        break;
    case BUTTON_RIGHT:
        //backMenu();
        qLcd[q_curr]->add();
        break;
    case BUTTON_LEFT:
        qLcd[q_curr]->sub();
        break;
    case BUTTON_SELECT:
        if(qLcd[q_curr]->ok() == 0) q_curr = MAINSCREEN;
        break;
    default:
        break;
    }
};