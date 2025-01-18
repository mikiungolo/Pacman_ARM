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
#include "../GLCD/GLCD.h" 
#include "Pacman/pacman.h"

extern volatile int time; 
extern volatile int random_time[R_TIME];
extern volatile bool InPause; 
extern volatile int blinky_coeff; 

volatile int time_move; 
volatile int cont_speed = TIME_MORE_FAST; 
int i = 0; 

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


void TIMER0_IRQHandler (void)
{
	if(LPC_TIM0->IR & 1) // MR0
	{ 
		// your code - movement
		if(!InPause){
			move_pacman();
			
			// blink move in according with his speed 
			if(time_move == 0){
				move_blinky(); 
				time_move = blinky_coeff; 
			}
			else 
				time_move--; 
		}
			
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
		// check time and game over
		time--; 
		show_time(); 
		if(time == 0) 
			showGameMode("GAME OVER");  
		
		// generate Power pills.
		if (time == random_time[i]){
			i++; 
			sub_Ppill(); 
		}
		
		// increase blinky speed 
		cont_speed--; 
		if (cont_speed == 0) {
			if (blinky_coeff != 0)
				blinky_coeff--; 
			cont_speed = TIME_MORE_FAST;
		}
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
		change_strategy(); 
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
