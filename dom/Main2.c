#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define ENTRYMAX 150

struct pokemonstruct
{
    int entry;
    char cPokeName[21];
    char cPokeType;
    char cPokeDesc[51];
    int seen;
    int defeated;
};

// miscellaneous functions
void clrscr(); // Clear Screen

// essential functions
void menu();
int addEntry(int i, struct pokemonstruct pokemon[]);
int Search(char key[], int nPkCtr, struct pokemonstruct pokemon[]);
int deleteEntry(int nPkCtr, struct pokemonstruct pokemon[]);
void modifyEntry(int nPkCtr, struct pokemonstruct pokemon[]);
void displayEntry(int i, struct pokemonstruct pokemon[]);
void displayAllEntries(int nPkCtr, struct pokemonstruct pokemon[]);
void searchPokeByName(int nPkCtr, struct pokemonstruct pokemon[]);
void searchPokeByType(int nPkCtr, struct pokemonstruct pokemon[]);

// research pokemon functions

//main
int main()
{
    struct pokemonstruct pokemon[ENTRYMAX];
    int nPkCtr = 0; // Counter of how many pokemon are indexed && current index that has no value, will be utilized for addEntry
    char cDc; // gets the Char input of user when prompted for such
    char cExit = 'N';
    clrscr();
    
        do
        {
            menu(); // Display Menu
            cDc = getch();  
            printf("\n");

            switch (cDc) // switch to corresponding function of cDc
            {
            case 'a': // Add Entry                
                nPkCtr = addEntry(nPkCtr, pokemon);
                break;

            case 'm': // Modify Entry
                printf("Total no. of Entries: %d", nPkCtr);
                // hindi ba much better if before they modify, we present them all entries like we call the display all entries function?, same for deleteentry
                modifyEntry(nPkCtr, pokemon);                
                break;

            case 'd': // Delete Entry
                printf("Total no. of Entries: %d", nPkCtr);
                nPkCtr = deleteEntry(nPkCtr, pokemon);
                // nPkCtr--;
                break;

            case 'l': // Display All Entries
                displayAllEntries(nPkCtr, pokemon);
                break;

            case 's': // Search Pokemon
                searchPokeByName(nPkCtr, pokemon);
                break;

            case 'p': // Search Pokemon by type
                searchPokeByType(nPkCtr, pokemon);
                break;

            case 'r': // Research Tasks            
                break;
            case 'e': // Export
                break;
            case 'i': // Import
                break;

            case 'x':
                printf("Do you want to exit the PokeDex?\n");
                printf("[Y] Yes\n");
                printf("[N] No\n");
                cExit = getch(); 
                break;

            // default:                
            //     printf ("Do you want to exit the Pokedex? [Y]Yes [N]No\n" );
            //     cExit = getch(); // asks the user to reloop, if no, loop breaks, funcion ends also here
            //     printf("\n");
            //     break;
            }
        } while (cExit == 'N' || cExit == 'n');

        printf("\n");

    // for (i=0;i<1; ++i)
    // {
    //     addEntry(i);
    // }
    // printf("\n");

    // for ( i = 0; i < 1; i++)
    // {
    //     displayEntry(i);
    // }
    // printf("\n");

    // modifyEntry(0);

    return 0;
}

void clrscr() // Clear Screen
{
    system("@cls||clear"); //implicit declaration, needs to be consulted for
}

void menu()
{
    printf("\nWhat do you want to accomplish?\n");
    printf("[A] Add Entry \n");
    printf("[M] Modify Entry \n");
    printf("[D] Delete Entry \n");
    printf("[L] Display All Entries \n");
    printf("[S] Search Pokemon \n");
    printf("[P] Search Pokemon by Type\n");
    printf("[R] Research tasks \n");
    printf("[E] Export \n");
    printf("[I] Import \n");
    printf("[X] Exit \n");
}

int addEntry(int i, struct pokemonstruct pokemon[])
{
    char inName[21];

    printf("Enter pokemon name: "); 
    scanf(" %[^\n]s", &inName);
        // fgets(inName, 21, stdin); // for getting and storing the pokemon name
        // inName[strcspn(inName, "\n")] = 0; // clears the \n stored in the string coming from the fgets function

    if (Search(inName, i, pokemon) == 1)
    {
        printf("Oops! This pokemon already exists. \n\n");
    } 
    else
    {
        pokemon[i].entry = i + 1; // initialize entry number based from the array no.
        printf ("\nFor Entry no. %d, \n", pokemon[i].entry);

        strcpy(pokemon[i].cPokeName, inName);
        printf("Name: %s \n", pokemon[i].cPokeName);

        do
        {
            printf ("Is the Pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric");
            pokemon[i].cPokeType = getch(); //getch nalang so that it's clean and walang further bugs na magkameron, altho stored char is the small letter
            printf("\n");

            if (pokemon[i].cPokeType == 'w') {
                printf("Pokemon Type: Water\n");
            }
            else if (pokemon[i].cPokeType == 'f') {
                printf("Pokemon Type: Fire\n");
            }
            else if (pokemon[i].cPokeType == 'g') {
                printf("Pokemon Type: Grass\n");
            }
            else if (pokemon[i].cPokeType == 'e') {
                printf("Pokemon Type: Electric\n");
            }
        } while (pokemon[i].cPokeType != 'w' && pokemon[i].cPokeType != 'f' && pokemon[i].cPokeType != 'g' && pokemon[i].cPokeType != 'e');
                    
        printf("Description: ");
        scanf(" %[^\n]s", pokemon[i].cPokeDesc);
        // fgets(pokemon[i].cPokeDesc,51, stdin); //for getting and storing the pokemon description
        // pokemon[i].cPokeDesc[strcspn(pokemon[i].cPokeDesc, "\n")] = 0; // clears the \n stored in the string galing sa fgets function
        pokemon[i].seen = 0;
        pokemon[i].defeated = 0;
        //Still needs some verification
        i++;
        }

    return i;
}

int deleteEntry(int nPkCtr, struct pokemonstruct pokemon[]) // Delete Entry
{
    int i,j; // i is for the actual index, j for the for loop
    char cDec; // Decision;
    
    if (nPkCtr == 0)
    {
        printf("\nThere are no entries to be deleted from.\n");
    }
    else
    {
        do //for verification kung yung ineedit ay within the possible range
        {
            printf("\nWhat entry do you want to delete: ");
            scanf(" %d", &i); // BUGGGGED NEED TO REMOVE THE NEWLINE CHARACTER;
        
            if (i > nPkCtr || i <= 0 ) //saying na mali if more than the maximum entry ang ininput || 0 or less
            {
                printf("Oops! This entry does not exist.");
                // getch();
            }
        } while (i > nPkCtr || i <= 0 ); // this shit will happen until valid number is inputted

        do
        {
            printf("You are deleting: \n");
            displayEntry(i-1, pokemon); // display the entry for correction to the user
            printf("\n");
            printf("Press Any Key to Confirm the Deletion of Entry #%d\n", i); // verification
            printf("[Y] Yes\n");
            printf("[N] No\n");
            cDec = getch();

            printf("YOU ENTERED: %c", cDec);

            i = i-1;

            if (cDec == 'y' || cDec == 'Y')
            {
                nPkCtr--;
                for (j = i; j < nPkCtr; j++) // LOGICAL WARNING!!!!!! DI MAWAWALA TEMPORARILY ANG LAST ENTRY UNLESS ADD ENTRY ULIT
                {
                    strcpy (pokemon[j].cPokeName, pokemon[j+1].cPokeName);
                    pokemon[j].cPokeType = pokemon[j+1].cPokeType;
                    strcpy (pokemon[j].cPokeDesc, pokemon[j+1].cPokeDesc);
                    pokemon[i].seen = pokemon[i+1].seen;
                    pokemon[i].defeated = pokemon[i+1].defeated;
                }
                printf("\nEntry Deleted.\n");
                printf("Pokedex Readjusted\n");
                printf("\n~~PRESS ANY KEY TO CONTINUE~~\n");
                getch();
            }
            else if (cDec == 'n' || cDec == 'N')
            {
                // for (j = i-1; j < nPkCtr; j++)
                // {
                //     strcpy (pokemon[j].cPokeName, pokemon[j].cPokeName);
                //     pokemon[j].cPokeType = pokemon[j].cPokeType;
                //     strcpy (pokemon[j].cPokeDesc, pokemon[j].cPokeDesc);
                // }
                printf("\nEntry Sustained.\n");
                printf("\n~~PRESS ANY KEY TO CONTINUE~~\n");
                getch();
            }
         } while (cDec != 'y' && cDec != 'n' && cDec != 'Y' && cDec != 'N');
    }
    
    return nPkCtr;
}

void modifyEntry(int nPkCtr, struct pokemonstruct pokemon[])
{
    int i; // for identifying what entry to modify
    char choice;
    char modify = 'Y';

    if (nPkCtr == 0)
    {
        printf("\nThere are no entries to be modified from.\n");
    }
    else
    {
        do
        {
            printf("\nWhat entry do you want to modify: ");
            scanf(" %d", &i); // BUGGGGED NEED TO REMOVE THE NEWLINE CHARACTER;
        
            if (i > nPkCtr || i <= 0 )
            {
                printf("\nOops! This entry does not exist.");
                // getch();
            }
        } while (i > nPkCtr || i <= 0 );

        i = i-1; // this is the actual index.

        printf ("\nYou are modifying this entry\n"); // These prints the basic info
        displayEntry(i, pokemon);
        printf("\n");
            
        do
        {
            printf("What do you want to modify?\n"); // question
            printf("[N] Name\n");
            printf("[T] Type\n");
            printf("[D] Description\n");
            printf("[X] Exit\n");
            choice = getch(); // gets anong gusto gawin ng user
            printf("\n");

            switch (choice) //dito mangyayari yung modification
            {
                case 'n':
                    strcpy(pokemon[i].cPokeName, "");
                    printf ("Enter New Pokemon Name: ");
                    // fgets(pokemon[i].cPokeName, 21, stdin); //for getting and storing the pokemon name
                    scanf(" %[^\n]s", &pokemon[i].cPokeName);

                    // pokemon[i].cPokeName[strcspn(pokemon[i].cPokeName, "\n")] = 0; //removes the \n inside the string

                    printf("Edited Pokemon Name: %s\n", pokemon[i].cPokeName); //for verificcation, subject for removal
                    printf ("\nDo you want to modify more?\n");
                    printf("[Y] Yes\n"); 
                    printf("[X] Exit\n");
                    modify = getch(); // asks the user for more modification and to reloop or not
                    break;

                case 't':
                    do
                    {
                        printf ("Is the Pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric"); 
                        pokemon[i].cPokeType = getch(); //getch nalang so that it's clean and walang further bugs na magkameron, altho stored char is the small letter
                        printf("\n");

                        if (pokemon[i].cPokeType == 'w') {
                            printf("Pokemon Type: Water\n"); // for verification, subject for removal
                        }
                        else if (pokemon[i].cPokeType == 'f') {
                            printf("Pokemon Type: Fire\n");
                        }
                        else if (pokemon[i].cPokeType == 'g') {
                            printf("Pokemon Type: Grass\n");
                        }
                        else if (pokemon[i].cPokeType == 'e') {
                            printf("Pokemon Type: Electric\n");
                        }
                    } while (pokemon[i].cPokeType != 'w' && pokemon[i].cPokeType != 'f' && pokemon[i].cPokeType != 'g' && pokemon[i].cPokeType != 'e');
                    
                    printf ("\nDo you want to modify more?\n");
                    printf("[Y] Yes\n"); 
                    printf("[X] Exit\n");
                    modify = getch(); // asks the user for more modification and to reloop or not
                    break;

                case 'd':
                    printf("Enter New Description: ");
                    scanf(" %[^\n]s", &pokemon[i].cPokeDesc);
                    // fgets(pokemon[i].cPokeDesc,51, stdin); //for getting and storing the pokemon description
                    // pokemon[i].cPokeName[strcspn(pokemon[i].cPokeName, "\n")] = 0; //removes the \n inside the string
                    printf("Edited Description: %s\n", pokemon[i].cPokeDesc); // for verification, subject for removal
                    printf ("\nDo you want to modify more?\n");
                    printf("[Y] Yes\n"); 
                    printf("[X] Exit\n");
                    modify = getch(); // asks the user for more modification and to reloop or not
                    break;

                case 'x':
                    modify = 'x';
                    break;
        
                // default:
                //     displayEntry(i); //shows entry para macheck ng user for correction
                //     printf ("Do you want further edits? [Y]Yes [N]No");
                //     modify = getch(); // asks the user to reloop, if no, loop breaks, funcion ends also here
                //     printf("\n");
                //     break;
            }
        } while (modify == 'y' || modify == 'Y');
        printf("\n");
    }
}

void displayEntry(int i, struct pokemonstruct pokemon[])
{
        printf("\nEntry No. %d\n", pokemon[i].entry); //prints entry no.
        printf("Pokemon Name: %s\n", pokemon[i].cPokeName); //prints Pokemon Name

        if (pokemon[i].cPokeType == 'w') { 
            printf("Pokemon Type: Water\n");
        }
        else if (pokemon[i].cPokeType == 'f') {
            printf("Pokemon Type: Fire\n");
        }
        else if (pokemon[i].cPokeType == 'g') {
            printf("Pokemon Type: Grass\n");
        }
        else if (pokemon[i].cPokeType == 'e') {
            printf("Pokemon Type: Electric\n");
        }

        printf("Description: %s\n", pokemon[i].cPokeDesc); //prints Pokermon Decription
}

void displayAllEntries(int nPkCtr, struct pokemonstruct pokemon[])
{
    int i;

    if (nPkCtr == 0) {
        printf("\n**NO ENTRIES FOUND**\n");
    }
    else {
        printf("\n// DISPLAYING ALL ENTRIES //\n");
        for ( i = 0; i < nPkCtr; i++)
        {   
            displayEntry(i, pokemon);
        }
        printf("\n~~PRESS ANY KEY TO CONTINUE~~\n");
        getch();
    }
}

int Search(char key[], int nPkCtr, struct pokemonstruct pokemon[]) //search function, strings only
{
   int i;
   int found = -1;

   for (i = 0; i < nPkCtr; i++)
   {
      if (strcmp(key, pokemon[i].cPokeName) == 0)
         {
            found = 1;
         }
   }
   
   if (found == 1)
   {
      return 1;
   } else
   {
      return -1;
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

void searchPokeByType(int nPkCtr, struct pokemonstruct pokemon[])
{
    int i = 0;
    int exist = 0;
    char inType;

    do {
        printf ("What Pokemon Type are you searching for?\n");
        printf("[W] Water\n");
        printf("[F] Fire\n");
        printf("[G] Grass\n");
        printf("[E] Electric\n");

        inType = getch(); //getch nalang so that it's clean and walang further bugs na magkameron, altho stored char is the small letter
    } while (inType != 'w' && inType != 'f' && inType != 'g' && inType != 'e');
    
    for (i = 0; i < nPkCtr; i++) 
    {
        if(inType == pokemon[i].cPokeType) 
        {
            displayEntry(i, pokemon);
            printf("\n");
            exist = 1;
        }

    }
    
    if (exist == 0) 
    {
        printf("No Pokemon of this type was found in this Pokedex.\n\n");
    }
}
