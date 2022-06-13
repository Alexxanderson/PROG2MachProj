#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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

// home menu functions
void welcomeMenu();
void homeSelection();
void manageDataMenu();
void researchTaskMenu();

// manageData functions
int Search(char key[], int nPkCtr, struct pokemonstruct pokemon[]); // search function, strings only
int addEntry(int i, struct pokemonstruct pokemon[]); // add entry function
void modifyEntry(int nPkCtr, struct pokemonstruct pokemon[]); // modify entry function
int deleteEntry(int nPkCtr, struct pokemonstruct pokemon[]);  // delete entry function
void displayEntry(int i, struct pokemonstruct pokemon[]); // utilized by modifyEntry()
void displayAllEntries(int nPkCtr, struct pokemonstruct pokemon[]); // display all entry function
void searchPokeByName(int nPkCtr, struct pokemonstruct pokemon[]); // searches Pokemon by their names, or if the input is a part of their name
void searchPokeByType(int nPkCtr, struct pokemonstruct pokemon[]); // searches Pokemon by their type
void export(int nPkCtr, struct pokemonstruct pokemon[]);
int import (int nPkCtr, struct pokemonstruct pokemon[]);

// researchTask functions
void researchDisplayAllEntries(int nPkCtr, struct pokemonstruct pokemon[],  int nRsrchCtr); //DISAPLYING ALL ENTRIES WITH NAME ONLY
void researchDisplayEntry(int i, struct pokemonstruct pokemon[],  int nRsrchCtr); 
void reviewResearchPerPokemon(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr); // Review Research Task per Pokemon
void displayResTaskType(int nRsrchCtr); // Display the lists of Research Task Types
void reviewResearchPerType(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr); // Review Research Task per Task Type
void updateResearchTask(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr); //Update Research Task

// design functions
void boxMaker(int tbLeft, int tbRight, int yTopHor, int yBotHor, int iLHor, int iRHor, int iLVer, int iRVer);
void gotoxy(int x, int y);
void colCyan();
void colBlue();
void colRed();
void colYellow();
void colGreen();
void colPurple();
void colReset();

// for bonus function
void showTopFive(int nPkCtr, struct pokemonstruct pokemon[],int nRsrchCtr, int inType);

int main()
{
    struct pokemonstruct pokemon[ENTRYMAX]; // main struct of PokeDex
    int nPkCtr = 0; // Counter of how many pokemon are indexed && current index that has no value, will be utilized for addEntry
    int nRsrchCtr = 2; // Counter of the Research Tasks Types

    char exit = 'n';
    char exitMD = 'n';
    char exitRT = 'n';
    char inputChar;
    char inputMD;
    char inputRT;

    welcomeMenu();
    
    do
    {
        homeSelection(); // choose between Manage Data and Research Tasks
        inputChar = getch();

        switch (inputChar)
        {
            case 'm':
                do
                {
                    manageDataMenu();
                    inputMD = getch();

                    switch (inputMD)
                    {
                        case 'a': // add entry
                            system ("cls");
                            nPkCtr = addEntry(nPkCtr, pokemon);
                            break;

                        case 'c': // modify entry && can't use 'm'
                            system ("cls");
                            modifyEntry(nPkCtr, pokemon);
                            break;

                        case 'd': // delete entry
                            nPkCtr = deleteEntry(nPkCtr, pokemon);
                            break;
                        
                        case 'l': // displays all entry
                            // system ("cls");
                            displayAllEntries(nPkCtr, pokemon);
                            break;

                        case 's': // search pokemon by name
                            system ("cls");
                            searchPokeByName(nPkCtr, pokemon);
                            break;

                        case 'p': // search pokemon by type
                            system ("cls");
                            searchPokeByType(nPkCtr, pokemon);
                            break;

                        case 'i': // import
                            system ("cls");
                            nPkCtr = import (nPkCtr, pokemon);
                            break;

                        case 'e': // export
                            system ("cls");
                            export(nPkCtr, pokemon);
                            break;

                        case 'x': // exits to homeSelection()
                            exitMD = 'y';

                        default: // reprompts manageDataMenu()
                            break;
                    }
                } while (exitMD == 'n');
                break;
            
            case 'r':
                do
                {
                    researchTaskMenu();
                    inputRT = getch();

                    switch (inputRT)
                    {
                        case 'p': // review research tasks per pokemon
                            system ("cls");
                            reviewResearchPerPokemon(nPkCtr, pokemon, nRsrchCtr);
                            break;
                        
                        case 't': // review research tasks per type
                            system ("cls");
                            reviewResearchPerType(nPkCtr, pokemon, nRsrchCtr);
                            break;

                        case 'u': // updates research task
                            system ("cls");
                            updateResearchTask(nPkCtr, pokemon, nRsrchCtr);  
                            break;

                        case 'x': // exits to homeSelection()
                            exitRT = 'y';

                        default: // reprompts researchTaskMenu()
                            break;
                    }
                } while (exitRT == 'n');
                break;

            case 'x':
                exit = 'y';
                break;

        }
    } while (exit == 'n');
    
    printf("test end of program..."); // to be removed
    return 0;
}

// HOME MENU FUNCTIONS
void boxMaker(int tbLeft, int tbRight, int yTopHor, int yBotHor, int iLHor, int iRHor, int iLVer, int iRVer)
{
    // tbLeft = xLeftVert, tbRight = xRightVert
    // tbLeft, tbRight, yTopHor, yBotHor, iLHor(tbleft+1), iRHor(tbRight-1), iLVer(yTopHor+1), iRVer(yBotHor-1)

    gotoxy(tbLeft, yTopHor); printf("%c", 201); // top-left
    gotoxy(tbRight, yTopHor); printf("%c", 187); // top-right
    gotoxy(tbLeft, yBotHor); printf("%c", 200); // bottom-left 
    gotoxy(tbRight, yBotHor); printf("%c", 188); // bottom-right 
    
    for (int i = iLHor; i <= iRHor; i++) { 
        gotoxy(i, yTopHor); printf("%c", 205); // top horizontals
        gotoxy(i, yBotHor); printf("%c", 205); // bottom horizontals
    }

    for (int i = iLVer; i <= iRVer; i++) {
        gotoxy(tbLeft, i); printf("%c", 186); // left side vertical
        gotoxy(tbRight, i); printf("%c", 186); // right side vertical
    }
}

void welcomeMenu(){
    system ("cls");
    
    // tbLeft = xLeftVert, tbRight = xRightVert
    // tbLeft, tbRight, yTopHor, yBotHor, iLHor, iRHor, iLVer, iRVer
    colCyan();
    boxMaker(43, 75, 4, 12, 44, 74, 5, 11);

    gotoxy(50,5); colYellow(); printf("WELCOME TO POKEDEX!");
    gotoxy(49,7); colRed(); printf("'gotta catch 'em all!");
    gotoxy(54,9); colBlue(); printf("DEVELOPERS:");
    gotoxy(48,10); colGreen(); printf("BACCAY, Dominic Luis M.");
    gotoxy(48,11); colGreen(); printf("MIRANDA, Bien Aaron C.");
    sleep(.5);
    // getch();
}

void homeSelection(){
    system ("cls");

    gotoxy(53,4); colYellow(); printf("POKEDEX HOME");
    gotoxy(33,5); colCyan(); printf("CHOOSE BETWEEN MANAGING DATA OR DOING RESEARCH TASKS");
    
    colRed();
    boxMaker(32, 54, 7, 19, 33, 53, 8, 18);
    gotoxy(36,8); printf("MANAGE DATA [M]");
    gotoxy(35,10); printf("Add");
    gotoxy(35,11); printf("Modify");
    gotoxy(35,12); printf("Delete");
    gotoxy(35,13); printf("Display Entries");
    gotoxy(35,14); printf("Search by Name");
    gotoxy(35,15); printf("Search by Type");
    gotoxy(35,16); printf("Import");
    gotoxy(35,17); printf("Export");

    colGreen();
    boxMaker(63, 85, 7, 14, 64, 84, 8, 13);
    gotoxy(66,8); printf("RESEARCH TASK [R]");
    gotoxy(65,10); printf("Review per Pokemon");
    gotoxy(65,11); printf("Review per Type");
    gotoxy(65,12); printf("Update Research");

    colCyan();
    boxMaker(63, 85, 15, 19, 64, 84, 16, 18);
    gotoxy(66,17); printf("LEAVE POKEDEX [X]");

    gotoxy(1, 22); printf(""); colReset();
}

void manageDataMenu(){
    system ("cls");
    gotoxy(54,5); colRed(); printf("MANAGE DATA");

    boxMaker(43, 75, 4, 17, 44, 74, 5, 16);
    gotoxy(48,7); printf("[A] Add");
    gotoxy(48,8); printf("[C] Modify");
    gotoxy(48,9); printf("[D] Delete");
    gotoxy(48,10); printf("[L] Display All Entries");
    gotoxy(48,11); printf("[S] Search by Name");
    gotoxy(48,12); printf("[P] Search by Type");
    gotoxy(48,13); printf("[I] Import");
    gotoxy(48,14); printf("[E] Export");
    gotoxy(48,15); printf("[X] Exit Manage Data"); colReset();
}

void researchTaskMenu(){
    system ("cls");
    gotoxy(53,5); colGreen(); printf("RESEARCH TASK");

    boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
    gotoxy(48,7); printf("[P] Review per Pokemon");
    gotoxy(48,8); printf("[T] Review per Type");
    gotoxy(48,9); printf("[U] Update Research");
    gotoxy(48,10); printf("[X] Exit Research Task"); colReset();
}

// MANAGE DATA FUNCTIONS
int Search(char key[], int nPkCtr, struct pokemonstruct pokemon[]) // search function, strings only
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

int addEntry(int i, struct pokemonstruct pokemon[])
{
    char inName[21]; // temporarily stores name for max. 20 char validation

    // i = 150; // test case for i == 150 menu

    if (i == 150) // if nPkCtr is == 150, no more entries can be added
    {
        colCyan();
        boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(55, 5); printf("ADD ENTRY\n");

        colRed();
        gotoxy(57, 7); printf("!!!!");
        gotoxy(48, 8); printf("MAXIMUM ENTRIES REACHED");
        colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    } 
    else 
    {
        colCyan();
        boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
        gotoxy(55, 5); printf("ADD ENTRY");
        

        gotoxy(35, 7); printf("ENTER POKEMON NAME:"); 
        gotoxy(35, 8); scanf(" %[^\n]s", &inName); // temporarily stores Pokemon Name

        if (Search(inName, i, pokemon) == 1) // validates Pokemon Name, if duplicate, terminate
        {          
            system ("cls"); // clears screen 
            colCyan();
            boxMaker(40, 78, 4, 12, 41, 77, 5, 11);
            gotoxy(55, 5); printf("ADD ENTRY\n");

            colRed();
            gotoxy(57, 7); printf("!!!!!");
            gotoxy(43, 8); printf("OOPS! THIS POKEMON ALREADY EXISTS");
            colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
            getch();
        } 
        else // else, continue for Pokemon Entry
        {
            pokemon[i].entry = i + 1; // initialize entry number based from the array no.
            gotoxy(35, 10); printf ("FOR ENTRY #%d: \n", pokemon[i].entry);

            strcpy(pokemon[i].cPokeName, inName);
            gotoxy(35, 12); printf("POKEMON NAME: %s \n", pokemon[i].cPokeName);

            do
            {
                gotoxy(50, 14); printf ("SELECT POKEMON TYPE");
                gotoxy(39, 15); printf("[W] WATER [F] FIRE [G] GRASS [E] ELECTRIC");
                pokemon[i].cPokeType = getch(); // getch() gets w/f/g/e char for storing of pokemon type in the struct 

                if (pokemon[i].cPokeType == 'w') {
                    gotoxy(47, 17); printf("POKEMON TYPE: WATER");
                }
                else if (pokemon[i].cPokeType == 'f') {
                    gotoxy(47, 17); printf("POKEMON TYPE: FIRE");
                }
                else if (pokemon[i].cPokeType == 'g') {
                    gotoxy(47, 17); printf("POKEMON TYPE: GRASS");
                }
                else if (pokemon[i].cPokeType == 'e') {
                    gotoxy(47, 17); printf("POKEMON TYPE: ELECTRIC");
                }
            } while (pokemon[i].cPokeType != 'w' && pokemon[i].cPokeType != 'f' && pokemon[i].cPokeType != 'g' && pokemon[i].cPokeType != 'e');
                        
            gotoxy(35, 19); printf("ENTER POKEMON DESCRIPTION:");
            gotoxy(35, 20); scanf(" %[^\n]s", pokemon[i].cPokeDesc);
            
            // pokemon[i].seen = 0; // STILL SUBJECT TO CHANGE
            // pokemon[i].defeated = 0;
            pokemon[i].nResearchType[0] = 0; // for seen
            pokemon[i].nResearchType[1] = 0; // for defeated

            i++;
        }
    }
    return i;
}

void modifyEntry(int nPkCtr, struct pokemonstruct pokemon[])
{
    int i; // for identifying what entry to modify
    char choice;
    char modify = 'y';

    // variables for name change
    char changeName[21];
    char validName;

    if (nPkCtr == 0)
    {   
        colCyan();
        boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(54, 5); printf("MODIFY ENTRY\n");

        colRed();
        gotoxy(57, 7); printf("!!!!!");
        gotoxy(47, 8); printf("NO ENTRIES TO MODIFY FROM");
        colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    else
    {
        do
        {
            system ("cls");
            gotoxy(1, 4); printf("!! REVIEW ENTRIES FOR MODIFICATION !!");
            displayAllEntries(nPkCtr, pokemon);

            colCyan();
            boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
            gotoxy(54, 5); printf("MODIFY ENTRY\n");
            gotoxy(48, 8); printf("SELECT ENTRY TO MODIFY:");
            gotoxy(48, 9);scanf(" %d", &i);
        
            if (i > nPkCtr || i <= 0 )
            {
                system ("cls");
                colCyan();
                boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
                gotoxy(54, 5); printf("MODIFY ENTRY\n");
                
                colRed(); gotoxy(49, 8); printf("ENTRY DOES NOT EXIST!"); 
                colCyan(); gotoxy(45, 11); printf("*PRESS ANY KEY TO TRY AGAIN*"); colReset();
                getch();
            }
        } while (i > nPkCtr || i <= 0 );

        i = i-1; // this is the actual index.

        system ("cls");
        gotoxy(54, 5); printf("MODIFY ENTRY\n");
        displayEntry(i, pokemon);
        printf("\n");
            
        do
        {
            gotoxy(44, 16); printf("SELECT POKEMON DATA TO MODIFY\n"); // question
            gotoxy(44, 17); printf("[1] NAME");
            gotoxy(44, 18); printf("[2] TYPE");
            gotoxy(44, 19); printf("[3] DESCRIPTION");
            gotoxy(44, 20); printf("[X] EXIT");
            choice = getch();
            
            switch (choice) // dito mangyayari yung modification
            {
                case '1':
                    do
                    {
                        system ("cls");
                        boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
                        gotoxy(54, 5); printf("MODIFY ENTRY\n");

                        //strcpy(pokemon[i].cPokeName, "");
                        gotoxy(44, 8); printf ("ENTER NEW POKEMON NAME: ");
                        gotoxy(44, 9); scanf(" %[^\n]s", &changeName);
                        

                            if (Search(changeName, nPkCtr, pokemon) == 1){ // verify if name change is correct
                                validName = 'n'; // not valid, reprompt
                                gotoxy(44, 11); printf ("NAME EXISTS IN THE POKEDEX.");
                                getch();
                            }
                            else {
                                strcpy(pokemon[i].cPokeName, changeName);
                                validName = 'y';
                            }
                        
                    } while (validName == 'n');
                    
                    gotoxy(44, 11); printf("EDITED POKEMON NAME: %s\n", pokemon[i].cPokeName); // for verificcation, subject for removal
                    gotoxy(44, 13); printf ("DO YOU WANT TO MODIFY MORE?\n");
                    gotoxy(44, 14); printf("[Y] Yes [X] Exit\n");
                    modify = getch(); // asks the user for more modification and to reloop or not
                    break;

                case '2':
                    do
                    {
                        system ("cls");
                        boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
                        gotoxy(54, 5); printf("MODIFY ENTRY\n");
                        gotoxy(48, 7); printf ("SELECT NEW POKEMON TYPE");
                        gotoxy(48, 8); printf ("[W] WATER [F] FIRE");
                        gotoxy(48, 9); printf ("[G] GRASS [E] ELECTRIC");
                        pokemon[i].cPokeType = getch(); //getch nalang so that it's clean and walang further bugs na magkameron, altho stored char is the small letter
                        printf("\n");

                        if (pokemon[i].cPokeType == 'w') {
                            gotoxy(44, 11); printf("EDITED POKEMON TYPE: WATER\n"); // for verification, subject for removal
                        }
                        else if (pokemon[i].cPokeType == 'f') {
                            gotoxy(44, 11); printf("EDITED POKEMON TYPE: FIRE\n");
                        }
                        else if (pokemon[i].cPokeType == 'g') {
                            gotoxy(44, 11); printf("EDITED POKEMON TYPE: GRASS\n");
                        }
                        else if (pokemon[i].cPokeType == 'e') {
                            gotoxy(44, 11); printf("EDITED POKEMON TYPE: ELECTRIC\n");
                        }
                    } while (pokemon[i].cPokeType != 'w' && pokemon[i].cPokeType != 'f' && pokemon[i].cPokeType != 'g' && pokemon[i].cPokeType != 'e');
                    
                    gotoxy(44, 13); printf ("DO YOU WANT TO MODIFY MORE?\n");
                    gotoxy(44, 14); printf("[Y] Yes [X] Exit\n");
                    modify = getch(); // asks the user for more modification and to reloop or not
                    break;

                case '3':
                    system ("cls");

                    boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
                    gotoxy(54, 5); printf("MODIFY ENTRY\n");
                    gotoxy(34, 7); printf ("ENTER NEW DESCRIPTION:");
                    gotoxy(34, 8); scanf(" %[^\n]s", &pokemon[i].cPokeDesc);
                    gotoxy(34, 10); printf("EDITED DESCRIPTION:"); // for verification, subject for removal
                    gotoxy(34, 11); printf("%s", pokemon[i].cPokeDesc);
                    gotoxy(44, 13); printf ("DO YOU WANT TO MODIFY MORE?\n");
                    gotoxy(44, 14); printf("[Y] Yes [X] Exit\n");
                    modify = getch(); // asks the user for more modification and to reloop or not
                    break;

                case 'x':
                    modify = 'n';
                    break;

                default:
                    break;
            }
        } while (modify == 'y');
    }
}

int deleteEntry(int nPkCtr, struct pokemonstruct pokemon[]) // Delete Entry
{
    int i,j; // i is for the actual index, j for the for loop
    char cDec; // Decision;

    if (nPkCtr == 0)
    {   
        system ("cls");
        colCyan();
        boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(53, 5); printf("DELETE ENTRY\n");

        colRed();
        gotoxy(56, 7); printf("!!!!!!");
        gotoxy(47, 8); printf("NO ENTRIES TO DELETE FROM");
        colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    else
    {
        do // for verification kung yung ineedit ay within the possible range
        {
            system ("cls");
            gotoxy(1, 4); printf("!! REVIEW ENTRIES FOR DELETION !!");
            displayAllEntries(nPkCtr, pokemon);
    
            // existing bug wherein npcktr, when deleted is set to 0, but display all entries still works.

            colCyan();
            boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
            gotoxy(53, 5); printf("DELETE ENTRY\n");
            gotoxy(48, 8); printf("SELECT ENTRY TO DELETE:");
            gotoxy(48, 9);scanf(" %d", &i);

            if (i > nPkCtr || i <= 0 ) // saying na mali if more than the maximum entry ang ininput || 0 or less
            {
                system ("cls");
                colCyan();
                boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
                gotoxy(53, 5); printf("DELETE ENTRY\n");
                
                colRed(); gotoxy(49, 8); printf("ENTRY DOES NOT EXIST!"); 
                colCyan(); gotoxy(45, 11); printf("*PRESS ANY KEY TO TRY AGAIN*"); colReset();
                getch();
            }
        } while (i > nPkCtr || i <= 0 ); // this will happen until valid number is inputted

        do
        {
            system ("cls");
            gotoxy(53, 5); printf("DELETE ENTRY\n");
            displayEntry(i-1, pokemon);
            printf("\n");

            gotoxy(44, 16); printf("ENTRY #%d IS SUBJECT FOR DELETION\n", i);

            gotoxy(44, 18); printf("ARE YOU SURE TO DELETE ENTRY #%d?\n", i); // verification
            gotoxy(44, 19); printf("[Y] YES [N] NO\n");
            cDec = getch();
            
            i = i-1;        

            switch (cDec)
            {
                case 'y':
                    
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
                    gotoxy(44, 22); printf("Entry Deleted. PokeDex Readjusted\n");
                    gotoxy(46, 23); printf("~~PRESS ANY KEY TO CONTINUE~~\n");
                    getch();
                    break;

                case 'n':
                    gotoxy (44, 22); printf("ENTRY SUSTAINED.\n");
                    gotoxy(46, 23); printf("~~PRESS ANY KEY TO CONTINUE~~\n");
                    getch();
                    break;

                default:
                    break;
            }
         } while (cDec != 'y' && cDec != 'n');
    }
    
    return nPkCtr;
}

void displayEntry(int i, struct pokemonstruct pokemon[])
{
        colCyan();
        // boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
        boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
        // gotoxy(54, 5); printf("MODIFY ENTRY\n");
        
        gotoxy(55, 7); printf("ENTRY #%d\n", pokemon[i].entry); //prints entry no.
        gotoxy(35, 9); printf("POKEMON NAME: %s\n", pokemon[i].cPokeName); //prints Pokemon Name

        if (pokemon[i].cPokeType == 'w') { 
            gotoxy(35, 11); printf("POKEMON TYPE: WATER\n");
        }
        else if (pokemon[i].cPokeType == 'f') {
            gotoxy(35, 11); printf("POKEMON TYPE: FIRE\n");
        }
        else if (pokemon[i].cPokeType == 'g') {
            gotoxy(35, 11); printf("POKEMON TYPE: GRASS\n");
        }
        else if (pokemon[i].cPokeType == 'e') {
            gotoxy(35, 11); printf("POKEMON TYPE: ELECTRIC\n");
        }

        gotoxy(35, 13); printf("POKEMON DESCRIPTION:"); // prints Pokermon Decription
        gotoxy(35, 14); printf("%s", pokemon[i].cPokeDesc);
}

void displayAllEntries(int nPkCtr, struct pokemonstruct pokemon[])
{
    int i = 0;
    char prevnext;
    // system ("cls");

    if (nPkCtr == 0) {
        gotoxy(1, 2); colRed(); printf("// NO ENTRIES FOUND TO DISPLAY //");
        gotoxy(1, 5); colYellow(); printf("Redirecting to Manage Data Menu... ");
        getch();
    }
    else 
    {
        if (nPkCtr == 1)
        {
            system("cls");
            gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL ENTRIES //\n");
            gotoxy(1, 5 ); printf(" ");
            colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
            colGreen(); printf("\n POKEMON NAME:\n");
            colGreen(); printf(" %s\n", pokemon[i].cPokeName);

                if (pokemon[i].cPokeType == 'w')
                {
                    colGreen(); printf("\n POKEMON TYPE: WATER\n");
                }
                else if (pokemon[i].cPokeType == 'f')
                {
                    colGreen(); printf("\n POKEMON TYPE: FIRE\n");
                }
                else if (pokemon[i].cPokeType == 'g')
                {
                    colGreen(); printf("\n POKEMON TYPE: GRASS\n");
                }
                else if (pokemon[i].cPokeType == 'e')
                {
                    colGreen(); printf("\n POKEMON TYPE: ELECTRIC\n");
                }

            colGreen(); printf("\n POKEMON DESCRIPTION:\n");
            colGreen(); printf(" %s\n", pokemon[i].cPokeDesc);
            colYellow (); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
            getch();
        }
        else if (nPkCtr > 1)
        {
            while (i < nPkCtr-1)
            {   
                if (i < 0) // when i is less than 0, it defaults to i = 0, triggered when user clicks PREVIOUS on Entry #1
                {
                    i = 0;
                }

                system("cls");
                gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL ENTRIES //\n");
                gotoxy(1, 5 ); printf(" ");
                colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
                colGreen(); printf("\n POKEMON NAME:\n");
                colGreen(); printf(" %s\n", pokemon[i].cPokeName);

                if (pokemon[i].cPokeType == 'w')
                {
                    colGreen(); printf("\n POKEMON TYPE: WATER\n");
                }
                else if (pokemon[i].cPokeType == 'f')
                {
                    colGreen(); printf("\n POKEMON TYPE: FIRE\n");
                }
                else if (pokemon[i].cPokeType == 'g')
                {
                    colGreen(); printf("\n POKEMON TYPE: GRASS\n");
                }
                else if (pokemon[i].cPokeType == 'e')
                {
                    colGreen(); printf("\n POKEMON TYPE: ELECTRIC\n");
                }

                colGreen(); printf("\n POKEMON DESCRIPTION:\n");
                colGreen(); printf(" %s\n", pokemon[i].cPokeDesc);

                colCyan(); printf("\n [P] PREVIOUS [N] NEXT\n");
                prevnext = getch();

                switch (prevnext)
                {
                    case 'p':
                        system("cls");
                        gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL ENTRIES //\n");
                        gotoxy(1, 5 ); printf(" ");
                        i--;
                        colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
                        colGreen(); printf("\n POKEMON NAME:\n");
                        colGreen(); printf(" %s\n", pokemon[i].cPokeName);

                        if (pokemon[i].cPokeType == 'w')
                        {
                            colGreen(); printf("\n POKEMON TYPE: WATER\n");
                        }
                        else if (pokemon[i].cPokeType == 'f')
                        {
                            colGreen(); printf("\n POKEMON TYPE: FIRE\n");
                        }
                        else if (pokemon[i].cPokeType == 'g')
                        {
                            colGreen(); printf("\n POKEMON TYPE: GRASS\n");
                        }
                        else if (pokemon[i].cPokeType == 'e')
                        {
                            colGreen(); printf("\n POKEMON TYPE: ELECTRIC\n");
                        }

                        colGreen(); printf("\n POKEMON DESCRIPTION:\n");
                        colGreen(); printf(" %s\n", pokemon[i].cPokeDesc);
                        break;

                    case 'n':
                        system("cls");
                        gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL ENTRIES //\n");
                        gotoxy(1, 5 ); printf(" ");
                        i++;
                        colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
                        colGreen(); printf("\n POKEMON NAME:\n");
                        colGreen(); printf(" %s\n", pokemon[i].cPokeName);

                        if (pokemon[i].cPokeType == 'w')
                        {
                            colGreen(); printf("\n POKEMON TYPE: WATER\n");
                        }
                        else if (pokemon[i].cPokeType == 'f')
                        {
                            colGreen(); printf("\n POKEMON TYPE: FIRE\n");
                        }
                        else if (pokemon[i].cPokeType == 'g')
                        {
                            colGreen(); printf("\n POKEMON TYPE: GRASS\n");
                        }
                        else if (pokemon[i].cPokeType == 'e')
                        {
                            colGreen(); printf("\n POKEMON TYPE: ELECTRIC\n");
                        }

                        colGreen(); printf("\n POKEMON DESCRIPTION:\n");
                        colGreen(); printf(" %s\n", pokemon[i].cPokeDesc);
                        break;
                            
                    default:
                        break;
                }
            }
        colYellow (); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
        getch();
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

    colCyan();
    boxMaker(40, 78, 4, 12, 41, 77, 5, 11);
    gotoxy(49, 5); printf("SEARCH POKEMON BY NAME\n");
    gotoxy(43, 8); printf("SEARCH POKEMON NAME:");
    colCyan(); gotoxy(43, 9); scanf(" %[^\n]s", &inName);

    inNameLen = strlen(inName);

    for (i = 0; i < nPkCtr; i++){
        pos = 0; //position starts at word[0]
        sublen = strlen(pokemon[i].cPokeName); // declaring the length of the word

        for (j = 0; j <= sublen - inNameLen; j++){ // for loop ng position 
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
        gotoxy(1,2); colYellow (); printf("// DISPLAYING SEARCH RESULTS BY NAME //\n");
        gotoxy(1,3); printf(" ");
                
        for (i = 0; i < ctr; i++)
        {
            // displayEntry(nList[i], pokemon);
            // printf("\n");
            // pokemon[i].entry = i + 1; // initialize entry number based from the array no.
            colCyan(); printf("\n || ENTRY #%d ||\n", pokemon[i].entry);
            colGreen(); printf("\n POKEMON NAME:\n");
            colGreen(); printf(" %s\n", pokemon[nList[i]].cPokeName);

            if (pokemon[nList[i]].cPokeType == 'w')
            {
                colGreen(); printf("\n POKEMON TYPE: WATER\n");
            }
            else if (pokemon[nList[i]].cPokeType == 'f')
            {
                colGreen(); printf("\n POKEMON TYPE: FIRE\n");
            }
            else if (pokemon[nList[i]].cPokeType == 'g')
            {
                colGreen(); printf("\n POKEMON TYPE: GRASS\n");
            }
            else if (pokemon[nList[i]].cPokeType == 'e')
            {
                colGreen(); printf("\n POKEMON TYPE: ELECTRIC\n");
            }

            colGreen(); printf("\n POKEMON DESCRIPTION:\n");
            colGreen(); printf(" %s\n", pokemon[nList[i]].cPokeDesc);
        }  
        colYellow (); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
        getch();
    }
    else {
        system ("cls");
        colCyan();
        boxMaker(40, 78, 4, 12, 41, 77, 5, 11);
        gotoxy(49, 5); printf("SEARCH POKEMON BY NAME\n");

        colRed();
        gotoxy(56, 7); printf("!!!!!");
        gotoxy(43, 8); printf("OOPS! THIS POKEMON DOESN'T EXIST");
        colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
}

void searchPokeByType(int nPkCtr, struct pokemonstruct pokemon[])
{
    int i = 0;
    int exist = 0;
    char inType;

    do {
        system ("cls");
        colCyan();
        boxMaker(40, 78, 4, 12, 41, 77, 5, 11);
        gotoxy(49, 5); printf("SEARCH POKEMON BY TYPE\n");
        gotoxy(50, 8); colGreen(); printf("SELECT POKEMON TYPE");
        gotoxy(48, 9); colYellow(); printf("[W] WATER [F] FIRE");
        gotoxy(48, 10); colYellow(); printf("[G] GRASS [E] ELECTRIC");

        inType = getch(); //getch nalang so that it's clean and walang further bugs na magkameron, altho stored char is the small letter
    } while (inType != 'w' && inType != 'f' && inType != 'g' && inType != 'e');

    gotoxy(1,2); colYellow (); printf("// DISPLAYING SEARCH RESULTS BY TYPE //\n");
    gotoxy(1,3); printf(" ");

    for (i = 0; i < nPkCtr; i++) 
    {
        // colYellow (); printf("// DISPLAYING SEARCH RESULTS BY TYPE //\n");
        if(inType == pokemon[i].cPokeType) 
        {
            colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
            colGreen(); printf("\n POKEMON NAME:\n");
            colGreen(); printf(" %s\n", pokemon[i].cPokeName);
            
            if (pokemon[i].cPokeType == 'w')
            {
                colGreen(); printf("\n POKEMON TYPE: WATER\n");
            }
            else if (pokemon[i].cPokeType == 'f')
            {
                colGreen(); printf("\n POKEMON TYPE: FIRE\n");
            }
            else if (pokemon[i].cPokeType == 'g')
            {
                colGreen(); printf("\n POKEMON TYPE: GRASS\n");
            }
            else if (pokemon[i].cPokeType == 'e')
            {
                colGreen(); printf("\n POKEMON TYPE: ELECTRIC\n");
            }

            colGreen(); printf("\n POKEMON DESCRIPTION:\n");
            colGreen(); printf(" %s\n", pokemon[i].cPokeDesc);

            // displayEntry(i, pokemon);
            // printf("\n");
            exist = 1;
        }
    }
        
    if (exist == 0) 
    {
        system ("cls");
        colCyan();
        boxMaker(40, 78, 4, 12, 41, 77, 5, 11);
        gotoxy(49, 5); printf("SEARCH POKEMON BY TYPE\n");

        colRed();
        gotoxy(56, 7); printf("!!!!!");
        gotoxy(43, 8); printf("OOPS! THIS POKEMON DOESN'T EXIST");
        colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }

    else if (exist == 1)
    {
        colYellow (); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
        getch();
    }    
}

void export(int nPkCtr, struct pokemonstruct pokemon[])
{
    char cFileName[31];
    FILE *fpointer;
    int i;

    colYellow(); printf("Enter a file name (exclude .txt): ");
    scanf(" %[^\n]s", &cFileName); //this is for asking the name of the file you want to get

    strcat(cFileName, ".txt"); // adding .txt para maging txt file siya

    fpointer = fopen(cFileName,"w"); // w = write, r = read, a = append
    
    for (i = 0; i < nPkCtr; i++)
    {
        // Name
        fprintf(fpointer, "Name: %s \n", pokemon[i].cPokeName);
        // Type
        if (pokemon[i].cPokeType == 'w') {
            fprintf(fpointer, "Type: Water\n");
        }
        else if (pokemon[i].cPokeType == 'f') {
            fprintf(fpointer, "Type: Fire\n");
        }
        else if (pokemon[i].cPokeType == 'g') {
            fprintf(fpointer, "Type: Grass\n");
        }
        else if (pokemon[i].cPokeType == 'e') {
            fprintf(fpointer, "Type: Electric\n");
        }
        // Description
        fprintf(fpointer, "Description: %s \n", pokemon[i].cPokeDesc);
        fprintf(fpointer, "\n");
    }
    
    fclose(fpointer);

    colGreen(); printf("\nExport Successful! \n");
    colCyan(); printf("\n// PRESS ANY KEY TO CONTINUE //");
    getch();
}

int import (int nPkCtr, struct pokemonstruct pokemon[])
{
    char filename[100];
    FILE *fp;

    char tempName[27];
    char tempType[15];
    char tempTypeCHAR;
    char tempDesc[64];

    char choice; 
    char dupChoice;
    int buffer; // only accounts for the imported (not skipped) entries
    int zeroEntry = 0;
    int manyEntry = 0;

    if (nPkCtr == 0)
    {
        buffer = 0;
        do
        {
            colCyan(); printf("// IMPORT ENTRY //\n");
            colRed(); printf("\n!! NO EXISTING ENTRIES !!\n\n");
            colCyan(); printf("HOW MANY ENTRIES WOULD YOU LIKE TO IMPORT?\nENTER VALUE: ");
            scanf(" %d", &zeroEntry);
        
            if (zeroEntry <= 0 || zeroEntry >= 151) {
                colRed(); printf("INVALID INPUT, PLEASE RETRY\n");
            }
            printf("\n");
        } while (zeroEntry <= 0 || zeroEntry >= 151);
        
        colYellow(); printf("\nENTER FILE NAME (EXCLUDE .txt): ");
        scanf(" %s", &filename);
        strcat(filename,".txt");

        fp = fopen(filename, "r");

        for (int i = 0; i < zeroEntry; i++)
        {
            system("cls");
            fscanf(fp, " %[^\n]s\n", &tempName);
            fscanf(fp, " %[^\n]s\n", &tempType);
            fscanf(fp, " %[^\n]s\n", &tempDesc);

            if (Search(&tempName[6], nPkCtr, pokemon) == -1)
            {
                do
                {
                    colCyan(); printf("\n// IMPORTED RESULTS //\n");

                    colPurple(); printf("Pokemon Name: %.20s\n", &tempName[6]);
                    colPurple(); printf("Pokemon Type: %s\n", &tempType[6]);
                    colPurple(); printf("Pokemon Description: %.50s\n", &tempDesc[13]);
                    colPurple(); printf("\n");
                    
                    colCyan(); printf("DO YOU LIKE TO IMPORT THIS ENTRY?\n");
                    colCyan(); printf("[Y] IMPORT [N] SKIP\n");
                    choice = getch();

                } while (choice != 'y' && choice != 'n');    

                switch (choice)
                {
                case 'y':
                    strcpy(pokemon[buffer].cPokeName, &tempName[6]);
                    if ( strcmp(&tempType[6],"Water") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'w';
                    }
                    else if ( strcmp(&tempType[6],"Fire") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'f';
                    }                
                    else if ( strcmp(&tempType[6],"Grass") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'g';
                    }
                    else if ( strcmp(&tempType[6],"Electric") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'e';
                    }
                    strcpy(pokemon[buffer].cPokeDesc, &tempDesc[13]);
                    // pokemon[i].entry = nPkCtr;
                    buffer++;
                    nPkCtr++;
                    pokemon[i].entry = nPkCtr;
                    colGreen(); printf("\n// IMPORT SUCCESFUL! //\n");
                    colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                    getch();
                    break;
                
                case 'n':
                    colRed(); printf("\n// IMPORT SKIPPED! //\n");
                    colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                    getch();
                    // buffer = buffer; // visual code confirmation that Imported Counter remains stagnant
                    // nPkCtr = nPkCtr; // visual code confirmation that Pokemon Counter remains stagnant
                    break;
                }
            }
            else if (Search(&tempName[6], nPkCtr, pokemon) == 1)
            {
                system("cls");
                colCyan(); printf("\n// IMPORTED RESULTS //\n");
                colRed(); printf("THIS POKEMON ALREADY EXISTS\n");

                do
                {
                    colYellow(); printf("\n[Y] OVERWRITE DUPLICATE IMPORT\n");
                    printf("[N] SKIP DUPLICATE IMPORT\n"); colReset();
                    dupChoice = getch();
                } while (dupChoice != 'y' && dupChoice != 'n');

                switch (dupChoice)
                {
                    case 'y':
                        system ("cls");
                        colGreen(); printf("\n// OVERWRITING IMPORT //\n");
                        
                        do
                        {
                            system ("cls");
                            nPkCtr = addEntry(nPkCtr, pokemon);
                        } while (nPkCtr == buffer);
                        pokemon[i].entry = nPkCtr;
                        buffer++;
                        printf("// IMPORT OVERWRITTEN //\n"); colReset();
                        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                        getch();
                        system ("cls");
                        break;
                    
                    case 'n':
                        colRed(); printf("\n// IMPORT SKIPPED! //\n");
                        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                        getch();
                        system("cls");
                        break;
                }
            }  
        }
        fclose(fp);
    }
    else if (nPkCtr > 0)
    {
        buffer = nPkCtr;
        do
        {
            colCyan(); printf("// IMPORT ENTRY //\n");
            colGreen(); printf("\n!! %d EXISTING ENTRIES !!\n\n", nPkCtr);
            colCyan(); printf("HOW MANY ENTRIES WOULD YOU LIKE TO IMPORT?\nENTER VALUE: ");
            scanf(" %d", &manyEntry);
            
            if (manyEntry <= 0 || manyEntry > (150-nPkCtr)) {
                colRed(); printf("INVALID INPUT, PLEASE RETRY\n");
            }
            printf("\n");
        } while (manyEntry <= 0 || manyEntry > (150-nPkCtr));

        colYellow(); printf("\n\nENTER FILE NAME (EXCLUDE.txt): ");
        scanf(" %s", &filename);
        strcat(filename,".txt");

        fp = fopen(filename, "r");

        for (int i = 0; i < manyEntry; i++)
        {        
            system("cls");
            fscanf(fp, " %[^\n]s\n", &tempName);
            fscanf(fp, " %[^\n]s\n", &tempType);
            fscanf(fp, " %[^\n]s\n", &tempDesc);

            if (Search(&tempName[6], nPkCtr, pokemon) == -1)
            {
                do
                {
                    colCyan(); printf("\n// IMPORTED RESULTS //\n");

                    colPurple(); printf("Pokemon Name: %.20s\n", &tempName[6]);
                    colPurple(); printf("Pokemon Type: %s\n", &tempType[6]);
                    colPurple(); printf("Pokemon Description: %.50s\n", &tempDesc[13]);
                    colPurple(); printf("\n");
                    
                    colCyan(); printf("DO YOU LIKE TO IMPORT THIS ENTRY?\n");
                    colCyan(); printf("[Y] IMPORT [N] SKIP\n");
                    choice = getch();

                } while (choice != 'y' && choice != 'n');    

                switch (choice)
                {
                case 'y':
                    strcpy(pokemon[buffer].cPokeName, &tempName[6]);
                    if ( strcmp(&tempType[6],"Water") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'w';
                    }
                    else if ( strcmp(&tempType[6],"Fire") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'f';
                    }                
                    else if ( strcmp(&tempType[6],"Grass") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'g';
                    }
                    else if ( strcmp(&tempType[6],"Electric") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'e';
                    }
                    strcpy(pokemon[buffer].cPokeDesc, &tempDesc[13]);
                    buffer++;
                    nPkCtr++;
                    colGreen(); printf("\n// IMPORT SUCCESFUL! //\n");
                    colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                    getch();
                    break;
                
                case 'n':
                    colRed(); printf("\n// IMPORT SKIPPED! //\n");
                    colYellow(); printf("\n\n// PRESS ANY KEY TO CONTINUE //\n");
                    getch();
                    // buffer = buffer; // visual code confirmation that Imported Counter remains stagnant
                    // nPkCtr = nPkCtr; // visual code confirmation that Pokemon Counter remains stagnant
                    break;
                }
            }
            else if (Search(&tempName[6], nPkCtr, pokemon) == 1)
            {
                system("cls");
                colCyan(); printf("\n// IMPORTED RESULTS //\n");
                colRed(); printf("THIS POKEMON ALREADY EXISTS\n");

                do
                {
                    colYellow(); printf("\n[Y] OVERWRITE DUPLICATE IMPORT\n");
                    printf("[N] SKIP DUPLICATE IMPORT\n"); colReset();
                    dupChoice = getch();
                } while (dupChoice != 'y' && dupChoice != 'n');

                switch (dupChoice)
                {
                    case 'y':
                        system ("cls");
                        colGreen(); printf("\n// OVERWRITING IMPORT //\n");
                        
                        do
                        {
                            system ("cls");
                            nPkCtr = addEntry(nPkCtr, pokemon);
                        } while (nPkCtr == buffer);
            
                        buffer++;
                        printf("// IMPORT OVERWRITTEN //\n"); colReset();
                        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                        getch();
                        system ("cls");
                        break;
                    
                    case 'n':
                        colRed(); printf("\n// IMPORT SKIPPED! //\n");
                        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                        getch();
                        system("cls");
                        break;
                }
            }     
        }
        fclose(fp);
    }

    return nPkCtr;
}

// RESEARCH TASK FUNCTIONS
void researchDisplayAllEntries(int nPkCtr, struct pokemonstruct pokemon[],  int nRsrchCtr) //DISAPLYING ALL ENTRIES WITH NAME ONLY
{
    int i; // for loop

    if (nPkCtr == 0) {  
        colYellow();
        boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(46, 5); printf("REVIEW RESEARCH PER POKEMON\n");

        colRed();
        gotoxy(57, 7); printf("!!!!!");
        gotoxy(52, 8); printf("NO ENTRIES FOUND");
        colYellow(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    else {
        gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL ENTRIES //\n");
        gotoxy(1,3); printf(" ");
        for ( i = 0; i < nPkCtr; i++)
        {   
            colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
            colGreen(); printf("\n POKEMON NAME: %s\n", pokemon[i].cPokeName); colReset();
        }
    }
}

void researchDisplayEntry(int i, struct pokemonstruct pokemon[],  int nRsrchCtr) // FOR DISPLAYING ENTRY WITH ALL THE RESEARCH TASKS
{
    int j;

        // printf("Entry No. %d\n", pokemon[i].entry); //prints entry no.
        // printf("Pokemon Name: %s\n", pokemon[i].cPokeName); //prints Pokemon Name

        colCyan(); printf("\n || ENTRY #%d ||\n", pokemon[i].entry);
        colCyan(); printf("\n POKEMON NAME: %s\n", pokemon[i].cPokeName); colReset();

        for (j = 0; j < nRsrchCtr; j++) //for looop for the bonus points
        {
            switch (j)
            {
            case 0:
                colGreen(); printf(" SEEN: %d \n",  pokemon[i].nResearchType[0]);
                break;
            case 1:
                colRed(); printf(" DEFEATED: %d \n",  pokemon[i].nResearchType[1]);
                break;
            default:
                break;
            }
        }
}

void reviewResearchPerPokemon(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr) // Review Research Task per Pokemon
{
    int entry; // entry is for the entry to find
    
    if (nPkCtr == 0)
    {
        colYellow();
        boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(46, 5); printf("REVIEW RESEARCH PER POKEMON\n");

        colRed();
        gotoxy(57, 7); printf("!!!!");
        gotoxy(51, 8); printf("NO ENTRIES FOUND");
        colYellow(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    else
    {
        do //for verification kung yung ineedit ay within the possible range
        {   
            system ("cls"); 
            researchDisplayAllEntries(nPkCtr,pokemon, nRsrchCtr); //Displaying all Pokemon Entries with names lang

            colYellow();
            boxMaker(46, 78, 4, 12, 47, 77, 5, 11);
            gotoxy(49, 5); printf("REVIEW RESEARCH PER POKEMON");

            // printf("\nWhat entry do you want to find: ");
            gotoxy(51, 8); printf("CHOOSE ENTRY TO REVIEW:");
            gotoxy(51, 9); scanf(" %d", &entry);

            if (entry > nPkCtr || entry <= 0 ) //saying na mali if more than the maximum entry ang ininput || 0 or less
            {
                // printf("Oops! This entry does not exist.");
                system("cls");
                colYellow();
                boxMaker(46, 78, 4, 12, 47, 77, 5, 11);
                gotoxy(49, 5); printf("REVIEW RESEARCH PER POKEMON");

                // printf("\nWhat entry do you want to find: ");
                gotoxy(60, 7); colRed(); printf("OOPS!");
                gotoxy(50, 8); colRed(); printf("THIS ENTRY DOESN'T EXIST.");
                gotoxy(50, 11); colYellow(); printf("*PRESS ANY KEY TO RETRY*"); colReset();
                getch();
            }
        } while (entry > nPkCtr || entry <= 0 ); // this will happen until valid number is inputted

        system ("cls");
        printf("// REVIEW RESEARCH PER POKEMON RESULTS // \n");
        researchDisplayEntry(entry-1, pokemon, nRsrchCtr); // display the entry for correction to the user
        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n"); colReset();
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
                gotoxy(49, 9); printf("[1] SEEN");
                break;
            case 1:
                gotoxy(49, 10); printf("[2] DEFEATED");
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
        // printf ("What Research Type are you searching for?\n");
        // displayResTaskType(nRsrchCtr); // For displaying the lists of research task type

        system ("cls");
        colYellow();
        boxMaker(46, 81, 4, 15, 47, 80, 5, 14);
        gotoxy(52, 5); printf("REVIEW RESEARCH PER TYPE");
        gotoxy(49, 8); printf ("SELECT RESEARCH TYPE TO REVIEW");
        // gotoxy(49, 9); printf("[1] SEEN");
        // gotoxy(49, 10); printf("[2] DEFEATED");
        displayResTaskType(nRsrchCtr); // For displaying the lists of research task type
        gotoxy (49, 12); printf("ENTER VALUE: "); 
        scanf(" %d", &inType);

        // if (inType <= 0 || inType > nRsrchCtr) // saying na mali if more than the maximum entry ang ininput || 0 or less
        //     {
        //         printf("Oops! This type does not exist.");
        //     }

        if (inType !=1 && inType != 2) //saying na mali if more than the maximum entry ang ininput || 0 or less
        {
            // printf("Oops! This entry does not exist.");
            system("cls");
            colYellow();
            boxMaker(46, 78, 4, 12, 47, 77, 5, 11);
            gotoxy(49, 5); printf("REVIEW RESEARCH PER POKEMON");

            // printf("\nWhat entry do you want to find: ");
            gotoxy(60, 7); colRed(); printf("OOPS!");
            gotoxy(50, 8); colRed(); printf("THIS TYPE DOESN'T EXIST.");
            gotoxy(50, 11); colYellow(); printf("*PRESS ANY KEY TO RETRY*"); colReset();
            getch();
        }

    } while (inType !=1 && inType != 2);

    inType--; // decrement para magstart sa index 0
    
    for (i = 0; i < nPkCtr; i++) // for displaying the entries
    {
        if(pokemon[i].nResearchType[inType] > 0) // if value is 0, do not include in the display
        {
            system("cls");
            // displayEntryByResTaskType(i, pokemon, nRsrchCtr, inType); //display entry with the specific research task
            // printf("\n");
            gotoxy(1, 2);
            colYellow(); printf("// DISPLAYING ALL ENTRIES //\n");
            colCyan(); printf("\n || ENTRY #%d ||\n", pokemon[i].entry);
            colCyan(); printf("\n POKEMON NAME: %s\n", pokemon[i].cPokeName); colReset();

            switch (inType)
            {
            case 0:
                colGreen(); printf(" SEEN: %d\n",  pokemon[i].nResearchType[0]); colReset();
                break;
            case 1:
                colRed(); printf(" DEFEATED: %d\n",  pokemon[i].nResearchType[1]); colReset();
                break;
            default:
                break;
            }

            exist = 1;
            colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n"); colReset();
            getch();
        }
    }
    
    if (exist == 0) // if all entries value of task type is 0
    {
        // printf("All pokemon in this specific type were all valued as 0.\n\n");

        system ("cls");
        colYellow();
        boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(47, 5); printf("REVIEW RESEARCH PER TYPE\n");

        colRed();
        gotoxy(57, 7); printf("!!!!");
        gotoxy(51, 8); printf("NO MATCHES FOUND");
        colYellow(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }

    showTopFive(nPkCtr,pokemon, nRsrchCtr, inType);
}

void displayEntryByResTaskType(int i, struct pokemonstruct pokemon[],  int nRsrchCtr, int inType) //display entry with the specific research task
{
    // nRsrchCtr WAS NOT USED, WILL ONLY BE USED FOR BONUS POINTS.
        colCyan(); printf(" || ENTRY NO. %d ||\n", pokemon[i].entry); //prints entry no.
        colPurple(); printf(" POKEMON NAME: %s\n", pokemon[i].cPokeName); //prints Pokemon Name

        switch (inType)
        {
        case 0:
            colGreen(); printf(" SEEN: %d\n",  pokemon[i].nResearchType[0]); colReset();
            break;
        case 1:
            colRed(); printf(" DEFEATED: %d\n",  pokemon[i].nResearchType[1]); colReset();
            break;
        default:
            break;
        }
}

void updateResearchTask(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr) //Update Research Task
{
    int inType,entry,nValue;
    int i = 0;
    int exist = 0;

    do { //FOR ASKING WHAT TASK TO UPDATE

        system ("cls");
        colYellow();
        boxMaker(46, 81, 4, 15, 47, 80, 5, 14);
        gotoxy(54, 5); printf("UPDATE RESEARCH TASK");
        gotoxy(49, 8); printf ("SELECT RESEARCH TYPE TO UPDATE");
        displayResTaskType(nRsrchCtr); // For displaying the lists of research task type
        gotoxy (49, 12); printf("ENTER TYPE VALUE: "); scanf(" %d", &inType);

        // if (inType <= 0 || inType > nRsrchCtr) //saying na mali if more than the maximum entry ang ininput || 0 or less
        //     {
        //         printf("Oops! This type does not exist.");
        //     }

        if (inType !=1 && inType != 2) //saying na mali if more than the maximum entry ang ininput || 0 or less
        {
            // printf("Oops! This entry does not exist.");
            system("cls");
            colYellow();
            boxMaker(46, 78, 4, 12, 47, 77, 5, 11);
            gotoxy(49, 5); printf("REVIEW RESEARCH PER POKEMON");

            // printf("\nWhat entry do you want to find: ");
            gotoxy(60, 7); colRed(); printf("OOPS!");
            gotoxy(50, 8); colRed(); printf("THIS TYPE DOESN'T EXIST.");
            gotoxy(50, 11); colYellow(); printf("*PRESS ANY KEY TO RETRY*"); colReset();
            getch();
        }
    } while (inType !=1 && inType != 2);

    inType--; // to decrement para magtugma sa program indexing

    // researchDisplayAllEntries(nPkCtr,pokemon, nRsrchCtr);
    
    if (nPkCtr == 0) // FOR UPDATING THE RESEARCH TASK OF A POKEMON, IF WALANG LAMAN, THEN THIS CODE WILL RUN
    {
        system ("cls");
        colYellow();
        boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(49, 5); printf("UPDATE RESEARCH TASK\n");

        colRed();
        gotoxy(56, 7); printf("!!!!!");
        gotoxy(51, 8); printf("NO ENTRIES FOUND");
        colYellow(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    else
    {
        do //for verification kung yung ineedit ay within the possible range
        {
            system ("cls");
            
            researchDisplayAllEntries(nPkCtr,pokemon, nRsrchCtr);   
            colYellow();
            boxMaker(46, 81, 4, 15, 47, 80, 5, 14);
            gotoxy(54, 5); printf("UPDATE RESEARCH TASK");
            gotoxy(49, 8); printf ("CHOOSE ENTRY TO UPDATE");
            gotoxy (49, 9); printf("ENTER ENTRY #: "); scanf(" %d", &entry);
        
            if (entry > nPkCtr || entry <= 0 ) //saying na mali if more than the maximum entry ang ininput || 0 or less
            {
                // printf("Oops! This entry does not exist.");

                system ("cls");
                colYellow();
                boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
                gotoxy(49, 5); printf("UPDATE RESEARCH TASK\n");

                colRed();
                gotoxy(57, 7); printf("!!!!!");
                gotoxy(48, 8); printf("THIS ENTRY DOESN'T EXIST");
                colYellow(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
                getch();

            }
        } while (entry > nPkCtr || entry <= 0 ); // this will happen until valid number is inputted

            entry--;// to decrement para magtugma sa program indexing
    
            // printf("You are trying to update: \n");

            do // abcd = do while loop implemented while nValue is a negative number
            {
            system ("cls");
            colYellow();
            // boxMaker(46, 81, 4, 15, 47, 80, 5, 14);
            boxMaker(43, 84, 4, 20, 44, 83, 5, 19);
            gotoxy(54, 5); printf("UPDATE RESEARCH TASK");
 
            // displayEntryByResTaskType(entry, pokemon, nRsrchCtr, inType); // display the entry for correction to the user

            gotoxy(46, 9); printf("ENTRY NO. %d\n", pokemon[entry].entry); //prints entry no.
            gotoxy(46, 10); printf("POKEMON NAME: %s\n", pokemon[entry].cPokeName); //prints Pokemon Name

            switch (inType)
            {
            case 0:
                gotoxy(46, 11); colGreen(); printf("SEEN: %d\n",  pokemon[entry].nResearchType[0]); colReset();
                break;
            case 1:
                gotoxy(46, 11); colRed(); printf("DEFEATED: %d\n",  pokemon[entry].nResearchType[1]); colReset();
                break;
            default:
                break;
            }
            
                gotoxy(46, 13); colCyan(); printf("ENTER INCREMENT AMOUNT: ");
                gotoxy(46, 14); scanf(" %d", &nValue);
            } while (nValue < 0);
            

            pokemon[entry].nResearchType[inType] = pokemon[entry].nResearchType[inType] + nValue;

            // gotoxy(46, 16); printf("TASK INCREMENTED.");
            gotoxy(51, 19); colYellow(); printf("*PRESS ANY KEY TO CONTINUE*");

            gotoxy(1, 2); printf("// UPDATED ENTRY //");
            gotoxy(1, 3); researchDisplayEntry(entry, pokemon, nRsrchCtr); // display the entry for correction to the user
            getch();
    }

}

void showTopFive(int nPkCtr, struct pokemonstruct pokemon[],int nRsrchCtr, int inType)
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

    if (nPkCtr >= 4)
    {
        if(pokemon[A[0]].nResearchType[inType] > 0) // this is to check if the highest has a value, pag wala, it means 0 lahat and therefore, no top 5
        {
            system("cls");
            colYellow(); printf("\n// TOP POKEMONS (MAX. 5) //\n\n");
        } 
        else 
        {
            system("cls");
            colRed(); printf("\n// NO TOP FIVE POKEMONS //\n\n");
        }

        for (h = 0; h < 5; h++) //this will print the top 5 pokemons
        {
            if(pokemon[A[h]].nResearchType[inType] > 0)
            {
                displayEntryByResTaskType(A[h], pokemon, nRsrchCtr, inType); //display entry with the specific research task
                printf("\n");
            }
            
        }
        colYellow(); printf("// PRESS ANY KEY TO CONTINUE //\n");
        getch();        
    }    
}

// CODE DESIGN/UI FUNCTIONS
void gotoxy(int x, int y){
    printf("%c[%d;%df", 0x1B, y, x); // places succeeding lines of print() to the coordinates passed onto it 
}

void colReset(){
    printf("\033[0;37m"); // white
}

void colCyan(){
    printf("\033[0;36m"); // cyan
}

void colBlue(){
    printf("\033[0;34m"); // blue
}

void colRed(){
    printf("\033[0;31m"); // red
}

void colYellow(){
    printf("\033[0;33m"); // yellow
}

void colGreen(){
    printf("\033[0;32m"); // green
}

void colPurple(){
    printf("\033[0;35m");
}