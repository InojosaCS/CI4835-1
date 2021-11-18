#include "parser.h"
#include "hash.h"

typedef struct Calc {
	hash_t * table;
} calc_t;

/*
 * calc_create() creates an instance of the struct Calc data type and returns a pointer to it.
 * @returns a pointer to the newly created struct Calc
 */
struct Calc *calc_create(void) {
	struct Calc * calc = (struct Calc *) malloc(sizeof(struct Calc));	 
	calc->table = (hash_t *) malloc(sizeof(hash_t));
	hash_init(calc->table, 128);
	
	return calc;
}

/* 
 * The calc_destroy function takes a pointer to the struct Calc data type as a parameter.
 * It frees the memory allocated to the struct Calc data type.
 * It returns no value.
 * */
void calc_destroy(struct Calc **calc) {
	free((*calc)->table);
}

/*
 * The calc_eval function evaluates an expression stored as a C character string in expr, saving the result
 * of evaluating the expression in the variable pointed to by result. If the evaluation succeeds, calc_eval
 * should return 1. If the evaluation fails because expr is invalid, calc_eval should return 0.
 * 
 * @param calc - pointer to the struct Calc data type
 * @param expr - pointer to the C character string containing the expression to be evaluated
 * @param result - pointer to the variable where the result of the evaluation will be stored
 * @return 1 if the evaluation succeeds, 0 otherwise
 */
int calc_eval(struct Calc *calc, char *expr, int *result){
	char (*splittedExpr[5]);

	for(int i = 0; i < 5; i++) {
		splittedExpr[i] = (char *) malloc(sizeof(char) * 16);
		splittedExpr[i][0] = '\0';
	}

	int i = 0, j = 0, pos = 0;

	/* split the expression into tokens */
	for(i = 0; i <= (int) strlen(expr); i++) {
		if(pos == 5) {
			break;
		}
		if(expr[i] == '\0' || expr[i] == ' ' || expr[i] == '\n' || expr[i] == '\r') {
			splittedExpr[pos][j] = '\0';
			pos++;
			j = 0;
		} else {
			splittedExpr[pos][j] = expr[i];
			j++;
		}
	}

	int null = 0;


	for(i = 0; i < 5; i++) {
		if(strcmp(splittedExpr[i], "") == 0) null++;
	}

	// Operand
	/* if the expression is a single operand */
	if(is_operand(splittedExpr[0]) && (null == 4)) {
		if(is_number(splittedExpr[0])) {
			*result = string_to_int(splittedExpr[0]);
			return TRUE;
		} 

		int value = hash_lookup(calc->table, splittedExpr[0]);

		if(value == NF){
			*result = FALSE;
			return FALSE;
		} 

		*result = value;
		return TRUE;
	} 

	// operand op operand
	/* if the expression is a binary operation */
	if(is_operand(splittedExpr[0]) && is_op(splittedExpr[1]) && is_operand(splittedExpr[2]) && (null == 2)) {
		int operand1 = NF;
		int operand2 = NF;

		/* Check if the operands are numbers or varibles that exists */
		if(is_number(splittedExpr[0])) operand1 = string_to_int(splittedExpr[0]);
		if(is_number(splittedExpr[2])) operand2 = string_to_int(splittedExpr[2]);
		if(hash_lookup(calc->table, splittedExpr[0]) != NF) operand1 = hash_lookup(calc->table, splittedExpr[0]);
		if(hash_lookup(calc->table, splittedExpr[2]) != NF) operand2 = hash_lookup(calc->table, splittedExpr[2]);
	
		/* if the operands are not numbers or variables that exists */
		if(operand1 == NF || operand2 == NF) {
			*result = FALSE;
			return FALSE;
		}

		/* division by zero */
		if((strcmp(splittedExpr[1], "/") == 0) && (operand2 == 0)) {
			*result = FALSE;
			return FALSE;
		}

		/* mappping the operator to the corresponding function */
		if(strcmp(splittedExpr[1], "+") == 0) *result = operand1 + operand2;
		if(strcmp(splittedExpr[1], "-") == 0) *result = operand1 - operand2;
		if(strcmp(splittedExpr[1], "*") == 0) *result = operand1 * operand2;
		if(strcmp(splittedExpr[1], "/") == 0) *result = operand1 / operand2;

		return TRUE;
	}

	// var = operand 
	/* if the expression is a variable assignment */
	if(is_variable(splittedExpr[0]) && is_equal(splittedExpr[1]) && is_operand(splittedExpr[2]) && (null == 2)) {
		int op2 = NF;

		//getting the value of op2
		if(is_number(splittedExpr[2])) {
			op2 = string_to_int(splittedExpr[2]);
		} else if(hash_lookup(calc->table, splittedExpr[2]) != NF) {
			op2 = hash_lookup(calc->table, splittedExpr[2]);
		} else {
		
			*result = FALSE;
			return FALSE;
		}

		/* if the variable is already in the table */
		hash_delete(calc->table, splittedExpr[0]);
		hash_insert(calc->table, splittedExpr[0], op2);
		*result = op2;
		return TRUE;
	}

	// var = operand op operand
	/* if the expression is a binary operation assignment */
	if(is_variable(splittedExpr[0]) && is_equal(splittedExpr[1]) 
		&& is_operand(splittedExpr[2]) && is_op(splittedExpr[3]) && is_operand(splittedExpr[4]) ) {
		
		int operand1 = NF;
		int operand2 = NF;

		/* Check if the operands are numbers or varibles that exists */
		if(is_number(splittedExpr[4])) operand2 = string_to_int(splittedExpr[4]);
		if(is_number(splittedExpr[2])) operand1 = string_to_int(splittedExpr[2]);
		if(hash_lookup(calc->table, splittedExpr[4]) != NF) operand2 = hash_lookup(calc->table, splittedExpr[4]);
		if(hash_lookup(calc->table, splittedExpr[2]) != NF) operand1 = hash_lookup(calc->table, splittedExpr[2]);
	
		/* if the operands are not numbers or variables that exists */
		if(operand1 == NF || operand2 == NF) {
			*result = FALSE;
			return FALSE;
		}

		/* division by zero */
		if(strcmp(splittedExpr[3], "/") == 0 && (operand2 == 0)) {
			*result = FALSE;
			return FALSE;
		}

		/* mappping the operator to the corresponding function */
		if(strcmp(splittedExpr[3], "+") == 0) *result = operand1 + operand2;
		if(strcmp(splittedExpr[3], "-") == 0) *result = operand1 - operand2;
		if(strcmp(splittedExpr[3], "*") == 0) *result = operand1 * operand2;
		if(strcmp(splittedExpr[3], "/") == 0) *result = operand1 / operand2;


		/* if the variable is already in the table */
		hash_delete(calc->table, splittedExpr[0]);
		hash_insert(calc->table, splittedExpr[0], *result);
		return TRUE;
	}

	return FALSE;
}