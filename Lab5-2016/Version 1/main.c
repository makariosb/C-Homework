#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int or(int,int);
int and(int,int);
int not(int);
int nand(int,int);
int nor(int,int);
int xor(int,int);
int xnor(int,int);

int main() {
	return 0;
}

int or(int a,int b){
	if (a==0 && b==0){
		return 0;
	}
	else{
		return 1;
	}	
}

int and(int a,int b){
	if (a==1 && b==1){
		return 1;
	}
	else {
		return 0;
	}
}

int not(int a){
	if (a==0)
		return 1;
	else
		return 0;
}

int nand(int a,int b){
	return (not(and(a,b)));
}

int nor(int a,int b){
	return (not(or(a,b)));
}

int xor(int a,int b){
	if (a==b)
		return 0;
	else
		return 1;
}

int xnor(int a,int b){
	return not(xor(a,b));
}
