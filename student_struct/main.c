/**
* @author Luis Palacios
* Becoming familiar with changing stored data.
*/

#include <stdio.h>
#include "studentStruct.h"
#include "parser.h"

int main(){
	//Allocate 100*sizeof(Student) bytes of data for storage
	Student students[100];
	
	////Fill that allocated memory and store the total number of students into count.
	int count = getArrayOfStudents("data", students);
  printf("Original record:\n\n");
	printStudent(students[0]);

	//Change the contents of that data and call print method
  char *newName="Hu Li";
  printf("\nRenaming to \"%s\"\n\n",newName);
	students[0] = renameStudent(students[0], newName);
  printStudent(students[0]);
	
	//Do the same thing again.
  newName="Balakrishnan Radhakrishnan";
  printf("\nRenaming to \"%s\"\n\n",newName);
  students[0] = renameStudent(students[0], newName);
	printStudent(students[0]);
	
}
