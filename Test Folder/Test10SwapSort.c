#include <stdio.h>

void clrscr() // Clear Screen
{
    system("@cls||clear");
}

void SelectionSort(int A[], int n)
{
int i, j, min, temp;

for (i = 0; i < n - 1; i++) {
    min = i; // min is the index of the lowest element

    for (j = i + 1; j < n; j++)
        if (A[min] < A[j]) // FOR STRUCTS; A[min].resTaskTYpe[inType]  < A[j].resTasktpe[inType]
        {
                for (k = 0; k < ctr; k++)
                {
                    if (nList[k] == i)
                    {
                        found = 1;
                    }
                }

                if (found == 0)
                {
                    min = j;

                    nList[ctr] = i;
                    ctr++;
                    exist = 1;
                }
                found = 0; // reset 
        }
                               
            }
            
// swap A[i] with A[min] 
if (i != min) {
    temp = A[i]; 
    A[i] = A[min]; 
    A[min] = temp;
        }
    }
}


void searchPokeByName(int nPkCtr, struct pokemonstruct pokemon[])
{
    int j,c,i,k;
    int ctr = 0; // to count the scanned pokemon
    int nList[150];
    int inNameLen; // length of key
    char inName[21]; 
    char sub[21]; //substring
    int sublen; // length of the array[word] in for loop no. 2
    int pos = 0; // THIS IS THE POSITION ITERATION PALA
    int exist = 0;
    int found = 0;

    printf("What do you want to find: ");
    scanf(" %[^\n]s", &inName);

    inNameLen = strlen(inName);

    for (i = 0; i < nPkCtr; i++){
        pos = 0; //position starts at word[0]
        sublen = strlen(pokemon[i].cPokeName); // declaring the length of the word

        for (j = 0; j <= sublen - inNameLen; j++){ //for loop ng position 
            c = 0;
		    while (c < inNameLen) { //substring function 
            sub[c] = pokemon[i].cPokeName[c+pos]; // B[i] is the array of words, pos ay yung position to start the copying
            c++; // iteration
   	        }
   		    sub[c] = '\0'; //while loop will stop at an empty index after the last character, put a \0 kasi needed to

            if (strcmp(sub, inName) == 0) { //if substring is found
                for (k = 0; k < ctr; k++)
                {
                    if (nList[k] == i)
                    {
                        found = 1;
                    }
                }

                if (found == 0)
                {
                    nList[ctr] = i;
                    ctr++;
                    exist = 1;
                }
                found = 0; // reset                                
            }
            pos++; // position will iterate until maubos yung letters. // for loop P ends then go to the next for loop i 
        }
	}

    if (exist == 1){ // for displaying the entries found
        for ( i = 0; i < ctr; i++)
        {
            displayEntry(nList[i], pokemon);
            printf("\n");
        }
            
    } 
    else {
        printf("Oops! This pokemon doesn't exist. \n\n");
    }
}


int main()
{
    clrscr();
    printf("Hello world \n");

    int A[5] = {1,2,3,4,5};
    int i;

    SelectionSort(A, 5);

    for ( i = 0; i < 5; i++)
    {
        printf("%d", A[i]);
    }
    






    return 0;
}
