//
//  main.c
//  task1
//
//  Created by juan on 11/10/2021.
//

#include <stdio.h>

int random_number_generator(int *seed);

int main(int argc, const char * argv[]) {
    // insert code here...
    int random_number;
    int main_seed; // main_seed resides in a memory location
    
    main_seed = 10;
    
    random_number = random_number_generator(&main_seed);
    
    printf("main_seed = %d, randn = %d\n", main_seed, random_number);
    getc(stdin);
    
    return 0;
}

int random_number_generator(int *seed) // seed resides in a memory location
{
    int number;
    
    printf("seed before initialisation = %d\n", *seed);
    
    *seed = 20;
    
    printf("seed = %d\n", *seed);
    
    number = *seed * 1103515245 + 12345;
    return (unsigned int)(number/65536) % 32768;
}
