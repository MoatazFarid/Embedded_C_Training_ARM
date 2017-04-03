/*
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

/* function defination */
void init(void);

/*main function Declaration */
int main(void) {

	uint8_t ui8Val=2; // the data value we will use as input to pin 1 LED
    // start the initialization of the PortF and pins we will use
	init();

    for(;;){
        // start reading from pin 0 to check if it was pressed
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0)==GPIO_PIN_0){// if the button is not clicked

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);// turn OFF the led
        }
        else{// the button is clicked
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ui8Val);// turn ON the led
        }
    }
	return 0;
}

/* initailization function */
void init(void){
    // enable the clock on port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //since pin 0 is locked by default therefore we need to unlock it first
    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= 0x01;
    //setting pin 0 as input
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0);

    //setting pin1 ,2,3 as outputs
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1); //we will use only this led in SW example
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_3);

}
