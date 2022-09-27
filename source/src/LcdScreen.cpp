#include "LcdScreen.h"

void LcdScreen::addItem0(const __FlashStringHelper *it){
    item0 = it;
};

void LcdScreen::addItem1(const __FlashStringHelper *it){
    item1 = it;
};

void StaticLcdScreen::show(LiquidCrystal *lcd){

    lcd->setCursor(0,0);
    lcd->print(item0);
    lcd->setCursor(0,1);
    lcd->print(item1);
    
};

void DinamicLcdScreen::addData0(uint16_t *d1, uint16_t *d2){
    d0_1 = d1;
    d0_2 = d2;
};


void DinamicLcdScreen::addData1(uint16_t *d1, uint16_t *d2){
    d1_1 = d1;
    d1_2 = d2;
};

void DinamicLcdScreen::addData(DataReal *data1, DataReal *data2){
    this->data1 = data1;
    this->data2 = data2;
};



void DinamicLcdScreen::show(LiquidCrystal *lcd){

    lcd->setCursor(0,0);
    lcd->printf(item0);
    lcd->setCursor(0,1);
    lcd->printf(item1,data1->getData()/100,data1->getData()%100,data2->getData()/100,data2->getData()%100);

};



void EditLcdScreen::addData0(uint16_t *d1){
    d0_1 = d1;
    d0_2 = d1;
};

void EditLcdScreen::addData1(uint16_t *d1){
    d1_1 = d1;
    d1_2 = d1;
};

void EditLcdScreen::addData(DataEdit *data){
    this->data1 = data;
};


void EditLcdScreen::add(){
    //(*d1_1)++;
    ((class DataEdit *)(this->data1))->nextStep();
};

void EditLcdScreen::sub(){
    //(*d1_1)--;
    ((class DataEdit *)(this->data1))->preStep();
};

uint8_t EditLcdScreen::ok(){
   //if( ((class DataEdit *)(this->data1))->getData() == ((class DataEdit *)(this->data1))->getEdit()) return 0;
    //*d0_1 = *d1_1;

    return ((class DataEdit *)(this->data1))->store();
    //return 1;
};
void EditLcdScreen::show(LiquidCrystal *lcd){

    lcd->setCursor(0,0);
    uint16_t param = ((class DataEdit *)(this->data1))->getData();
    if(param)
        lcd->printf(item0,param/100,param%100);
    else lcd->printf(item0,0,0);
    lcd->setCursor(0,1);
    param = ((class DataEdit *)(this->data1))->getEdit();
    if(param)
        lcd->printf(item1,param/100,param%100);
    else lcd->printf(item1,0,0);

};

void ModeLcdScreen::addData(DataEdit *data){
    this->data = data;
    this->mode = new const char*[data->getMax() + 1];
};

void ModeLcdScreen::addMode(const char* mode){
    if(mode == NULL) return;
    this->mode[((DataEdit *)(this->data))->getEdit()] = mode;
    ((DataEdit *)(this->data))->nextStep();
};

void ModeLcdScreen::show(LiquidCrystal *lcd){
    lcd->setCursor(0,0);
    if(mode[((DataEdit *)(this->data))->getData()])
        lcd->printf(item0,this->mode[((DataEdit *)(this->data))->getData()]);
    lcd->setCursor(0,1);
    if(mode[((DataEdit *)(this->data))->getEdit()])
        lcd->printf(item1,this->mode[((DataEdit *)(this->data))->getEdit()]);

};

void ModeLcdScreen::add(){
    ((class DataEdit *)(this->data))->nextStep();
};

void ModeLcdScreen::sub(){
    ((class DataEdit *)(this->data))->preStep();
};

uint8_t ModeLcdScreen::ok(){
   ((class DataEdit *)(this->data))->store();
   return 0;
};