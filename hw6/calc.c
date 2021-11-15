#include "parser.h"

typedef struct Calc {
	char * key;
	int val;
	struct Calc * next;
} node_t;

void pl(struct Calc * head) {
    node_t * current = head;

	puts("****");
	
    while (current != NULL) {
        printf("%d %s\n", current->val, current->key);
        current = current->next;
    }
	
	free(current);
	puts("****");
	return;
}


int change_value(node_t * head, char * look, int new_val) {
	node_t * current = head;
	
	while(current != NULL) {
		if(strcmp(current->key, look) == 0) {
			current->val = new_val;
			free(current);
			return TRUE;
		}
		current = current->next;
	}

	free(current);
	return FAIL;
}

int get_value(node_t * head, char * look) {
	if(is_number(look)) return string_to_int(look);

    node_t * current = head;

    while (current != NULL) {
		printf("%s %s comparando\n", current->key, look);
		if (strcmp(current->key, look) == 0) {
			printf("%s y %s son iguales, %d encontrado\n", look, current->key, current->val);
			free(current);
			return current->val;
		}
		current = current->next;
    }

	printf("%s no esta\n", look);
	free(current);
	return FAIL;
}
// The calc_create function creates an instance of the struct Calc data type and returns a pointer to it.
struct Calc *calc_create(void) {
	struct Calc *calc = (struct Calc *)malloc(sizeof(struct Calc));
	
	calc = (node_t *) malloc(sizeof(node_t));
	calc->key = "messi";
	calc->val = 10;
	calc->next = NULL;

	return calc;
}

// The calc_destroy function destroys an instance of the struct Calc data type, by deallocating its memory.
void calc_destroy(struct Calc **calc) {
}

/*
The calc_eval function evaluates an expression stored as a C character string in expr, saving the result of evaluating the expression in the variable pointed to by result. If the evaluation succeeds, calc_eval should return 1. If the evaluation fails because expr is invalid, calc_eval should return 0.
*/
int calc_eval(struct Calc *calc, const char *expr, int *result){
	printf("\nCASO %s\n", expr);
	char splittedExpr[4][26];
	int i = 0;
	int j = 0;
	int pos = 0;

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

	for(i = 0; i < 4; i++) {
		if(strcmp(splittedExpr[i], "") == 0) {
			null++;
		}
	}

	// Operand
	if(is_operand(splittedExpr[0]) && (null == 3)) {
		int value = get_value(calc, splittedExpr[0]);
		if(value == FAIL){
			*result = FALSE;
			return FALSE;
		} 
		*result = value;
		return value;
	} 

	// operand op operand
	if(is_operand(splittedExpr[0]) && is_equal(splittedExpr[1]) && is_operand(splittedExpr[2]) && (null == 1)) {
		int value = get_value(calc, splittedExpr[2]);
		printf("existe el valor de %d\n", value);
		if(value == FAIL) {
			return *result = FALSE;
		}

		int exists = get_value(calc, splittedExpr[0]);

		printf("%s vale %d\n", splittedExpr[0], exists);
		if(exists == FAIL){
			node_t * current = calc;
			printf("%p\n", current->next);
			while (current->next != NULL) {
				printf("%s %d TTTT\n", current->key, current->val);
				current = current->next;
			}

			/* now we can add a new variable */
			current->next = (node_t *) malloc(sizeof(node_t));
			current->next->val = value;
			current->next->key = splittedExpr[0];
			printf("wtf %s %d\n", current->next->key, current->next->val);
			current->next->next = NULL;
			printf("%p\n", current->next);
		} 
		
		else change_value(calc, splittedExpr[0], value);
	}

	*result = 5;
	return *result;
}

int main(int argc, char *argv[]) {
	struct Calc **calc = calc_create();

	int result = 0;
	calc_eval(&calc, "hello = 10", &result);
	pl(&calc);
	calc_eval(&calc, "hell = 20", &result);
	calc_eval(&calc, "hel = 30", &result);
	pl(calc);
	printf("%d\n", result);
	
}
