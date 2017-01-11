#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	Η γενικη ιδεα του αλγοριθμου ειναι:
	
	διετρεξε πινακα
		αν συναντησεις συμβολο:
			κοψε λεξη(αρχη, τελος)
			βαλε στη λιστας
			αν κι ο επομενος χαρακτηρας συμβολο
				προχωρα τον iterator διατρεξης του πινακα
			βαλε τον iterator διατρεξης της λεξης ως iterator αρχης της επομενης λεξης
		συνεχισε την διατρεξη μεχρι τελος της λεξης
	
	εκτυπωσε λιστα
	
	-Μακαριος
*/


//κοβει και βαζει στο πρωτο ορισμα το κομματι τις λεξεις απο το σημειο start μεχρι το end
void cut(char *output,int start, int end)
{
	char word[]="abc defg| hi";
	char tempword[10];
	int i,j=0;
	
	for(i=start ; i<=end ; i++)
	{
		tempword[j]=word[i];
		j++;
		
	}
	tempword[j]='\0';
	
    strcpy(output,tempword);
	
	return;
}




int main(){
    char word[]="abc defg| hi\0";  //χωριζω λεξη με βαση space και |
    char list[3][10];
    int i,j=0,start=0;   //το i χρησιμοποιειται σαν iterator, το j σαν iterator της λιστας και το start για τον αλγοριθμο
    
    for(i=0 ; word[i]!='\0' ; i++)
    {
		if(word[i]==' ' || word[i]=='|')//εδω τσεκαρεις τους χαρακτηρες που θες
		{
			cut(list[j++],start,i-1); //βλεπε πανω
			if(word[i+1]==' ' || word[i+1]=='|')// εαν ειναι 2 χαρακτηρες στη σειρα (μπορεις να το γενικευσεις ευκολα με μια while)
			{
				i+=2;
			}
			else //αν βρει απλα εναν χαρακτηρα
			{
				i++;
			}
			start=i;
		}
	}
	cut(list[j],start,i-1);//για να βαλει την τελευταια λεξη
	
	for (i=0 ; i<3 ; i++)//εκτυπωση της λιστας στην οθονη
	{
        printf("%s\n",list[i]);
    }
	system("PAUSE");
    return 0;   
}
