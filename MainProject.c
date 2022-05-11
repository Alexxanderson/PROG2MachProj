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

void addEntry(int i)
{
        pokemon[i].entry = i + 1;
         printf ("For Entry no. %d, \n", pokemon[i].entry);
         printf ("Enter pokemon name: ");
         fgets(pokemon[i].cPokeName, 21, stdin);
         printf ("Is the pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric: ");
         scanf(" %c", &pokemon[i].cPokeType);
         printf("Description: ");
         fgets(pokemon[i].cPokeDesc,51, stdin);
         fgets(pokemon[i].cPokeDesc,51, stdin);
         printf("\n");
}

void displayEntries(int i)
{
        printf("Entry No. %d\n", pokemon[i].entry);
        printf("Pokemon Name: %s\n", pokemon[i].cPokeName);
        printf("Pokemon Type: %c\n", pokemon[i].cPokeType);
        printf("Description: %s\n", pokemon[i].cPokeDesc);
}

//main
int main()
{
    int i;
    clrscr();

    for (i=0;i<2; ++i)
    {
        addEntry(i);
    }

    for ( i = 0; i < 2; i++)
    {
        displayEntries(i);
    }

    return 0;
}
