#include "ProcessIU.h"

                 // Для напряжения: 
float KUp = 1.0;//                 0.5
float KUi = 0.2;//                 1.1
float KUd = 0.2;//                 0.2

                 // Для тока: 
float KIp = 0.5;//                 0.5
float KIi = 0.1;//                 1.1
float KId = 0.2;//                 0.2

char processIU(uint16_t voltage_limit, uint16_t curent_limit, uint16_t &out_, uint16_t voltage, uint16_t curent){

    static int16_t preErrI = 0;
    static int16_t preErrU = 0;
    static int64_t intgI = 0;
    static int64_t intgU = 0;
    char mode = '0';

    if((voltage > voltage_limit)){
      // On U regulator Off I
      mode = 'U';
      int16_t errInputU = voltage_limit - voltage;
      
      if(out_ > 1 && out_ < 4096) 
        intgU += errInputU;
      
      int16_t diffU = errInputU - preErrU;

      float outfloatU = KUp * errInputU + KUi * intgU + KUd * diffU;
      out_ = (uint16_t)outfloatU;

      if (outfloatU >= 4096) {
        out_ = 4096;
      } 
      if (outfloatU <= 0) out_ = 1;

      preErrU = errInputU;
      
    } else {
      // On I
      mode = 'I';
      int16_t errInputI = curent_limit - curent;
      
      if(out_ > 1 && out_ < 4096) 
        intgI += errInputI;
      
      int16_t diffI = errInputI - preErrI;

      float outfloatI = KIp * errInputI + KIi * intgI + KId * diffI;
      out_ = (uint16_t)outfloatI;

      if (outfloatI >= 4096) {
        out_ = 4096;
      } 
      if (outfloatI <= 0) out_ = 1;

      preErrI = errInputI;
        
    }

    return mode;
}


char processUI(uint16_t voltage_limit, uint16_t curent_limit, uint16_t &out_, uint16_t voltage, uint16_t curent){

    static int16_t preErr = 0;
    static int64_t intg = 0;

    if (curent < curent_limit){
        
        int16_t errInput = voltage_limit - voltage;

        //ограничить максим и миним размер ошибки
        // if (errInput > errInputMax) errInput = errInputMax;
        // // errInput = errInput < errInputMax?errInput:errInputMax;
        // 
        // if (errInput > errInputMax) errInput = errInputMax
        // // errInput = errInput > errInputMin?errInput:errInputMin;

        if(out_ > 1 && out_ < 4096)
        intg += errInput;
        
        int16_t diff = errInput - preErr;
        
        float outfloat = KUp * errInput + KUi * intg + KUd * diff;

        out_ = (uint16_t)outfloat;
        if (outfloat >= 4096) out_ = 4096;
        if (outfloat <= 0) out_ = 1;

        preErr = errInput;

        return 'U';
    }
    out_ = 0;
    return 'K';
}

char processRI(uint16_t voltage_limit, uint16_t curent_limit, uint16_t &out_, uint16_t voltage, uint16_t curent){
  static int16_t preErrI = 0;
  static int16_t preErrU = 0;
  static int64_t intgI = 0;
  static int64_t intgU = 0;
  char mode = '0';

  mode = 'I';
      int16_t errInputI = curent_limit - curent;
      
      if(out_ > 1 && out_ < 4096) 
        intgI += errInputI;
      
      int16_t diffI = errInputI - preErrI;

      float outfloatI = KIp * errInputI + KIi * intgI + KId * diffI;
      out_ = (uint16_t)outfloatI;

      if (outfloatI >= 4096) {
        out_ = 4096;
      } 
      if (outfloatI <= 0) out_ = 1;

      preErrI = errInputI;

}

/*/  старый рабочий
////////................///////
//Регулятор напряжения//  

  TimerNew = millis()%1000/50;
  if(TimerPrev != TimerNew){
    TimerPrev = TimerNew;

    static int16_t preErr = 0;
    static int64_t intg = 0;

    if (setPoint != preSetPoint){
        intg = 0;
        preErr = 0;
        preSetPoint = setPoint;
    } 
    int16_t errInput = setPoint - input_;

    //ограничить максим и миним размер ошибки
    // if (errInput > errInputMax) errInput = errInputMax;
    // // errInput = errInput < errInputMax?errInput:errInputMax;
    // 
    // if (errInput > errInputMax) errInput = errInputMax
    // // errInput = errInput > errInputMin?errInput:errInputMin;

    if(out > 1 && out < 4096) 
      intg += errInput;
    
    int16_t diff = errInput - preErr;
    //int16_t diff = errInput - intg;
  
    float outfloat = KUp * errInput + KUi * intg + KUd * diff;

    out = (uint16_t)outfloat;
    if (outfloat >= 4096) out = 4096;
    if (outfloat <= 0) out = 1;

    preErr = errInput;
    lastInput = input_;
 

  }
   
////////..............///////
//старый рабочий */