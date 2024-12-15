/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"
#include "../led/led.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include <stdio.h> /*for sprintf*/

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern unsigned char led_value;					/* defined in funct_led								*/

unsigned char ledval = 0xA5;

void TIMER0_IRQHandler (void)
{
	static int clear = 0;
	char time_in_char[5] = "";
	int mosse[6][2]={{1,1},{-1,-1},{1,0},{-1,0},{0,1},{0,-1}};
	int i=0;
	
	if(LPC_TIM0->IR & 1) // MR0
	{ 
		// your code - Refresh touch 
		
		LPC_TIM0->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM0->IR & 2){ // MR1
		// your code	
		
		LPC_TIM0->IR = 2;			// clear interrupt flag 
	}
	else if(LPC_TIM0->IR & 4){ // MR2
		// your code	
		
		LPC_TIM0->IR = 4;			// clear interrupt flag 
	}
	else if(LPC_TIM0->IR & 8){ // MR3
		// your code	
		
		LPC_TIM0->IR = 8;			// clear interrupt flag 
		
	}
  return;
}

/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{

	if(LPC_TIM1->IR & 1) // MR0
	{ 
		// your code 
		
		LPC_TIM1->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM1->IR & 2){ // MR1
		
		LPC_TIM1->IR = 2;			// clear interrupt flag 
	}
	else if(LPC_TIM1->IR & 4){ // MR2
		// your code	
		
		LPC_TIM1->IR = 4;			// clear interrupt flag 
	}
	else if(LPC_TIM1->IR & 8){ // MR3
		// your code	
		
		LPC_TIM1->IR = 8;			// clear interrupt flag 
	} 
	return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void)
{
	if(LPC_TIM0->IR & 1) // MR0
	{ 
		// your code
		
		LPC_TIM2->IR = 1;			/* clear interrupt flag */
	}
	else if(LPC_TIM0->IR & 2){ // MR1
		// your code	
		
		LPC_TIM2->IR = 2;			/* clear interrupt flag */
	}
	else if(LPC_TIM0->IR & 4){ // MR2
		// your code	
		
		LPC_TIM2->IR = 4;			/* clear interrupt flag */		
	}
	else if(LPC_TIM0->IR & 8){ // MR3
		// your code	
		
		LPC_TIM2->IR = 8;			/* clear interrupt flag */
	}
  return;
}


/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler (void)
{
	if(LPC_TIM0->IR & 1) // MR0
	{ 
		// your code
		
		LPC_TIM3->IR = 1;			/* clear interrupt flag */
	}
	else if(LPC_TIM0->IR & 2){ // MR1
		// your code	
		
		LPC_TIM3->IR = 2;			/* clear interrupt flag */
	}
	else if(LPC_TIM0->IR & 4){ // MR2
		// your code	
		
		LPC_TIM3->IR = 4;			/* clear interrupt flag */
	}
	else if(LPC_TIM0->IR & 8){ // MR3
		// your code	
		
		LPC_TIM3->IR = 8;			/* clear interrupt flag */
	}
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
