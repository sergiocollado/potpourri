#include "removeChars.h"

char* removeChars(char* inputString, size_t max_repetitions)
{
	int index = 0;
	unsigned char* actualChar = NULL;
	unsigned char* previousChar = NULL;
	size_t counter = 0;

	size_t length = strlen(inputString);
	char* outputString = (char*)calloc((length+1), sizeof(char)); //lenght +1 is to account for the \0 at the end.
	size_t outputIndex = 0;

	while(index < length+1) {
		actualChar = &inputString[index];
		if(index > 0) { previousChar = &inputString[index-1];}

		if (previousChar && *actualChar != *previousChar)
		{ counter = 1;}
		else
		{ counter++; }

		if (counter <=  max_repetitions && max_repetitions < (length+1)) {
			outputString[outputIndex] = *actualChar;
			outputIndex++;
		}

		index++;
	}

	return outputString;
}
