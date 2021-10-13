//
//  main.c
//  task1
//
//  Created by juan on 11/10/2021.
//

#include <stdio.h>

int random_number_generator(void);


int main(int argc, const char * argv[]) {
    // insert code here...
    int random_number;
    
    random_number = random_number_generator();
    printf("rand = %d\n", random_number);

    random_number = random_number_generator();
    printf("rand = %d\n", random_number);
    
    getc(stdin);
    
    return 0;
}



int random_number_generator(void) // seed resides in a memory location
{
    int number;
    static int seed = 0;
    seed++;
    
    printf("seed = %d\n", seed);
    
    number = seed * 1103515245 + 12345;
    return (unsigned int)(number/65536) % 32768;
}
