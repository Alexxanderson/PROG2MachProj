#include <stdio.h>

void clrscr() // Clear Screen
{
    system("@cls||clear");
}

int main()
{
    clrscr();
    int i;

    for ( i = 0; i < 1; i++)
    {
       printf("Hello world \n");
    }
    
    return 0;
}