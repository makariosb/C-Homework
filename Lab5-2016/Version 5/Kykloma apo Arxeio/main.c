#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#define BUFFERSIZE 100
/*Το προγραμμα δουλευει για κυκλωματα με 1 εξοδο.
	αριθμος εισοδων
	αριθμος εξοδων
	αριθμος πυλων
	ΣΥΝΑΡΤΗΣΗΠΥΛΗΣ εισοδος1 εισοδος2
	ΣΥΝΑΡΤΗΣΗΠΥΛΗΣ εισοδος1 εισοδος2
	.
	.
	.
	(εαν η εισοδος καποιας πυλης ειναι καποια αλλη πυλη, αναφερθειτε σε αυτη ως G# οπου # το νουμερο της πυλης που εχει ηδη δηλωθει, δηλ πχ αν θελετε να εχει ως εισοδο την πρωτη πυλη που εχετε ορισει γραψτε G1 κλπ.)
	(εαν η εισοδος καποιας πυλης ειναι καποια εισοδος του κυκλωματος, αναφερθειτε σε αυτη ως I# οπου # το νουμερο της εισοδου, δηλ πχ αν θελετε να εχει ως εισοδο την πρωτη εισοδο του κυκλωματος γραψτε Ι1 κλπ.)

*/

int getinput(char *,int *);
void getfile(FILE **);
int nextgate(Gate,char *,int *);
void makegate(Gateptr,char *,char*,char*,Gateptr *,Gateptr *);

int main() {
	char buffer[BUFFERSIZE],gatefunction[10],in1[10],in2[10];
	FILE *kykloma;
	FILE *sourcefile;
	Gateptr *inputlist=NULL,*gatelist=NULL;
	int i,pos,inputs,outputs,gatenum;

	/*Open the two text files*/
	getfile(&kykloma);
	puts("Please enter the name of the text file that describes the outputs of the circuit:");
	scanf("%s",buffer);
	sourcefile=fopen(buffer,"rt");
	strcpy(buffer,"");

	fscanf(kykloma,"%d\n%d\n%d\n",&inputs,&outputs,&gatenum);
	printf("Number of inputs: %d\nNumber of outputs: %d\nNumber of gates:%d\n",inputs,outputs,gatenum);

	inputlist=realloc(inputlist,inputs*sizeof(Gateptr)); /*allocate memory for the input structures pointer list*/
	for (i=0;i<inputs;i++){         /*Make blocks of memory and initialize them for each pointer of the list*/
		inputlist[i]=(Gateptr)malloc(sizeof(Gate));
		inputlist[i]->function=getinput;
		inputlist[i]->in1=NULL;
		inputlist[i]->in2=NULL;
	}
	
	gatelist=realloc(gatelist,gatenum*sizeof(Gateptr)); /*allocate memory for the gate structures pointer list*/
	for (i=0;i<gatenum;i++){         /*Make blocks of memory for each pointer of the list*/
		gatelist[i]=(Gateptr)malloc(sizeof(Gate));
	}
	i=0;
	while(fgets(buffer,BUFFERSIZE,kykloma)!=NULL){
		sscanf(buffer,"%s %s %s",gatefunction,in1,in2);
		makegate(gatelist[i++],gatefunction,in1,in2,inputlist,gatelist);
		strcpy(gatefunction,"");
		strcpy(in1,"");
		strcpy(in2,"");
	}
	
	strcpy(buffer,"");
	while ((fgets(buffer,sizeof(buffer),sourcefile))!=NULL){
		pos=0;
		if (nextgate(*gatelist[gatenum-1],buffer,&pos)!=(buffer[2*(inputs+outputs-1)]-'0')){
			printf("Did not calculate the correct output, refference string: %s",buffer);
		}
	}
	puts("Everything is correct!");
	return 0;
}

void getfile(FILE **kykloma){
	char temp[50];
	puts("Please enter the name of the text file that describes your circuit:");
	scanf("%s",temp);
	(*kykloma)=fopen(temp,"rt");
}

int getinput(char *stemp,int *posptr){
	int temp=stemp[(*posptr)*2]-'0';
	if ( (temp!=0) && (temp!=1))
		exit(1);
	else{
		(*posptr)++;
		return temp;
	}
}

void makegate(Gateptr currentgateptr,char *gatefunction,char *in1,char *in2,Gateptr *inputptrlist,Gateptr *gateptrlist){
		int (*functionlist[6])(int a, int b)={&OR,&AND,&NAND,&NOR,&XOR,&XNOR};
		int i;
		char functioncases[6][5]={"OR","AND","NAND","NOR","XOR","XNOR"};
		/*Fill function*/
		for (i=0;i<7;i++){
			if (strcmp(gatefunction,functioncases[i])==0){
				currentgateptr->function=functionlist[i];
				break;
			}
			if (strcmp(gatefunction,"NOT")==0){
				currentgateptr->function=&NOT;
			}
		}
		/*Fill input 1*/
		switch(in1[0]){
			case 'I':
				i=atoi(&in1[1]);
				currentgateptr->in1=inputptrlist[i-1];
				break;
			case 'G':
				i=atoi(&in1[1]);
				currentgateptr->in1=gateptrlist[i-1];
				break;
		}
		/*Fill input 2*/
		switch(in2[0]){
			case 'I':
				i=atoi(&in2[1]);
				currentgateptr->in2=inputptrlist[i-1];
				break;
			case 'G':
				i=atoi(&in2[1]);
				currentgateptr->in2=gateptrlist[i-1];
				break;
		}
}

int nextgate(Gate pyli,char *stemp,int *posptr){
	int result1=-1,result2=-1,final;
	if (pyli.in1!=NULL){
		result1=nextgate(*pyli.in1,stemp,posptr);
	}
	if (pyli.in2!=NULL){
		result2=nextgate(*pyli.in2,stemp,posptr);
	}
	if (pyli.function==getinput){
		return (*pyli.function)(stemp,posptr);
	}
	final=(*pyli.function)(result1,result2);
	return final;
}
