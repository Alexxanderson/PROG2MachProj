#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define ENTRYMAX 150

typedef char String[21];

struct pokemonstruct
{
    int entry;
    char cPokeName[21];
    char cPokeType;
    char cPokeDesc[51];
    int nResearchType[5];
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
void reviewResearchPerPokemon(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]);
void reviewResearchPerType(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]);
void researchDisplayAllEntries(int nPkCtr, struct pokemonstruct pokemon[]);
void researchDisplayEntry(int i, struct pokemonstruct pokemon[],  int nRsrchCtr, String sRsrchName[]);
void displayName(int i, struct pokemonstruct pokemon[]);
void displayResTaskType(int nRsrchCtr, String sRsrchName[]);
void displayEntryByResTaskType(int i, struct pokemonstruct pokemon[], int inType, String sRsrchName[]);
void updateReseachTask(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]);

void showTopFive(int nPkCtr, struct pokemonstruct pokemon[],int nRsrchCtr, int inType, String sRsrchName[]);

void export(int nPkCtr, struct pokemonstruct pokemon[]);

int addRsrch(int nRsrchCtr, String sRsrchName[]);
int SearchRsrch(char key[], int nPkCtr, String sRsrchName[]);

//main
int main()
{
    struct pokemonstruct pokemon[ENTRYMAX];
    int nPkCtr = 0; // Counter of how many pokemon are indexed && current index that has no value, will be utilized for addEntry
    int nRsrchCtr = 2; // Counter of the Research Tasks Types, for the bonus pointss
    char cDc; // gets the Char input of user when prompted for such
    char cExit = 'N';

    String sRsrchName[5];

    strcpy(sRsrchName[0], "Seen");
    strcpy(sRsrchName[1], "Defeated");


    clrscr();
    
        do
        {
            menu(); // Display Menu
            printf("current research counter: %d", nRsrchCtr);

            

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
                updateReseachTask(nPkCtr, pokemon, nRsrchCtr, sRsrchName);  
                break;
            case 'r': // Review Research per Pokemon; Search Research by Name
                reviewResearchPerPokemon(nPkCtr, pokemon, nRsrchCtr, sRsrchName);
                break;
            case 't': // Review Research per Task Type; Search Research By Type
                reviewResearchPerType(nPkCtr, pokemon, nRsrchCtr, sRsrchName);
                break;
            case 'e': // Export
                export(nPkCtr, pokemon);
                break;
            case 'i': // Import
                break;
            case 'k': //AddResearch
                nRsrchCtr = addRsrch(nRsrchCtr, sRsrchName);
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

    printf("[K] Add Research \n");

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
                    pokemon[j].nResearchType[0] = pokemon[j+1].nResearchType[0];
                    pokemon[j].nResearchType[1] = pokemon[j+1].nResearchType[1];
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

void researchDisplayAllEntries(int nPkCtr, struct pokemonstruct pokemon[]) //DISAPLYING ALL ENTRIES WITH NAME ONLY
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

void researchDisplayEntry(int i, struct pokemonstruct pokemon[],  int nRsrchCtr, String sRsrchName[]) // FOR DISPLAYING ENTRY WITH ALL THE RESEARCH TASKS
{
    int j;
        printf("\nEntry No. %d\n", pokemon[i].entry); //prints entry no.
        printf("Pokemon Name: %s\n", pokemon[i].cPokeName); //prints Pokemon Name

        for (j = 0; j < nRsrchCtr; j++) //for looop for the bonus points
        {
            printf("%s: %d \n",sRsrchName[j], pokemon[i].nResearchType[j]);

            // switch (j)
            // {
            // case 0:
            //     printf("%s: %d \n",sRsrchName[j], pokemon[i].nResearchType[j]);
            //     break;
            // case 1:
            //     printf("Defeated: %d \n",  pokemon[i].nResearchType[1]);
            //     break;
            // case 2:
            //     printf("Seen: %d \n",  pokemon[i].nResearchType[0]);
            //     break;
            // case 3:
            //     printf("Defeated: %d \n",  pokemon[i].nResearchType[1]);
            //     break;
            // case 4:
            //     printf("Defeated: %d \n",  pokemon[i].nResearchType[1]);
            //     break;
            // default:
            //     break;
            // }
        }
}

void reviewResearchPerPokemon(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]) // Review Research Task per Pokemon
{
    researchDisplayAllEntries(nPkCtr,pokemon); //Displaying all Pokemon Entries with names lang

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
            researchDisplayEntry(entry-1, pokemon, nRsrchCtr, sRsrchName); // display the entry for correction to the user
            printf("\n");

            getch(); // UI, stop lang
    }
}

void displayResTaskType(int nRsrchCtr, String sRsrchName[]) // Display the lists of Research Task Types
{
    int j;

        for (j = 0; j < nRsrchCtr; j++)
        {
            printf("[%d] %s\n", j+1, sRsrchName[j]);
            // switch (j)
            // {
            // case 0:
            //     printf("[1] Seen \n");
            //     break;
            // case 1:
            //     printf("[2] Defeated \n");
            //     break;
            // default:
            //     break;
            // }
        }
}

void reviewResearchPerType(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]) // Review Research Task per Task Type
{
    int i = 0;
    int exist = 0;
    int inType = 0;

    do {
        printf ("What Research Type are you searching for?\n");
        displayResTaskType(nRsrchCtr, sRsrchName); // For displaying the lists of research task type
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
            displayEntryByResTaskType(i, pokemon, inType, sRsrchName); //display entry with the specific research task
            printf("\n");
            exist = 1;
        }

    }
    
    if (exist == 0) //if all entries value of task type is 0
    {
        printf("All pokemon in this specific type were all valued as 0.\n\n");
    }

    showTopFive(nPkCtr,pokemon, nRsrchCtr, inType, sRsrchName);
}

void displayEntryByResTaskType(int i, struct pokemonstruct pokemon[], int inType, String sRsrchName[]) //display entry with the specific research task
{
    // nRsrchCtr WAS NOT USED, WILL ONLY BE USED FOR BONUS POINTS.
        printf("\nEntry No. %d\n", pokemon[i].entry); //prints entry no.
        printf("Pokemon Name: %s\n", pokemon[i].cPokeName); //prints Pokemon Name
        printf("%s: %d \n",sRsrchName[inType],  pokemon[i].nResearchType[inType]);

            // switch (inType)
            // {
            // case 0:
            //     printf("%s: %d \n",sRsrchName[inType]  pokemon[i].nResearchType[inType]);
            //     break;
            // case 1:
            //     printf("Defeated: %d \n",  pokemon[i].nResearchType[1]);
            //     break;
            // case 2:
            //     printf("Seen: %d \n",  pokemon[i].nResearchType[0]);
            //     break;
            // case 3:
            //     printf("Defeated: %d \n",  pokemon[i].nResearchType[1]);
            //     break;
            // case 4:
            //     printf("Seen: %d \n",  pokemon[i].nResearchType[0]);
            //     break;
            // default:
            //     break;
            // }
}

void updateReseachTask(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]) //Update Research Task
{
    int inType,entry,nValue;
    int i = 0;
    int exist = 0;

    do { //FOR ASKING WHAT TASK TO UPDATE
        printf ("What Research Type are you trying update?\n");
        displayResTaskType(nRsrchCtr, sRsrchName);
        scanf(" %d", &inType);

        if (inType <= 0 || inType > nRsrchCtr) //saying na mali if more than the maximum entry ang ininput || 0 or less
            {
                printf("Oops! This type does not exist.");
            }
    } while (inType <= 0 || inType > nRsrchCtr);
    inType--; // to decrement para magtugma sa program indexing

    researchDisplayAllEntries(nPkCtr,pokemon);
    
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
            
            displayEntryByResTaskType(entry, pokemon, inType, sRsrchName); // display the entry for correction to the user
            printf("\n");

            printf("How much will you increment in this task: ");
            scanf(" %d", &nValue);

            pokemon[entry].nResearchType[inType] = pokemon[entry].nResearchType[inType] + nValue;

            printf("Task Incremented. \n");
            researchDisplayEntry(entry, pokemon, nRsrchCtr, sRsrchName); // display the entry for correction to the user
    }

}

void showTopFive(int nPkCtr, struct pokemonstruct pokemon[],int nRsrchCtr, int inType, String sRsrchName[])
{
    int i,j,k,h, min, temp;
    int A[ENTRYMAX]; // temporary lists of index numbers

    // for initializing the temporary entry numbers, ENTRYMAX kasi nagkakabugs pag pokemon counter yan
    // for initializing the temporary entry numbers, ENTRYMAX kasi nagkakabugs pag pokemon counter yan
    for (k = 0; k < ENTRYMAX; k++) 
    {
        A[k] = k;
    }
    
    // swap sort algorithm
    for (i = 0; i < nPkCtr - 1; i++) { 
        min = i; // min is the index of the lowest element

        for (j = i + 1; j < nPkCtr; j++)
             if (pokemon[A[min]].nResearchType[inType]  < pokemon[A[j]].nResearchType[inType] ) // FOR STRUCTS; A[min].resTaskTYpe[inType]  < A[j].resTasktpe[inType]
                min = j;

        // swap function
        if (i != min) {
            temp = A[i]; 
            A[i] = A[min]; 
            A[min] = temp;
        }
    }

    if(pokemon[A[0]].nResearchType[inType] > 0) // this is to check if the highest has a value, pag wala, it means 0 lahat and therefore, no top 5
        {
            printf("Here are the top pokemons [max. 5]: \n\n");
        } else
        {
            printf("No top 5 pokemons. \n\n");
        }

    for (h = 0; h < 5; h++) //this will print the top 5 pokemons
    {
        if(pokemon[A[h]].nResearchType[inType] > 0)
        {
            displayEntryByResTaskType(A[h], pokemon, inType, sRsrchName); //display entry with the specific research task
            printf("\n");
        }
    }

}

void export(int nPkCtr, struct pokemonstruct pokemon[])
{
    char cFileName[31];
    FILE *fpointer;
    int i;

    printf("Enter a file name (.txt is not included): ");
    scanf(" %[^\n]s", &cFileName); //this is for asking the name of the file you want to get

    strcat(cFileName, ".txt"); // adding .txt para maging txt file siya

    fpointer = fopen(cFileName,"w"); // w = write, r = read, a = append
    
    for (i = 0; i < nPkCtr; i++)
    {
       fprintf(fpointer, "Name: %s \n", pokemon[i].cPokeName);
       fprintf(fpointer, "Type: %c \n", pokemon[i].cPokeType);
       fprintf(fpointer, "Description: %s \n", pokemon[i].cPokeDesc);
       fprintf(fpointer, "\n");
    }
    
    fclose(fpointer);

    printf("Export Successful! \n");

}

int addRsrch(int nRsrchCtr, String sRsrchName[])
{
    int i;
    String tempName;

    for (i = 0; i < nRsrchCtr; i++)
    {
        printf("sample print: %s \n", sRsrchName[i]);
    }

    if (nRsrchCtr >= 5)
    {
       printf("Maximum Research Task reached. \n\n");
    } else {

        printf("What Research Task do you want to add: ");
        scanf(" %[^\n]s", &tempName);

        if (SearchRsrch(tempName, nRsrchCtr, sRsrchName) == 1)
        {
            printf("Research Task Exist\n\n");
        }else{
            strcpy(sRsrchName[nRsrchCtr], tempName);
            nRsrchCtr++;
            printf("Research Task Added.\n\n");
        }

    }

    getch();

    return nRsrchCtr;
}

int SearchRsrch(char key[], int nPkCtr, String sRsrchName[]) //search function, strings only
{
   int i;
   int found = -1;

   for (i = 0; i < nPkCtr; i++)
   {
      if (strcmp(key, sRsrchName[i]) == 0)
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