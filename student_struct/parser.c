
#include <stdio.h>
#include <stdlib.h>
#include "studenStruct.h"

/**
* Parses a passed file and fills out the passed Student array
*/
int getArrayOfStudents(char * fileName, Student * students){
	//Allocate just enough memory for names of 30 characters long	
	char lastname[30],firstname[30];
	
	//
	FILE * file = fopen(fileName, "r");	//open the file
	int idCounter=0;
	if (file){
		//Continue fscanf(file) as long as every line is token-able into grade, first, lastname			
		while(fscanf(file,"%c,%30s %30s\n",&students[idCounter].grade,firstname,lastname)==3) {
			students[idCounter].identifier=idCounter+1;						
			snprintf(students[idCounter].name,30,"%s %s",firstname,lastname);
			idCounter++;
		}
	}
	return idCounter;
}
