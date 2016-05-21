#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Λεκτικη περιγραφη: Το προγραμμα καλει αναδρομικα την συναρτηση nextgate μεχρι να παρει τις απαραιτητες εισοδους των πυλων
και επειτα υπολογιζει κι επιστρεφει την τιμη της συναρτησης της καθε δομης.

Βασικες διεργασιες:
α)Καλεσε την συναρτηση nextgate.
β)Αν η συναρτηση της δομης ειναι η getinput επεστρεψε το νουμερο της συναρτησης αυτης
γ)Αλλιως καλεσε την nextgate μεχρι να γεμισεις και τις δυο μεταβλητες της πυλης σου και επεστρεψε το αποτελεσμα της.

Αποθηκευμενες πληροφοριες:
	Ποια συναρτηση υλοποιει η καθε πυλη
	Ποιες ειναι οι 2 εισοδοι της πυλης
Οι δυο αυτες πληροφοριες περιεχονται στη δομη Gate,ενω οι απλες εισοδοι που δινονται απο το χρηστη αναπαριστονται και αυτες με τη δομη αυτη, χωρις ορισματα εισοδων (NULL).

*/


int or(int,int);
int and(int,int);
int not(int);
int nand(int,int);
int nor(int,int);
int xor(int,int);
int xnor(int,int);
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
	Gate g1={and,&in1,&in2};
	Gate g2={xor,&in3,&in4};
	Gate g3={nand,&g1,&g2};
	Gate g4={or,&g3,&in5};
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
