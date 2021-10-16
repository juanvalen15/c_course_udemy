//
//  main.c
//  task1
//
//  Created by juan on 11/10/2021.
//

#include <stdio.h>

extern int random_number_generator(int seed);


int main(int argc, const char * argv[]) {
    // insert code here...
    int random_number;
    int i;
    
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
