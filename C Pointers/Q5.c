/* CS261- Assignment 1 - Q.5*/
/* Name: Adam Kniffin	
* Date: 6/21/2016
* Solution description: This program allows a user to enter a string
and then converts it to sticky caps. Each function has more description
below.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch) {
	//check to make sure letter is  lower case
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 'A';
	else
		return ch;
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch) {
	//check to make sure letter is upper case
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 'a';
	else
		return ch;
}

void sticky(char* word) {
	/*Convert to sticky caps*/
	int i; //int used in for-loop

	//loops through each value (up to 100) and
	//if the position needs to be capitalized then the
	//upper and lower functions are called to complete the task
	for (i = 0; i < 100; i++){
		if (word[i] == '\0')
			return;

		if (i % 2)
			word[i] = toLowerCase(word[i]);
		else
			word[i] = toUpperCase(word[i]);
	}
}

int main() {
	//create character array
	char word[100];

	/*Read word from the keyboard using scanf*/
	printf("Please enter a string: ");
	scanf("%s", word);

	/*Call sticky*/
	sticky(word);

	/*Print the new word*/
	printf("%s\n", word);

	return 0;
}
