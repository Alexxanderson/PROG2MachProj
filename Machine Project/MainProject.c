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
void modifyEntry(int i);

//main
int main()
{
    int i;
    clrscr();

    for (i=0;i<1; ++i)
    {
        addEntry(i);
    }
    printf("\n");

    for ( i = 0; i < 1; i++)
    {
        displayEntry(i);
    }
    printf("\n");

    modifyEntry(0);

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

void modifyEntry(int i)
{
    char choice;
    char modify = 'Y';

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