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
void displayEntries(int i);

//main
int main()
{
    int i;
    clrscr();

    for (i=0;i<2; ++i) // test code
    {
        addEntry(i);
    }

    for ( i = 0; i < 2; i++) //test code
    {
        displayEntries(i);
    }

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