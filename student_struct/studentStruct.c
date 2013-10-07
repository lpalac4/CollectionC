/**
* @author Luis Palacios
* Common operations for a simple Student struct.
*
*/

#include <stdio.h>
#include "studentStruct.h"

/**
* Prints the information inside Student strutc in both hex format and as a string.
*/
void printStudent(Student student){
	//Print the student struct in hex
	char* studentPtr = (char*) &student;
	for(i = 0; i < sizeof(Student); i++){
		printf("%X", studentPtr[i]);
	}

	//Prints struct information in a comprehendable format
	
	printf("ID: %d",student.identifier);
	printf("Name: ");
	printf("%s", student.name);
	printf ("Grade: %c",student.grade);
}

/**
* Prints only the last name of every student
*/
void printStudentShort(Student student){
	//Print only the last name of every Student entry
	char* lastName;

	while(*lastName != ' ') lastName++;
	printf("%c. %s \n", student.name[0], lastName);

}

/**
* Replaces the name of Student s, with the passed char*.
*/
Student renameStudent(Student s, char* newName){
	int i;
	for(i=0;i<sizeof(newName); i++)
		s.name[i] = newName[i];
	//add the null terminator	
	s.name[i] = 0;
	return s;
}

/**
* Sorts the Student structs in our array using a simple bubble sort
* may not handle all cases on swap- not saying I cant just that its hopefully a 
* reason to update later.
*/
void sortStudentRecords(Student *students, int count){	
 
	int i, j;
	Student tmp;
	for(i = (count - 1); i > 0; i--){
		for(j=0; j<= i; j++){
			if(students[j-1].grade < students[j].grade){
				tmp = students[j-1];
				students[j-1] = students[j];
				students[j] = tmp;
			}
		}
	}	
} 
