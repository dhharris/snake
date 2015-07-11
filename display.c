/*
  display.c
  Displays the graphics to standard output.
*/

#include "snake.h"

/* Converts int to string */
void itoa(int i, char string[]){
    char const digit[] = "0123456789";
    char* p = string;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);

}

/* Places snake body onto arena */
void drawSnake(Snake *snake, char arena[][xmax]) {
	for (int i=0;i<snake->length;i++) {
		arena[snake->body[i].y][snake->body[i].x]='*';
	}
}

void drawApple(char arena[][xmax]) {
	int x, y;

	srand(time(NULL)); /* Seed */
	do {
		x=rand() % (xmax);
		y=rand() % (ymax);
	} while(arena[y][x]!=' ' || y <= YMIN || y >= YMAX || x <= XMIN || x >= XMAX); /* Keep going until apple is placed in an empty space within boundaries */

	arena[y][x]='o';
	return;
}

/* Displays score to user */
void scoreCounter(Snake *snake) {
	char intstring[20];
	itoa(snake->score,intstring);
	mvprintw(0,0,"Score: ");
	mvprintw(0,7,intstring);
	refresh();
}

void render(char arena[][xmax]) {
	clear(); /* Clear the screen */
	for (int i=0;i<ymax;i++) {
		for (int j=0;j<xmax;j++) {
			mvprintw(i,j,&arena[i][j]);
		}
	}
	refresh();
}