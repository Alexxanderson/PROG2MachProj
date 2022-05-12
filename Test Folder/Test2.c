#include <stdio.h>
#include <string.h>

struct pokemon
{
    int entry;
    char cPokeName[21];
    char cPokeType;
    char cPokeDesc[51];
}pokemon[999];

void addEntry(int i);
void clrscr(); // Clear Screen}
void displayEntry(int i);
void displayAllEntries(int nPkCtr);
void menu();
void modifyEntry(int nPkCtr);

//main
int main()
{
    int nPkCtr = 0; // Counter of how many pokemon are indexed && current index that has no value, will be utilized for addEntry
    char cDc;
    char cExit = 'Y';
    clrscr();
        
        do
        {
            menu(); // Display Menu
            cDc = getch();  
            printf("\n");

            switch (cDc) //dito mangyayari yung modification
            {
            case 'a': // Add Entry
                addEntry(nPkCtr);
                nPkCtr++;
                break;
            case 'm': // Modify Entry
                printf("%d", nPkCtr);
                modifyEntry(nPkCtr);                
                break;
            case 'd': // Delete Entry
                break;
            case 'l': // Display All Entries
                displayAllEntries(nPkCtr);
                break;
            case 's': // Search Pokemon
                break;
            case 'r': // Research Tasks            
                break;
            case 'e': // Delete Entry
                break;
            case 'i': // Delete Entry
                break;
            default:                
                printf ("Do you want to exit the Pokedex? [Y]Yes [N]No\n" );
                cExit = getch(); // asks the user to reloop, if no, loop breaks, funcion ends also here
                printf("\n");
                break;
            }
        } while (cExit == 'y' || cExit == 'Y');



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

void addEntry(int i)
{
        pokemon[i].entry = i + 1; // initialize entry number based from the array no.
         printf ("For Entry no. %d, \n", pokemon[i].entry);
         printf ("Enter pokemon name: "); 
         fgets(pokemon[i].cPokeName, 21, stdin); //for getting and storing the pokemon name
         pokemon[i].cPokeName[strcspn(pokemon[i].cPokeName, "\n")] = 0; // clears the \n stored in the string galing sa fgets function
         printf ("Is the pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric");
         pokemon[i].cPokeType = getch(); //getch nalang so that it's clean and walang further bugs na magkameron, altho stored char is the small letter
         printf("\n");
         printf("Description: ");
         fgets(pokemon[i].cPokeDesc,51, stdin); //for getting and storing the pokemon description
         pokemon[i].cPokeDesc[strcspn(pokemon[i].cPokeDesc, "\n")] = 0; // clears the \n stored in the string galing sa fgets function

        //Still needs some verification

}

void clrscr() // Clear Screen
{
    system("@cls||clear"); //implicit declaration, needs to be consulted for
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
    printf("[S]Search POkemon \n");
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