/*
    This is setMain.c file.  It contains the main() function for the SETS problem.
	
	DO the following to test your LASTNAME-SETS.c solution: 
	
	1. Edit Line 40 below to include your own source file.
	2. Compile this setMain.c file to produce main.exe.  Make sure to use -Wall compiler directive!
	3. If there are no compilation errors and/or warnings, go to the Command Line Interface via CMD. 
	4. Run main.exe in the command line with I/O redirection as follows:
   
           	For Windows:    main < INPUT.txt > LASTNAME-ACTUAL.txt
			For Linux/Mac:  ./main < INPUT.txt > LASTNAME-ACTUAL.txt

	   where INPUT.txt is an accompanying sample text files that contain input data 
	   read via scanf() in the ReadWords() function.

       For example, if your lastname is SANTOS, you should run main.exe in Windows as:
	   
       		main < INPUT.txt > SANTOS-ACTUAL.txt
		      
    5. Using Notepad (or other text editors), open and compare your LASTNAME-ACTUAL.txt with the 
	   contents of the accompanying EXPECTED.TXT file. They should be exactly the same -- even the spacing!
	   If they are not the same, then there's a strong probability that there's a logical error in your 
	   solution, or you did not follow some specifications.  

	6. Debug and retry until you get the correct results.    
	   
	7. Devise your own tests. Do NOT simply depend on the sample INPUT and EXPECTED text files.
*/

/* Do NOT change  the #include below.  You are NOT allowed to include other files. */
#include <stdio.h>
#include <string.h>
#include "sets.h"  // make sure that you read/understand the contents of this header file

/*
    TO DO: change the #include below to your own file/solution. For example if your 
	lastname is SANTOS, then it should be changed to #include "SANTOS-SETS.c".
*/	
#include "MIRANDA-sets.c"

/*
	Input the contents of the array Data.
	We'll use input redirection to avoid manual keyboard input.
*/
int
ReadWords(String Data[])
{
	int i;
	int n;
	
	scanf("%d", &n);  // assume user inputs an n <= MAXLIST
	
	for (i = 0; i < n; i++) // input the strings repesenting the creatures
		scanf("%s", Data[i]);
		
	return n;	// n is the actual number of elements in the Data[] array.
}


/*
	Print the contents of the Data[] containing n elements.
*/
void
PrintWords(String Data[], int n)
{
	int i;

	printf("%d\n", n);
	for (i = 0; i < n; i++) 
		printf("%s\n", Data[i]);
}

/*
    This is the main() function for testing your solution.  
	
	You are not supposed to modify the contents and the logic of this function.
    
    If you need to experiment, i.e. you'd like to edit/introduce new codes, then it is suggested that you
	copy this file, and make changes on your copy.
	
	Note that the teacher-in-charge of checking your solution may use another set of input data 
	and a different main() function.  
	
	Your functions should work correctly even with a different set of input data and a different main() function.
*/	
int main()
{
    int nElemA, nElemB, nElemC;	// number of creatures in the MasterList
	String A[MAXLIST], B[MAXLIST], C[MAXLIST * 2];

	nElemA = ReadWords(A);  // read data via input redirection
	printf("A[] contents\n");
	PrintWords(A, nElemA);
	printf("\n\n");
	
	nElemB = ReadWords(B);  // read data via input redirection
	printf("B[] contents\n");
	PrintWords(B, nElemB);
	printf("\n\n");
	
	// Test the functions that the student defined.
	printf("**01-Search()**\n");
	printf("Result of Search(\"%s\", A, %d) = %d\n",
           "today", nElemA, Search("today", A, nElemA));
	printf("Result of Search(\"%s\", B, %d) = %d\n",
           "today", nElemB, Search("today", B, nElemB));
   
   	printf("\n**02-setUnion()**\n");
    nElemC = setUnion(A, B, C, nElemA, nElemB);
	printf("C[] contents\n");
	PrintWords(C, nElemC);

    //contents of A and B are still the same
	printf("\n**03-setDiff()**\n");
    nElemC = setDiff(A, B, C, nElemA, nElemB);
	printf("C[] contents\n");
	PrintWords(C, nElemC);
	
	//contents of A and B are still the same
	printf("\n**04-intersect()**\n");
    nElemC = intersect(A, B, C, nElemA, nElemB);
	printf("C[] contents\n");
	PrintWords(C, nElemC);

    //contents of B are still the same
	printf("\n**05-substringList()**\n");
    nElemC = substringList("or", B, C, nElemB);
	printf("C[] contents with substring \"%s\"\n", "or");
	PrintWords(C, nElemC);

    //contents of A are still the same
    nElemC = substringList("at", A, C, nElemA);
	printf("\nC[] contents with substring \"%s\"\n", "at");
	PrintWords(C, nElemC);

    //contents of B are still the same
    nElemC = substringList("day", B, C, nElemB);
	printf("\nC[] contents with substring \"%s\"\n", "day");
	PrintWords(C, nElemC);

	//verifying contents of A and B are still same from inputs
    printf("\nOriginal A[] contents\n");
	PrintWords(A, nElemA);
	printf("\n\n");  
	
    printf("Original B[] contents\n");
	PrintWords(B, nElemB);
	
	return 0;	
}
