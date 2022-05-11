#include <stdio.h>

void clrscr() // Clear Screen
{
    system("@cls||clear");
}

struct pokemon
{
    int entry;
    char cPokeName[21];
    char cPokeType;
    char cPokeDesc[51];
}pokemon[100];

void addEntry(int i);
void clrscr(); // Clear Screen}
void displayEntries(int i);

void modifyEntry(int* pokeEntry, char* pokeName[21], char* pokeType, char* pokeDesc[51],int i)
{
    char choice;
    int modify = 1;
        printf ("You are modifying entry no. %d, \n", *pokeEntry);
        printf("Pokemon Name: %s", pokeName); // this should have an \n
        printf("Pokemon Type: %c\n", pokeType);
        printf("Description: %s\n", pokeDesc);

        do
        {
            printf("What do you want to modify? \n[n]Name, [t]Type, or [d]Description [any]Exit: ");
            getchar(choice);

            switch (choice)
            {
            case 'n':
                printf ("Enter pokemon name: ");
                fgets(pokeName, 21, stdin);
                printf ("Do you want to modify more? [1]Yes [0]No");
                scanf("%d", &choice);
                break;
            case 't':
                printf ("Is the pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric: ");
                scanf(" %c", pokeType);
                printf ("Do you want to modify more? [1]Yes [0]No");
                scanf("%d", &choice);
                break;
            case 'd':
                printf("Description: ");
                fgets(pokeDesc,51, stdin);
                printf ("Do you want to modify more? [1]Yes [0]No");
                scanf("%d", &choice);
                break;
            default:
                modify = 0;
                break;
            }

        } while (modify == 1);



         printf("\n");
}

//main
int main()
{
    int i;
    clrscr();

    for (i=0;i<2; ++i)
    {
        addEntry(&pokemon[i].entry, &pokemon[i].cPokeName, &pokemon[i].cPokeType,&pokemon[i].cPokeDesc, i);
    }

    for ( i = 0; i < 2; i++)
    {
        displayEntries(pokemon[i].entry, pokemon[i].cPokeName, pokemon[i].cPokeType,pokemon[i].cPokeDesc, i);
    }

    modifyEntry(&pokemon[i].entry, &pokemon[i].cPokeName, &pokemon[i].cPokeType,&pokemon[i].cPokeDesc, 0);

    return 0;
}

void addEntry(int i)
{
        pokemon[i].entry = i + 1;
         printf ("For Entry no. %d, \n", pokemon[i].entry);
         printf ("Enter pokemon name: ");
         fgets(pokemon[i].cPokeName, 21, stdin);
         printf ("Is the pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric: ");
         scanf(" %c", &pokemon[i].cPokeType);
         printf("Description: ");
         fgets(pokemon[i].cPokeDesc,51, stdin); //2 fgets kasi this line gets ignored, newline problem, should be consulted for.
         fgets(pokemon[i].cPokeDesc,51, stdin);
         printf("\n");
}

void clrscr() // Clear Screen
{
    system("@cls||clear"); //implicit declaration, needs to be consulted for
}

void displayEntries(int i)
{
        printf("Entry No. %d\n", pokemon[i].entry);
        printf("Pokemon Name: %s\n", pokemon[i].cPokeName);
        printf("Pokemon Type: %c\n", pokemon[i].cPokeType);
        printf("Description: %s\n", pokemon[i].cPokeDesc);
}