/***************************************************************************************
**--------------File Info---------------------------------------------------------------
** It includes all functions for pacman board creation. 
**--------------------------------------------------------------------------------------       
***************************************************************************************/

/* include libraries */ 
//#include <stdio.h>
#include "LPC17xx.h"
#include "pacman.h"
#include "GLCD/GLCD.h" 

/* define constants */ 
#define ROWS 30
#define COLUMNS 26
#define PIXEL_CELL 9
#define SP_r 3 				// radius standard pill
#define PP_r 5 				// radius power pill
#define PACMAN_r 7 		// "radius" Pacman

/* define enum for kind of cells in board */
enum kind_cell{S,			// standard pill
							 P,			// power pill
							 W,			// wall
							 F,			// free cell
							 E,			// edge of board 
							 TL,		// teleport left		
							 TR};	  // teleport right  	

/* fnuctions declaration */ 
void draw_board(void); 
void draw_edge(int, int); 
void draw_wall(int, int); 
void draw_pill(int, int, int); 


/* define global variables */ 	

/* map to display in board matrix */							 
volatile uint8_t board[ROWS][COLUMNS] = {
	E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E,
	E, S, S, S, S, S, S, S, S, S, S, S, E, E, S, S, S, S, S, S, S, S, S, S, S, E,
  E, S, W, W, W, W, S, W, W, W, W, S, E, E, S, W, W, W, W, S, W, W, W, W, S, E, 
	E, S, W, W, W, W, S, W, W, W, W, S, E, E, S, W, W, W, W, S, W, W, W, W, S, E, 
	E, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, E,
	E, S, W, W, W, W, S, W, W, S, W, W, W, W, W, W, S, W, W, S, W, W, W, W, S, E, 
	E, S, W, W, W, W, S, W, W, S, W, W, W, W, W, W, S, W, W, S, W, W, W, W, S, E, 
	E, S, S, S, S, S, S, W, W, S, S, S, W, W, S, S, S, W, W, S, S, S, S, S, S, E,
	E, E, E, E, E, E, S, W, W, W, W, S, W, W, S, W, W, W, W, S, E, E, E, E, E, E,
	F, F, F, F, F, E, S, W, W, W, W, S, W, W, S, W, W, W, W, S, E, F, F, F, F, F,
	F, F, F, F, F, E, S, W, W, W, W, S, W, W, S, W, W, W, W, S, E, F, F, F, F, F, 
	F, F, F, F, F, E, S, W, W, S, S, F, F, F, F, S, S, W, W, S, E, F, F, F, F, F,
	F, F, F, F, F, E, S, W, W, S, W, W, W, W, W, W, S, W, W, S, E, F, F, F, F, F,
	E, E, E, E, E, E, S, W, W, S, W, W, W, W, W, W, S, W, W, S, E, E, E, E, E, E,
	TL, F, F, F, F, F, F, F, F, S, W, W, W, W, W, W, S, F, F, F, F, F, F, F, F, TR, 
	E, E, E, E, E, E, S, W, W, S, W, W, W, W, W, W, S, W, W, S, E, E, E, E, E, E,
	F, F, F, F, F, E, S, W, W, S, W, W, W, W, W, W, S, W, W, S, E, F, F, F, F, F,
	F, F, F, F, F, E, S, W, W, S, S, F, F, F, F, S, S, W, W, S, E, F, F, F, F, F,
	F, F, F, F, F, E, S, W, W, S, W, W, W, W, W, W, S, W, W, S, E, F, F, F, F, F,
	F, F, F, F, F, E, S, W, W, S, W, W, W, W, W, W, S, W, W, S, E, F, F, F, F, F,
	E, E, E, E, E, E, S, W, W, S, S, S, W, W, S, S, S, W, W, S, E, E, E, E, E, E,
	E, S, S, S, S, S, S, S, S, S, W, S, W, W, S, W, S, S, S, S, S, S, S, S, S, E, 
	E, S, W, W, W, W, S, W, W, W, W, S, W, W, S, W, W, W, W, S, W, W, W, W, S, E, 
	E, S, W, W, W, W, S, W, W, W, W, S, W, W, S, W, W, W, W, S, W, W, W, W, S, E, 
	E, S, W, W, W, W, S, S, S, S, S, S, S, S, S, S, S, S, S, S, W, W, W, W, S, E, 
	E, S, S, S, S, S, S, W, W, W, W, S, W, W, S, W, W, W, W, S, S, S, S, S, S, E, 
	E, S, W, W, W, W, W, W, W, W, W, S, W, W, S, W, W, W, W, W, W, W, W, W, S, E, 
	E, S, W, W, W, W, W, W, W, W, W, S, W, W, S, W, W, W, W, W, W, W, W, W, S, E,
	E, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, S, E,
	E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E}; 							 
							 
/*---------------------------- Define functions -----------------------------*/ 

/*----------------------------------------------------------------------------
  Function that draws Pacman board
 *----------------------------------------------------------------------------*/
void draw_board(void){
	int i, j; 
	LCD_Clear(Black);
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			switch(board[i][j]){
				case E: 
					draw_edge(j, i); 
					break; 
				case W: 
					draw_wall(j, i); 
					break;
				case S: 
					draw_pill(board[i][j], j, i); 
					break;
				default: 
					break; 
			}
		}
	}
}
 
/*----------------------------------------------------------------------------
  Function that draws a wall 
 *----------------------------------------------------------------------------*/
void draw_wall(int i, int j){
	int x0, y0, y1; 
	for (x0 = i*PIXEL_CELL, y0 = j*PIXEL_CELL, y1 = y0 + PIXEL_CELL; y0 < y1; y0++){
		LCD_DrawLine(x0, y0, x0 + PIXEL_CELL, y0, Blue2); 
	}
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void draw_edge(int i, int j){
	LCD_DrawLine((i*PIXEL_CELL), (j*PIXEL_CELL), ((i*PIXEL_CELL)+PIXEL_CELL), (j*PIXEL_CELL), Blue2); 
	LCD_DrawLine((i*PIXEL_CELL)+PIXEL_CELL, (j*PIXEL_CELL), ((i*PIXEL_CELL)+PIXEL_CELL), (j*PIXEL_CELL)+PIXEL_CELL, Blue2); 
	LCD_DrawLine((i*PIXEL_CELL), (j*PIXEL_CELL)+PIXEL_CELL, ((i*PIXEL_CELL)+PIXEL_CELL), (j*PIXEL_CELL)+PIXEL_CELL, Blue2); 
	LCD_DrawLine((i*PIXEL_CELL), (j*PIXEL_CELL), ((i*PIXEL_CELL)), (j*PIXEL_CELL)+PIXEL_CELL, Blue2); 
}


/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void draw_pill(int kind_cell, int i, int j){
	switch(kind_cell){
		case S: 
			LCD_DrawCircle(((i*PIXEL_CELL)+5), ((j*PIXEL_CELL)+5), SP_r/2, White); 
		case P: 
			LCD_DrawCircle(((i*PIXEL_CELL)+5), ((j*PIXEL_CELL)+5), PP_r/2, White); 
		default:
			break; 
	}
}