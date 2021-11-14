//
//  main.c
//  task1
//
//  Created by juan on 11/10/2021.
//

/*
 Code specifications
 - generate 10 random numbers
 - store them in 10 different files. the files should be named as file_i.txt where 0<=i<=9
 */

#include <stdio.h> // input and output functions e.g., printf, puts, putc (out) scanf, gets, getc (in)
#include <string.h> // string manipulation functions e.g., strcpy (string copy), strcmp (string compare)
#include <stdlib.h> // memory allocation functions, number conversion functions e.g., malloc (memory allocation), exit, atoi (string to number)

extern int random_number_generator(int seed);


int main(int argc, const char * argv[]) {
    // insert code here...
    int random_number;
    int i;
    unsigned long len;
    char filename[100]; //  string lenght
    FILE *fp;
    
    
    for (i=0; i<10; i++)
    {
        random_number = random_number_generator(i);
        printf("seed = %d rand = %d\n", i,  random_number);
        
        strcpy(filename, "/Users/juan/Documents/GitHub/c_course_udemy/task1/task1/file_");
        len = strlen(filename);
        
        filename[len] = '0' + i; // refers to the null character of the filename
        filename[len+1] = '\0'; // sets the new null character of the filename
        
        strcat(filename, ".txt");
        printf("filename = %s length = %lu\n", filename, strlen(filename));
        
        fp = fopen(filename, "w");
        
        
        if (fp == NULL)
        {
            printf("Error opening file: %s\n", filename);
            return 1;
        }
        fprintf(fp, "%d\n", random_number); // writing random_number to file
        fclose(fp); // after writing the file needs to be closed
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
