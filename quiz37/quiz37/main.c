//
//  main.c
//  quiz37
//
//  Created by juan on 16/11/2021.
//

#include <stdio.h>

union u_hardware{
    struct hardware_register {
        unsigned int status:1;
        unsigned int port_select:2;
        unsigned int source_if:5;
        unsigned int data:24;
    } reg_val;
    unsigned int register_value;
};

union u_hardware my_register;

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    my_register.register_value = 0xaabbccdd;
    
    printf("my_register.register_value = %x\n", my_register.register_value);
    printf("my_register.reg_val.data   = %x\n", my_register.reg_val.data);
    
    return 0;
}




