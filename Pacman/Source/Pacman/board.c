/***************************************************************************************
**--------------File Info---------------------------------------------------------------
** It includes all functions for pacman board creation. 
**--------------------------------------------------------------------------------------       
***************************************************************************************/

/* include libraries */ 
#include "LPC17xx.h"
#include "pacman.h"

/* define constants */ 
#define PIXEL_CELL 9
#define SP_SIZE 1 				// radius standard pill
#define PP_SIZE 2 				// radius power pill
#define PACMAN_SIZE 3 		// "radius" Pacman
#define START_Y 40				// start board on display. 
#define X_number 115			// X for number of score and time 
#define Y_write 17 				// Y for score write 

/* fnuctions declaration */ 
void draw_board(void); 
void draw_edge(int, int); 
void draw_wall(int, int); 
void draw_pill(int, int, int, bool); 
void draw_pacman(int, int, bool); 
void show_time(void); 
void show_score(void); 
void disableAll(void); 
void resume(void); 
void enableAll(void); 
void showGameMode(char* s); 

/* define global variables */ 	
volatile uint8_t coordinates_pill[2][N_PILLS]; 

extern volatile uint8_t time; 
extern volatile int score; 
extern Position pacman; 

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
	F, F, F, F, F, E, S, W, W, S, S, S, F, F, F, S, S, W, W, S, E, F, F, F, F, F,
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
	int i, j, z = 0; 
	
	LCD_Clear(Black);
	GUI_Text(0, 0, (uint8_t*)" Countdown: ", White, Black); 
	GUI_Text(0, Y_write, (uint8_t*)" Score: ", White, Black); 
	show_score(); 
	show_time(); 
	
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
					draw_pill(board[i][j], i, j, false); 
					coordinates_pill[0][z] = i; 		// y cord 
					coordinates_pill[1][z] = j; 		// x cord 
					z++; 
					break;
			}
		}
	} 
}
 
/*----------------------------------------------------------------------------
  Function that shows overall score. 
 *----------------------------------------------------------------------------*/
void show_score(void) {
	char sScore[5]; 
	
	sprintf(sScore, "%d", score);
	GUI_Text(X_number, Y_write, (uint8_t*)sScore, White, Black); 
}

/*----------------------------------------------------------------------------
  Function that shows countdown timer 
 *----------------------------------------------------------------------------*/
void show_time(void) {
	char sTime[2]; 
	
	sprintf(sTime, "%d", time); 
	if (time < 10){
		sTime[1] = sTime[0]; 
		sTime[0] = ' '; 
	}
		
	GUI_Text(X_number, 0, (uint8_t*)sTime, White, Black); 
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
  Function that draws a edge 
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
  Function that draws a pill
 *----------------------------------------------------------------------------*/
// y --> i become y
// x --> j become x 
void draw_pill(int kind_cell, int y, int x, bool clean){
	int xb = (x * PIXEL_CELL); 
	int yb = (y * PIXEL_CELL) + START_Y; 
	uint16_t color; 
	if (clean) 
		color = Black; 
	else 
		color = White; 
	
	switch(kind_cell){
		case S: 
			LCD_DrawCircle((xb + 5), (yb + 5), SP_SIZE, color); 
			break;
		case P: 
			LCD_DrawCircle((xb + 5), (yb + 5), PP_SIZE, color); 
			break; 
	}
}

/*----------------------------------------------------------------------------
  Function that draws Pacman 
 *----------------------------------------------------------------------------*/
void draw_pacman(int y, int x, bool clean){
	uint16_t color; 
	if (clean) 
		color = Black; 
	else 
		color = Yellow; 
	
	LCD_DrawCircle(x * PIXEL_CELL + 5, y * PIXEL_CELL + START_Y + 5, PACMAN_SIZE, color); 
}

/*----------------------------------------------------------------------------
  Function that draws Blinky Red
----------------------------------------------------------------------------*/
void draw_blinky(int y, int x, bool clean, enum game_strategy s) {
  uint16_t body_color, eye_color, pupil_color;
	int line_y, i; 
	int xb = x * PIXEL_CELL;
	int yb = y * PIXEL_CELL + START_Y;
	
	if (clean) {
		body_color = Black;
		eye_color = Black;
	} else {
		if (s == Chase)
			body_color = Red;
		else 
			body_color = Blue;
		eye_color = White;
	}

	// Draw Blinky's body (semicircle with a rectangle)
	LCD_DrawFilledCircle(xb + 4, yb + 4, 2, body_color); 
	for (line_y = yb + 4; line_y < yb + PIXEL_CELL-2; line_y++) {
		LCD_DrawLine(xb+3, line_y, xb + PIXEL_CELL-3, line_y, body_color);
	}

	// Add wave pattern for the bottom of the ghost
	for (i = 1; i < PIXEL_CELL; i += 2) {
		if (i % 4 == 0) {
			LCD_DrawLine(xb + i, yb + PIXEL_CELL - 2, xb + i + 1, yb + PIXEL_CELL-1, body_color);
		} else {
			LCD_DrawLine(xb + i, yb + PIXEL_CELL-1, xb + i + 1, yb + PIXEL_CELL - 2, body_color);
		}
	}

	// Draw Blinky's eyes
	LCD_DrawCircle(xb + 3, yb + 5, 1, eye_color); 
	LCD_DrawCircle(xb + 7, yb + 5, 1, eye_color); 
}

/*----------------------------------------------------------------------------
  Function that enable timer and reset Rit 
 *----------------------------------------------------------------------------*/
void enableAll(void){
	enable_timer(0); 
	enable_timer(1); 
	reset_RIT(); 
}

/*----------------------------------------------------------------------------
  Function that disable timer and reset Rit
 *----------------------------------------------------------------------------*/
void disableAll(void){
	reset_RIT(); 
	disable_timer(0); 
	disable_timer(1); 
}

/*----------------------------------------------------------------------------
  Function that resume game
 *----------------------------------------------------------------------------*/
void resume(void){
	draw_board(); 
	enableAll(); 
}

/*----------------------------------------------------------------------------
  Function that shows string game mode on Display: pause, game over, victory... 
 *----------------------------------------------------------------------------*/
void showGameMode(char* s){
	disableAll();
	LCD_Clear(Black);
	GUI_Text(100, 150, (uint8_t*)s, White, Black);  	
}