/* Main.c file generated by New Project wizard
 *
 * Created:   qua dez 9 2020
 * Processor: LPC1114FN28/102
 * Compiler:  GCC for ARM
 */

#include <LPC11xx.h>

#define DEBUG_FLAG 1

#include "lib/adc.h"
#include "lib/gpio.h"
#include "lib/pwm.h"
#include "lib/timer.h"

#if DEBUG_FLAG
#include "lib/uart.h"
#endif


int main(void) {      //Toggle a GPIO (FBD48 pin 23, PIO0_7, controls the LED on the LPC Expresso PCB)
 
     LPC_SYSCON->SYSAHBCLKCTRL   |= (1<<6);     //enable clock GPIO (sec 3.5.14)
     LPC_IOCON->PIO0_7           &= ~(0x10);    //NOT REQUIRED, turn off pull up (sec 7.4.19)
     LPC_GPIO0->DIR              |= (1<<7);     //set pin direction to output (sec 12.3.2)
     
     unsigned int i = 0;
 
     while(1){                      //infinite loop
 
          LPC_GPIO0->DATA           |= (1<<7);    //set pin high (sec 12.3.1)
          for(i=0; i<0xEEEEE; ++i);               //arbitrary delay
          LPC_GPIO0->DATA           &= ~(1<<7);   //set pin low (sec 12.3.1)
          for(i=0; i<0x55555; ++i);               //arbitrary delay
 
     }
      return 0 ;
}
