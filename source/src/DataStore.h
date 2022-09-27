#ifndef DataStore_h
#define DataStore_h

#include <inttypes.h>

class DataReal{
protected:
    uint16_t data;

public:
    DataReal(){
        this->data = 0;
    };
    DataReal(uint16_t data){
        this->data = data;
    };

    inline void setData(uint16_t data){
        this->data = data;
    };

    inline uint16_t getData(){
        return this->data;
    };

};

class DataEdit: public DataReal{
private:
    uint16_t edit;
    uint8_t ring;
protected:
    uint16_t min;
    uint16_t max;
    uint16_t step;
public:
    DataEdit(uint16_t data, uint16_t min, uint16_t max, uint16_t step, uint8_t ring = 0):DataReal(data){
        this->min = min;
        this->max = max;
        this->step = step;
        this->edit = data;
        this->ring = ring;
    };
    inline uint16_t getEdit(){
        return this->edit;
    };
    inline uint16_t nextStep(){
        if((this->max - this->edit) >= this->step)
            this->edit = this->edit + step;
        else if(ring) this->edit = this->min;
        return this->edit;
    };
    inline uint16_t preStep(){
        if((this->edit - this->min) >= this->step)
            this->edit = this->edit - step;
        else if(ring) this->edit = this->max;
        return this->edit;
    };
    inline uint8_t store(){
        if (this->edit == this->data) return 0;
        this->data = this->edit;
        return 1;
    };
    inline uint8_t check(){
        return (this->edit == this->data)?0:1;
    };
    inline uint16_t getMax(){
        return this->max;
    };

};

#endif