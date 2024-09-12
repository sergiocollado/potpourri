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

/*
 * Complete the 'timeConversion' function below.
 *
 * the function must convert, between a 10 hour AM/PM format
 * to a 24-hours format.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 *
 * Note: - 12:00:00AM on a 12-hour clock is 00:00:00 on a 24-hour clock.
 * - 12:00:00PM on a 12-hour clock is 12:00:00 on a 24-hour clock.
 *
 * example:
 * example input: 12:45:54PM
 * expected output: 24:45:54
 *
 * example:
 * example input: 07:05:45PM
 * expected output: 19:05:45
 *
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
char* timeConversion(char* s) {
    printf("input: %s\n", s);
    printf("strlen input: %lu\n", strlen(s));
    char hour[3];   
    int index = 0;
    int input_len = strlen(s);
    
    if (input_len == 10) // XX:XX:XXPM
    {
        printf("hour 2 digits\n");
        hour[0] = s[0];
        hour[1] = s[1];
        hour[2] = '\0';  
        index = 2;        
    }
    else if (input_len == 9) // X:XX:XXPM
    {
        printf("hour 1 digits\n");
        hour[0] = '0';
        hour[1] = s[0];
        hour[2] = '\0';  
        index = 1;         
    }
    else
    {
        return "unknown format!\n";
    }
       
    long ihour = strtol(hour, NULL, 10);
    printf("ihour = %ld\n", ihour);
    
    static char return_string[] = "00:00:00";
    memset(return_string, 0x00, 9);
        
    if( s[6+ index] == 'P' || s[6 + index] == 'p') {
        printf("it is PM\n");
        ihour += 12;
        if (ihour == 24) { ihour = 12;}
    }
    if( (ihour == 12) && ((s[6+index] == 'A') || (s[6 + index] == 'a') )) { 
        ihour = 0;
    } 

    sprintf(return_string, "%02d", (int)ihour);
    printf("%02d\n", (int)ihour);
    printf("output1: %s\n", return_string);
    printf("strlen output1: %lu\n", strlen(return_string));
    printf("to append: %s\n", &s[index]);
    
    strncpy(&return_string[2], &s[index], 6);
    printf("output2: %s\n", return_string);
    return return_string;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = timeConversion(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length); // what about freeing this??? 

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
ç


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
