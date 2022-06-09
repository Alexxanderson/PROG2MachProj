#include <stdio.h>
#include <string.h>

void clrscr() // Clear Screen
{
    system("@cls||clear");
}

int main()
{
    clrscr();
    char inName[20];
    char ctype = 'c';
    char cDescp[21];


    printf("Enter a name: ");
    scanf(" %[^\n]s", &inName); //this is for asking the name of the file you want to get
    printf("Enter a description: ");
    scanf(" %[^\n]s", &cDescp); //this is for asking the name of the file you want to get

    FILE *fpointer;

    fpointer = fopen("trystring.txt","w"); // w = write, r = read, a = append

       fprintf(fpointer, "The string is: %s \n", inName);
       fprintf(fpointer, "The type is: %c \n", ctype);
       fprintf(fpointer, "The description is: %s \n", cDescp);
       
    

    fclose(fpointer);

    printf("Hello world \n");
    return 0;
}
// setMain < INPUT.txt > MIRANDA-ACTUAL.txt