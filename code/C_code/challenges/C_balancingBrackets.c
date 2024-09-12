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
Given  strings of brackets, determine whether each sequence of brackets is balanced. If a string is balanced, return YES. Otherwise, return NO.

Sample input:
STDIN Function ----- -------- 3 n = 3 {[()]} first s = '{[()]}' {[(])} second s = '{[(])}' {{[[(())]]}} third s ='{{[[(())]]}}'

expected output:

YES 
NO
YES
*/

/*
 * Complete the 'isBalanced' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
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
char* isBalanced(char* s) {
    static char No[] = "NO";
    static char Yes[] = "YES";
    
    printf("\n\nNew test case: %s\n", s);
    
    char a[1000];
    memset(a, 0x0, 1000*sizeof(char));
    int index = 0;
     
    int i = 0;
    while(s[i] != '\0')
    {
        if (s[i] == '(' ) { 
            a[index] = '('; 
            index++;
        }
        else if (s[i] == '[' ) { 
            a[index] = '['; 
            index++;
        }
        else if (s[i] == '{' ) { 
            a[index] = '{'; 
            index++;
        }
        else if (s[i] == ')' && a[index-1] == '(') { 
            a[index-1] = 0; 
            index -= 1;
        }
        else if (s[i] == ')' && a[index-1] != '(') { 
            return No;
        }
        else if (s[i] == ']' && a[index-1] == '[') { 
            a[index -1] = 0; 
            index -= 1;
        }
        else if (s[i] == ']' && a[index-1] != '[') { 
            return No;
        }
        else if (s[i] == '}' && a[index-1] == '{') { 
            a[index -1] = 0; 
            index -= 1;
        }
        else if (s[i] == '{' && a[index-1] != '}') { 
            return No;
        }
        
        printf("a[%d]: %s", i, a);
        printf("\n");
        i++;
    }
    printf("%s", (index==0) ? Yes: No);
    return (index==0) ? Yes: No;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char* s = readline();

        char* result = isBalanced(s);

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
