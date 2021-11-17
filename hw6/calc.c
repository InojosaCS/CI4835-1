#include "parser.h"
#include "hash.h"

typedef struct Calc {
	hash_t * table;
} calc_t;

// The calc_create function creates an instance of the struct Calc data type and returns a pointer to it.
struct Calc *calc_create(void) {
	struct Calc * calc = (struct Calc *) malloc(sizeof(struct Calc));	 
	calc->table = (hash_t *) malloc(sizeof(hash_t));
	hash_init(calc->table, 128);
	
	return calc;
}

// The calc_destroy function destroys an instance of the struct Calc data type, by deallocating its memory.
void calc_destroy(struct Calc **calc) {
	free((*calc)->table);
}

/*
The calc_eval function evaluates an expression stored as a C character string in expr, saving the result of evaluating the expression in the variable pointed to by result. If the evaluation succeeds, calc_eval should return 1. If the evaluation fails because expr is invalid, calc_eval should return 0.
*/
int calc_eval(struct Calc *calc, char *expr, int *result){
	char (*splittedExpr[5]);
	for(int i = 0; i < 5; i++) {
		splittedExpr[i] = (char *) malloc(sizeof(char) * 16);
		splittedExpr[i][0] = '\0';
	}

	int i = 0, j = 0, pos = 0;

	for(i = 0; i <= (int) strlen(expr); i++) {
		if(pos == 5) {
			break;
		}
		if(expr[i] == '\0' || expr[i] == ' ' || expr[i] == '\n') {
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
	if(is_operand(splittedExpr[0]) && (null == 4)) {
		if(is_number(splittedExpr[0])) {
			*result = string_to_int(splittedExpr[0]);
			return TRUE;
		} 

		int value = hash_lookup(calc->table, splittedExpr[0]);
		//printf("%d here %s\n", hash_lookup(calc->table, splittedExpr[0]), splittedExpr[0]);
		//printf("%d here %s\n", hash_lookup(calc->table, "hola"), "hola");

		if(value == NF){
			*result = FALSE;
			return FALSE;
		} 

		*result = value;
		return TRUE;
	} 

	// operand op operand
	if(is_operand(splittedExpr[0]) && is_op(splittedExpr[1]) && is_operand(splittedExpr[2]) && (null == 2)) {
		int operand1 = NF;
		int operand2 = NF;

		if(is_number(splittedExpr[0])) operand1 = string_to_int(splittedExpr[0]);
		if(is_number(splittedExpr[2])) operand2 = string_to_int(splittedExpr[2]);
		if(hash_lookup(calc->table, splittedExpr[0]) != NF) operand1 = hash_lookup(calc->table, splittedExpr[0]);
		if(hash_lookup(calc->table, splittedExpr[2]) != NF) operand2 = hash_lookup(calc->table, splittedExpr[2]);
	
		if(operand1 == NF || operand2 == NF) {
			*result = FALSE;
			return FALSE;
		}

		if((strcmp(splittedExpr[1], "/") == 0) && (operand2 == 0)) {
			*result = FALSE;
			return FALSE;
		}

		if(strcmp(splittedExpr[1], "+") == 0) *result = operand1 + operand2;
		if(strcmp(splittedExpr[1], "-") == 0) *result = operand1 - operand2;
		if(strcmp(splittedExpr[1], "*") == 0) *result = operand1 * operand2;
		if(strcmp(splittedExpr[1], "/") == 0) *result = operand1 / operand2;

		return TRUE;
	}

	// var = operand 
	if(is_variable(splittedExpr[0]) && is_equal(splittedExpr[1]) && is_operand(splittedExpr[2]) && (null == 2)) {
		int op2 = NF;
		//printf("%d here %s\n", hash_lookup(calc->table, splittedExpr[2]), splittedExpr[2]);
		//printf("%d here %s\n", hash_lookup(calc->table, "hola"), "hola");
		//printf("%d\n", strcmp(splittedExpr[2], "hola"));

		//getting the value of op2
		if(is_number(splittedExpr[2])) {
			op2 = string_to_int(splittedExpr[2]);
		} else if(hash_lookup(calc->table, splittedExpr[2]) != NF) {
			op2 = hash_lookup(calc->table, splittedExpr[2]);
		} else {
		
			*result = FALSE;
			return FALSE;
		}

		hash_delete(calc->table, splittedExpr[0]);
		hash_insert(calc->table, splittedExpr[0], op2);
		*result = op2;
		//printf("%s = %d\n", splittedExpr[0], op2);
		return TRUE;
	}

	// var = operand op operand
	if(is_variable(splittedExpr[0]) && is_equal(splittedExpr[1]) 
		&& is_operand(splittedExpr[2]) && is_op(splittedExpr[3]) && is_operand(splittedExpr[4]) ) {
		
		int operand1 = NF;
		int operand2 = NF;

		//printf("%d here %s\n", hash_lookup(calc->table, splittedExpr[2]), splittedExpr[2]);
		//printf("%d here %s\n", hash_lookup(calc->table, "hola"), "hola");

		if(is_number(splittedExpr[4])) operand2 = string_to_int(splittedExpr[4]);
		if(is_number(splittedExpr[2])) operand1 = string_to_int(splittedExpr[2]);
		if(hash_lookup(calc->table, splittedExpr[4]) != NF) operand2 = hash_lookup(calc->table, splittedExpr[4]);
		if(hash_lookup(calc->table, splittedExpr[2]) != NF) operand1 = hash_lookup(calc->table, splittedExpr[2]);
	
		if(operand1 == NF || operand2 == NF) {
			*result = FALSE;
			return FALSE;
		}

		if(strcmp(splittedExpr[3], "/") == 0 && (operand2 == 0)) {
			*result = FALSE;
			return FALSE;
		}

		if(strcmp(splittedExpr[3], "+") == 0) *result = operand1 + operand2;
		if(strcmp(splittedExpr[3], "-") == 0) *result = operand1 - operand2;
		if(strcmp(splittedExpr[3], "*") == 0) *result = operand1 * operand2;
		if(strcmp(splittedExpr[3], "/") == 0) *result = operand1 / operand2;


		hash_delete(calc->table, splittedExpr[0]);
		hash_insert(calc->table, splittedExpr[0], *result);
		return TRUE;
	}

	return FALSE;
}

/*
int main(int argc, char *argv[]) {
//	struct Calc *calc = calc_create();
	struct Calc *calc = calc_create();

	int result = 0;

	calc_eval(calc, "b = 33 - 15", &result);
	printf("%d\n", result);
	calc_eval(calc, "b", &result);
	printf("%d\n", result);
	calc_eval(calc, "hola = 41 + 3", &result);
	printf("%d\n", result);
	calc_eval(calc, "hola", &result);
	printf("%d\n", result);
	calc_eval(calc, "hola + 5", &result);
	printf("%d\n", result);
	calc_eval(calc, "hola = hola + 3", &result);
	printf("%d\n", result);
	calc_eval(calc, "a = hola", &result);
	printf("%d\n", result);
	calc_eval(calc, "a = hola", &result);
	printf("%d\n", result);
}
*/