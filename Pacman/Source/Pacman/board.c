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
#define SP_SIZE 1 				// radius standard pill
#define PP_SIZE 3 				// radius power pill
#define PACMAN_SIZE 4 		// "radius" Pacman
#define START_Y 40				// start board on display. 

/* define enum for kind of cells in board */
enum kind_cell{S,			// standard pill
							 P,			// power pill
							 W,			// wall
							 F,			// free cell
							 E,			// edge of board 
							 TL,		// teleport left		
							 TR,		// teleport right 
							 PA};	  // pacman  	

/* fnuctions declaration */ 
void draw_board(void); 
void draw_edge(int, int); 
void draw_wall(int, int); 
void draw_pill(int, int, int); 
void draw_pacman(int, int); 

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
	F, F, F, F, F, E, S, W, W, S, E, E, E, E, E, E, S, W, W, S, E, F, F, F, F, F,
	E, E, E, E, E, E, S, W, W, S, E, E, E, E, E, E, S, W, W, S, E, E, E, E, E, E,
	TL, F, F, F, F, F, F, F, F, S, E, E, E, E, E, E, S, F, F, F, F, F, F, F, F, TR, 
	E, E, E, E, E, E, S, W, W, S, E, E, E, E, E, E, S, W, W, S, E, E, E, E, E, E,
	F, F, F, F, F, E, S, W, W, S, E, E, E, E, E, E, S, W, W, S, E, F, F, F, F, F,
	F, F, F, F, F, E, S, W, W, S, S, P, PA, F, F, S, S, W, W, S, E, F, F, F, F, F,
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
					draw_edge(i, j); 
					break; 
				case W: 
					draw_wall(i, j); 
					break;
				case S: 
					draw_pill(board[i][j], i, j); 
					break;
				case P: 
					draw_pill(board[i][j], i, j);
					break;
				case PA: 
					draw_pacman(i, j); 
					break; 
			}
		}
	}
}
 
/*----------------------------------------------------------------------------
  Function that draws a wall 
 *----------------------------------------------------------------------------*/
// y --> i become y
// x --> j become x 
void draw_wall(int y, int x){
	int x0, y0, y1; 
	for (x0 = x*PIXEL_CELL, 
				y0 = y*PIXEL_CELL + START_Y, 
				y1 = y0 + PIXEL_CELL; 
			 y0 < y1; 
			 y0++){
				 
		LCD_DrawLine(x0, y0, x0 + PIXEL_CELL, y0, Blue2); 
	}
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/

// y --> i become y
// x --> j become x 
void draw_edge(int y, int x){
	int xb = x*PIXEL_CELL; 
	int yb = y*PIXEL_CELL + START_Y; 
	// up
	if (y > 0 && board[y-1][x] == E) {
		// to clean line 
		LCD_DrawLine((xb+1), (yb), ((xb)+PIXEL_CELL-1), (yb), Black); 
	} else {
		// to add new line of board 
		LCD_DrawLine((xb), (yb), ((xb)+PIXEL_CELL), (yb), Blue2);  
	}
	
	// right 
	LCD_DrawLine((xb)+PIXEL_CELL, (yb), ((xb)+PIXEL_CELL), (yb)+PIXEL_CELL, Blue2); 
	
	// down
	LCD_DrawLine((xb), (yb)+PIXEL_CELL, ((xb)+PIXEL_CELL), (yb)+PIXEL_CELL, Blue2); 
	
	// left 
	if (x > 0 && board[y][x-1] == E) {
		LCD_DrawLine((xb), (yb)+1, ((xb)), (yb)+PIXEL_CELL-1, Black);
	} else {
		LCD_DrawLine((xb), (yb), ((xb)), (yb)+PIXEL_CELL, Blue2);
	}
}


/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
// y --> i become y
// x --> j become x 
void draw_pill(int kind_cell, int y, int x){
	int xb = (x * PIXEL_CELL); 
	int yb = (y * PIXEL_CELL) + START_Y; 
	switch(kind_cell){
		case S: 
			LCD_DrawCircle((xb + 5), (yb + 5), SP_SIZE, White); 
			break;
		case P: 
			LCD_DrawCircle((xb + 5), (yb + 5), PP_SIZE, White); 
			break; 
	}
}

void draw_pacman(int y, int x){
		LCD_DrawCircle(x * PIXEL_CELL + 5, y * PIXEL_CELL + START_Y + 5, PACMAN_SIZE, Yellow); 
}

// MOVEMENT PACMAN 