#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define FAIL -251199
#define debug printf("Aqui\n")

int is_number(char * str);
int is_variable(char * str);
int string_to_int(char * str);
int is_op(char * str);
int is_operand(char * str);
int is_equal(char * str);


