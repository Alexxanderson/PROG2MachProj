#include <stdio.h>
#include <string.h>

#define MAX 21 //for trying to test out a lot of numbers

void clrscr() // Clear Screen
{
    system("@cls||clear");
}

int main()
{
    clrscr();

    int num[100]; // for initializing lang 1 to 100
    int num2[100]; // for reading and copying variable
    int x,y; // test variable used for testing
    int i; // iterate variable
    char inName[20]; //Name of file.txt


    for (i = 0; i < 100; i++) // num1 
    {
       num[i] = i+1;
    }

    printf("Enter a file name: ");
    scanf(" %[^\n]s", &inName); //this is for asking the name of the file you want to get

    strcat(inName, ".txt"); // adding .txt para maging txt file siya
    

    FILE *fpointer; // for reading
    FILE *fcopy; // for copying
    
    fpointer = fopen("Pokedex.txt","r"); // w = write, r = read, a = append ; for opening the file

    for (i = 0; i < MAX; i++)
    {
       fscanf(fpointer, " %d", &num2[i]); // trying to scan everything, automatically na magiiscan to the next line to sabi daw
    }
    
    fclose(fpointer); // file closing

    for (i = 0; i < MAX; i++) // test print for loop
    {
        printf("%d, ",num2[i]);
    }
    

    fcopy = fopen(inName,"a"); // w = write, r = read, a = append ; copying the file

    for (i = 0; i < MAX; i++)
    {
        fprintf(fcopy," %d\n", num2[i]); //copying the file 
    }
    

    fclose(fcopy); // closing it
    


    printf("Data Written\n");
    return 0;
}

// fpointer = fopen("Pokedex","w"); // w = write, r = read, a = append

//     for (i = 0; i < 100; i++)
//     {
//        fprintf(fpointer, "%d \n", num[i]);
//     }
    

//     fclose(fpointer);