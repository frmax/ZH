#include "sma_filter.h"


_filter filter[CHANELES]; //инициализация внешней переменной

uint16_t Filtering(uint16_t input_data, _filter * flt)
{
 
    flt->sum -= flt->Filter_Data[(uint8_t)flt->top];        // отнять от суммы значение на которое указывает top
    flt->Filter_Data[(uint16_t)flt->top] = input_data;       // запомнить значение по top
    if(++flt->top > LEN_FILTER-1) flt->top = 0;             // увеличить указатель top, если он больше длины фильтра установить в начало
    //return (uint16_t)((flt->sum += input_data)/LEN_FILTER);  // к сумме прибавить новое значение и вернуть среднее значение
    return (uint16_t)((flt->sum += input_data)>>5); // при глубине фильтра 32 
}

uint16_t NoFiltering(_filter *flt){

    return (uint16_t)(flt->sum>>5); 
}