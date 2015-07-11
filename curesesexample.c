#include <curses.h>
#include <string.h>

int main(void) {
	WINDOW *win=initscr(); /* Initialize game window */
		cbreak(); /*Sets the terminal so that it reads characters from keyboard 
			immediately as they are typed, without waiting for carriage return.*/
				noecho(); /* don't echo any keypresses */
					curs_set(FALSE); /* Don't display a cursor */
						keypad(stdscr,TRUE);
	
	while (1) {
	int ch;
	ch=getch();
	if (ch==KEY_LEFT)
		printw("left arrow is pressed!\n");
	}
}
