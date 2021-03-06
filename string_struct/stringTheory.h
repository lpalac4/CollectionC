/**Header file for the String structure
* @Author Luis Palacios
*/

#include <stdio.h>
#include <stdlib.h>
#include "string.c"
/**
* String struct holding variables int len, char* str and pointers to next and previous struct Strings
* that together make up a entire string.
*/
struct String;
/**
* Constructor passing a pointer to the beginning of a char array.
*/
struct String* string_new(char* str);
/**
* Destructor
*/
void string_free(struct String* s);
/**
* A copy method for a passed String
*/
struct String* string_clone(struct String* s);
/**
* Returns the length of a passed String excluding the null terminator byte
*/
int string_length(struct String* s);
/**
* Appends a char* at the end of a String
*/
void string_append(struct String* a, char* b); 
/**
* Returns the char at a given index in the passed String
*/
char string_charAt(struct String* s,  int index);
/**
* Returns a substring in s, from index start to length
*/
char* string_range(struct String* s,  int start,  int length);
/**
* Returns the String as a char* given the string only
*/
char* string_chars(struct String* s);
/**
* Quick function evaluating the minimum length of strings between two ints
*/
int min(int a, int b);


