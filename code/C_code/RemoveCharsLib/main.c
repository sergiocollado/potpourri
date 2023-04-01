#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "removeChars.h"

int main(int argc, char* argv[]) {

	printf("Removed charactes!\n");

	if ( argc < 3) {

		printf("add a string and an max repetition limit\n");
		printf("example: ./myprogram kkkllrrrzzz 3\n");
		return (EXIT_FAILURE);
        }

	char* outputString = removeChars(argv[1], atoi(argv[2]));

	printf("output string: %s\n", outputString);
	free(outputString);
}
