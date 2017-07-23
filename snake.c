/*
  SNAKE

  My first video game

  Created on 12/8/14
  Written by Hugh Harris
*/

/*
  Snake.c
  Handles the game logic and main function.
*/

#include "snake.h"

/* Returns the opposite direction of travel */
int opposite(int direction) {
	switch(direction) {
		case 1: return 2;
		case 2: return 1;
		case 3: return 4;
		case 4: return 3;
		default: return 0;
	}
}


void wrap_up() {

    curs_set(1);
    clear();
    if (endwin()==ERR)
		printf("Error closing window!");
	system("clear");
}

void initArena(char arena[][xmax]) {
	for (int i=0;i<ymax;i++) {
 		for (int j=0;j<xmax;j++) {
 			arena[i][j]=' ';
 		}
 	}
}

int checkCollisions(Snake *snake, char arena[][xmax]) {
	switch(arena[snake->body[0].y][snake->body[0].x]) {
		case ' ': break;
		case '-': return 1;
		case '|': return 1;
		case 'o':
			snake->score++;
			snake->length++;
			break;
	}
	for (int i=2;i<snake->length;i++)
		if (snake->body[0].x==snake->body[i].x && snake->body[0].y==snake->body[i].y)
			return 1;
	return 0;
}

/* Returns 1 if there is an apple and 0 if not */
int findApple(char arena[][xmax]) {
	for (int i=0;i<ymax;i++) {
 		for (int j=0;j<xmax;j++) {
 			if (arena[i][j]=='o')
 				return 1;
 		}
 	}
 	return 0;
}

void resetArena(char arena[][xmax]) {
	if (findApple(arena)==0)
		drawApple(arena);
	for (int i=0;i<ymax;i++) {
 		for (int j=0;j<xmax;j++) {
 			if (arena[i][j]=='o')
 				; /* Do nothing */
 			else if ((i==YMIN && j > XMIN && j < XMAX) || (i==YMAX && j>XMIN && j< XMAX)) /* Arena boundaries */
 				arena[i][j]='-';
 			else if ((j==XMIN && i > YMIN && i < YMAX) || (j==XMAX && i > YMIN && i < YMAX))
 				arena[i][j]='|';
			else
 				arena[i][j]=' '; /* Initialize values in array to an empty space */
 		}
 	}
}

void moveBody(Snake *snake) {
	for (int i=snake->length;i>0;i--) {
		snake->body[i]=snake->body[i-1];
	}
}


/* Function to move character every tick */
void moveHead(Snake *snake) {
	switch(snake->direction) {
		case 1: snake->body[0].y--;
			break;
		case 2: snake->body[0].y++;
			break;
		case 3: snake->body[0].x++;
			break;
		case 4: snake->body[0].x--;
			break;
	}
}



int input(void) {
	int ch=getch();
	switch(ch) {
		case KEY_UP:
                case 'k':
                        return 1;
		case KEY_DOWN:
                case 'j':
                        return 2;
		case KEY_RIGHT:
                case 'l':
                        return 3;
		case KEY_LEFT:
                case 'h':
                        return 4;
		case '\n': return 0; /* Pause button */
	}
return -1; /* If no input */
}

/* Update snake & apple locations */
int tick(Snake *snake, char arena[][xmax]) {

	int d=input();

	if (d==0) {
		while (1) {
		mvprintw(0,34,"Game paused");
		if (getch()=='\n')
			return 0; /* Wait for user to press return to unpause */
		}
	}
	if ((d != -1) && (d != opposite(snake->direction)))
		snake->direction=d;


	moveHead(snake);

	moveBody(snake);
	if (checkCollisions(snake,arena)==1)
		return -1;
	drawSnake(snake, arena);
	return 1;
}


int main(void) {
	int status; /* Value returned by tick
				1: Game running
				0: Game paused
				-1: Game over */

	int delta=0; /* Reduces delay */

	system("clear");
	printf("Welcome to the snake game!\nPress return to begin.\n");
	fflush(stdout);
	getchar();

	/* Initialize curses window */
	WINDOW *win=initscr(); /* Initialize game window */
    /*Sets the terminal so that it reads characters from keyboard
	immediately as they are typed, without waiting for carriage return.*/
	noecho(); /* don't echo any keypresses */
	curs_set(FALSE); /* Don't display a cursor */
	keypad(stdscr,TRUE);
	nodelay(stdscr,TRUE); /* Does not wait for input */

	/* Initialize snake object */
	Snake snake; /* Snake character */
		snake.length=STARTLENGTH;
		snake.score=0;
		snake.direction=3; /* Starts moving to the right */
		snake.body[0].x=xmax-40;
		snake.body[0].y=ymax+15;

	/* Global var `stdscr` is created by the call to `initscr()` */
 	getmaxyx(stdscr, ymax, xmax);

 	/* Initialize arena */
 	char arena[ymax][xmax]; /* arena array that contains all the characters */
 	initArena(arena);


	int running=1; /* Game is running */

	/* Main game loop */
	while(running) {
		resetArena(arena);
		status=tick(&snake,arena);
		if (status==-1)
			running=0;
		else if (status==0)
			continue;
		render(arena);
		scoreCounter(&snake);

		delta=snake.score * DELAYMULTIPLIER;
		if (DELAY-delta > 0)
			usleep(DELAY-delta);



	}
	sleep(1);
	wrap_up();
	outputMain(&snake);
	return 0;
}
