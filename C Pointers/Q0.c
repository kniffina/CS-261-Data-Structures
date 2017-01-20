/* CS261- Assignment 1 - Q. 0*/
/* Name: Adam Kniffin
* Date: 4/5/2016
* Solution description: For each of the questions
asked I go through and print wht the question is asking
for clarity. I then you pointer notation in the print
statements to print the addresses and values of the
data element in question.
*/

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr) {
	/*Print the value pointed to by iptr*/
	printf("The value pointed to by iptr is %i\n", *iptr);

	/*Print the address pointed to by iptr*/
	printf("The address pointed to by iptr is %p\n", iptr);

	/*Print the address of iptr itself*/
	printf("The address of iptr itself is %p\n", &iptr);
}

int main() {

	/*declare an integer x*/
	int x = 5;

	/*print the address of x*/
	printf("The address of x is %p\n", &x);

	/*Call fooA() with the address of x*/
	fooA(&x);

	/*print the value of x*/
	printf("The value of x is %i\n", x);

	return 0;
}