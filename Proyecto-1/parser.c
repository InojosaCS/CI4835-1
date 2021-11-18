#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define NF -251199
#define debug printf("Aqui\n")

 /*
  * The is_number function checks if the string passed as a parameter is a number.	
  *	
  * @param string - The string to be checked.
  * @return 1 if the string is a number, 0 otherwise.
  */
int is_number(char * str) {
	int i = 0;
	int is_number = TRUE;
	
	while(str[i] != '\0' && str[i] != '\n' && str[i] != '\r') {
		if(!isdigit(str[i])) {
			is_number = FALSE;
			break;
		}
		i++;
	}
	
	return is_number;
}

/* 
 * The is_variable function checks if the string is a variable like [a-zA-Z]. 
 * 
 * @param string - The string to be checked.
 * @return 1 if the string is a variable, 0 otherwise.
 */
int is_variable(char * str){
	int i = 0;
	int is_variable = TRUE;
	
	while(str[i] != '\0' && str[i] != '\n' && str[i] != '\r') {
		if(!isalpha(str[i])) {
			is_variable = FALSE;
			break;
		}
		i++;
	}
	
	return is_variable;
}

/*
 * The string_to_int function converts a string to an integer.
 * 
 * @param string - The string to be converted.
 * @return The integer value of the string.
 */
int string_to_int(char * str) {
	int i = 0;
	int number = 0;
	
	while(str[i] != '\0' && str[i] != '\n' && str[i] != '\r') {
		number = number * 10 + (str[i] - '0');
		i++;
	}
	
	return number;
}

/* 
 * is_op function checks if the string is an operator.
 * 
 * @param string - The string to be checked.
 * @return 1 if the string is an operator, 0 otherwise.
 */
int is_op(char * str) {
	return strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "*") == 0 || strcmp(str, "/") == 0;
}

/*
 * is_operand function checks if the string is a variable or a literal.
 *
 * 	@param string - The string to be checked.
 * 	@return 1 if the string is a variable or a literal, 0 otherwise.
 */
int is_operand(char * str){
	return is_number(str) || is_variable(str);
}

int is_equal(char * str) {
	return strcmp(str, "=") == 0;
}

