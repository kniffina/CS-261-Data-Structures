/* CS261- Assignment 1 - Q.1*/
/* Name:
* Date:
* Solution description:
*/

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student {
	int id;
	int score;
};

struct student* allocate() {
	/*Allocate memory for ten students*/
	struct student* students = (struct student*)malloc(10 * sizeof(struct student));

	/*return the pointer*/
	return students;
}


void generate(struct student* students) {
	/*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/

	int i, j;	   //integers used in for-loops
	int studentId; //int used to hold random student ID
	int flag;	   //flag used to determine if ID is unique

	//for loop goes until the maximum 
	for (i = 0; i < 10; i++) {
		
		do {
			flag = 1; //set flag to 1
			
			studentId = (rand() % 10 + 1); //generate a random student id

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
}

void output(struct student* students) {
	/*Output information about the ten students in the format:
	ID1 Score1
	ID2 score2
	ID3 score3
	...
	ID10 score10*/
	int i;
	//loops through each element in the students array
	for (i = 0; i < 10; i++) {
		printf("ID%i  Score %i\n", students[i].id, students[i].score);
	}
}

void summary(struct student* students) {
	/*Compute and print the minimum, maximum and average scores of the ten students*/
	int i, min, max, total = 0, average;

	//set min and max value to the first score
	min = students[0].score;
	max = students[0].score;
	total += students[0].score;

	//start the for loop at 1 because the first value
	//already has been covered
	for (i = 1; i < 10; i++){
		if (students[i].score < min)
			min = students[i].score;

		if (students[i].score > max)
			max = students[i].score;

		//increment each of the students score
		total += students[i].score;
	}
	//calculate average by dividing the total by 10
	average = total / 10;

	printf("The minimum score is %i\n", min);
	printf("The maximum score is %i\n", max);
	printf("The average score is %i\n", average);
}

void deallocate(struct student* stud) {
	/*Deallocate memory from stud*/
	if (stud != NULL)
		free(stud);
}

int main() {
	//struct student* stud = NULL;
	struct student* stud = NULL;

	/*call allocate*/
	stud = allocate();

	/*call generate*/
	generate(stud);

	/*call output*/
	output(stud);

	/*call summary*/
	summary(stud);

	/*call deallocate */
	deallocate(stud);
	return 0;
}
