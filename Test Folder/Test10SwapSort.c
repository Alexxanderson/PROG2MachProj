#include <stdio.h>

void clrscr() // Clear Screen
{
    system("@cls||clear");
}

void SelectionSort(int A[], int n)
{
int i, j, min, temp;

for (i = 0; i < n - 1; i++) {
    min = i; // min is the index of the lowest element

    for (j = i + 1; j < n; j++)
        if (A[min] < A[j]) // FOR STRUCTS; A[min].resTaskTYpe[inType]  < A[j].resTasktpe[inType]
            min = j;

// swap A[i] with A[min] 
if (i != min) {
    temp = A[i]; 
    A[i] = A[min]; 
    A[min] = temp;
        }
    }
}


int main()
{
    clrscr();
    printf("Hello world \n");

    int A[5] = {1,2,3,4,5};
    int i;

    SelectionSort(A, 5);

    for ( i = 0; i < 5; i++)
    {
        printf("%d", A[i]);
    }
    






    return 0;
}
