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

int parse_int(char*);

/*
 * Complete the 'gridChallenge' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING_ARRAY grid as parameter.
 *
 * Given a matix of ascii elments, rearrange each row
 * alphabetically ascendig. Then check if the columns 
 * also are in ascending alphabetical order, top to bottom.
 * Return YES, if they are, otherwise return NO.
 * 
 * Example: 
 1
5
eabcd
fghij
olkmn
trpqs
xywuv

 expected output: YES
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
 
void print_matrix(int n, char** matrix)
{
    printf("matrix: ");
    for (int i = 0; i < n; i++)
    {
        printf("\n ");
        for (int j = 0; j < n-1; j++)
        {
            printf("%3c ", matrix[i][j]);
        }
    }
    printf("\n");
}
 
int comp(const void *_a, const void *_b) {
 
        unsigned char *a, *b;
        
        a = (unsigned char *) _a;
        b = (unsigned char *) _b;
        
        return (int)(*a - *b);
}

char* gridChallenge(int grid_count, char** grid) {

    // grid_count : number of rows, columns
    // grid : array grid
    printf("grid count: %d\n", grid_count);
    
    static char Yes[] = "YES";
    static char No[]  = "NO";
    
    //print_matrix( grid_count, grid);
    
    // loop to orther the rows
    for (int i = 0; i < grid_count; i++)
    {
        qsort (&grid[i][0], grid_count, sizeof(char), comp);
    }
    
    printf("ordered rows");
    //print_matrix(grid_count, grid);
    
    // check if the columns are in order
    bool isOrdered = true;
    
    for (int j = 0; j < grid_count ; j++) // loop the columns
    {
        for (int i = 0; i < grid_count -1; i++) // loop the rows
        {
            if ( grid[i][j] > grid[i+1][j]) { isOrdered = false; break;}
        }
        if (isOrdered == false) { break; }
    }
    
    return isOrdered ? Yes : No;     
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char** grid = malloc(n * sizeof(char*));

        for (int i = 0; i < n; i++) {
            char* grid_item = readline();

            *(grid + i) = grid_item;
        }

        char* result = gridChallenge(n, grid);

        fprintf(fptr, "%s\n", result);
    }

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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
