/*
  output.c
  Writes scores to a file
*/

#include "snake.h"

FILE *fptr, *fptr1; /* Global variables */

void initScores(void) {
	system("touch .highscores.txt .names.txt");
	fptr=fopen(".highscores.txt","w+");
	fptr1=fopen(".names.txt","w+");
	fprintf(fptr,"%i ",-1);
	fprintf(fptr1,"%s ","snake");
	freopen(".highscores.txt","r+",fptr);
	freopen(".names.txt","r+",fptr1);
}

int compare(Highscore *ptr1, Highscore *ptr2) {
	return ptr2->score-ptr1->score;
}

void sortScores(Highscore highscores[], int count) {
	qsort(highscores,count,sizeof(Highscore),compare);
}

/* find index of snake, if found return index */
int findSnake(Highscore highscores[], int count) {
	for (int i=0;i<count;i++) {
		if (strcmp(highscores[i].name, "snake")==0)
			return i;
	}
	return -1;
}

void displayScores(Highscore highscores[], int count) {
	printf("				HIGH SCORES\n");
	for (int i=0;i<count;i++) {
		if (i != 9)
			printf("%i.  %s 							%-3i points\n",i+1,highscores[i].name,highscores[i].score);
		else
			printf("%i. %s 							%-3i points\n",i+1,highscores[i].name,highscores[i].score);
	}
}

void writeScores(Highscore highscores[], int count) {
	freopen(".highscores.txt","w+",fptr);
	freopen(".names.txt","w+",fptr1);

	for (int i=0;i<count;i++) {
		fprintf(fptr,"%i ",highscores[i].score);
		fprintf(fptr1,"%s ",highscores[i].name);
	}
}

int getScores(Highscore highscores[]) {
	int count1=0, count2=0;
	fptr=fopen(".highscores.txt","r+");
	if (fptr==NULL) {
		initScores();
		printf("High scores list initialized!\n");
	}
	fptr1=fopen(".names.txt","r+");
	if (fptr1==NULL) {
		initScores();
		printf("High scores list initialized!\n");
	}
	while (EOF != fscanf(fptr, "%i ",&highscores[count1].score))
		count1++;
	
	while (EOF != fscanf(fptr1, "%s",highscores[count2].name))
		count2++;

	if (count1==count2 && count1!=0)
		return count1;
	else
		return -1;

}

void deleteScore(Highscore highscores[], int index) {
	highscores[index-1].score=-1;
	strcpy(highscores[index-1].name,"snake");
}

void resetScores(void) {
	system("rm -rf .highscores.txt .names.txt");
	return;
}

void outputMain(Snake *snake) {
	Highscore highscores[10];
	int count;
	int newHighscore=0; /* Flag variable that says whether a new highscore is to be written */
	char name[20];

	system("clear");

	printf("GAME OVER\nYour score: %i\n\n",snake->score);

	count=getScores(highscores);
	if (count==-1) {
		printf("File error. Check high scores files.\n");
		return;
	}

	if (count < 10)
		newHighscore=1;
	else {
		for (int i=0;i<count;i++) {
			if (snake->score > highscores[i].score)
			newHighscore=1;
			}
	}
	if (newHighscore) {
		sortScores(highscores,count);
		printf("New high score!\nPlease enter your first name: ");
		fflush(stdout); /* Forces printf() to execute before scanf() */
		scanf("%s",name);

		/* Delete all high scores */
		if (strcmp(name,"DEL_HS")==0) {
			resetScores();
			printf("High scores reset successful!\n");
			return;
		}

		/* Delete one high score */
		if (strcmp(name,"DEL")==0) {
			int index;
			displayScores(highscores,count);
			printf("Which score do you want to delete? (enter the number value)\n");
			fflush(stdout);
			scanf("%i",&index);
			deleteScore(highscores,index);
			sortScores(highscores,count);
			count--;
			printf("High score removed successfully!\n");
			writeScores(highscores,count);
			displayScores(highscores,count);
			return;
		}

		int s=findSnake(highscores,count);
		if (s != -1) {
			highscores[s].score=snake->score;
			strcpy(highscores[s].name,name);
		}
		else if (count == 10) {
			highscores[9].score=snake->score;
			strcpy(highscores[9].name,name);
		}
		else {
			highscores[count].score=snake->score;
			strcpy(highscores[count].name,name);
			count++;
		}
		sortScores(highscores,count);
		writeScores(highscores,count);
	}
	printf("\n");
	displayScores(highscores,count);
	printf("\n");
	fclose(fptr);
	fclose(fptr1);
	return;
	
}