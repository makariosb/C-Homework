#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define PRINT 0
#define SAVE 1
#define MAXWORDS 100
#define MAXCHARS 50
int makeselection(void);
void getinputtext(char wordlist[MAXWORDS][MAXCHARS]);
void countwordschars(char wordlist[MAXWORDS][MAXCHARS]);
void countuniquewords(char wordlist[MAXWORDS][MAXCHARS]);
void makehistogram(char wordlist[MAXWORDS][MAXCHARS],int MODE);
void spellcheck(char wordlist[MAXWORDS][MAXCHARS]);

int main(void) {
	char selection;
	char wordlist[MAXWORDS][MAXCHARS]={' '};
	while ((selection=makeselection())!='s'){
		switch(selection){
			case 'a':
				getinputtext(wordlist);
				countwordschars(wordlist);
				break;
			case 'b':
				getinputtext(wordlist);
				countuniquewords(wordlist);
				break;
			case 'c':
				getinputtext(wordlist);
				makehistogram(wordlist,PRINT);
				break;
			case 'd':
				getinputtext(wordlist);
				makehistogram(wordlist,SAVE);
				break;
			case 'e':
				getinputtext(wordlist);
				spellcheck(wordlist);
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

int makeselection(void){
	int input;
	printf("\nWelcome to the poor man's Text Editor!\nPlease type a letter that corresponds to what you want to do:\na : Count characters and words\nb : Count unique words\nc : Print word length histogram\nd : Save word length histogram\ne : Spell check\nf : Formatting Check\nTo stop the program type \"s\"\n");
	input=getch();
	return input;
}

void getinputtext(char wordlist[MAXWORDS][MAXCHARS]){
	char tempword[MAXCHARS];
	int i=0,j;
	for(j=0;j<MAXWORDS;strcpy(wordlist[j++],""));
	puts("Please enter words:");
	while (1==1){
		scanf("%s",tempword);
		if (strcmp(tempword,"*TELOS**")==0){
			break;
		}
		strcpy(wordlist[i++],tempword);
	}
}

void countwordschars(char wordlist[MAXWORDS][MAXCHARS]){
	int words,chars=0;
	for (words=0;strcmp(wordlist[words],"")!=0;words++){
		chars+=strlen(wordlist[words]);
	}
	printf("Number of Words: %d\n",words);
	printf("Number of Characters: %d\n",chars);
}

void countuniquewords(char wordlist[MAXWORDS][MAXCHARS]){
	char unique[MAXWORDS][MAXCHARS];
	int i=0,count=0,j,mode=1;
	while (strcmp(wordlist[i],"")!=0){
		for (j=0;strcmp(unique[j],"")!=0;j++){
			if (strcmp(wordlist[i],unique[j])==0){
				mode=0;
				break;
			}
		}
		switch(mode){
			case 1:
				strcpy(unique[count++],wordlist[i]);
				break;
			case 0:
				mode=1;
				break;
		}
		i++;
	}
	printf("Number of unique words: %d\n",count);
}

void makehistogram(char wordlist[MAXWORDS][MAXCHARS],int MODE){
	int i=0;
	int lens[MAXCHARS]={0};
	while (strcmp(wordlist[i],"")!=0){
		lens[strlen(wordlist[i])]++;
		i++;
	}
	switch (MODE){
		case PRINT:
			printf("makehistogram PRINT MODE : \n");
			for (i=0;i<MAXCHARS;i++){
				if (lens[i]!=0){
					printf("%s%d%s%d\n","The number of words with ",i," characters is: ",lens[i]);
				}
			}
			break;
		case SAVE:
			puts("Not implemented in this version.");
			break;
	}
}

void spellcheck(char wordlist[MAXWORDS][MAXCHARS]){
	puts("Not implemented in this version.");
}
