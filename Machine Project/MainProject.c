#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define ENTRYMAX 150

struct pokemon
{
    int entry;
    char cPokeName[21];
    char cPokeType;
    char cPokeDesc[51];
}pokemon[ENTRYMAX];

int addEntry(int i);
void clrscr(); // Clear Screen
void deleteEntry(int nPkCtr);
void displayEntry(int i);
void displayAllEntries(int nPkCtr);
void menu();
void modifyEntry(int nPkCtr);
int Search(char key[], int nPkCtr);
void searchPokeByName(int nPkCtr);
void searchPokeByType(int nPkCtr);



//main
int main()
{
    int nPkCtr = 0; // Counter of how many pokemon are indexed && current index that has no value, will be utilized for addEntry
    char cDc;
    char cExit = 'N';
    clrscr();
        
        do
        {
            menu(); // Display Menu
            cDc = getch();  
            printf("\n");

            switch (cDc) //dito mangyayari yung modification
            {
            case 'a': // Add Entry                
                nPkCtr = addEntry(nPkCtr);
                break;
            case 'm': // Modify Entry
                printf("%d", nPkCtr);
                modifyEntry(nPkCtr);                
                break;
            case 'd': // Delete Entry
                deleteEntry(nPkCtr);
                nPkCtr--;
                break;
            case 'l': // Display All Entries
                displayAllEntries(nPkCtr);
                break;
            case 's': // Search Pokemon
                searchPokeByName(nPkCtr);
                break;
            case 'p': // Search Pokemon by type
                searchPokeByType(nPkCtr);
                break;
            case 'r': // Research Tasks            
                break;
            case 'e': // Export
                break;
            case 'i': // Import
                break;
            default:                
                printf ("Do you want to exit the Pokedex? [Y]Yes [N]No\n" );
                cExit = getch(); // asks the user to reloop, if no, loop breaks, funcion ends also here
                printf("\n");
                break;
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

int addEntry(int i)
{
    char inName[21];

    printf ("Enter pokemon name: "); 
         fgets(inName, 21, stdin); //for getting and storing the pokemon name
         inName[strcspn(inName, "\n")] = 0; // clears the \n stored in the string galing sa fgets function

         if (Search(inName, i) == 1)
         {
             printf("This pokemon exist. \n\n");
         } else
         {

        pokemon[i].entry = i + 1; // initialize entry number based from the array no.
         printf ("For Entry no. %d, \n", pokemon[i].entry);

         strcpy(pokemon[i].cPokeName, inName);
         printf("Name: %s \n", pokemon[i].cPokeName);

         printf ("Is the pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric");
         pokemon[i].cPokeType = getch(); //getch nalang so that it's clean and walang further bugs na magkameron, altho stored char is the small letter
         printf("\n");
         printf("Description: ");
         fgets(pokemon[i].cPokeDesc,51, stdin); //for getting and storing the pokemon description
         pokemon[i].cPokeDesc[strcspn(pokemon[i].cPokeDesc, "\n")] = 0; // clears the \n stored in the string galing sa fgets function

        //Still needs some verification
        i++;
         }

    return i;

}

void clrscr() // Clear Screen
{
    system("@cls||clear"); //implicit declaration, needs to be consulted for
}

void deleteEntry(int nPkCtr) // Delete Entry
{
    int i,j; // i is for the actual index, j for the for loop
    char cDec; // Decision;
    do //for verification kung yung ineedit ay within the possible range
    {
        printf("What entry do you want to delete: ");
        scanf(" %d", &i); // BUGGGGED NEED TO REMOVE THE NEWLINE CHARACTER;
    
        if (i >= nPkCtr || i <=0 ) //saying na mali if more than the maximum entry ang ininput || 0 or less
        {
            printf("I'm Sorry, this index does not exist.");
            getch();
        }

    } while (i >= nPkCtr || i <=0 ); // this shit will happen until valid number is inputted
    i = i-1;

    printf("You are deleting: \n");
    displayEntry(i); // display the entry for correction to the user
    printf("\n");
    printf("Are you sure you want to delete this Entry? [Y]Yes or [N]No \n"); // verification
    cDec = getch();

    if (cDec == 'y' || cDec == 'y')
    {
        for (j = i ; j < nPkCtr; j++) // for loop that adjust the index, basically, the deleted entry will copy the entry next to it.
        {
            strcpy (pokemon[j].cPokeName, pokemon[j+1].cPokeName);
            pokemon[j].cPokeType = pokemon[j+1].cPokeType;
            strcpy (pokemon[j].cPokeDesc, pokemon[j+1].cPokeDesc);
        }
        printf("Entry Deleted.\n");
        printf("Pokedex Readjusted\n");
        getch();
    }

}

void displayEntry(int i)
{
        printf("Entry No. %d\n", pokemon[i].entry); //prints entry no.
        printf("Pokemon Name: %s\n", pokemon[i].cPokeName); //prints Pokemon Name
        printf("Pokemon Type: %c\n", pokemon[i].cPokeType); //prints Pokemon Type [character pa lang to]
        printf("Description: %s\n", pokemon[i].cPokeDesc); //prints Pokermon Decription
}
void displayAllEntries(int nPkCtr)
{
    int i;
    for ( i = 0; i < nPkCtr; i++)
    {
        displayEntry(i);
        printf("\n");
    }
    getch();
}

void menu()
{
    printf("What do you want to accomplish:\n");
    printf("[A]Add Entry \n");
    printf("[M]Modify Entry \n");
    printf("[D]Delete Entry \n");
    printf("[L]Display All Entries \n");
    printf("[S]Search Pokemon \n");
    printf("[R]Research tasks \n");
    printf("[E]Export \n");
    printf("[I]Import \n");
    printf("[Any]Exit \n");
}

void modifyEntry(int nPkCtr)
{
    int i; // for identifying what entry to modify
    char choice;
    char modify = 'Y';

    do
    {
        printf("What entry do you want to modify: ");
    scanf("%d", &i); // BUGGGGED NEED TO REMOVE THE NEWLINE CHARACTER;
    scanf("%d", &i); // BUGGGGED NEED TO REMOVE THE NEWLINE CHARACTER;
    
    if (i >= nPkCtr || i <=0 )
    {
        printf("I'm Sorry, this index does not exist.");
        getch();
    }
    } while (i >= nPkCtr || i <=0 );

    i = i-1; // this is the actual index.

        printf ("You are modifying this entry\n"); // These prints the basic info
        displayEntry(i);
        printf("\n");
        
        do
        {
            printf("What do you want to modify? \n[n]Name, [t]Type, or [d]Description [any]Exit \n"); //question
            choice = getch(); // gets anong gusto gawin ng user
            printf("\n");

            switch (choice) //dito mangyayari yung modification
            {
            case 'n':
                printf ("Enter pokemon name: ");
                fgets(pokemon[i].cPokeName, 21, stdin); //for getting and storing the pokemon name
                pokemon[i].cPokeName[strcspn(pokemon[i].cPokeName, "\n")] = 0; //removes the \n inside the string
                printf("Pokemon Name: %s\n", pokemon[i].cPokeName); //for verificcation, subject for removal
                printf ("Do you want to modify more? [Y]Yes [N]No");
                modify = getch(); // asks the user for more modification and to reloop or not
                printf("\n"); // newline, subject to change
                break;
            case 't':
                printf ("Is the pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric");
                pokemon[i].cPokeType = getch(); //storing the new Pokemon Type
                printf("\n");
                printf("Pokemon Type: %c\n", pokemon[i].cPokeType); // for verification, subject for removal
                printf ("Do you want to modify more? [Y]Yes [N]No");
                modify = getch(); // asks the user for more modification and to reloop or not
                printf("\n");
                break;
            case 'd':
                printf("Description: ");
                fgets(pokemon[i].cPokeDesc,51, stdin); //for getting and storing the pokemon description
                pokemon[i].cPokeName[strcspn(pokemon[i].cPokeName, "\n")] = 0; //removes the \n inside the string
                printf("Description: %s\n", pokemon[i].cPokeDesc); // for verification, subject for removal
                printf ("Do you want to modify more? [Y]Yes [N]No");
                modify = getch(); // asks the user for more modification and to reloop or not
                printf("\n");
                break;
            default:
                displayEntry(i); //shows entry para macheck ng user for correction
                printf ("Do you want further edits? [Y]Yes [N]No");
                modify = getch(); // asks the user to reloop, if no, loop breaks, funcion ends also here
                printf("\n");
                break;
            }

        } while (modify == 'y' || modify == 'Y');



         printf("\n");
}

int Search(char key[], int nPkCtr) //search function, strings only
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

void searchPokeByName(int nPkCtr)
{
   int j = 0;

   char inName[21];

   printf("Name of the Pokemon: ");
    fgets(inName, 21, stdin); //for getting and storing the pokemon name
    inName[strcspn(inName, "\n")] = 0; // clears the \n stored in the string galing sa fgets function

   
      if (Search(inName, nPkCtr) == 1) 
      {
          for (j = 0; j < nPkCtr; j++)
        {
            if(strcmp(inName, pokemon[j].cPokeName) == 0)
            {
                displayEntry(j);
                printf("\n");
            }
        }
      } else if (Search(inName, nPkCtr) == -1) 
      {
         printf("I'm sorry, this pokemon doesn't exist. \n\n");
      }
	
}

void searchPokeByType(int nPkCtr)
{
   int i = 0;
    int exist = 0;
   char inType;

    printf ("What type are you searching: [W]Water, [F]Fire, [G]Grass, [E]Electric \n");
    inType = getch(); //getch nalang so that it's clean and walang further bugs na magkameron, altho stored char is the small letter
   
          for (i = 0; i < nPkCtr; i++)
        {
            if(inType == pokemon[i].cPokeType)
            {
                displayEntry(i);
                printf("\n\n");
                exist = 1;
            }
        }
        if (exist == 0)
        {
             printf("No Pokemon of this type was found in this Pokedex.\n\n");
        }
       
	
}