#ifndef SMAFILTER_H
#define SMAFILTER_H
#include <stdint.h>

#define CHANELES    3   // количество каналов какой выбрать канал chanll_adapt[]
 
// константы фильтра для фиксированного варианта и для инициализации варианта с изменяемой глубиной
#define LEN_FILTER  32  // максимальная глубина фильтра

// буфер каналов
// int16_t filtered_data[CHANELES]; // отфильтрованные данные для передачу в программу
 
// формат данных фильтра скользящее среднее
typedef struct  
{
    uint16_t Filter_Data[LEN_FILTER];    // данные фильтра
    uint64_t sum;                        // текущая сумма
    uint8_t top;                        // указатель на текущую выборку
} __attribute__((packed)) _filter;      // упаковать данные
 
// декларируем масcив данных фильтра как внешний
extern _filter filter[CHANELES];        

uint16_t Filtering(uint16_t input_data, _filter * flt);

uint16_t NoFiltering(_filter *flt);

// example used
// filtered_data[0]=(int16_t)Filtering(ADC1BUF0, &filter[0]);

#endif // SMAFILTER_H