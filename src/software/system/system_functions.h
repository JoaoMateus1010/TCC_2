#ifndef SYS_FUNC
#define SYS_FUNC

    #define DEBUG_FLAG 1

    #include <LPC11xx.h>    

    #include "../lib/adc.h"
    #include "../lib/gpio.h"
    #include "../lib/pwm.h"
    #include "../lib/timer.h"
    #include "math.h"
    #if DEBUG_FLAG
        #include "../lib/uart.h"
    #endif

    #define PIN_LED_STATUS_SYSTEM       (5)//0_5

    #define PIN_MOTOR_0_CONTROL_ENABLE  (1)//0_1
    #define PIN_MOTOR_1_CONTROL_ENABLE  (2)//0_2
    #define PIN_MOTOR_0_CONTROL         (3)//0_3
    #define PIN_MOTOR_1_CONTROL         (4)//0_4
    #define PIN_PWM_MOTOR_NORTH_SOUTH               (PWM_MR1)
    #define PIN_PWM_MOTOR_EAST_WEST                 (PWM_MR0)
    #define PIN_MOTOR_0_1_SANS                      (AD4)

    #define PIN_LDR_NORTH       (AD0)
    #define PIN_LDR_SOUTH       (AD1)
    #define PIN_LDR_EAST        (AD2)
    #define PIN_LDR_WEST        (AD3)

    #define PI (3.14159265359)

    #define RADIANOS_TO_GRAUS(RAD)      ((180*RAD)/(PI))
    #define GRAUS_TO_RADIANOS(GRA)      ((PI*GRA)/(180))

    #define Kp  (0.05)
    #define Ki  (0.098)
    #define Kd  (0.0525)

    void init_system();

    float tracking_sun_position(float value_lux_sensor_A,float value_lux_sensor_B); // Recebe os valores de leitura dos sensores Leste e Oeste e retorna o ângulo entre 0~2pi, sendo 0 onde o sol nasce e 180 onde se põe.    
    float get_radianos_motor(int PIN_MOTOR);
    float control_motor(int PIN_MOTOR,float set_point);
#endif