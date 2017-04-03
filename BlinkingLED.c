/*
 * main.c
 */
#include "stdint.h"

/* defining addresses for the LEDS */
#define PORTF 0x00000020
#define SYSCTR (*((volatile uint32_t *)0x400FE108))
#define PORTFDIR (*((volatile uint32_t *)0x40025400))
#define DENPORTF (*((volatile uint32_t *)0x4002551c))
#define PORTF_DATA (*((volatile uint32_t *)0x400253FC))

//defining the LEDS PINS
#define LED_RED 0x02
#define LED_BLUE 0x04
#define LED_GREEN 0x08


int main(void) {

    /** LEDS configurations **/
    //enable port F
    SYSCTR = PORTF;
    //direction of port f pins
    PORTFDIR = LED_RED|LED_BLUE|LED_GREEN; // rest of ports are inputs by default
    //    data enable DEN for port F Pins
    DENPORTF = LED_RED|LED_BLUE|LED_GREEN;
    //    send Data on port F
    PORTF_DATA = LED_RED|LED_BLUE|LED_GREEN;

    while(1){//super looop
        DENPORTF = LED_RED|LED_BLUE|LED_GREEN;//turn LEDS to white
        SysCtlDelay(16000000 / 3);//delay 1 sec
        DENPORTF = 0; // turn to black
        SysCtlDelay(16000000 / 3);// delay 1 sec
    }
	
	return 0;
}
