#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define PRINT 0
#define SAVE 1
#define MAXCHARS 100
char makeselection(void);
char **makewordlist(char **wordlist,FILE *userfile);
char **makepunctlist(char **punct,FILE *userfile);
void countwordschars(char **wordlist);
void countuniquewords(char **wordlist);
void makehistogram(char **wordlist,int MODE);
void makeuniquewordlist(char **wordlist,int MODE);
void syntaxcheck(char **wordlist,char **punctlist);
void fixsyntax(char **punctlist,char **wordlist);
void dictcheck(char **wordlist,char **punct);
void replace(char *word);
void addtodict(FILE *dictfile,char *word);
int isindict(FILE *dictfile,char *word);
FILE *getfile(void);

int main(void) {
	int i;
	char selection;
	char **wordlist=NULL;
	char **punct=NULL;
	FILE *userfile;
	while ((selection=makeselection())!='s'){
		switch(selection){
			case 'a':
				userfile=getfile();
				wordlist=makewordlist(wordlist,userfile);
				countwordschars(wordlist);
				fclose(userfile);
				break;
			case 'b':
				userfile=getfile();
				wordlist=makewordlist(wordlist,userfile);
				countuniquewords(wordlist);
				fclose(userfile);
				break;
			case 'c':
				userfile=getfile();
				wordlist=makewordlist(wordlist,userfile);
				makehistogram(wordlist,PRINT);
				makeuniquewordlist(wordlist,PRINT);
				fclose(userfile);
				break;
			case 'd':
				userfile=getfile();
				wordlist=makewordlist(wordlist,userfile);
				makehistogram(wordlist,SAVE);
				makeuniquewordlist(wordlist,SAVE);
				fclose(userfile);
				break;
			case 'e':
				userfile=getfile();
				wordlist=makewordlist(wordlist,userfile);
				punct=makepunctlist(punct,userfile);
				syntaxcheck(wordlist,punct);
				break;
			case 'f':
				userfile=getfile();
				wordlist=makewordlist(wordlist,userfile);
				punct=makepunctlist(punct,userfile);
				dictcheck(wordlist,punct);
			case 's':
				break;
			case '\n':
				break;
			default:
				puts("\nYour selection is invalid, please type another letter: ");
				break;
		}
	}
	return 0;
}

char makeselection(void){
	char input;
	printf("\n\nWelcome to the poor man's Text Editor!\nPlease type a letter that corresponds to what you want to do:\na : Count characters and words\nb : Count unique words\nc : Print word length histogram and unique words.\nd : Save word length histogram and unique words.\ne : Grammar and Syntax check\nf : Dictionary Check\n\nTo stop the program type \"s\"\n");
	input=getch();
	return input;
}

FILE *getfile(void){
	char textstream[MAXCHARS];
	FILE *userfile;
	puts("Please enter the name of the file to be imported(no .txt in the end):");
	scanf("%s",textstream);
	userfile=fopen(strcat(textstream,".txt"),"rt");
	return userfile;
}

char **makewordlist(char **words,FILE *userfile){
	char string[MAXCHARS],temp,last;
	int i=0;
	unsigned int numofwords=0;
	free(words);        /*CLEAR WORDLIST*/
	words=NULL;

	while((temp=fgetc(userfile))!=EOF){
		if (isalnum(temp)){
			string[i]=temp;
			i++;
		}
		else{
			if (isalnum(last)){
				string[i]='\0';
				words=realloc(words,(++numofwords)*sizeof(char *));
				words[numofwords-1]=malloc((1+strlen(string))*sizeof(char));
				strcpy(words[numofwords-1],string);
				strcpy(string,"");
    			i=0;
			}
			else{
				last=temp;
				continue;
			}
		}
		last=temp;
	}
	if(isalnum(last)){
		string[i]='\0';
		words=realloc(words,(++numofwords)*sizeof(char *));
		words[numofwords-1]=malloc((1+strlen(string))*sizeof(char));
		strcpy(words[numofwords-1],string);
	}
	words=realloc(words,(numofwords+1)*sizeof(char *));
	words[numofwords]=NULL;
	rewind(userfile);
	return words;
}

char **makepunctlist(char **punct,FILE *userfile){
	char string[MAXCHARS],temp,last='a';
	int i=0;
	unsigned int numofpunct=0;
	free(punct); 		/*CLEAR PUNCTLIST*/
	punct=NULL;

	while((temp=fgetc(userfile))!=EOF){
		if (!isalnum(temp)){
			string[i]=temp;
			i++;
		}
		else{
			if (!isalnum(last)){
				string[i]='\0';
				punct=realloc(punct,(++numofpunct)*sizeof(char *));
				punct[numofpunct-1]=malloc((1+strlen(string))*sizeof(char));
				strcpy(punct[numofpunct-1],string);
				strcpy(string,"");
    			i=0;
			}
			else{
				last=temp;
				continue;
			}
		}
		last=temp;
	}
	if(!isalnum(last)){
		string[i]='\0';
		punct=realloc(punct,(++numofpunct)*sizeof(char *));
		punct[numofpunct-1]=malloc((1+strlen(string))*sizeof(char));
		strcpy(punct[numofpunct-1],string);
	}
	punct=realloc(punct,(numofpunct+1)*sizeof(char *));
	punct[numofpunct]=NULL;
	fclose(userfile);
	return punct;
}

void countwordschars(char **wordlist){
	unsigned int words,chars=0;
	
	for(words=0;wordlist[words]!=NULL;words++){
		chars+=strlen(wordlist[words]);
	}
	printf("Number of Words: %u\n",words);
	printf("Number of Characters: %u\n",chars);
}

void countuniquewords(char **wordlist){
	char **unique=NULL;
	unsigned long int i=0,count=0,j;
	int mode=1;
	unique=realloc(unique,sizeof(char *));
	unique[0]=NULL;
	while (wordlist[i]!=NULL){
		for (j=0;j<count;j++){
			if (strcmp(wordlist[i],unique[j])==0){
				mode=0;
				break;
			}
		}
		switch(mode){
			case 1:
				if(unique[0]==NULL){
					unique[0]=malloc((1+strlen(wordlist[i]))*sizeof(char));
					strcpy(unique[0],wordlist[i]);
					count++;
				}
				else{
					unique=realloc(unique,(++count)*sizeof(char *));
					unique[count-1]=malloc((1+strlen(wordlist[i]))*sizeof(char));
					strcpy(unique[count-1],wordlist[i]);
				}
				break;
			case 0:
				mode=1;
				break;
		}
		i++;
	}
	printf("Number of unique words: %lu\n",count);
	free(unique);         /*CLEAR THE ARRAY*/
}

void makehistogram(char **wordlist,int MODE){
	int i=0;
	char outputname[MAXCHARS];
	unsigned long int lens[MAXCHARS]={0};
	FILE *histogram;

	while (wordlist[i]!=NULL){
		lens[strlen(wordlist[i])]++;
		i++;
	}
	switch (MODE){
		case PRINT:
			printf("\nWord Length Histogram : \n");
			for (i=0;i<MAXCHARS;i++){
				if (lens[i]!=0){
					printf("%s%d%s%lu\n","The number of words with ",i," characters is: ",lens[i]);
				}
			}
			printf("\n");
			break;
		case SAVE:
			puts("How would you like the histogram text file to be named?(no .txt in the end): ");
			scanf("%s",outputname);
			histogram=fopen(strcat(outputname,".txt"),"wt");
			fprintf(histogram,"Word Length Histogram : \n");
			for (i=0;i<MAXCHARS;i++){
				if (lens[i]!=0){
					fprintf(histogram,"%s%d%s%lu\n","The number of words with ",i," characters is: ",lens[i]);
				}
			}
			fprintf(histogram,"\n");
			fclose(histogram);
			puts("Done.");
			break;
	}
}

void makeuniquewordlist(char **wordlist,int MODE){
	char **unique=NULL;
	char fname[MAXCHARS];
	unsigned int i=0,j,count=0,mode=1;
	FILE *wlist;
	unique=realloc(unique,sizeof(char *));
	unique[0]=NULL;
	while (wordlist[i]!=NULL){
		for (j=0;j<count;j++){
			if (strcmp(wordlist[i],unique[j])==0){
				mode=0;
				break;
			}
		}
		switch(mode){
			case 1:
				if(unique[0]==NULL){
					unique[0]=malloc((1+strlen(wordlist[i]))*sizeof(char));
					strcpy(unique[0],wordlist[i]);
					count++;
				}
				else{
					unique=realloc(unique,(++count)*sizeof(char *));
					unique[count-1]=malloc((1+strlen(wordlist[i]))*sizeof(char));
					strcpy(unique[count-1],wordlist[i]);
				}
				break;
			case 0:
				mode=1;
				break;
		}
		i++;
	}
	switch(MODE){
		case PRINT:
			puts("List of unique words:");
			for(i=0;i<count;i++){
				printf("#%4u  %s\n",i+1,unique[i]);
			}
			break;
		case SAVE:
			puts("What would you like the wordlist file to be called? (no .txt in the end):");
			scanf("%s",fname);
			wlist=fopen(strcat(fname,".txt"),"wt");
			fprintf(wlist,"Catalogue of unique words:\n");
			for(i=0;i<count;i++){
				fprintf(wlist,"#%4u  %s\n",i+1,unique[i]);
			}
			fclose(wlist);
			puts("Done.");
			break;
	}
}

void syntaxcheck(char **wordlist,char **punctlist){
	char textstream[MAXCHARS];
	FILE *fixedfile;
	unsigned int i=0;
	puts("Please enter the name of the file to be created with the syntax checked text( no .txt in the end):");
	scanf("%s",textstream);
	fixedfile=fopen(strcat(textstream,".txt"),"wt");
	fixsyntax(punctlist,wordlist);
	for(i=0;wordlist[i]!=NULL;i++){
		fprintf(fixedfile,"%s",wordlist[i]);
		if(punctlist[i]!=NULL)
			fprintf(fixedfile,"%s",punctlist[i]);
	}
	fclose(fixedfile);
	puts("Done.");
}

void fixsyntax(char **punctlist,char **wordlist){
	unsigned int i,j=0;
	char string[MAXCHARS],temp;
	for (i=0;punctlist[i]!=NULL;i++){
		if (strlen(punctlist[i])>1){
			if (strlen(punctlist[i])>2){
				if (ispunct(punctlist[i][1]) && punctlist[i][0]==' ' && punctlist[i][2]==' '){
					strcpy(string,&punctlist[i][1]);
					punctlist[i]=malloc((1+strlen(string))*sizeof(char));
					strcpy(punctlist[i],string);
					strcpy(string,"");
				}
				else{
					if (punctlist[i][strlen(punctlist[i])-1]=='\n'){
						if (ispunct(punctlist[i][strlen(punctlist[i])-2]) && punctlist[i][strlen(punctlist[i])-3]==' '){
						temp=punctlist[i][strlen(punctlist[i])-2];
						punctlist[i][strlen(punctlist[i])-2]=' ';
						punctlist[i][strlen(punctlist[i])-3]=temp;
						}
					}
				}
			}
			if (ispunct(punctlist[i][strlen(punctlist[i])-1]) && punctlist[i][strlen(punctlist[i])-2]==' '){
				temp=punctlist[i][strlen(punctlist[i])-1];
				punctlist[i][strlen(punctlist[i])-1]=' ';
				punctlist[i][strlen(punctlist[i])-2]=temp;
			}
			if(strcmp(punctlist[i],". ")==0 || strcmp(punctlist[i],"? ")==0 || strcmp(punctlist[i],"! ")==0){
				wordlist[i+1][0]=toupper(wordlist[i+1][0]);
			}
		}
	}
}

void dictcheck(char **wordlist,char **punct){
	FILE *dictfile;
	FILE *newfile;
	char dictname[50],name[50],select;
	unsigned int i,towrite=0;
	i=0;

	puts("\nName of the dictionary file (no .txt in the end):");
	scanf("%s",dictname);
	strcat(dictname,".txt");
	dictfile=fopen(dictname,"a+");
	rewind(dictfile);
	while(wordlist[i]!=NULL){
		if (isindict(dictfile,wordlist[i])!=1){
			printf("The word \"%s\" is not in the dictionary what would you like to do?\n",wordlist[i]);
				puts("a) Replace the word in the file\nb) Add it to the dictionary\nc) Do nothing");
				select=getc(stdin);
				while(select!='a' && select!='b' && select!='c'){
					select=getc(stdin);
				}
				switch (select){
					case 'a':
	  					replace(wordlist[i]);
	  					towrite++;
						break;
					case 'b':
						addtodict(dictfile,wordlist[i]);
						break;
					case 'c':
						break;
				}
		}
		i++;
	}
	if(towrite>0){
		puts("How would you like the new file, with all the replaced words to be named? (no .txt in the end)");
		scanf("%s",name);
		strcat(name,".txt");
		newfile=fopen(name,"wt");
		for(i=0;wordlist[i]!=NULL;i++){
			fprintf(newfile,"%s",wordlist[i]);
			if (punct[i]!=NULL)
				fprintf(newfile,"%s",punct[i]);
		}
		fclose(newfile);
	}
}

void replace(char *word){
	char tempword[MAXCHARS];
	puts("Type the correct word: ");
	scanf("%s",tempword);
	word=realloc(word,(1+strlen(tempword))*sizeof(char));
	strcpy(word,tempword);
}

void addtodict(FILE *dictfile,char *word){
	fseek(dictfile,0,SEEK_END);
 	fprintf(dictfile,"\n%s",word);
	rewind(dictfile);
}

int isindict(FILE *dictfile,char *word){
	char tempstring[MAXCHARS],tempstringupper[MAXCHARS],stringcaps[MAXCHARS];
	int i;
	while(fgets(tempstring,MAXCHARS,dictfile)!=NULL){
		strcpy(tempstringupper,tempstring);
		strcpy(stringcaps,tempstring);
		tempstringupper[0]=toupper(tempstringupper[0]);
		for(i=0;i<strlen(stringcaps);i++){
			stringcaps[i]=toupper(stringcaps[i]);
		}
		if (!isalnum(tempstring[1])){
			if(strncmp(tempstring,word,1)==0){
				return 1;
			}
		}
		else{
			if(strncmp(word,tempstring,strlen(tempstring)-1)==0 || strncmp(word,tempstringupper,strlen(tempstringupper)-1)==0 || strncmp(word,stringcaps,strlen(stringcaps)-1)==0){
				rewind(dictfile);
				return 1;
			}
			strcpy(tempstringupper,"");
			strcpy(tempstring,"");
		}
	}
	rewind(dictfile);
	return 0;
}
