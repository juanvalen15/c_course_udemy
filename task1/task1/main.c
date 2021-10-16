//
//  main.c
//  task1
//
//  Created by juan on 11/10/2021.
//

#include <stdio.h> // input and output functions e.g., printf, puts, putc (out) scanf, gets, getc (in)
#include <string.h> // string manipulation functions e.g., strcpy (string copy), strcmp (string compare)
#include <stdlib.h> // memory allocation functions, number conversion functions e.g., malloc (memory allocation), exit, atoi (string to number)

extern int random_number_generator(int seed);


int main(int argc, const char * argv[]) {
    // insert code here...
    int random_number;
    int i;
    char filename[20]; //  string lenght
    
    strcpy(filename, "file_");
    
    for (i=0; i<10; i++)
    {
        random_number = random_number_generator(i);
        printf("seed = %d rand = %d\n", i,  random_number);
    }
    
    getc(stdin);
    
    return 0;
}



int random_number_generator(int seed) // seed resides in a memory location
{
    int number;
    
    number = seed * 1103515245 + 12345;
    return (unsigned int)(number/65536) % 32768;
}
