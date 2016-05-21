#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int OR(int,int);
int AND(int,int);
int NOT(int);
int NAND(int,int);
int NOR(int,int);
int XOR(int,int);
int XNOR(int,int);

typedef struct gate{
	int (*function)();
	struct gate *in1;
	struct gate *in2;
}Gate;


int OR(int a,int b){
	if (a==0 && b==0){
		return 0;
	}
	else{
		return 1;
	}
}

int AND(int a,int b){
	if (a==1 && b==1){
		return 1;
	}
	else {
		return 0;
	}
}

int NOT(int a){
	if (a==0)
		return 1;
	else
		return 0;
}

int NAND(int a,int b){
	return (NOT(AND(a,b)));
}

int NOR(int a,int b){
	return (NOT(OR(a,b)));
}

int XOR(int a,int b){
	if (a==b)
		return 0;
	else
		return 1;
}

int XNOR(int a,int b){
	return NOT(XOR(a,b));
}
