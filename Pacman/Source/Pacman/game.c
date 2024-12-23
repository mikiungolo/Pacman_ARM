/***************************************************************************************
**--------------File Info---------------------------------------------------------------
** It includes all Pacman game functions.
**--------------------------------------------------------------------------------------       
***************************************************************************************/

// include libraries 
#include "LPC17xx.h"
#include "pacman.h"


// define constants to game
#define SCORE_S_PILLS 10
#define SCORE_P_PILLS 50
#define N_PILLS 240 

void set_direction(enum movement); 
void move_pacman(void); 
void set_direction(enum movement d); 
void set_point(void); 
void game(void); 
void disableAll(void); 
							
// define variables
volatile enum movement direction = left;
volatile uint8_t cordX = 7; 
volatile uint8_t cordY = 14; 
volatile uint8_t time = 60; 
volatile int score = 0; 
volatile uint8_t n_pills = N_PILLS; 
volatile bool InPause = true; 
extern volatile uint8_t board[ROWS][COLUMNS]; 

/* define functions */ 
void move_pacman(void); 
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
	set_point(); 
}

void set_direction(enum movement d){
	direction = d; 
}

void set_point(void) {
	switch(board[cordY][cordX]){
		case S: 
			score += SCORE_S_PILLS; 
			board[cordY][cordX] = F;  
			n_pills--; 
			break; 
		case P: 
			score += SCORE_P_PILLS; 
			board[cordY][cordX] = F;
			n_pills--; 		
			break; 
		default: 
			break; 
	}
	if(n_pills == 0) 
		show_win(); 
	else 
		show_score(); 
}

void disableAll(void){
	reset_RIT(); 
	disable_timer(0); 
	disable_timer(1); 
}

void enableAll(void){
	reset_RIT(); 
	enable_timer(0); 
	enable_timer(1); 
}

void pause(void){
	LCD_Clear(Black); 
	GUI_Text(105, 150, (uint8_t*)"PAUSE", White, Black); 
	disableAll(); 
}

void resume(void){
	draw_board(); 
	enableAll(); 
}

void game_over(){
	LCD_Clear(Black); 
	GUI_Text(105, 150, (uint8_t*)"GAME OVER!", White, Black); 
	disableAll(); 
}