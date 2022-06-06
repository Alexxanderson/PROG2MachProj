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
    int nResearchType[2];
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

//NEW FUNCTIONS
void reviewResearchPerPokemon(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr);
void reviewResearchPerType(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr);
void updateResearchTask(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr);
void researchDisplayAllEntries(int nPkCtr, struct pokemonstruct pokemon[],  int nRsrchCtr);
void researchDisplayEntry(int i, struct pokemonstruct pokemon[],  int nRsrchCtr);
void displayName(int i, struct pokemonstruct pokemon[]);
void displayResTaskType(int nRsrchCtr);
void displayEntryByResTaskType(int i, struct pokemonstruct pokemon[],  int nRsrchCtr, int inType);
void updateReseachTask(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr);

//main
int main()
{
    struct pokemonstruct pokemon[ENTRYMAX];
    int nPkCtr = 0; // Counter of how many pokemon are indexed && current index that has no value, will be utilized for addEntry
    int nRsrchCtr = 2; // Counter of the Research Tasks Types, for the bonus pointss
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
            case 'u': // Update Research Task    
                updateReseachTask(nPkCtr, pokemon, nRsrchCtr);  
                break;
            case 'r': // Review Research per Pokemon; Search Research by Name
                reviewResearchPerPokemon(nPkCtr, pokemon, nRsrchCtr);
                break;
            case 't': // Review Research per Task Type; Search Research By Type
                reviewResearchPerType(nPkCtr, pokemon, nRsrchCtr);
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

            }
        } while (cExit == 'N' || cExit == 'n');

        printf("\n");

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
    printf("[R] Review Research tasks per Pokemon\n");
    printf("[T] Review Research tasks per Type\n");
    printf("[U] update Research tasks \n");
    printf("[E] Export \n");
    printf("[I] Import \n");
    printf("[X] Exit \n");
}

int addEntry(int i, struct pokemonstruct pokemon[])
{
    char inName[21];

    if (i == 150)
    {
       printf("Maximum entries reached. \n\n");
    } else {

    printf("Enter pokemon name: "); 
    scanf(" %[^\n]s", &inName);

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
        
        // pokemon[i].seen = 0; // STILL SUBJECT TO CHANGE
        // pokemon[i].defeated = 0;
        pokemon[i].nResearchType[0] = 0;
        pokemon[i].nResearchType[1] = 0; 

        i++;
        }
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
            scanf(" %d", &i);
        
            if (i > nPkCtr || i <= 0 ) //saying na mali if more than the maximum entry ang ininput || 0 or less
            {
                printf("Oops! This entry does not exist.");
            }
        } while (i > nPkCtr || i <= 0 ); // this will happen until valid number is inputted

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
                for (j = i; j < nPkCtr; j++)
                {
                    strcpy (pokemon[j].cPokeName, pokemon[j+1].cPokeName);
                    pokemon[j].cPokeType = pokemon[j+1].cPokeType;
                    strcpy (pokemon[j].cPokeDesc, pokemon[j+1].cPokeDesc);
                    // pokemon[i].seen = pokemon[i+1].seen;
                    // pokemon[i].defeated = pokemon[i+1].defeated;
                    pokemon[i].nResearchType[0] = pokemon[i+1].nResearchType[0];
                    pokemon[i].nResearchType[1] = pokemon[i+1].nResearchType[1];
                }
                nPkCtr--;  
                printf("\nEntry Deleted.\n");
                printf("Pokedex Readjusted\n");
                printf("\n~~PRESS ANY KEY TO CONTINUE~~\n");
                getch();
            }
            else if (cDec == 'n' || cDec == 'N')
            {
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
            scanf(" %d", &i);
        
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
            choice = getch(); // anong gusto gawin ng user
            printf("\n");

            switch (choice) //dito mangyayari yung modification
            {
                case 'n':
                    strcpy(pokemon[i].cPokeName, "");
                    printf ("Enter New Pokemon Name: ");
                    scanf(" %[^\n]s", &pokemon[i].cPokeName);

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
                    printf("Edited Description: %s\n", pokemon[i].cPokeDesc); // for verification, subject for removal
                    printf ("\nDo you want to modify more?\n");
                    printf("[Y] Yes\n"); 
                    printf("[X] Exit\n");
                    modify = getch(); // asks the user for more modification and to reloop or not
                    break;

                case 'x':
                    modify = 'x';
                    break;
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

void researchDisplayAllEntries(int nPkCtr, struct pokemonstruct pokemon[],  int nRsrchCtr) //DISAPLYING ALL ENTRIES WITH NAME ONLY
{
    int i; // for loop

    if (nPkCtr == 0) {
        printf("\n**NO ENTRIES FOUND**\n"); // REPEATING SA reviewResearchPerPokemon NA FUNCTION
    }
    else {
        printf("\n// DISPLAYING ALL ENTRIES //\n");
        for ( i = 0; i < nPkCtr; i++)
        {   
            displayName(i, pokemon); // display name function
        }
        
    }
}

void displayName(int i, struct pokemonstruct pokemon[]) //FOR DISPLAYING NAME ONLY
{
        printf("\nEntry No. %d\n", pokemon[i].entry); //prints entry no.
        printf("Pokemon Name: %s\n\n", pokemon[i].cPokeName); //prints Pokemon Name
}

void researchDisplayEntry(int i, struct pokemonstruct pokemon[],  int nRsrchCtr) // FOR DISPLAYING ENTRY WITH ALL THE RESEARCH TASKS
{
    int j;
        printf("\nEntry No. %d\n", pokemon[i].entry); //prints entry no.
        printf("Pokemon Name: %s\n", pokemon[i].cPokeName); //prints Pokemon Name

        for (j = 0; j < nRsrchCtr; j++) //for looop for the bonus points
        {
            switch (j)
            {
            case 0:
                printf("Seen: %d \n",  pokemon[i].nResearchType[0]);
                break;
            case 1:
                printf("Defeated: %d \n",  pokemon[i].nResearchType[1]);
                break;
            default:
                break;
            }
        }
}

void reviewResearchPerPokemon(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr) // Review Research Task per Pokemon
{
    researchDisplayAllEntries(nPkCtr,pokemon, nRsrchCtr); //Displaying all Pokemon Entries with names lang

    int entry; // entry is for the entry to find
    
    if (nPkCtr == 0)
    {
        printf("\nThere are no entries.\n"); // REPEATING SA researchDisplayAllEntries NA FUNCTIONS
    }
    else
    {
        do //for verification kung yung ineedit ay within the possible range
        {
            printf("\nWhat entry do you want to find: ");
            scanf(" %d", &entry);
        
            if (entry > nPkCtr || entry <= 0 ) //saying na mali if more than the maximum entry ang ininput || 0 or less
            {
                printf("Oops! This entry does not exist.");
            }
        } while (entry > nPkCtr || entry <= 0 ); // this will happen until valid number is inputted

            printf("You are finding: \n");
            researchDisplayEntry(entry-1, pokemon, nRsrchCtr); // display the entry for correction to the user
            printf("\n");

            getch(); // UI, stop lang
    }
}

void displayResTaskType(int nRsrchCtr) // Display the lists of Research Task Types
{
    int j;

        for (j = 0; j < nRsrchCtr; j++)
        {
            switch (j)
            {
            case 0:
                printf("[1] Seen \n");
                break;
            case 1:
                printf("[2] Defeated \n");
                break;
            default:
                break;
            }
        }
}

void reviewResearchPerType(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr) // Review Research Task per Task Type
{
    int i = 0;
    int exist = 0;
    int inType = 0;

    do {
        printf ("What Research Type are you searching for?\n");
        displayResTaskType(nRsrchCtr); // For displaying the lists of research task type
        scanf(" %d", &inType);

        if (inType <= 0 || inType > nRsrchCtr) //saying na mali if more than the maximum entry ang ininput || 0 or less
            {
                printf("Oops! This type does not exist.");
            }
    } while (inType <= 0 || inType > nRsrchCtr);

    inType--; //decrement para magstart sa index 0
    
    for (i = 0; i < nPkCtr; i++) // for displaying the entries
    {
        if(pokemon[i].nResearchType[inType] > 0) // if value is 0, do not include in the display
        {
            displayEntryByResTaskType(i, pokemon, nRsrchCtr, inType); //display entry with the specific research task
            printf("\n");
            exist = 1;
        }

    }
    
    if (exist == 0) //if all entries value of task type is 0
    {
        printf("All pokemon in this specific type were all valued as 0.\n\n");
    }
}

void displayEntryByResTaskType(int i, struct pokemonstruct pokemon[],  int nRsrchCtr, int inType) //display entry with the specific research task
{
    // nRsrchCtr WAS NOT USED, WILL ONLY BE USED FOR BONUS POINTS.
        printf("\nEntry No. %d\n", pokemon[i].entry); //prints entry no.
        printf("Pokemon Name: %s\n", pokemon[i].cPokeName); //prints Pokemon Name

            switch (inType)
            {
            case 0:
                printf("Seen: %d \n",  pokemon[i].nResearchType[0]);
                break;
            case 1:
                printf("Defeated: %d \n",  pokemon[i].nResearchType[1]);
                break;
            default:
                break;
            }
}

void updateReseachTask(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr) //Update Research Task
{
    int inType,entry,nValue;
    int i = 0;
    int exist = 0;

    do { //FOR ASKING WHAT TASK TO UPDATE
        printf ("What Research Type are you trying update?\n");
        displayResTaskType(nRsrchCtr);
        scanf(" %d", &inType);

        if (inType <= 0 || inType > nRsrchCtr) //saying na mali if more than the maximum entry ang ininput || 0 or less
            {
                printf("Oops! This type does not exist.");
            }
    } while (inType <= 0 || inType > nRsrchCtr);
    inType--; // to decrement para magtugma sa program indexing

    researchDisplayAllEntries(nPkCtr,pokemon, nRsrchCtr);
    
    if (nPkCtr == 0) // FOR UPDATING THE RESEARCH TASK OF A POKEMON, IF WALANG LAMAN, THEN THIS CODE WILL RUN
    {
        printf("\nThere are no entries.\n"); // REPEATING SA researchDisplayAllEntries NA FUNCTIONS
    }
    else
    {
        do //for verification kung yung ineedit ay within the possible range
        {
            printf("\nWhat entry do you want to update: ");
            scanf(" %d", &entry);
        
            if (entry > nPkCtr || entry <= 0 ) //saying na mali if more than the maximum entry ang ininput || 0 or less
            {
                printf("Oops! This entry does not exist.");
            }
        } while (entry > nPkCtr || entry <= 0 ); // this will happen until valid number is inputted

            entry--;// to decrement para magtugma sa program indexing
            printf("You are trying to update: \n");
            
            displayEntryByResTaskType(entry, pokemon, nRsrchCtr, inType); // display the entry for correction to the user
            printf("\n");

            printf("How much will you increment in this task: ");
            scanf(" %d", &nValue);

            pokemon[entry].nResearchType[inType] = pokemon[entry].nResearchType[inType] + nValue;

            printf("Task Incremented. \n");
            researchDisplayEntry(entry, pokemon, nRsrchCtr); // display the entry for correction to the user
    }

}
