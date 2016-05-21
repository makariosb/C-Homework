#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define PRINT 0
#define SAVE 1
char makeselection(void);
int getinputtext(int x);
void countwordschars(int x);
void countuniquewords(int x);
void makehistogram(int x,int MODE);
void spellcheck(int x);

int main(void) {
	char selection;
	int input;
	printf("Welcome to the poor man's Text Editor!\nPlease type a letter that corresponds to what you want to do:\na : Count characters and words\nb : Count unique words\nc : Print word length histogram\nd : Save word length histogram\ne : Spell check\nf : Formatting Check\nTo stop the program type \"s\"\n");
	while ((selection=makeselection())!='s'){
		switch(selection){
			case 'a':
				input=getinputtext(1);
				countwordschars(input);
				break;
			case 'b':
				input=getinputtext(1);
				countuniquewords(input);
				break;
			case 'c':
				input=getinputtext(1);
				makehistogram(input,PRINT);
				break;
			case 'd':
				input=getinputtext(1);
				makehistogram(input,SAVE);
				break;
			case 'e':
				input=getinputtext(1);
				spellcheck(input);
				break;
			case 's':
				break;
			case '\n':
				break;
			default:
				puts("Your selection is invalid, please type another letter: ");
				break;
		}
	}
	return 0;
}

char makeselection(void){
	char input;
	input=getchar();
	return input;
}

int getinputtext(int x){
	printf("getinputtext : %d\n",++x);
	return x;
}

void countwordschars(int x){
	printf("countwordschars : %d\n",++x);
}

void countuniquewords(int x){
	printf("countuniquewords : %d\n",++x);
}

void makehistogram(int x,int MODE){
	switch (MODE){
		case PRINT:
			printf("makehistogram PRINT MODE : %d\n",++x);
			break;
		case SAVE:
			printf("makehistogram SAVE MODE : %d\n",++x);
			break;
	}
}

void spellcheck(int x){
	printf("spellcheck : %d\n",++x);
}
