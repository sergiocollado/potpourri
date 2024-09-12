#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'lonelyinteger' function below.
 *
 * Given an array of integers, where all the elements 
 * are repeated twice but one, find the unique element
 * in the given array
 *
 * example: [1, 2, 3, 4, 3, 2, 1]
 * expected ouptut: 4
 */

int lonelyinteger(int a_count, int* a) {

    const int key = 0;
    const int count = 1;
    int dictionary_elem = 0;
    int dictionary[a_count][2];
    memset(dictionary, 0x0, 2*a_count*sizeof(int));
    int i = 0, j = 0;
    
    for (i = 0; i < a_count; i++) //loop over all input elements
    {
        bool elem_found = false;
        for( j = 0; j < dictionary_elem; j++) //find the element in the dictionary
        { 
            if ( a[i] == dictionary[j][key])
            { 
                elem_found = true;
                dictionary[j][count] += 1;
                printf("+ found repeated %d - counted %d\n", a[i], dictionary[j][count]);
                break;
            }
        }  
        
        // if the element was not found, create it;
        if (elem_found == false)
        {
            dictionary[dictionary_elem][key] = a[i];
            dictionary[dictionary_elem][count] = 1;
            dictionary_elem ++;
            printf("found new elememnt %d\n", a[i]);
        } 
    }
    
    //once everything is analyzed, we check the element in the dictionary that only has 1 instance
    for (int k = 0; k < dictionary_elem; k++)
    {
        if (dictionary[k][count] == 1)
        {
            return dictionary[k][key];
        }
    }
    return 0;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** a_temp = split_string(rtrim(readline()));

    int* a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int a_item = parse_int(*(a_temp + i));

        *(a + i) = a_item;
    }

    int result = lonelyinteger(n, a);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
