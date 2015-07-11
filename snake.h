/* 
   snake.h
   Header file
*/
#ifndef FILE_SNAKE_SEEN
#define FILE_SNAKE_SEEN

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>


#define STARTLENGTH 2 /* starting length of snake */

#define DELAY 70000 /* amount of time between ticks
					   changes as score goes up */
#define DELAYMULTIPLIER 2000 /* Reduces delay by DELAYMULTIPLIER * score */


/* Arena Boundaries */
#define XMIN 20
#define YMIN 5
#define XMAX xmax-XMIN
#define YMAX ymax-YMIN

int xmax, ymax; /* Global variables */

typedef struct {
	int x;
	int y;
} Coordinates;

typedef struct {
	int length;
	int score;
	int direction;
	Coordinates body[100]; /* Array of snake "body parts" that holds coordinate values 
							 body[0] being the head, and body [length-1] being the tail	*/
} Snake;

typedef struct {
	int score;
	char name[20];
} Highscore;

/* 
  Direction:
  UP==1
  DOWN==2
  RIGHT==3
  LEFT==4
*/


/* Prototypes */
/* display.c */
void drawSnake(Snake *snake, char arena[][xmax]);
void drawApple(char arena[][xmax]);
void scoreCounter(Snake *snake);
void render(char arena[][xmax]);
/* output.c */
void outputMain(Snake *snake); 

#endif /* !FILE_SNAKE_SEEN */