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

void addEntry(int* pokeEntry, char* pokeName[21], char* pokeType, char* pokeDesc[51],int i)
{
        *pokeEntry = i + 1;
         printf ("For Entry no. %d, \n", *pokeEntry);
         printf ("Enter pokemon name: ");
         fgets(pokeName, 21, stdin);
         printf ("Is the pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric: ");
         scanf(" %c", pokeType);
         printf("Description: ");
         fgets(pokeDesc,51, stdin); //double copy because scanf issue
         fgets(pokeDesc,51, stdin);
         printf("\n");
}

void displayEntries(int pokeEntry, char pokeName[21], char pokeType, char pokeDesc[51],int i)
{
        printf("Entry No. %d\n",pokeEntry);
        printf("Pokemon Name: %s", pokeName); // this should have an \n
        printf("Pokemon Type: %c\n", pokeType);
        printf("Description: %s\n", pokeDesc);
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

    return 0;
}
