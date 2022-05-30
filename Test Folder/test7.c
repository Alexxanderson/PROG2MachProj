void searchPokeByName(int nPkCtr)
{
    int j,c, i;
    int inNameLen; // length of key
    char inName[21]; 
    char sub[21]; //substring
    int sublen; // length of the array[word] in for loop no. 2
    int pos = 0; // THIS IS THE POSITION ITERATION PALA
    int exist = 0;

    printf("Name of the Pokemon: ");
    fgets(inName, 21, stdin); //for getting and storing the pokemon name
    inName[strcspn(inName, "\n")] = 0; // clears the \n stored in the string galing sa fgets function

    inNameLen = strlen(inName);
   
    //   if (Search(inName, nPkCtr) == 1) 
    //   {
    //       for (j = 0; j < nPkCtr; j++)
    //     {
    //         if(strcmp(inName, pokemon[j].cPokeName) == 0)
    //         {
    //             displayEntry(j);
    //             printf("\n");
    //         }
    //     }
    //   } else if (Search(inName, nPkCtr) == -1) 
    //   {
    //      printf("I'm sorry, no pokemon found. \n\n");
    //   }


      	for (i = 0; i < nPkCtr; i++)
	        {
             pos = 0; //position starts at word[0]
             sublen = strlen(pokemon[i].cPokeName); // declaring the length of the word

                for (j = 0; j <= sublen - inNameLen; j++) //for loop ng position
                 {
                    c = 0;
		            while (c < inNameLen) { //substring function 
                    sub[c] = pokemon[i].cPokeName[c+pos]; // B[i] is the array of words, pos ay yung position to start the copying
                    c++; // iteration
   	                }
   		            sub[c] = '\0'; //while loop will stop at an empty index after the last character, put a \0 kasi needed to

		                if (strcmp(sub, inName) == 0) //if substring is found
                            {
                                displayEntry(i);
                                printf("\n");
                                exist = 1;
                                // if (Search(*(B+i), C,ctr) == -1)  // this function related sa sets to, ikaw na bahala kung ano laman neto
                                //      {
                                //         strcpy(*(C+ctr), *(B+i));
                                //         ctr++;
                                //      }
                            }
                    pos++; // position will iterate until maubos yung letters. // for loop P ends then go to the next for loop i 
                 }

	        }
        if (exist == 0)
        {
             printf("I'm sorry, no pokemon found. \n\n");
        }
	
}


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