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
#define Y_LIFE 30

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
volatile int time = 60; 
volatile int score = 0; 
volatile uint8_t n_pills = N_PILLS; 
volatile bool InPause = true; 
volatile int random_time[R_TIME]; 
volatile int nLife = 0; 
volatile int xLife = 25; 

extern volatile uint8_t board[ROWS][COLUMNS]; 
extern volatile uint8_t coordinates_pill[2][N_PILLS]; 

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
	// check
	if(n_pills == 0) 
		show_win(); 
	else 
		show_score(); 
	// new life 
	if (score - (nLife*1000) >= 1000) {
		nLife++;
		// show new pacman life 
		draw_pacman(Y_LIFE, xLife, false); 
		xLife--; 
	}
}

void enableAll(void){
	enable_timer(0); 
	enable_timer(1); 
	reset_RIT(); 
}

void pause(void){
	LCD_Clear(Black);
	GUI_Text(100, 150, (uint8_t*)"PAUSE", White, Black); 
	//disableAll(); 	
	reset_RIT(); 
}

void disableAll(void){
	reset_RIT(); 
	disable_timer(0); 
	disable_timer(1); 
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

/* Calculate random time */
void random_Ppills(void) {
	srand(ADC_start_conversion());

	int i, j, n;
	for (i = 0; i < R_TIME; i++) {
		n = rand() % 59 + 1;

		for (j = i; j > 0 && random_time[j - 1] < n; j--) {
			random_time[j] = random_time[j - 1];
		}
		random_time[j] = n;
	}
}

// Substitute standard with power pills 
void sub_Ppill(void) {
	int r, x, y; 
	bool valid = false; 
		
	do {
		r = rand() % 240; 
		y = coordinates_pill[0][r]; 
		x = coordinates_pill[1][r]; 
		if (board[y][x] == S)
			valid = true; 
	} while(!valid); 
	board[y][x] = P; 
	draw_pill(S, y, x, true); 	
	draw_pill(P, y, x, false); 
}