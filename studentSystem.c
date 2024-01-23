// This program will run FSKTM student detail system
// author mashitah
// version : 4
// last edit : 10/6/21 2:52 am

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 80
#define PROGRAM_STR_LEN 5

// structure for node
struct node 
{
	int studentId;
	char name[MAX_STR_LEN];
	char program[PROGRAM_STR_LEN];
	float cgpa;
	struct node *next; // node pointer that point to itself
};

void cleanInput(char *input); // Function to remove \n in string array
struct node *newNode(int studentId, char *name, char *program, float cgpa); // Create new node
int check(struct node *head, int studentId); // Function to check if the inserted detail already exist or not
void sortedInsert(struct node** head_ref, struct node* head, struct node* new_node, int studentId); // Insert new node in alphabetical name sorted
void findByProgram( struct node *head, char *program); // Find student info by entering program
void findByStudentID(struct node *head, int studentId);				   // Find student info by entering student id
void printList(struct node *head); // Print list of student detail
void Delete(int studentId, struct node *head); // Delete info by entering Id number

// Main Function
int main() 
{
	int choice, studentId;
	char name[MAX_STR_LEN], program[PROGRAM_STR_LEN];
	float cgpa;
	struct node *head = NULL; // declaration for head node
	struct node *new_node;	// declaration for the new node

	printf("----------WELCOME TO FSKTM STUDENT LIST MANAGEMENT "
		   "SYSTEM----------\n");

	// menu
	while (1) 
	{
		printf("\n\n1. Insert new student detail\n");
		printf("2. Remove a student\n");
		printf("3. Find student detail by Student ID\n");
		printf("4. Find student information in particular program\n");
		printf("5. Print all student detail\n");
		printf("6. Exit\n\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		fflush(stdin);

		switch (choice) {
		// to insert new student detail
		case 1:
			// input student id
			printf("\nEnter student ID: ");
			scanf("%d", &studentId);
			fflush(stdin);

			// input student name
			printf("Enter student name: ");
			fgets(name, MAX_STR_LEN, stdin);
			cleanInput(name);

			// input student program
			printf("( BIS / BIT / BIW / BIP / BIW )\nEnter student program : ");
			fgets(program, PROGRAM_STR_LEN, stdin);
			cleanInput(program);

			// input student cgpa
			printf("Enter student CGPA: ");
			scanf("%f", &cgpa);

			// to create a new node
			new_node = newNode(studentId, name, program, cgpa);

			// sort the node in alphabetical order of name
			sortedInsert(&head, head, new_node,studentId);
			break;

		// to remove a student detail by entering student id
		case 2:

			// input student id
			printf("\nEnter Student ID: ");
			scanf("%d", &studentId);

			// for deleting the detail
			Delete(studentId, head);
			break;

		// to find student detail by entering student id
		case 3:

			// input id
			printf("\nEnter Student ID: ");
			scanf("%d", &studentId);

			// search student detail by entering id
			findByStudentID(head, studentId);
			break;

		// to find student detail by entering program
		case 4:

			// input program
			printf("\nEnter Program: ");
			fgets(program, PROGRAM_STR_LEN, stdin);
			cleanInput(program);

			// search student detail in the same program
			findByProgram(head, program);
			break;
		case 5:

			// to print student detail list
			printList(head);
			break;
		case 6:
			exit(0);
			break;
		default:
			printf("\nPlease enter the right choice.\n");
		}
	}
	return 0;
}

// Function to remove \n in string array
void cleanInput(char *input) 
{
	int len = strlen(input);
	int i;
	for (i = 0; i < len - 1; i++) {
	}
	input[i] = '\0';
}

// Function to create a new node
struct node *newNode(int studentId, char *name, char *program, float cgpa) 
{
	// create a new node
	struct node *new_node;
	new_node = (struct node *)malloc(sizeof(struct node));

	// assigning the student detail in the node
	new_node->studentId = studentId;
	strcpy(new_node->name, name);
	strcpy(new_node->program, program);
	new_node->cgpa = cgpa;
	new_node->next = NULL;

	// returning the new node for sorting purpose
	return new_node;
}

// Function to check if the inserted detail already exist or not
int check(struct node *head, int studentId) 
{
	int count = 0;
	struct node *temp;
	temp = head;

	// to find if there is the same detail in the list as inserted detail
	// linearly
	while (temp != NULL) 
	{
		// if inserted detail same as detail in the node
		if (temp->studentId == studentId) 
		{
			count++;
			return 1;
		}
		// if do not have same detail in the node
		// go to next node
		else 
		{
			temp = temp->next;
		}
	}

	// if the inserted detail is not found in the list
	if (count < 1) 
	{
		return 0;
	}
}

// Insert student detail sorted by alphabetical ordering of namee
void sortedInsert(struct node **head_ref, struct node *head, struct node *new_node, int studentId) 
{
	struct node *current;
	int check1;

	check1 = check(head, studentId);

	// to check if the student already exist
	if (check1 == 1) 
	{
		printf("\nStudent with this record are already exists\n");
		free(new_node);
		return;
	}
	// if the new node location at head
	if (*head_ref == NULL || strcmp((*head_ref)->name, new_node->name) >= 0) 
	{
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	// if the new node location other than head
	else 
	{
		current = *head_ref;
		while (current->next != NULL && strcmp(current->next->name, new_node->name) <= 0) 
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

// Find student info by entering program
void findByProgram(struct node *head, char *program) 
{
	int result, count = 0;
	struct node *temp;
	temp = head;

	// loop to search the student detail linearly
	while (temp != NULL) 
	{
		// compare if the program inserted same as student program
		result = strcmpi(temp->program, program);

		// if the program inserted same as student program
		// print the detail
		if (result == 0) 
		{
			printf("\nStudent ID\t: %d\n", temp->studentId);
			printf("Name\t\t: %s\n", temp->name);
			printf("Program\t\t: %s\n", temp->program);
			printf("CGPA\t\t: %.2f\n", temp->cgpa);
			temp = temp->next;
			count++;
		}
		// the program inserted is not same as student program
		// go to next node
		else 
		{
			temp = temp->next;
		}
	}
	// if the program inserted are not found in the list
	if (count == 0) 
	{
		printf("\nStudent with program %s is not found in the system.\n", program);
	}
}

// Find student info by entering student id
void findByStudentID(struct node *head, int studentId) 
{
	int count = 0;
	struct node *temp;
	temp = head;

	// loop to search the student detail linearly
	while (temp != NULL) {
		// to find if the inserted id is same as id in the list
		// print the detail
		if (temp->studentId == studentId) 
		{
			printf("\nStudent ID\t: %d\n", temp->studentId);
			printf("Name\t\t: %s\n", temp->name);
			printf("Program\t\t: %s\n", temp->program);
			printf("CGPA\t\t: %.2f\n", temp->cgpa);
			temp = temp->next;
			count++;
		}

		// if the inserted id is not the same as id in the list
		// go to next node
		else 
		{
			temp = temp->next;
		}
	}

	// if the inserted id is not found in the list
	if (count == 0)
	{
		printf("\nStudent with ID %d is not found in the system.\n", studentId);
	}
}

// Print list of student detail
void printList(struct node *head) 
{
	struct node *temp = head;
	// loop to print the list
	while (temp != NULL) 
	{
		printf("\nStudent ID\t: %d\n", temp->studentId);
		printf("Name\t\t: %s\n", temp->name);
		printf("Program\t\t: %s\n", temp->program);
		printf("CGPA\t\t: %.2f\n", temp->cgpa);
		temp = temp->next;
	}
}

// Delete info by entering Id number
void Delete(int studentId, struct node *head) 
{
	struct node *temp1 = head;
	struct node *temp2 = head;

	while (temp1 != NULL) 
	{
		if (temp1->studentId == studentId) 
		{
			printf(
				"Student details with Id number %d is found in the system.\n", studentId);

			if (temp1 == temp2) // this condition will run if the record that we need to delete is the first node of the linked list
			{
				head = head->next;
				free(temp1);
			} else {
				temp2->next = temp1->next; // temp 1 is the node to delete while temp 2 is node previous to temp 1
				free(temp1);
			}

			printf("Student details with Id number %d is deleted from the system.\n", studentId);
			return;
		}
		temp2 = temp1;
		temp1 = temp1->next;
	}
	printf("Student with Id number %d is not found in the system.\n", studentId);
}
