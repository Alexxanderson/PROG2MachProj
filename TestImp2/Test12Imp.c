#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

struct pokemonstruct
{
    int entry;
    char cPokeName[21];
    char cPokeType;
    char cPokeDesc[51];
    int nResearchType[2];
};

void clrscr() // Clear Screen
{
    system("@cls||clear");
}

int main()
{
    clrscr();
    struct pokemonstruct pokemon[99];
    char inName[99];
    char ctype[99];
    char cDescp[99];


    // printf("Enter a name: ");
    // scanf(" %[^\n]s", &inName); //this is for asking the name of the file you want to get
    // printf("Enter a description: ");
    // scanf(" %[^\n]s", &cDescp); //this is for asking the name of the file you want to get

    FILE *fpointer;
    FILE *fpointsss;

    fpointsss = fopen("try3.txt","r"); // w = write, r = read, a = append ; for opening the file


        fscanf(fpointsss, " %[^\n]s", &inName); // trying to scan everything, automatically na magiiscan to the next line to sabi daw
        fscanf(fpointsss, " %[^\n]s", &ctype);
         fscanf(fpointsss, " %[^\n]s", &cDescp);

    fclose(fpointsss); // file closing

    printf(" %s\n", inName);
    printf(" %s\n", ctype);
    printf(" %s\n", cDescp);


    printf("Hello world \n");
    return 0;
}
// setMain < INPUT.txt > MIRANDA-ACTUAL.txt


    // fpointer = fopen("trystring.txt","w"); // w = write, r = read, a = append

    //    fprintf(fpointer, "The string is: %s \n", inName);
    //    fprintf(fpointer, "The type is: %c \n", ctype);
    //    fprintf(fpointer, "The description is: %s \n", cDescp);
       
    

    // fclose(fpointer);