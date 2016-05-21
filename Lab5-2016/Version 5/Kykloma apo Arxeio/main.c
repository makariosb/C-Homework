#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

/*Το προγραμμα δουλευει για κυκλωματα με 1 εξοδο.*/

int getinput(char *,int *);
void getfile(FILE **);
int nextgate(Gate,char *,int *);

int main() {
	char stemp[50];
	FILE *kykloma;
	FILE *sourcefile=fopen("testinputs.txt","rt");
	int pos,inputs,outputs;

	getfile(&kykloma);
	fscanf(sourcefile,"%d\n%d\n",&inputs,&outputs);
	printf("Number of inputs: %d\nNumber of outputs: %d\n",inputs,outputs);
	while ((fgets(stemp,sizeof(stemp),sourcefile))!=NULL){
		pos=0;
		if (nextgate(g4,stemp,&pos)!=(stemp[2*(inputs+outputs-1)]-'0')){
			printf("Did not calculate the correct output, refference string: %s",stemp);
		}
	}
	puts("Everything is correct!");
	return 0;
}

void getfile(FILE **kykloma){
	char temp[50];
	puts("Please enter the name of the binary file that describes your circuit:");
	scanf("%s",temp);
	(*kykloma)=fopen(temp,"rb");
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
