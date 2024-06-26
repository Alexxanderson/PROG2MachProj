/**
  * Problem: Sets
  *
  * Name: MIRANDA, BIEN AARON
  * Section: S11B
  *
  */

#include "sets.h"   // Do NOT edit or delete this line
  
/* To Do: (1) Implement Search() to return the index where
          key was first found in A.  If not found, return -1.
   @param key - string to search for in A 
   @param A - array of strings 
   @param nElem - number of elements in A
*/   
int
Search(String key, String A[], int nElem)
{
   int i;
   int found = -1;

   for (i = 0; i < nElem; i++)
   {
      if (strcmp(key, A[i]) == 0)
         {
            found = 1;
         }
   }
   
   if (found == 1)
   {
      return 1;
   } else
   {
      return -1;
   }
   

	
}

/* To Do: (2) Implement setUnion() that will produce the
           union of unique values from the array A and array B.
           In math, union of sets will be the elements from both
		   sets. Do not assume that the arrays have same number 
		   of elements. The function returns the number of 
		   elements in C.
	
   Reminder: 1. Do NOT use array indexing notation for this function.
    
	         2. You are required to to meaningfully use Search()
  			    as part of the solution for this function.
			  
		Refer to pdf file for the details and complete 
		list of restrictions.	

   @param A first array of strings
   @param B second array of strings
   @param C resulting array to contain the union of A and B
   @param nElemA number of elements in array A
   @param nElemB number of elements in array B
*/
int 
setUnion(String *A, String *B, String *C, int nElemA, int nElemB)
{
   int i;
   int ctr = 0;

   strcpy(*(C), *(A));
   ctr++;

   for (i = 1; i < nElemA; i++)
   {
      if (Search(*(A+i), C,ctr) == -1) 
      {
         strcpy(*(C+ctr), *(A+i));
         ctr++;
      }
   }
   for (i = 1; i < nElemB; i++)
   {
         if (Search(*(B+i), C,ctr) == -1) 
      {
         strcpy(*(C+ctr), *(B+i));
         ctr++;
      }
   }
   

	
   // Search(String key, String A[], int nElem);

	return ctr;
}

/* To Do: (3) Implement setDiff() that will generate contents of 
           array C to contain unique elements from array A that are not in
		   array B. The function returns the number of 
		   elements in C.

   Reminder: You are required to to meaningfully use Search()
  			 as part of the solution for this function.
			  
		Refer to pdf file for the details and complete 
		list of restrictions.	
		   
   @param A first array of strings
   @param B second array of strings
   @param C resulting array to contain elements in A but not in B
   @param nElemA number of elements in array A
   @param nElemB number of elements in array B
   @return number of elements in array C
*/
int
setDiff(String A[], String B[], String C[], int nElemA, int nElemB)
{
   int i;
   int ctr = 0;

   for (i = 0; i < nElemA; i++)
   {
      if (Search(*(A+i), B,nElemB) == -1) 
      {
      if (Search(*(A+i), C,ctr) == -1) 
      {
         strcpy(*(C+ctr), *(A+i));
         ctr++;
      }
      }
   }
	
	return ctr;
}

/* To Do: (4) Implement intersect() that will produce the
           intersection of unique values from the array A and array B.
           In math, intersection of sets will be the common elements only
		   from both sets. Do not assume that the arrays have same number 
		   of elements. The function returns the number of 
		   elements in C.

   Reminder: You are required to to meaningfully use Search()
  			 as part of the solution for this function.
			  
		Refer to pdf file for the details and complete 
		list of restrictions.	
		   
   @param A first array of strings
   @param B second array of strings
   @param C resulting array to contain the intersection of A and B
   @param nElemA number of elements in array A
   @param nElemB number of elements in array B
*/
int
intersect(String A[], String B[], String C[], int nElemA, int nElemB)
{
   int i;
   int ctr = 0;

      for (i = 0; i < nElemA; i++)
   {
      if (Search(*(A+i), B,nElemB) == 1) 
      {
      if (Search(*(A+i), C,ctr) == -1) 
      {
         strcpy(*(C+ctr), *(A+i));
         ctr++;
      }
      }
   }
	
	return ctr;
}

/* To Do: (5) Implement substringList() that will produce the collection
           of words from the 1D array B that has substrings equivalent to
		   the string key. The function returns the number of 
		   elements in C.
		   
	Reminder: You are only allowed to use strlen(), strcmp(), strcat(),
  	          and strcpy() from string.h.  No other functions from 
			  string.h can be used.
			  
			  Refer to pdf file for the details and complete 
			  list of restrictions.
		   
   @param key - string to search for within strings in B 
   @param B array of strings
   @param C resulting array to contain strings that have key as substrings
   @param nElemB number of elements in array B
   @return number of elements in array C
*/
int
substringList(String key, String B[], String C[], int nElemB) //key = yung hinahanap, B[] = array of words, C[] = where you will store the founded wods with key, nElemB = how many arrays yung B
{
	int ctr = 0; // this counts how many words are found with the key
	int c, i; // for iteration
	char sub[5]; //substring
   int keylen = strlen(key); // length of key
   int p = 0; // p is just like a for loop variable lang, NOTHING ELSE
   int sublen; // length of the array[word] in for loop no. 2
   int pos = 0; // THIS IS THE POSITION ITERATION PALA

	for (i = 0; i < nElemB; i++)
	{
      pos = 0; //position starts at word[0]
		c = 0; //
      sublen = strlen(*(B+i)); // declaring the length of the word

      for (p = 0; p < sublen - 1; p++) //for loop ng position
      {
         c = 0;
		   while (c < keylen) { //substring function 
         *(sub+c) = B[i][c+pos]; // B[i] is the array of words, pos ay yung position to start the copying
         c++; // iteration
   	   }
   		sub[c] = '\0'; //while loop will stop at an empty index after the last character, put a \0 kasi needed to

		   if (strcmp(sub, key) == 0) //if substring is found
         {
            if (Search(*(B+i), C,ctr) == -1)  // this function related sa sets to, ikaw na bahala kung ano laman neto
             {
               strcpy(*(C+ctr), *(B+i));
               ctr++;
            }
         }
         pos++; // position will iterate until maubos yung letters. // for loop P ends then go to the next for loop i 
	
      }

	}
	
	return ctr; //for telling how many words na nakita with the string key on it.
}