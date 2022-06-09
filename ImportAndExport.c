    FILE *fpointer; // for reading
    FILE *fcopy; // for copying

//Wrinting
fpointer = fopen("Pokedex","w"); // w = write, r = read, a = append

    for (i = 0; i < 100; i++)
    {
       fprintf(fpointer, "%d \n", num[i]);
    }

    fclose(fpointer);


//Reading
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
    

//Copying
    fcopy = fopen(inName,"a"); // w = write, r = read, a = append ; copying the file

    for (i = 0; i < MAX; i++)
    {
        fprintf(fcopy," %d\n", num2[i]); //copying the file 
    }
    

    fclose(fcopy); // closing it