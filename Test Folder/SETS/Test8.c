#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENTRYMAX 150
typedef char String[21];

struct pokemonstruct
{
    int entry;
    char cPokeName[21];
    char cPokeType;
    char cPokeDesc[51];
};

// int addEntry(int i, int entry, char cPokeName[], char cPokeType, char cPokeDesc[])
// {
//     char inName[21];

//     printf ("Enter pokemon name: "); 
//          fgets(inName, 21, stdin); //for getting and storing the pokemon name
//          inName[strcspn(inName, "\n")] = 0; // clears the \n stored in the string galing sa fgets function

//          if (Search(inName, i) == 1)
//          {
//              printf("This pokemon exist. \n\n");
//          } else
//          {

//         pokemon[i].entry = i + 1; // initialize entry number based from the array no.
//          printf ("For Entry no. %d, \n", pokemon[i].entry);

//          strcpy(pokemon[i].cPokeName, inName);
//          printf("Name: %s \n", pokemon[i].cPokeName);

//          printf ("Is the pokemon [W]Water, [F]Fire, [G]Grass, [E]Electric");
//          pokemon[i].cPokeType = getch(); //getch nalang so that it's clean and walang further bugs na magkameron, altho stored char is the small letter
//          printf("\n");
//          printf("Description: ");
//          fgets(pokemon[i].cPokeDesc,51, stdin); //for getting and storing the pokemon description
//          pokemon[i].cPokeDesc[strcspn(pokemon[i].cPokeDesc, "\n")] = 0; // clears the \n stored in the string galing sa fgets function

//         //Still needs some verification
//         i++;
//          }

//     return i;

// }

// int Search(char key[], int nPkCtr, char A[][]) //search function, strings only
// {
//    int i;
//    int found = -1;

//    for (i = 0; i < nPkCtr; i++)
//    {
//       if (strcmp(key, pokemon[i].cPokeName) == 0)
//          {
//             found = 1;
//          }
//    }
   
//    if (found == 1)
//    {
//       return 1;
//    } else
//    {
//       return -1;
//    }
// }

void clrscr() // Clear Screen
{
    system("@cls||clear");
}

void try(struct pokemonstruct pokemon[], int nElem)
{
    int i;
    for (i = 0; i < nElem; i++)
    {
        printf ("Enter pokemon name: "); 
         fgets(pokemon[i].cPokeName, 21, stdin); //for getting and storing the pokemon name
         pokemon[i].cPokeName[strcspn(pokemon[i].cPokeName, "\n")] = 0; // clears the \n stored in the string galing sa fgets function

       printf(" %s\n", pokemon[i].cPokeName);
    }
    
}

int main()
{
    struct pokemonstruct pokemon[5];
    int ctr = 0;
    String A[2];
    int nPkCtr = 0; // Counter of how many pokemon are indexed && current index that has no value, will be utilized for addEntry
    char cExit = 'N';
    clrscr();

        printf ("Enter pokemon name: "); 
         fgets(pokemon[0].cPokeName, 21, stdin); //for getting and storing the pokemon name
         pokemon[0].cPokeName[strcspn(pokemon[0].cPokeName, "\n")] = 0; // clears the \n stored in the string galing sa fgets function

        printf ("Enter pokemon name: "); 
         fgets(pokemon[1].cPokeName, 21, stdin); //for getting and storing the pokemon name
         pokemon[1].cPokeName[strcspn(pokemon[1].cPokeName, "\n")] = 0; // clears the \n stored in the string galing sa fgets function

            printf ("Enter name: "); 
         fgets(A[0], 21, stdin); //for getting and storing the pokemon name
        A[0][strcspn(A[0], "\n")] = 0; // clears the \n stored in the string galing sa fgets function

        printf ("Enter name: "); 
         fgets(A[1], 21, stdin); //for getting and storing the pokemon name
         A[1][strcspn(A[1], "\n")] = 0; // clears the \n stored in the string galing sa fgets function

    printf(" %s", pokemon[0].cPokeName);
    printf(" %s\n", pokemon[1].cPokeName);

    printf(" %s", A[0]);
    printf(" %s\n", A[1]);

    printf("\n\n");

    try(pokemon, 2);

    printf(" %s", pokemon[0].cPokeName);
    printf(" %s\n", pokemon[1].cPokeName);




        
        // do
        // {
        //     menu(); // Display Menu
        //     cDc = getch();  
        //     printf("\n");

        //     switch (cDc) //dito mangyayari yung modification
        //     {
        //     case 'a': // Add Entry                
        //         nPkCtr = addEntry(nPkCtr);
        //         break;
        //     case 'm': // Modify Entry
        //         printf("%d", nPkCtr);
        //         modifyEntry(nPkCtr);                
        //         break;
        //     case 'd': // Delete Entry
        //         deleteEntry(nPkCtr);
        //         nPkCtr--;
        //         break;
        //     case 'l': // Display All Entries
        //         displayAllEntries(nPkCtr);
        //         break;
        //     case 's': // Search Pokemon
        //         searchPokeByName(nPkCtr);
        //         break;
        //     case 'p': // Search Pokemon by type
        //         searchPokeByType(nPkCtr);
        //         break;
        //     case 'r': // Research Tasks            
        //         break;
        //     case 'e': // Export
        //         break;
        //     case 'i': // Import
        //         break;
        //     default:                
        //         printf ("Do you want to exit the Pokedex? [Y]Yes [N]No\n" );
        //         cExit = getch(); // asks the user to reloop, if no, loop breaks, funcion ends also here
        //         printf("\n");
        //         break;
        //     }
        // } while (cExit == 'N' || cExit == 'n');

        //  printf("\n");



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