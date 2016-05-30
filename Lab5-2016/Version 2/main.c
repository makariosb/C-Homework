#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*������� ���������: �� ��������� ����� ���������� ��� ��������� nextgate ����� �� ����� ��� ����������� �������� ��� �����
��� ������ ���������� �� ���������� ��� ���� ��� ���������� ��� ���� �����.

������� ����������:
�)������ ��� ��������� nextgate.
�)�� � ��������� ��� ����� ����� � getinput ��������� �� ������� ��� ���������� �����
�)������ ������ ��� nextgate ����� �� �������� ��� ��� ��� ���������� ��� ����� ��� ��� ��������� �� ���������� ���.

������������� �����������:
	���� ��������� �������� � ���� ����
	����� ����� �� 2 ������� ��� �����
�� ��� ����� ����������� ����������� ��� ���� Gate,��� �� ����� ������� ��� �������� ��� �� ������ �������������� ��� ����� �� �� ���� ����, ����� �������� ������� (NULL).

*/


int OR(int,int);
int AND(int,int);
int NOT(int);
int NAND(int,int);
int NOR(int,int);
int XOR(int,int);
int XNOR(int,int);
int getinput(void);
typedef struct gate{
	int (*function)();
	struct gate *in1;
	struct gate *in2;
}Gate;
int nextgate(Gate);



int main() {
	Gate in1={getinput,NULL,NULL};
	Gate in2={getinput,NULL,NULL};
	Gate in3={getinput,NULL,NULL};
	Gate in4={getinput,NULL,NULL};
	Gate in5={getinput,NULL,NULL};
	Gate g1={AND,&in1,&in2};
	Gate g2={XOR,&in3,&in4};
	Gate g3={NAND,&g1,&g2};
	Gate g4={OR,&g3,&in5};
	printf("Final output: %d\n",nextgate(g4));
	
	return 0;
}

int getinput(void){
	int temp;
	printf("Please enter input:\n");
	scanf("%d",&temp);
	if (temp!=1 && temp!=0){
		exit(0);
	}
	else
		return temp;
}

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

int nextgate(Gate pyli){
	int result1=-1,result2=-1,final;
	if (pyli.in1!=NULL){
		result1=nextgate(*pyli.in1);
	}
	if (pyli.in2!=NULL){
		result2=nextgate(*pyli.in2);
	}
	if (pyli.function==getinput){
		return (*pyli.function)();
	}
	final=(*pyli.function)(result1,result2);
	return final;
}
