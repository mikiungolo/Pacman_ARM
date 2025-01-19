/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** Prototypes of functions defined in board.c, ...
** It includes all functions for pacman game. 
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

/* include libraries */ 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "GLCD/GLCD.h" 

/* define constants e new type */ 
#define SIM_TO_REAL 0.04
#define ROWS 30
#define COLUMNS 26
#define N_PILLS 240 
#define TELEPORT_POSY 14
#define TR_X 25
#define TL_X 0
#define R_TIME 6 
#define TIME_MORE_FAST 15 

// enum movement 
enum movement{up, 
							right, 
							down, 
							left};

/* define enum for kind of cells in board */
enum kind_cell{S,			// standard pill
							 P,			// power pill
							 W,			// wall
							 F,			// free cell
							 E,			// edge of board 
							 TL,		// teleport left		
							 TR,		// teleport right 
							 PA};	  // pacman  	

// Position
typedef struct {
    int x, y;  // Coordinate della cella
} Position;

enum game_strategy{Chase,
									 Frightened}; 
/*----------------------------------------------------------------------------
  Function that draws Pacman board
 *----------------------------------------------------------------------------*/
void draw_board(void); 
							 
/*----------------------------------------------------------------------------
  Function that set Pacman direction
 *----------------------------------------------------------------------------*/					 
void set_direction(enum movement); 
							 
/*----------------------------------------------------------------------------
  Function that move Pacman 
 *----------------------------------------------------------------------------*/							 
void move_pacman(void); 
							 
/*----------------------------------------------------------------------------
  Function that draws pill
 *----------------------------------------------------------------------------*/							 
void draw_pill(int, int, int, bool); 

/*----------------------------------------------------------------------------
  Function that draws Pacman 
 *----------------------------------------------------------------------------*/
void draw_pacman(int, int, bool); 

/*----------------------------------------------------------------------------
  Function that draws Blinky Red
----------------------------------------------------------------------------*/
void draw_blinky(int y, int x, bool clean, enum game_strategy s); 

/*----------------------------------------------------------------------------
  Function that shows countdown timer 
 *----------------------------------------------------------------------------*/
void show_time(void); 

/*----------------------------------------------------------------------------
  Function that shows overall score. 
 *----------------------------------------------------------------------------*/
void show_score(void); 

/*----------------------------------------------------------------------------
Function that shows string game mode on Display: pause, game over, victory... 
 *----------------------------------------------------------------------------*/
 void showGameMode(char* s); 
 
/*----------------------------------------------------------------------------
  Function that resume game. 
 *----------------------------------------------------------------------------*/
void resume(void);

/*----------------------------------------------------------------------------
  Function that calculate positioning of Power Pills. 
 *----------------------------------------------------------------------------*/
void random_Ppills(void);

/*----------------------------------------------------------------------------
  Function that substitute Standard Pills with Power Pills. 
 *----------------------------------------------------------------------------*/
void sub_Ppill(void); 

/*----------------------------------------------------------------------------
  Function that move Blinky with an AI controlled  
 *----------------------------------------------------------------------------*/	
void move_blinky(void); 

/*----------------------------------------------------------------------------
  Function that change strategy
 *----------------------------------------------------------------------------*/
void change_strategy(void); 

/*----------------------------------------------------------------------------
  Function that check contact between Pacman and Blinky 
 *----------------------------------------------------------------------------*/
void check_contact(void); 

/*----------------------------------------------------------------------------
  Function that restore Blinky after dead 
 *----------------------------------------------------------------------------*/
void restore_blinky(void); 