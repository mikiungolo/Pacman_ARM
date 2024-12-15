/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "../led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;


void RIT_IRQHandler (void)
{			
	/* Static as its value persists between calls to the function. It is not reinitialized each time the function is executed.*/
	static uint8_t position=0;
	static int J_up=0; 
	static int J_down=0; 
	static int J_left=0; 
	static int J_right=0; 
	
	/*************************JOYSTICK UP***************************/

	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick UP pressed */
		J_up++;
		switch(J_up){
			case 1:
				// code J_up
				LED_On(0); 
				break;
			// code J_up when pressure is long 
			case 60:	//3sec = 3000ms/50ms = 60
				
				break;
			default:
				break;
		}
	}
	else{
			J_up=0;
	}

	/*************************JOYSTICK DOWN***************************/

	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		/* Joytick DOWN pressed */
		J_down++;
		switch(J_down){
			case 1:
				// code J_down
				LED_On(1); 
				break;
			// code J_down when pressure is long 
			case 60:	//3sec = 3000ms/50ms = 60
				
				break;
			default:				
				break;
		}
	}
	else{
			J_down=0;
	}
	
		/*************************JOYSTICK LEFT***************************/

	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
		/* Joytick DOWN pressed */
		J_left++;
		switch(J_left){
			case 1:
				// code J_left
				LED_On(2); 
				break;
			// code J_left when pressure is long 
			case 60:	//3sec = 3000ms/50ms = 60
				
				break;
			default:		
				break;
		}
	}
	else{
			J_left=0;
	}
	
		/*************************JOYSTICK RIGHT***************************/

	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
		/* Joytick right pressed */
		J_right++;
		switch(J_right){
			case 1:
				// code J_right
				LED_On(3); 
				break;
			// code J_right when pressure is long 
			case 60:	//3sec = 3000ms/50ms = 60
				
				break;
			default:
				break;
		}
	}
	else{
			J_right=0;
	}
	
	/*************************BUTT INT0***************************/
	if(down_0 !=0){
		down_0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
			switch(down_0){
				case 2:					// lasciare 2 ai bottoni: serve a non elaborare più volte il segnale. 
					// code button 0 here 
				
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down_0=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	} // end INT0

	/*************************BUTT KEY1***************************/
	if(down_1 !=0){
		down_1++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
			switch(down_1){
				case 2:
					// code button 1 here 
				
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down_1=0;			
			NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	} // end KEY1

	/*************************BUTT KEY2***************************/
	if(down_2 !=0){
		down_2++;
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
			switch(down_2){
				case 2:
					// code button 2 here 
					
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down_2=0;		
			NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
	} // end KEY2
		
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
