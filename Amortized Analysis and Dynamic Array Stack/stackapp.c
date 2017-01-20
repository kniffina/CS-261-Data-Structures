/*	stack.c: Stack application. */
/*	dynamicArray.c: Dynamic Array implementation. */
/* CS261- Assignment 1 - stackapp.c*/
/* Name: Adam Kniffin
* Date: 7/7/2016
* Solution description: This program is used to determine if a character
array passed to the isBalanced() function has an equal number of opening
and closing braces. In additiont to this, they must appear in the correct
order. This is done by using a stack application to push and pop the values
off as they come up.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"

/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
param: 	s pointer to a string
pre: s is not null
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s + i);
	if (c == '\0')
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
param: 	s pointer to a string
pre: s is not null
post:
*/
int isBalanced(char* s)
{
	//create stack that we can use
	struct DynArr *stack = newDynArr(10);
	char c;

	//loop until the next char in s is equal to nothing
	while ((c = nextChar(s)) != '\0') {
		//if there is an opening brace, push it on the stack
		switch (c) {
		case '{':
		case '[':
		case '(':
			pushDynArr(stack, c);
			break;

			//next part of code checks to see if a closing bracket is next
			//in the char array passed in. If it is, then it checks the top 
			//of the stack to see if an opening brace is there. If it is, then the top
			//of the stack is removed. If it is not then, false is returned.
		case '}':
			if (topDynArr(stack) == '{') {
				popDynArr(stack);
				break;
			}
			return 0;

		case ']':
			if (topDynArr(stack) == '[') {
				popDynArr(stack);
				break;
			}
			return 0;

		case ')':
			if (topDynArr(stack) == '(') {
				popDynArr(stack);
				break;
			}
			return 0;
		}
	}

	//if stack is empty then all the parenthesis have been removed
	if (isEmptyDynArr(stack) == 1)
		return 1;
	else
		return 0;
}

int main(int argc, char* argv[]) {

	char *s = { "(([Testing])} " };
	int res;

	printf("Assignment 2\n");

	res = isBalanced(s);

	
	if (res)
		printf("The string %s is balanced\n", s);
	else
		printf("The string %s is not balanced\n", s);

	return 0;
}