//
//  main.c
//  task2
//
//  Created by juan on 14/11/2021.
//

/*
 Code specifications
 - read the stored numbers from the files that were created in task1
 - store the numbers in a linked list. each element of the linked list is a structure containing a number, and a pointer to a string.
 */


#include <stdio.h> // input and output functions e.g., printf, puts, putc (out) scanf, gets, getc (in)
#include <string.h> // string manipulation functions e.g., strcpy (string copy), strcmp (string compare)
#include <stdlib.h> // memory allocation functions, number conversion functions e.g., malloc (memory allocation), exit, atoi (string to number)

extern int random_number_generator(int seed);
extern int create_list_of_numbers(void);
extern int add_number_to_list(int number);

struct num_and_string // definition of struct type
{
    int number;
    char *poetry;
    struct num_and_string *next;
};

struct num_and_string *ns_list; // variable of type num_and_string

int main(int argc, const char * argv[]) {
    // insert code here...
    int random_number;
    int i;
    unsigned long len;
    char filename[100]; //  string lenght
    FILE *fp;
    
    // Initialize list indicating that the list is empty
    ns_list = NULL;
    
    for (i=0; i<10; i++)
    {
        random_number = random_number_generator(i);
        
        strcpy(filename, "/Users/juan/Documents/GitHub/c_course_udemy/task2/task2/file_");
        len = strlen(filename);
        filename[len] = '0' + i; // refers to the null character of the filename
        filename[len+1] = '\0'; // sets the new null character of the filename
        strcat(filename, ".txt");
        
        fp = fopen(filename, "w");
        if (fp == NULL)
        {
            printf("Error opening file: %s\n", filename);
            return 1;
        }
        fprintf(fp, "%d\n", random_number); // writing random_number to file
        fclose(fp); // after writing the file needs to be closed
    }
    
    create_list_of_numbers();
    
    getc(stdin);
    
    return 0;
}



int random_number_generator(int seed) // seed resides in a memory location
{
    int number;
    
    number = seed * 1103515245 + 12345;
    return (unsigned int)(number/65536) % 32768;
}

int create_list_of_numbers(void)
{
    FILE *fp;
    int i, random_number;
    unsigned long len;
    char filename[100]; // string length
    struct num_and_string *temp_node;
    
    for(i=0; i<10; i++)
    {
        strcpy(filename, "/Users/juan/Documents/GitHub/c_course_udemy/task2/task2/file_");
        len = strlen(filename);
        filename[len] = '0' + i; // refers to the null character of the filename
        filename[len+1] = '\0'; // sets the new null character of the filename
        strcat(filename, ".txt");
        
        fp = fopen(filename, "r");
        if (fp == NULL)
        {
            printf("Error opening file: %s\n", filename);
            return 1; // indicating error
        }
        fscanf(fp, "%d\n", &random_number); // reading random_number from file
        // TODO: add a check to evaluate if files read is not empty
        
        printf("filename = %s, number = %d\n", filename, random_number);
        add_number_to_list(random_number);
        fclose(fp); // after writing the file needs to be closed
    }
    
    // traverse the list
    temp_node = ns_list; // initialize to the head of the list = ns_list
    
    while(temp_node != NULL) // when temp_node != NULL reaching head of the list temp_node, not the next
    {
        printf("List member: number: %d\n", temp_node->number);
        temp_node = temp_node->next;
    }
    
    return 0;
    
}

int add_number_to_list(int number)
{
    struct num_and_string *new_node, *temp_node; // pointer to num_and_string
    
    new_node = (struct num_and_string *)malloc(sizeof(struct num_and_string)); // casting memory to struct type
    if(new_node == NULL)
    {
        printf("Error allocating memory: %d\n", number);
        return 1; // indicating error
    }
    
    new_node->number = number;
    new_node->poetry = NULL;
    new_node->next   = NULL;
    
    if(ns_list == NULL) // If the list is empty
    {
        ns_list = new_node;
        return 0;
    }
    else // If the list is not empty
    {
        // traverse the list
        temp_node = ns_list; // initialize to the head of the list = ns_list
        
        while(temp_node->next != NULL)
        {
            temp_node = temp_node->next;
        }
        
        // AT THIS POINT: temp_node is the last element in the list
        
        temp_node->next = new_node;
    }
    return 0;
}
