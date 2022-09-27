#ifndef PROCESSIU_H
#define PROCESSIU_H

#include <stdint.h>

                 // Для напряжения: 
extern float KUp;//                 0.5
extern float KUi;//                 1.1
extern float KUd;//                 0.2

                 // Для тока: 
extern float KIp;//                 0.5
extern float KIi;//                 1.1
extern float KId;//                 0.2

///Регулятор тока с ограничением по напряжению
char processIU(uint16_t voltage_limit, uint16_t curent_limit, uint16_t &out_, uint16_t voltage, uint16_t curent);

///Регулятор напряжения с защитой по току  
char processUI(uint16_t voltage_limit, uint16_t curent_limit, uint16_t &out_, uint16_t voltage, uint16_t curent);
///Регулятор тока разряда на резистор
char processRI(uint16_t voltage_limit, uint16_t curent_limit, uint16_t &out_, uint16_t voltage, uint16_t curent);

#endif // PROCESSIU_H