/* CS261- Assignment 1 - Q.3*/
/* Name: Adam Kniffin	
* Date: 6/21/2016
* Solution description: Random integers are generated
and space is set aside in memory. The array is then sent 
to the sort function which puts them into ascending order
based on their value.
*/

#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n) {
	/*Sort the given array number , of length n*/
	int i, j; //declare 2 ints to use in for-loops

	//two forloops go through each value and determine if there is a 
	//value in the array that needs to be swapped. If it does, then 
	//a temp integer holds the value that is lower and is swapped,
	//leaving the array in ascending order.
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (number[j] > number[i]) {
				int temp = number[i];
				number[i] = number[j];
				number[j] = temp;
			}
		}
	}//end both for loops
}

int main() {
	/*Declare an integer n and assign it a value of 20.*/
	int n = 20;

	/*Allocate memory for an array of n integers using malloc.*/
	int *array = (int *)malloc(n * sizeof(int));

	/*Fill this array with random numbers, using rand().*/
	int i;
	for (i = 0; i < n; i++) {
		//generate random numbers between 1 and 10
		array[i] = rand() % 11;
	}

	/*Print the contents of the array.*/
	for (i = 0; i < n; i++){
		printf("| %i | is at position | %i | of the array.\n", array[i], i);
	}

	/*Pass this array along with n to the sort() function of part a.*/
	sort(array, n);

	/*Print the contents of the array.*/
	printf("\n\n****   SORTED   ***\n"); //for spacing and clarity

	for (i = 0; i < n; i++) {
		printf("| %i | is at position | %i | of the array.\n", array[i], i);
	}

	return 0;
}