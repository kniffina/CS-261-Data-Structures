/* CS261- Assignment 1 - Q.2*/
/* Name: Adam Kniffin
* Date: 6/21/2016
* Solution description: In main integers are initialized, and 
then passed to the foo function where multiple different procedures
takes place. The value of c is returned from foo. The ints are 
outputted to the user before, and after.
*/

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c) {
	/*Set a to double its original value*/
	*a = *a * 2;

	/*Set b to half its original value*/
	*b = *b / 2;

	/*Assign a+b to c*/
	c = *a + *b;

	/*Return c*/
	return c;
}

int main() {
	/*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5;
	int y = 6;
	int z = 7;

	/*Print the values of x, y and z*/
	printf("int x = %i\n", x);
	printf("int y = %i\n", y);
	printf("int z = %i\n", z);

	/*Call foo() appropriately, passing x,y,z as parameters*/
	int toReturn = foo(&x, &y, z);

	/*Print the value returned by foo*/
	printf("The value returned by the function foo is %i\n", toReturn);

	/*Print the values of x, y and z again*/
	printf("int x = %i\n", x);
	printf("int y = %i\n", y);
	printf("int z = %i\n", z);

	/*Is the return value different than the value of z?  Why?

	ANSWER: The reason the value of z has not changed is because
	the value was passed in by value and not by reference.Since
	the value was passed in by value and even thought it is changed
	in the function foo, once it leaves that function and is back in
	int main, it contains the same value and is out of scope.
	*/
	return 0;
}


