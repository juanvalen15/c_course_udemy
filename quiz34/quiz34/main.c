//
//  main.c
//  quiz34
//
//  Created by juan on 16/11/2021.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    int *pi;
    int i;
    i = 100;
    
    pi = i;
    pi = *i;
    pi = (int *)i;
    
    return 0;
}
