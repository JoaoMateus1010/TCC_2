#ifndef SYS_ACT
#define SYS_ACT

#define DEBUG_FLAG 1

    #include "system_functions.h"    

    /*
        Como padrão irei usar medidas de ângulos em radianos
    */        

    #define RAD_TO_MS(RAD)  (((1/(PI))*(RAD))+1)
    #define MS_TO_RAD(MS)   (PI*(MS-1))
    
    #define IMMEDIATE_VALUE     (0)
    #define MATH_VALUE          (1)

    float set_motor_inc(int PIN_MOTOR, float INC_RAD_MOTOR,int TYPE_VALUE);//Motor norte-sul ou leste-oeste | inclinação do motor em radianos | retorna inclinação antiga
#endif