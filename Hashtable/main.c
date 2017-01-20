#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/**
* Allocates a string for the next word in the file and returns it. This string
* is null terminated. Returns NULL after reaching the end of the file.
* @param file
* @return Allocated string or NULL.
*/
char* nextWord(FILE* file)
{
	int maxLength = 16;
	int length = 0;
	char* word = malloc(sizeof(char) * maxLength);
	while (1)
	{
		char c = fgetc(file);
		if ((c >= '0' && c <= '9') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z') ||
			c == '\'')
		{
			if (length + 1 >= maxLength)
			{
				maxLength *= 2;
				word = realloc(word, maxLength);
			}
			word[length] = c;
			length++;
		}
		else if (length > 0 || c == EOF)
		{
			break;
		}
	}
	if (length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

/**
* Prints the concordance of the given file and performance information. Uses
* the file input1.txt by default or a file name specified as a command line
* argument.
* @param argc
* @param argv
* @return
*/
int main(int argc, const char** argv)
{
	// FIXME: implement
	const char* fileName = "input1.txt";
	if (argc > 1)
	{
		fileName = argv[1];
	}
	printf("Opening file: %s\n", fileName);

	clock_t timer = clock();

	struct HashMap* map = hashMapNew(10);

	// --- Concordance code begins here ---
	// Be sure to free the word after you are done with it here.
	char *word;

	int tableSize = 10;

	//create the fileptr and open
	FILE *fileptr = fopen(fileName, "r");

	timer = clock();
	
	word = nextWord(fileptr);

	//loop until not a word
	while (word) {

		//if the word is already in the map, increment its occurences (value)
		if (hashMapContainsKey(map, word))
			++(*hashMapGet(map, word));

		//word isnt in the list yet, so add it and give it value of 1
		else
			hashMapPut(map, word, 1);

		//move to the next word using nextWord function
		word = nextWord(fileptr);
	}
	//close the file
	fclose(fileptr);
	fileptr = NULL;

	
	//print the words with the number of occurences that took place
	printf("\n\n");
	int i;
	for (i = 0; i < map->capacity; i++) {
		struct HashLink *current = map->table[i];
		while (current != NULL) {
			printf("%s: %d\n", current->key, current->value);
			current = current->next;
		}
	}
	// --- Concordance code ends here ---

	hashMapPrint(map);

	timer = clock() - timer;
	printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
	printf("Number of links: %d\n", hashMapSize(map));
	printf("Number of buckets: %d\n", hashMapCapacity(map));
	printf("Table load: %f\n", hashMapTableLoad(map));

	hashMapDelete(map);
	return 0;
}
