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

/* define functions */ 
void set_direction(enum movement); 
void move_pacman(void); 
void set_direction(enum movement d); 
void set_point(void); 
void random_Ppills(void); 
void sub_Ppill(void); 
							
// variables
volatile enum movement direction = left;
Position pacman = {7, 14}; 
Position blinky = {12, 11}; 
volatile int time = 60; 
volatile int score = 0; 
volatile uint8_t n_pills = N_PILLS; 
volatile bool InPause = true; 
volatile int random_time[R_TIME]; 
volatile int nLife = 0; 
volatile int xLife = 25; 
volatile enum game_strategy strategy = Chase; 
volatile int blinky_coeff = 3; 
volatile Position openList[ROWS * COLUMNS];
volatile bool visited[ROWS][COLUMNS] = {false};

// Directions to move 
int directions[4][2] = {
    {-1, 0},  // above
    {1, 0},   // under
    {0, -1},  // left
    {0, 1}    // right
};
 

extern volatile uint8_t board[ROWS][COLUMNS]; 
extern volatile uint8_t coordinates_pill[2][N_PILLS]; 

/*----------------------------------------------------------------------------
  Function for pacman movement
 *----------------------------------------------------------------------------*/
void move_pacman(void){
	if (pacman.x < (COLUMNS-1) && pacman.y < (ROWS-1)
				|| (pacman.y == TELEPORT_POSY && (pacman.x == TR_X || pacman.x == TL_X))) {
		switch(direction) {
			// for each direction: check if possible continue and update Pacman position
			case up: 
				if(board[pacman.y-1][pacman.x] != W && board[pacman.y-1][pacman.x] != E) {
					draw_pacman(pacman.y, pacman.x, true); 
					pacman.y--; 
					draw_pacman(pacman.y, pacman.x, false);
				}
				break; 
				
			case right: 
				if(pacman.x == TR_X && pacman.y == TELEPORT_POSY) {
					draw_pacman(pacman.y, pacman.x, true);
					pacman.x = TL_X;
				} else if(board[pacman.y][pacman.x+1] != W && board[pacman.y][pacman.x+1] != E) {
					draw_pacman(pacman.y, pacman.x, true);
					pacman.x++;
				}
				draw_pacman(pacman.y, pacman.x, false);
				break; 
			
			case down: 
				if(board[pacman.y+1][pacman.x] != W && board[pacman.y+1][pacman.x] != E) {
					draw_pacman(pacman.y, pacman.x, true);
					pacman.y++; 
					draw_pacman(pacman.y, pacman.x, false);
				}
				break; 
			
			case left: 
				if(pacman.x == TL_X && pacman.y == TELEPORT_POSY) {
					draw_pacman(pacman.y, pacman.x, true);
					pacman.x = TR_X;
				}
				else if(board[pacman.y][pacman.x-1] != W && board[pacman.y][pacman.x-1] != E) {
					draw_pacman(pacman.y, pacman.x, true);
					pacman.x--; 
				}
				draw_pacman(pacman.y, pacman.x, false);
				break; 
			
			default: 
				break; 
		}
	}
	set_point(); 
}

/*----------------------------------------------------------------------------
  Function that set new direction at pacman movement
 *----------------------------------------------------------------------------*/
void set_direction(enum movement d){
	direction = d; 
}

/*----------------------------------------------------------------------------
  Function that set points. Check new life and victory
 *----------------------------------------------------------------------------*/
void set_point(void) {
	switch(board[pacman.y][pacman.x]){
		case S: 
			score += SCORE_S_PILLS; 
			board[pacman.y][pacman.x] = F;  
			n_pills--; 
			break; 
		case P: 
			score += SCORE_P_PILLS; 
			board[pacman.y][pacman.x] = F;
			n_pills--; 		
			change_strategy(); 
			break; 
		default: 
			break; 
	}
	// check
	if(n_pills == 0) 
		showGameMode("VICTORY!"); 
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

/*----------------------------------------------------------------------------
  Function that calculate random time 
 *----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------
  Function that substitute standard with power pills 
 *----------------------------------------------------------------------------*/
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


/*----------------------------------------------------------------------------
  **************************Blinky Control************************************
 *----------------------------------------------------------------------------*/
// heuristic function: distance manhattan
int heuristic(Position current, Position target) {
  return abs(current.x - target.x) + abs(current.y - target.y);
}

// Check valid node 
bool is_valid(Position node) {
  return node.y >= 0 && node.y < ROWS &&
         node.x >= 0 && node.x < COLUMNS &&
         board[node.y][node.x] != E && 
         board[node.y][node.x] != W &&
         !visited[node.y][node.x];    
}

// Add new node to list 
void add_to_open(int *openCount, Position node) {
  openList[(*openCount)++] = node;
}
 
// Find lowest heuristic cost
int find_lowest_h(int openCount, Position target) {
  int minIndex = 0, minValue = heuristic(openList[0], target);
  int i; 
  for (i = 1; i < openCount; i++) {
    int h = heuristic(openList[i], target);
    if (h < minValue) {
      minValue = h;
      minIndex = i;
    }
  }
  return minIndex;
}

// With pacman position and aggresivity coefficient, calculate target for blinky
Position get_aggr_target() {
  Position target;

  if (pacman.x > blinky.x && (pacman.x - blinky_coeff) > 0 && board[pacman.y][pacman.x - blinky_coeff] != E && board[pacman.y][pacman.x - blinky_coeff] != W) {  
    target.x = pacman.x - blinky_coeff;
  } else if (pacman.x < blinky.x && (pacman.x + blinky_coeff) < COLUMNS && board[pacman.y][pacman.x + blinky_coeff] != E && board[pacman.y][pacman.x + blinky_coeff] != W) {
    target.x = pacman.x + blinky_coeff;
  } else {
    // if not possible, target is pacman
    target.x = pacman.x;  // fallback alla posizione attuale
  }

  if (target.x == pacman.x){
    target.y = pacman.y; 
  }else if (pacman.y > blinky.y && (pacman.y - blinky_coeff) > 0 && board[pacman.y - blinky_coeff][pacman.x] != E && board[pacman.y - blinky_coeff][pacman.x] != W) {
    target.y = pacman.y - blinky_coeff; 
  } else if (pacman.y + blinky_coeff < ROWS) {
    target.y = pacman.y + blinky_coeff; 
  }
  return target;
}

void change_strategy(){
	if(strategy == Chase){
		init_timer(2, 0, 0, 5, 0xEE6B280); 		// 10 sec: duration of strategy Frightened
		strategy = Frightened; 
		enable_timer(2); 
	} else {
		strategy = Chase; 
		disable_timer(2); 
	}
}

void move_blinky() {
  int openCount = 0;
  draw_blinky(blinky.y, blinky.x, true, strategy); 

  // Reset visited array
  int i, j; 
  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLUMNS; j++) {
      visited[i][j] = false;
    }
  }

  // Add initial position to open list
  add_to_open(&openCount, blinky);

  Position target = (strategy == Chase) ? get_aggr_target() : pacman;

  while (openCount > 0) {
    // Find the node with the lowest heuristic value
    int currentIndex = find_lowest_h(openCount, target);
    Position current = openList[currentIndex];

    // Remove the node from open list
    for (i = currentIndex; i < openCount - 1; i++) {
      openList[i] = openList[i + 1];
    }
    openCount--;

    // Mark current node as visited
    visited[current.y][current.x] = true;

    Position bestMove = current;  // Default to current if no move is better

    int d;
    for (d = 0; d < 4; d++) {
      Position neighbor = {current.x + directions[d][0], current.y + directions[d][1]};

      if (is_valid(neighbor)) {
        if (strategy == Chase && heuristic(neighbor, target) < heuristic(bestMove, target)) {
          bestMove = neighbor;
        }
        if (strategy == Frightened && heuristic(neighbor, pacman) > heuristic(bestMove, pacman)) {
          bestMove = neighbor;
        }
      }
    }

    // Move Blinky to the best cell and exit loop
    if (bestMove.x != current.x || bestMove.y != current.y) {
      blinky = bestMove;
      draw_blinky(blinky.y, blinky.x, false, strategy);
      return;
    }
  }

  // Default: No valid move, stay in current position
  draw_blinky(blinky.y, blinky.x, false, strategy); 
}

