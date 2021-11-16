#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define NF -251199
#define debug printf("Aqui\n")

// The is_number function checks if the string passed as a parameter is a number.
int is_number(char * str) {
	int i = 0;
	int is_number = TRUE;
	
	while(str[i] != '\0' && str[i] != '\n') {
		if(!isdigit(str[i])) {
			is_number = FALSE;
			break;
		}
		i++;
	}
	
	return is_number;
}

// The is_variable function checks if the string is a variable like [a-zA-Z]. 
int is_variable(char * str){
	int i = 0;
	int is_variable = TRUE;
	
	while(str[i] != '\0' && str[i] != '\n') {
		if(!isalpha(str[i])) {
			is_variable = FALSE;
			break;
		}
		i++;
	}
	
	return is_variable;
}

// The string_to_int function converts a string to an integer.
int string_to_int(char * str) {
	int i = 0;
	int number = 0;
	
	while(str[i] != '\0') {
		number = number * 10 + (str[i] - '0');
		i++;
	}
	
	return number;
}

int is_op(char * str) {
	return strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "*") == 0 || strcmp(str, "/") == 0;
}

int is_operand(char * str){
	return is_number(str) || is_variable(str);
}

int is_equal(char * str) {
	return strcmp(str, "=") == 0;
}

