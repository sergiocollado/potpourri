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


/*
It is New Year's Day and people are in line for the Wonderland rollercoaster ride. Each person wears a sticker indicating their initial position in the queue from  to . Any person can bribe the person directly in front of them to swap positions, but they still wear their original sticker. One person can bribe at most two others.

Determine the minimum number of bribes that took place to get to a given queue order. Print the number of bribes, or, if anyone has bribed more than two people, print Too chaotic.

Example


If person  bribes person , the queue will look like this: . Only  bribe is required. Print 1.


Person  had to bribe  people to get to the current position. Print Too chaotic.

Sample Input

STDIN       Function
-----       --------
2           t = 2
5           n = 5
2 1 5 3 4   q = [2, 1, 5, 3, 4]
5           n = 5
2 5 1 3 4   q = [2, 5, 1, 3, 4]
Sample Output

3
Too chaotic

8
5 1 2 3 7 8 6 4

Too chaotic

8
1 2 5 3 7 8 6 4

7

8
1 2 5 3 4 7 8 6

4

*/
int parse_int(char*);

/*
 * Complete the 'minimumBribes' function below.
 *
 * The function accepts INTEGER_ARRAY q as parameter.
 */
void printfArray(int k, int n, int* a)
{
    printf("a(%d): ", k);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void minimumBribes(int q_count, int* q) {

    bool debug = false;
     
    if(debug) printf("\n\ninitial array: \n");
    if(debug) printfArray( -1, q_count, q);
    
    bool same = false;
    int num_swap = 0;
    int any_swap = 0;
    int overall_swap = 0;
    
    int bribes = 0;
    int last = q[q_count-1];
    
    for(int i = q_count-2; i >= 0; --i){
        if(q[i] > i+3){
            //std::cout << "Too chaotic" << std::endl;
            printf("Too chaotic\n");
            return;
        }
        else if(q[i] == i+3)
            bribes += 2;
        else if(q[i] > last)
            ++bribes;
        else 
            last = q[i];
    }
    
    //std::cout << bribes << std::endl;
    printf("%d\n", bribes);
    /*
    do {
      any_swap =0;
      for (int i = 0; i < q_count -1; i++) // loop thru the array
      {
        if (q[i] > q [i+1]) // this will swap
        {
            int tmp = q[i+1];
            q[i+1] = q[i];  // swap
            q[i] = tmp; 
            
            if(debug) printf(" swapped: %d <-> %d\tnum_swaped: %d\n", q[i+1], q[i], num_swap);
            if (same == true) {
                 num_swap++;
                if ( num_swap +1 > 2) { printf("Too chaotic\n"); return;}
                if(debug) printf("same true, num_swap++: %d\n", num_swap);
                }
            if(debug) printfArray(i, q_count, q);

            same = true;
            overall_swap ++;
            any_swap++;
        }
        else {
        {
            same = false;
            num_swap = 0;
        }
        }
        //if ( num_swap > 2) { printf("Too chaotic\n"); return;}
      }
    } while (any_swap != 0);
    */
    //printf("%d\n", overall_swap);
    return;
}

int main()
{
    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char** q_temp = split_string(rtrim(readline()));

        int* q = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int q_item = parse_int(*(q_temp + i));

            *(q + i) = q_item;
        }

        minimumBribes(n, q);
    }

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
