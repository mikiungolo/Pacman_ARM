/***************************************************************************************
**--------------File Info---------------------------------------------------------------
** It includes all Pacman game functions.
**--------------------------------------------------------------------------------------       
***************************************************************************************/

// include libraries 
#include "LPC17xx.h"
#include "pacman.h"



void set_direction(enum movement); 
void move_pacman(void); 
							
// define variables
volatile enum movement direction = left;
volatile uint8_t cordX = 7; 
volatile uint8_t cordY = 14; 
extern volatile uint8_t board[ROWS][COLUMNS]; 

/* define functions */ 
							
/*----------------------------------------------------------------------------
  Function for pacman movement
 *----------------------------------------------------------------------------*/
void move_pacman(void){
	if (cordX < (COLUMNS-1) && cordY < (ROWS-1)
				|| (cordY == TELEPORT_POSY && (cordX == TR_X || cordX == TL_X))) {
		switch(direction) {
			
		case up: 
			if(board[cordY-1][cordX] != W && board[cordY-1][cordX] != E) {
				draw_pacman(cordY, cordX, true); 
				cordY--; 
				draw_pacman(cordY, cordX, false);
			}
			break; 
			
		case right: 
				if(cordX == TR_X && cordY == TELEPORT_POSY) {
					draw_pacman(cordY, cordX, true);
					cordX = TL_X;
				} else if(board[cordY][cordX+1] != W && board[cordY][cordX+1] != E) {
					draw_pacman(cordY, cordX, true);
					cordX++;
				}
				draw_pacman(cordY, cordX, false);
			break; 
		
		case down: 
			if(board[cordY+1][cordX] != W && board[cordY+1][cordX] != E) {
				draw_pacman(cordY, cordX, true);
				cordY++; 
				draw_pacman(cordY, cordX, false);
			}
			break; 
		
		case left: 
			if(cordX == TL_X && cordY == TELEPORT_POSY) {
				draw_pacman(cordY, cordX, true);
				cordX = TR_X;
			}
			else if(board[cordY][cordX-1] != W && board[cordY][cordX-1] != E) {
					draw_pacman(cordY, cordX, true);
					cordX--; 
			}
			draw_pacman(cordY, cordX, false);
			break; 
		
		default: 
			break; 
		}
	}
}

void set_direction(enum movement d){
	direction = d; 
}