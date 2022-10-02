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
 * Complete the 'superDigit' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING n
 *  2. INTEGER k
 
 superDigit(p) = superDigit(9875987598759875)
                  9+8+7+5+9+8+7+5+9+8+7+5+9+8+7+5 = 116
    superDigit(p) = superDigit(116)
                  1+1+6 = 8
    superDigit(p) = superDigit(8)

	super_digit(9875)   	9+8+7+5 = 29 
	super_digit(29) 	2 + 9 = 11
	super_digit(11)		1 + 1 = 2
	super_digit(2)		= 2  


 */

int superDigit(char* n, int k) {
    
    // n : number stirng
    // k : multiplication factor
    
    // long int val = strtol(n, NULL, 10);
    //if (val == 0) { printf("error 0"); return 0; }
    
    char* p = n;
    long int sum = 0;
    while (*p != '\0') {
        printf(" %d + ", ((unsigned char)*p - '0'));
        sum += ((unsigned char)*p - '0');
        p++;
    }
    
    // loop trhought the digits, ex: 9875
    /*
    while ( val > 10) 
    {   
        printf("val: %ld\n", val);
        sum += (val%10); 
        printf("digit: %ld\n", (val%10));
        val /= 10;
        printf("sum: %ld\n\n", sum);
    }
    sum += (val%10); 
    printf("digit: %ld\n", (val%10));
    printf("sum: %ld\n\n", sum);
    */
    
    // multiply acording to the string
    sum = sum * k;
    
    printf(" multiply > sum * %d: %ld", k, sum);
    
    printf(" > calculate superdigit: ");
    // reduce
    int super_digit = 0;
   
    do {
      super_digit = 0;
      while (sum > 0)
      {
        super_digit += (sum%10);
        printf(" %ld +", (sum%10));
        sum /= 10;
      }
      super_digit += (sum%10);
      sum = super_digit;
      printf("\n super digit: %d\n", super_digit);
    } while (super_digit > 10);
    
    return super_digit; 
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    char* n = *(first_multiple_input + 0);

    int k = parse_int(*(first_multiple_input + 1));

    int result = superDigit(n, k);

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
