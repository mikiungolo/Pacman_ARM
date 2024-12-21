/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** Prototypes of functions defined in board.c, ...
** It includes all functions for pacman game. 
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include <stdbool.h>

#define ROWS 30
#define COLUMNS 26
#define TELEPORT_POSY 14
#define TR_X 25
#define TL_X 0

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
