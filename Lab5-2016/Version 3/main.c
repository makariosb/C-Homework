#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

/*
Λεκτικη περιγραφη: Επεκταση της λογικης της προηγουμενης Version. Διαβαζονται οι δυο πρωτες γραμμες, ετσι ωστε να καθοριστει ο αριθμος των εισοδων/εξοδων του κυλωματος και με βαση αυτες διαβαζοντας απο το αρχειο ελεγχουμε
το string που διαβαζει καθε φορα η fgets. Η μεταβλητη pos μετραει σε καθε σειρα που διαβαζουμε τη θεση του στοιχειου που πρεπει να διαβαστει απο το string, ετσι ωστε οταν κληθει η getinput να επιστρεψει τη σωστη τιμη.
Οι δηλωσεις των συναρτησεων των λογικων πυλων εχουν μπει στο αρχειο "definitions.h" για να ειναι πιο ευαναγνωστος ο κωδικας.


Βασικες διεργασιες:
α)Ανοιξε αρχειο.
β)Διαβασε αριθμο εισοδων και εξοδων του κυκλωματος.
γ)Διαβασε την επομενη σειρα και καλεσε τη συναρτηση nextgate.
δ)Δες αν η αναμενομενη εξοδος (της οποιας τη θεση στο string καθοριζεις μεσω του αριθμου των εισοδων και εξοδων) ειναι αυτη που επιστρεφει η nextgate
ε)Τυπωσε σχετικο μηνυμα αν εχει γινει λαθος.
ζ)Επανελαβε τα βηματα γ-ε μεχρι το τελος του αρχειου.

Αποθηκευμενες πληροφοριες:
	Ποσες εισοδους και ποσες εξοδους εχει το κυκλωμα μας
(αποθηκευονται σε μεταβλητη τυπου ακεραιου).
	Ποιες ειναι οι τιμες των εισοδων του κυκλωματος και ποιο το αναμενομενο αποτελεσμα με βαση αυτες
(αποθηκευονται σε πινακα χαρακτηρων και προσπελασσονται με μια ακεραια μεταβλητη).
	Ποια συναρτηση υλοποιει η καθε πυλη
	Ποιες ειναι οι 2 εισοδοι της πυλης
Οι δυο αυτες πληροφοριες περιεχονται στη δομη Gate,ενω οι απλες εισοδοι που λαμβανονται απο το αρχειο αναπαριστονται και αυτες με τη δομη αυτη, χωρις ορισματα εισοδων (NULL).
*/



int getinput(char *,int *);
typedef struct gate{
	int (*function)();
	struct gate *in1;
	struct gate *in2;
}Gate;
int nextgate(Gate,char *,int *);


int main() {
	char stemp[30];
	FILE *sourcefile=fopen("testinputs.txt","rt");
	int pos,inputs,outputs;
	Gate in1={getinput,NULL,NULL};
	Gate in2={getinput,NULL,NULL};
	Gate in3={getinput,NULL,NULL};
	Gate in4={getinput,NULL,NULL};
	Gate in5={getinput,NULL,NULL};
	Gate g1={and,&in1,&in2};
	Gate g2={xor,&in3,&in4};
	Gate g3={nand,&g1,&g2};
	Gate g4={or,&g3,&in5};
	
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
