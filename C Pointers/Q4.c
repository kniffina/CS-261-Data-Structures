/* CS261- Assignment 1 - Q.4*/
/* Name: Adam Kniffin	
* Date: 6/21/2016
* Solution description: The main point of this program is to
sort studnets in ascending order based on their score. This is done
by comparing scores and if a score needs to be moved, a temp student
is created and the values are swapped and then the temp is used
to reallocate the correct position.
*/

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student {
	int id;
	int score;
};

void sort(struct student* students, int n) {
	/*Sort the n students based on their score*/

	//integer declaration for, for-loops
	int i, j;

	//two forloops go through each value and determine if there is a 
	//value in the array that needs to be swapped. If the score
	//is higher then the score being compared then a temp struct student
	//is created and the positions are swapped. 
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (students[j].score > students[i].score)
			{
				struct student temp = students[i];
				students[i] = students[j];
				students[j] = temp;
			}
		}
	}//end for loop
}

int main() {
	/*Declare an integer n and assign it a value.*/
	int n = 5;

	/*Allocate memory for n students using malloc.*/
	struct student *students = (struct student*)malloc(n * sizeof(struct student));

	/*Generate random IDs and scores for the n students, using rand().*/
	int i, j;
	int studentId, flag;
	//for loop goes until the maximum 
	for (i = 0; i < n; i++) {

		do {
			flag = 1; //set flag to 1

			studentId = (rand() % n + 1); //generate a random student id

										   //loop through each of the students already in the array, and 
										   //as long as flag is equal to 1
			for (j = 0; j < i && flag == 1; j++) {

				//if the student id equals at the current location in the array
				//is equal to the studentID generated, do not add it to the array
				if (students[j].id == studentId) {
					flag = 0; //set flag to 0
				}
			}
		} while (flag == 0); //will loop until unique ID is found

		students[i].id = studentId;
		students[i].score = (rand() % 101);
	}

	/*Print the contents of the array of n students.*/
	for (i = 0; i < n; i++) {
		printf("Student ID: %i  Score: %i \n", students[i].id, students[i].score);
	}

	/*Pass this array along with n to the sort() function*/
	sort(students, n);
	printf("\n\n****   SORTED   ***\n\n"); //for spacing and clarity

	/*Print the contents of the array of n students.*/
	for (i = 0; i < n; i++) {
		printf("Student ID: %i  Score: %i \n", students[i].id, students[i].score);
	}
	return 0;
}
