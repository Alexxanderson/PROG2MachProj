#include <stdio.h>
#include <string.h>

struct pokemon
{
    int entry;
    char cPokeName[21];
    char cPokeType;
    char cPokeDesc[51];
}pokemon[100];

void addEntry(int i);
void clrscr(); // Clear Screen}
void displayEntry(int i);

void modifyEntry(int i)
{
    char choice;
    char modify = 'Y';
        printf ("You are modifying entry no. %d, \n", pokemon[i].entry);
        printf("Pokemon Name: %s\n", pokemon[i].cPokeName); // this should have an \n
        printf("Pokemon Type: %c\n", pokemon[i].cPokeType);
        printf("Description: %s\n", pokemon[i].cPokeDesc);

        do
        {
            printf("What do you want to modify? \n[n]Name, [t]Type, or [d]Description [any]Exit ");
            choice = getch();
            printf("\n");

            switch (choice)
            {
            case 'n':
                printf ("Enter pokemon name: ");
                fgets(pokemon[i].cPokeName, 21, stdin);
                pokemon[i].cPokeName[strcspn(pokemon[i].cPokeName, "\n")] = 0;
                printf("Pokemon Name: %s\n", pokemon[i].cPokeName);
                printf ("Do you want to modify more? [Y]Yes [N]No");
                modify = getch();
                printf("\n");
                break;
            case 't':
                printf ("Is the pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric");
                pokemon[i].cPokeType = getch();
                printf("\n");
                printf("Pokemon Type: %c\n", pokemon[i].cPokeType);
                printf ("Do you want to modify more? [Y]Yes [N]No");
                modify = getch();
                printf("\n");
                break;
            case 'd':
                printf("Description: ");
                fgets(pokemon[i].cPokeDesc,51, stdin);
                pokemon[i].cPokeName[strcspn(pokemon[i].cPokeName, "\n")] = 0;
                printf("Description: %s\n", pokemon[i].cPokeDesc);
                printf ("Do you want to modify more? [Y]Yes [N]No");
                modify = getch();
                printf("\n");
                break;
            default:
                displayEntry(i);
                printf ("Do you want further edits? [Y]Yes [N]No");
                modify = getch();
                printf("\n");
                break;
            }

        } while (modify == 'y' || modify == 'Y');



         printf("\n");
}

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
        pokemon[i].entry = i + 1;
         printf ("For Entry no. %d, \n", pokemon[i].entry);
         printf ("Enter pokemon name: ");
         fgets(pokemon[i].cPokeName, 21, stdin);
         pokemon[i].cPokeName[strcspn(pokemon[i].cPokeName, "\n")] = 0; // clears the \n stored in the string
         printf ("Is the pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric");
         pokemon[i].cPokeType = getch();
         printf("\n");
         printf("Description: ");
         //fgets(pokemon[i].cPokeDesc,51, stdin); //2 fgets kasi this line gets ignored, newline problem, should be consulted for.
         fgets(pokemon[i].cPokeDesc,51, stdin);
         pokemon[i].cPokeDesc[strcspn(pokemon[i].cPokeDesc, "\n")] = 0; // clears the \n stored in the string

}

void clrscr() // Clear Screen
{
    system("@cls||clear"); //implicit declaration, needs to be consulted for
}

void displayEntry(int i)
{
        printf("Entry No. %d\n", pokemon[i].entry);
        printf("Pokemon Name: %s\n", pokemon[i].cPokeName);
        printf("Pokemon Type: %c\n", pokemon[i].cPokeType);
        printf("Description: %s\n", pokemon[i].cPokeDesc);
}
