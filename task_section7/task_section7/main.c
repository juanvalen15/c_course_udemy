//
//  main.c
//  task_section7
//
//  Created by juan on 16/11/2021.
//
    

/*
 Code specifications
 - sort the linked list based on the first string in the line from the rhyme stored in each element of the linked list. That is, pick out the words "One", "Two" etc. from the stored lines. Convert them to numbers 1, 2 etc. Sort the linked list based on these numbers. Sort in descending order.
 - print the lines from each node in the linked list after sorting.
 */

#include <stdio.h> // input and output functions e.g., printf, puts, putc (out) scanf, gets, getc (in)
#include <string.h> // string manipulation functions e.g., strcpy (string copy), strcmp (string compare)
#include <stdlib.h> // memory allocation functions, number conversion functions e.g., malloc (memory allocation), exit, atoi (string to number)
#include <ctype.h> //  for isspace and isalpha

extern int random_number_generator(int seed);
extern int create_list_of_numbers(char *file_prefix);
extern int add_number_to_list(int number);
extern void add_strings_to_list(char *poetry_file);
extern char *get_poetry_line(int num, char *poetry_file);
extern char *get_first_word(char *line);
extern void sort_linked_list_ascending_number(void);
extern void sort_linked_list_descending_string(void);
extern int get_number(char *word);

struct num_and_string // definition of struct type
{
    int number;
    char *poetry;
    struct num_and_string *next;
};

extern void insert_node_ascending(struct num_and_string *new_node); // declaration after the struct
extern void insert_node_descending(struct num_and_string *new_node); // declaration after the struct


struct num_and_string *ns_list; // variable of type num_and_string

char *number_map[10] = {"One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten"};

int main(int argc, char *argv[]) {
    // insert code here...
    int random_number;
    int i;
    unsigned long len;
    char filename[100]; //  string lenght
    struct num_and_string *temp_node;
    FILE *fp;
    
    // Initialize list indicating that the list is empty
    ns_list = NULL;
    
    printf("argc = %d, argv[0] %s\n", argc, argv[0]);
    
    if(argc != 3)
    {
        printf("Usage: program_name file_prefix poetry_file\n");
        return 1;
    }
    
    for (i=0; i<10; i++)
    {
        random_number = random_number_generator(i);
        
        strcpy(filename, argv[1]);
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
    
    create_list_of_numbers(argv[1]);
    add_strings_to_list(argv[2]);
    sort_linked_list_ascending_number();  // ascending ordering based on a number
    sort_linked_list_descending_string(); // descending ordering based on a string
    
    temp_node = ns_list;
    
    while(temp_node != NULL) // when temp_node != NULL reaching head of the list temp_node, not the next
    {
        printf("List member: number: %d\n", temp_node->number);
        temp_node = temp_node->next;
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

int create_list_of_numbers(char *file_prefix)
{
    FILE *fp;
    int i, random_number;
    unsigned long len;
    char filename[100]; // string length
    struct num_and_string *temp_node;
    
    for(i=0; i<10; i++)
    {
        strcpy(filename, file_prefix);
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

void add_strings_to_list(char *poetry_file)
{
    struct num_and_string *temp_node;
    int i;
    
    // traverse the list
    temp_node = ns_list; // initialize to the head of the list = ns_list
    i = 0;
    
    while(temp_node != NULL) // when temp_node != NULL reaching head of the list temp_node, not the next
    {
        temp_node->poetry = get_poetry_line(i, poetry_file);
        i++;
        if(temp_node->poetry != NULL)
            printf("i = %d, line: %s\n", i, temp_node->poetry);
        temp_node = temp_node->next;
    }
}

char *get_poetry_line(int num, char *poetry_file) // function will use inter i to be able to compare with an input
{
    FILE *fp;
    char line[80];
    char *word, *poetry_line;
    
    if(num > 9)
    {
        printf("Wrong arg num: %d\n", num);
        return NULL;
    }
    
    fp = fopen(poetry_file, "r");
    if(fp == NULL)
    {
        printf("Error: cannot open file: %s\n", poetry_file);
        return NULL; // char function
    }
    
    // if file can be open, line by line is read
    while( fgets(line,70,fp) ) // if null = true , else false |  assuming lines with 70 characters
    {
        word = get_first_word(line);
        
        if (word != NULL)
        {
            if ( strcmp(word, number_map[num]) == 0 )
            {
                poetry_line = (char *)malloc(strlen(line)+1); // +1 extra space to store 0 = end of string
                if (poetry_line == NULL)
                {
                    printf("Error in get_poetry_line: cannot allocate memory: %d\n", num);
                    fclose(fp);
                    return NULL;
                }
                
                strcpy(poetry_line, line);
                fclose(fp);
                return poetry_line; // returning line
            }
        }
    }
    
    // At this point the line was read, but a number was not found in the line
    fclose(fp);
    return NULL;
}

char *get_first_word(char *line)
{
    static char word[10];
    int i,j;
    
    i = 0;
    j = 0;
    
    while( (line[i] != 0) && isspace(line[i]) ) // dont reach end of string AND if we encounter spaces at the begining of the line
        i++;
    
    if(line[i] == 0)
    {
        return NULL;
    }
    
    while( (line[i] != 0) && isalpha(line[i]) ) // dont reach the end of tring AND if the character is not in alphabet
    {
        word[j] = line[i];
        i++;
        j++;
    }
    
    word[j] = 0;
    return word;
}

void sort_linked_list_ascending_number()
{
    struct num_and_string *curr, *prev, *temp_node; // pointers for current, previous, and temporal node
    
    if (ns_list == NULL)
        return;
    
    curr = prev = ns_list; // initialization
    
    while(curr != NULL)
    {
        if (curr->number >= prev->number) // already in ascending order
        {
            prev = curr;
            curr = curr->next;
        }
        else // not ascending order curr->number < prev->number
        {
            temp_node  = curr; // store current number in temp_node
            prev->next = curr->next;
            curr       = curr->next;
            
            insert_node_ascending(temp_node);
        }
    }
    
}

void insert_node_ascending(struct num_and_string *new_node)
{
    struct num_and_string *iprev, *icurr;
    
    if (ns_list == NULL)
        return;
    
    icurr = iprev = ns_list;
    
    while(icurr != NULL)
    {
        if (new_node->number > icurr->number)
        {
            iprev = icurr; //  keep traversing list
            icurr = icurr->next;
        }
        else
        {
            // new node has to be insrted before current node
            // because this new_node's number <= icurr's number
            if (icurr == iprev) // icurr is at the head of the list (first element)
            {
                new_node->next = icurr;
                ns_list = new_node;
            }
            else
            {
                new_node->next = icurr;
                iprev->next    = new_node;
            }
            return;
        }
    }
    // new_node has to be inserted at the end of the list
    new_node->next = NULL;
    iprev->next    = new_node;
    return;
}


void sort_linked_list_descending_string()
{
    struct num_and_string *curr, *prev, *temp_node; // pointers for current, previous, and temporal node
    char *word;
    int curr_number, prev_number;
    
    if (ns_list == NULL)
        return;
    
    curr = prev = ns_list; // initialization
    
    while(curr != NULL)
    {
        word = get_first_word(curr->poetry); // this will return the first word in the poetry line
        curr_number = get_number(word);
        
        word = get_first_word(prev->poetry); // this will return the first word in the poetry line
        prev_number = get_number(word);
        
        if (curr_number <= prev_number) // already in descending order
        {
            prev = curr;
            curr = curr->next;
        }
        else // not descending order curr_number > prev_number
        {
            temp_node  = curr; // store current number in temp_node
            prev->next = curr->next;
            curr       = curr->next;
            
            insert_node_descending(temp_node); // format list in descending order
        }
    }
    
}

void insert_node_descending(struct num_and_string *new_node)
{
    struct num_and_string *iprev, *icurr;
    char *word;
    int icurr_number, iprev_number, new_number;
    
    if (ns_list == NULL)
        return;
    
    icurr = iprev = ns_list;
    
    while(icurr != NULL)
    {
        word = get_first_word(icurr->poetry); // this will return the first word in the poetry line
        icurr_number = get_number(word);
        
        word = get_first_word(iprev->poetry); // this will return the first word in the poetry line
        iprev_number = get_number(word);
        
        word = get_first_word(new_node->poetry); // this will return the first word in the poetry line
        new_number = get_number(word);
        
        if (new_number < icurr_number)
        {
            iprev = icurr; //  keep traversing list
            icurr = icurr->next;
        }
        else
        {
            // new node has to be insrted before current node
            // because this new_number >= icurr_number
            if (icurr == iprev) // icurr is at the head of the list (first element)
            {
                new_node->next = icurr;
                ns_list = new_node;
            }
            else
            {
                new_node->next = icurr;
                iprev->next    = new_node;
            }
            return;
        }
    }
    // new_node has to be inserted at the end of the list
    new_node->next = NULL;
    iprev->next    = new_node;
    return;
}


int get_number(char *word)
{
    int i;
    
    for(i=0; i<10; i++)
    {
        if ( strcmp(word, number_map[i]) == 0 ) // strcmp returns 0 if both match
        {
            return i++;
        }
    }
    return 0;
    // TODO: ideally if there is no matching number it should return -1 to show an error
}
