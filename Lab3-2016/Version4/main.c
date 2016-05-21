#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define PRINT 0
#define SAVE 1
#define MAXWORDS 1000
#define MAXCHARS 400
char makeselection(void);
void makewordlist(char wordlist[MAXWORDS][MAXCHARS],FILE *userfile);
void makepunctlist(char punct[MAXWORDS][MAXCHARS],FILE *userfile);
void analyze(char wordlist[MAXWORDS][MAXCHARS],char punct[MAXWORDS][MAXCHARS]);
void countwordschars(char wordlist[MAXWORDS][MAXCHARS]);
void countuniquewords(char wordlist[MAXWORDS][MAXCHARS]);
void makehistogram(char wordlist[MAXWORDS][MAXCHARS],int MODE);
void makeuniquewordlist(char wordlist[MAXWORDS][MAXCHARS],int MODE);
void syntaxcheck(char wordlist[MAXWORDS][MAXCHARS],char punctlist[MAXWORDS][MAXCHARS]);
void fixsyntax(char punctlist[MAXWORDS][MAXCHARS],char wordlist[MAXWORDS][MAXCHARS]);
void dictcheck(char wordlist[MAXWORDS][MAXCHARS],char punct[MAXWORDS][MAXCHARS]);
void replace(char *word);
void addtodict(FILE *dictfile,char *word);
int isindict(FILE *dictfile,char *word);
FILE *getfile(void);

int main(void) {
	char selection;
	char wordlist[MAXWORDS][MAXCHARS],punct[MAXWORDS][MAXCHARS];
	FILE *userfile;
	while ((selection=makeselection())!='s'){
		switch(selection){
			case 'a':
				userfile=getfile();
				makewordlist(wordlist,userfile);
				countwordschars(wordlist);
				fclose(userfile);
				break;
			case 'b':
				userfile=getfile();
				makewordlist(wordlist,userfile);
				countuniquewords(wordlist);
				fclose(userfile);
				break;
			case 'c':
				userfile=getfile();
				makewordlist(wordlist,userfile);
				makehistogram(wordlist,PRINT);
				makeuniquewordlist(wordlist,PRINT);
				fclose(userfile);
				break;
			case 'd':
				userfile=getfile();
				makewordlist(wordlist,userfile);
				makehistogram(wordlist,SAVE);
				makeuniquewordlist(wordlist,SAVE);
				fclose(userfile);
				break;
			case 'e':
				analyze(wordlist,punct);
				syntaxcheck(wordlist,punct);
				break;
			case 'f':
				analyze(wordlist,punct);
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

void makewordlist(char words[MAXWORDS][MAXCHARS],FILE *userfile){
	char string[MAXCHARS],temp,last;
	int i=0,j;
	for(j=0;j<MAXWORDS;strcpy(words[j++],"")); 		/*CLEAR WORDLIST*/
	j=0;
	
	while((temp=fgetc(userfile))!=EOF){
		if (isalnum(temp)){
			string[i]=temp;
			i++;
		}
		else{
			if (isalnum(last)){
				string[i]='\0';
				strcpy(words[j++],string);
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
		strcpy(words[j],string);
	}
	rewind(userfile);
}

void analyze(char wordlist[MAXWORDS][MAXCHARS],char punct[MAXWORDS][MAXCHARS]){
	char string[MAXCHARS],temp,last;
	FILE *userfile=getfile();
	int i=0,j;
	for(j=0;j<MAXWORDS;strcpy(punct[j++],"")); 		/*CLEAR PUNCTLIST*/
	j=0;
	makewordlist(wordlist,userfile);
	while((temp=fgetc(userfile))!=EOF){
		if (!isalnum(temp)){
			string[i]=temp;
			i++;
		}
		else{
			if (!isalnum(last)){
				string[i]='\0';
				strcpy(punct[j++],string);
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
		strcpy(punct[j],string);
	}
	fclose(userfile);
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
	while (strcmp(wordlist[i],"")!=0 || i>MAXWORDS){
		for (j=0;strcmp(unique[j],"")!=0 && j<MAXWORDS;j++){
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
	for(j=0;j<MAXWORDS;strcpy(unique[j++],""));         /*CLEAR THE ARRAY*/
}

void makehistogram(char wordlist[MAXWORDS][MAXCHARS],int MODE){
	int i=0;
	char outputname[MAXCHARS];
	int lens[MAXCHARS]={0};
	FILE *histogram;
	while (strcmp(wordlist[i],"")!=0){
		lens[strlen(wordlist[i])]++;
		i++;
	}
	switch (MODE){
		case PRINT:
			printf("\nWord Length Histogram : \n");
			for (i=0;i<MAXCHARS;i++){
				if (lens[i]!=0){
					printf("%s%d%s%d\n","The number of words with ",i," characters is: ",lens[i]);
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
					fprintf(histogram,"%s%d%s%d\n","The number of words with ",i," characters is: ",lens[i]);
				}
			}
			fprintf(histogram,"\n");
			fclose(histogram);
			puts("Done.");
			break;
	}
}

void makeuniquewordlist(char wordlist[MAXWORDS][MAXCHARS],int MODE){
	char unique[MAXWORDS][MAXCHARS],fname[MAXCHARS];
	int i,j,pos=0,valid=1;
	FILE *wlist;
	for(i=0;i<MAXWORDS;strcpy(unique[i++],""));

	for (i=0;strcmp(wordlist[i],"")!=0;i++){
		for(j=0;strcmp(unique[j],"")!=0;j++){
			if(strcmp(unique[j],wordlist[i])==0){
				valid=0;
			}
		}
		switch(valid){
			case 0:
				valid=1;
				continue;
			case 1:
				strcpy(unique[pos++],wordlist[i]);
				continue;
		}
	}
	switch(MODE){
		case PRINT:
			puts("List of unique words:");
			for(i=0;strcmp(unique[i],"")!=0 && i<MAXWORDS;i++){
				printf("#%2d  %s\n",i+1,unique[i]);
			}
			break;
		case SAVE:
			puts("What would you like the wordlist file to be called? (no .txt in the end):");
			scanf("%s",fname);
			wlist=fopen(strcat(fname,".txt"),"wt");
			fprintf(wlist,"Catalogue of unique words:\n");
			for(i=0;strcmp(unique[i],"")!=0 && i<MAXWORDS;i++){
				fprintf(wlist,"#%2d  %s\n",i+1,unique[i]);
			}
			fclose(wlist);
			puts("Done.");
			break;
	}
}

void syntaxcheck(char wordlist[MAXWORDS][MAXCHARS],char punctlist[MAXWORDS][MAXCHARS]){
	char textstream[MAXCHARS];
	FILE *fixedfile;
	int i=0,j;
	puts("Please enter the name of the file to be created with the syntax checked text( no .txt in the end):");
	scanf("%s",textstream);
	fixedfile=fopen(strcat(textstream,".txt"),"wt");
	fixsyntax(punctlist,wordlist);
	for(i=0;i<MAXWORDS;i++){
		fprintf(fixedfile,"%s",wordlist[i]);
		fprintf(fixedfile,"%s",punctlist[i]);
	}
	fclose(fixedfile);
	puts("Done.");
}

void fixsyntax(char punctlist[MAXWORDS][MAXCHARS],char wordlist[MAXWORDS][MAXCHARS]){
	int i,j=0;
	char string[MAXCHARS],temp;
	for (i=0;strcmp(punctlist[i],"")!=0 && i<MAXCHARS;i++){
		if (strlen(punctlist[i])>1){
			if (ispunct(punctlist[i][1]) && punctlist[i][0]==' ')
				strcpy(punctlist[i],&punctlist[i][1]);
			if (punctlist[i][strlen(punctlist[i])-1]=='\n'){
				if (ispunct(punctlist[i][strlen(punctlist[i])-2]) && punctlist[i][strlen(punctlist[i])-3]==' '){
				temp=punctlist[i][strlen(punctlist[i])-2];
				punctlist[i][strlen(punctlist[i])-2]=' ';
				punctlist[i][strlen(punctlist[i])-3]=temp;
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

void dictcheck(char wordlist[MAXWORDS][MAXCHARS],char punct[MAXWORDS][MAXCHARS]){
	FILE *dictfile;
	FILE *newfile;
	char dictname[50],name[50],select;
	char tempwordlist[MAXWORDS][MAXCHARS];
	int i,towrite=0;
	for(i=0;i<MAXWORDS;strcpy(tempwordlist[i++],""));  /*Clear wordlist array*/
	i=0;

	puts("\nName of the dictionary file (no .txt):");
	scanf("%s",dictname);
	strcat(dictname,".txt");
	dictfile=fopen(dictname,"a+");
	rewind(dictfile);
	while(strcmp(wordlist[i],"")!=0 && i<MAXWORDS){
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
		for(i=0;i<MAXWORDS;i++){
			fprintf(newfile,"%s",wordlist[i]);
			fprintf(newfile,"%s",punct[i]);
		}
		fclose(newfile);
	}
}

void replace(char *word){
	char tempword[MAXCHARS];
	int i,count;
	puts("Type the correct word: ");
	scanf("%s",tempword);
	strcpy(word,"");
	strcpy(word,tempword);
}

void addtodict(FILE *dictfile,char *word){
	fseek(dictfile,0,SEEK_END);
 	fprintf(dictfile,"\n%s",word);
	rewind(dictfile);
}

int isindict(FILE *dictfile,char *word){
	char tempstring[MAXCHARS],tempstringupper[MAXCHARS];
	while(fgets(tempstring,MAXCHARS,dictfile)!=NULL){
		strcpy(tempstringupper,tempstring);
		tempstringupper[0]=toupper(tempstringupper[0]);
		if (!isalnum(tempstring[1])){
			if(strncmp(tempstring,word,1)==0){
				return 1;
			}
		}
		else{
			if(strncmp(word,tempstring,strlen(tempstring)-1)==0 || strncmp(word,tempstringupper,strlen(tempstringupper)-1)==0){
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
