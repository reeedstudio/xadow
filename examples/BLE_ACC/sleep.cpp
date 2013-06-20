#include <Sleep_n0m1.h>
#include "sleep.h"

Sleep sleep;


void pwrDown(unsigned long tSleep)
{
#if defined(__AVR_ATmega32U4__)
    power_adc_disable();
    power_usart0_disable();
    power_spi_disable();
    power_twi_disable();
    power_timer1_disable();
    power_timer2_disable();
    power_timer3_disable();
    power_usart1_disable();
    power_usb_disable();
#endif
    sleep.pwrDownMode();        //set sleep mode
    sleep.sleepDelay(tSleep);   //sleep for: sleepTime
}

void wakeUp()
{
#if defined(__AVR_ATmega32U4__)
    power_adc_enable();
    power_usart0_enable();
    power_spi_enable();
    power_twi_enable();
    power_timer1_enable();
    power_timer2_enable();
    power_timer3_enable();
    power_usart1_enable();
    power_usb_enable();
#endif
}
