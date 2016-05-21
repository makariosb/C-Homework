#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

/**/

int getinput(char *,int *);
int nextgate(Gate,char *,int *);

int main() {
	char stemp[50];
	FILE *sourcefile=fopen("testinputs.txt","rt");
	int pos,inputs,outputs;
	Gate in1={getinput,NULL,NULL};
	Gate in2={getinput,NULL,NULL};
	Gate in3={getinput,NULL,NULL};
	Gate in4={getinput,NULL,NULL};
	Gate in5={getinput,NULL,NULL};
	Gate g1={AND,&in1,&in2};
	Gate g2={XOR,&in3,&in4};
	Gate g3={NAND,&g1,&g2};
	Gate g4={OR,&g3,&in5};

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
