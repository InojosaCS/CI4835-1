#include "parser.h"
#include "hash.h"

typedef struct Calc {
	hash_t * table;
} calc_t;

// The calc_create function creates an instance of the struct Calc data type and returns a pointer to it.
struct Calc *calc_create(void) {
	struct Calc * calc = (struct Calc *) malloc(sizeof(struct Calc));	 
	calc->table = (hash_t *) malloc(sizeof(hash_t));
	hash_init(calc->table, 0);
	
	return calc;
}

// The calc_destroy function destroys an instance of the struct Calc data type, by deallocating its memory.
void calc_destroy(struct Calc **calc) {
}

/*
The calc_eval function evaluates an expression stored as a C character string in expr, saving the result of evaluating the expression in the variable pointed to by result. If the evaluation succeeds, calc_eval should return 1. If the evaluation fails because expr is invalid, calc_eval should return 0.
*/
int calc_eval(struct Calc *calc, const char *expr, int *result){
	char splittedExpr[5][26] = {"-", "-", "-", "-", "-"};
	int i = 0, j = 0, pos = 0;

	for(i = 0; i <= strlen(expr); i++) {
		if(expr[i] == '\0' || expr[i] == ' ') {
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
		if(strcmp(splittedExpr[i], "-") == 0) null++;
	}


	// Operand
	if(is_operand(splittedExpr[0]) && (null == 4)) {
		puts("Operand");

		if(is_number(splittedExpr[0])) {
			*result = string_to_int(splittedExpr[0]);
			return *result;
		} 

		int value = hash_lookup(calc->table, splittedExpr[0]);

		if(value == NF){
			*result = FALSE;
			return FALSE;
		} 

		*result = value;
		return value;
	} 

	// operand op operand
	if(is_variable(splittedExpr[0]) && is_op(splittedExpr[1]) && is_operand(splittedExpr[2]) && (null == 2)) {
		puts("operand op operand");
	}


	// var = operand 
	if(is_variable(splittedExpr[0]) && is_equal(splittedExpr[1]) && is_operand(splittedExpr[2]) && (null == 2)) {
		puts("var = operand");
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

		hash_delete(calc->table, splittedExpr[0]);
		hash_insert(calc->table, splittedExpr[0], op2);
	}

	// var = operand op operand
	if(is_operand(splittedExpr[0]) && is_equal(splittedExpr[1]) 
		&& is_operand(splittedExpr[2]) && is_op(splittedExpr[3]) && is_operand(splittedExpr[4]) ) {
			puts("var = operand op operand");
	}

	return *result;
}

void calc_print(struct Calc *calc, const char * key, int val) {
	hash_insert(calc->table, key, val);
}

int main(int argc, char *argv[]) {
//	struct Calc *calc = calc_create();
	struct Calc *calc = calc_create();
	calc_print(calc, "a", 1);
	calc_print(calc, "b", 2);
	calc_print(calc, "c", 3);
	int a = hash_lookup(calc->table, "a");
	int b = hash_lookup(calc->table, "b");
	int c = hash_lookup(calc->table, "c");
	int result = 0;

	calc_eval(calc, "42", &result);
	printf("%d\n", result);
	calc_eval(calc, "hola = 41", &result);
	printf("%d\n", result);
	calc_eval(calc, "hola", &result);

	printf("%d\n", result);
	printf("%d %d %d\n", a, b, c);



}
