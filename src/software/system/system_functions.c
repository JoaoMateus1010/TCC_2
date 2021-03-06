#include "system_functions.h"
#include "system_sensors.h"
#include "system_actuators.h"

void init_system(){
    init_GPIO();
    init_TIMER_0();
    #if DEBUG_FLAG
        init_UART();
    #endif
    init_PWM();
    init_ADC();
    
    set_DIR(PIN_DAY_STATUS,OUTPUT);
    set_DIR(PIN_ACTUATOR_L_W_STATUS,OUTPUT);
    set_DIR(PIN_ACTUATOR_N_S_STATUS,OUTPUT);
    set_DIR(PIN_LED_STATUS_SYSTEM,OUTPUT);

    write_digital_gpio(PIN_DAY_STATUS,LOW);
    write_digital_gpio(PIN_ACTUATOR_L_W_STATUS,LOW);
    write_digital_gpio(PIN_ACTUATOR_N_S_STATUS,LOW);
    write_digital_gpio(PIN_LED_STATUS_SYSTEM,LOW);

    start_ADC(PIN_LDR_NORTH);
    start_ADC(PIN_LDR_SOUTH);
    start_ADC(PIN_LDR_EAST);
    start_ADC(PIN_LDR_WEST);  

    write_digital_gpio(PIN_LED_STATUS_SYSTEM,HIGH);

}

float tracking_sun_position(float value_lux_sensor_A,float value_lux_sensor_B){
    if(value_lux_sensor_A>value_lux_sensor_B){
        return (((PI*value_lux_sensor_A)/(2*(GET_LUX_MAX)))>(PI/2))?(PI/2):((PI*value_lux_sensor_A)/(2*(GET_LUX_MAX)));
    }else if(value_lux_sensor_B>value_lux_sensor_A){
        return (((-PI*value_lux_sensor_B)/(2*(GET_LUX_MAX))+PI)>(PI))?(PI):((-PI*value_lux_sensor_B)/(2*(GET_LUX_MAX))+PI);
    }
    return PI/2;
}
float get_radianos_motor(int PIN_MOTOR){
    float rad = 0.0;
    rad = get_duty_cycle(PIN_MOTOR);
    rad = MS_TO_RAD(rad);    
    return rad;
}
float control_motor(int PIN_MOTOR,float set_point){    
    float point = MS_TO_RAD(get_duty_cycle(PIN_MOTOR));
    float erro_faixa = GRAUS_TO_RADIANOS(1.5);
    float erro = 0;
    float Up = 0;
    float Ui = 0;
    float Ud = 0;
    float U  = 0;        
    for(float i=0;!((point>=set_point-erro_faixa)&&(point<=set_point+erro_faixa));i=i+(PI/300)){
        erro = set_point-point;
        Up = Kp*erro;
        Ui = Ki*erro*i;        
        Ud = Kd*erro/i;
        U = Up+Ui+Ud;        
        /*Atuação na planta*/

        set_motor_inc(PIN_MOTOR,U,MATH_VALUE);
        delay_MS(10);
        /*-------*/
        point = MS_TO_RAD(get_duty_cycle(PIN_MOTOR));
    }
    return U;
}
float get_azimuth_by_angle(float inc_N_S,float inc_E_W){        

    if((inc_N_S==inc_E_W)&&(inc_E_W==(PI/2))){
        return 0;
    }

    if(inc_E_W<(PI/2)){
        if(inc_N_S<(PI/2)){
            //printf("A");
            return (PI/2)-inc_E_W;
        }else{
            //printf("B");
            return (PI/2)+inc_E_W;
        }
    }else{        
        if(inc_N_S<(PI/2)){
            //printf("C");
            return (PI)-inc_E_W+(3*PI/2);
        }else{
            //printf("D");
            return (PI/2)+inc_E_W;
        }
    }
}
float get_altitude_by_angle(float inc_N_S){
    if(inc_N_S<(PI/2)){
        return inc_N_S;
    }else{
        return (PI)-inc_N_S;
    }
}

float get_inc_N_S_by_Azimuth_Altitude(float azimuth, float altitude){
    if((azimuth>(PI/2))&&(azimuth<(3*PI/2))){
        return (PI/2)-altitude+(PI/2);
    }else{
        return altitude;
    }
}
float get_inc_E_W_by_Azimuth_Altitude(float azimuth, float altitude){    
    
    if((azimuth>=0)&&(azimuth<=(PI/2))){
        return (PI/2)-azimuth;
    }
    if((azimuth>(PI/2))&&(azimuth<=(PI))){
        return azimuth - (PI/2) ;
    }
    if((azimuth>(PI))&&(azimuth<=(3*PI/2))){
        return azimuth-(PI)+(PI/2);
    }
    if((azimuth>(3*PI/2))&&(azimuth<=(2*PI))){
        return (2*PI)-azimuth+(PI/2);
    }  
    return 0;      
}