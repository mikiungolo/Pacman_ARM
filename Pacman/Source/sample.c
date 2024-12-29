/*----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/

                  
#include <stdio.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "adc/adc.h"
#include "GLCD/GLCD.h" 
#include "Pacman/pacman.h"

/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in lib_led								*/
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  BUTTON_init();												/* BUTTON Initialization              */
	joystick_init(); 
	ADC_init();
	init_RIT(0x16E360);										/* RIT Initialization 15 msec        */
	enable_RIT();
	LCD_Initialization(); 
	
	LPC_SC -> PCONP |= (1 << 22);  // TURN ON TIMER 2
	LPC_SC -> PCONP |= (1 << 23);  // TURN ON TIMER 3	
	
	// your code here 
	init_timer(0, 0, 0, 3, 0x571B0);		// timer for pacman movement. 30ms B71B0 25ms 98968; 15ms 0x571B0
	init_timer(1, 0, 0, 3, 0x17D7840); 	// game countdown, 1 sec
	
	/* start game in pause mode */ 
	pause(); 
	
	/* calculate random time to generate Power pills */ 
	random_Ppills(); 
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}
