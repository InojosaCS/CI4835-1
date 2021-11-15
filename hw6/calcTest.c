#include <stdio.h>
#include <stdlib.h>
#include "tctest.h"

#include "calc.h"

typedef struct {
	struct Calc *calc;
} TestObjs;

TestObjs *setup(void) {
	TestObjs *objs = malloc(sizeof(TestObjs));
	objs->calc = calc_create();
	return objs;
}

void cleanup(TestObjs *objs) {
	calc_destroy(objs->calc);
	free(objs);
}

void testEvalLiteral(TestObjs *objs);
void testAssignment(TestObjs *objs);
void testComputation(TestObjs *objs);
void testComputationAndAssignment(TestObjs *objs);
void testUpdate(TestObjs *objs);
void testInvalidExpr(TestObjs *objs);

int main(void) {
	TEST_INIT();

	TEST(testEvalLiteral);
	TEST(testAssignment);
	TEST(testComputation);
	TEST(testComputationAndAssignment);
	TEST(testUpdate);
	TEST(testInvalidExpr);

	TEST_FINI();
}

void testEvalLiteral(TestObjs *objs) {
	int result;

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "42", &result));
	ASSERT(42 == result);
}

void testAssignment(TestObjs *objs) {
	int result;

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "a = 4", &result));
	ASSERT(4 == result);

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "a", &result));
	ASSERT(4 == result);

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "b = a", &result));
	ASSERT(4 == result);
}

void testComputation(TestObjs *objs) {
	int result;

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "33 + 15", &result));
	ASSERT(48 == result);

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "33 - 15", &result));
	ASSERT(18 == result);

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "33 * 15", &result));
	ASSERT(495 == result);

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "33 / 15", &result));
	ASSERT(2 == result);
}

void testComputationAndAssignment(TestObjs *objs) {
	int result;

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "a = 33 + 15", &result));
	ASSERT(48 == result);
	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "a", &result));
	ASSERT(48 == result);

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "b = 33 - 15", &result));
	ASSERT(18 == result);
	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "b", &result));
	ASSERT(18 == result);

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "c = 33 * 15", &result));
	ASSERT(495 == result);
	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "c", &result));
	ASSERT(495 == result);

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "d = 33 / 15", &result));
	ASSERT(2 == result);
	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "d", &result));
	ASSERT(2 == result);
}

void testUpdate(TestObjs *objs) {
	int result;

	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "a = 2", &result));
	ASSERT(2 == result);
	result = 0;
	ASSERT(0 != calc_eval(objs->calc, "a = a + 1", &result));
	ASSERT(3 == result);
}

void testInvalidExpr(TestObjs *objs) {
	int result;

	/* bad syntax */
	ASSERT(0 == calc_eval(objs->calc, "+ 4", &result));
	/* bad syntax */
	ASSERT(0 == calc_eval(objs->calc, "4 +", &result));
	/* undefined variable */
	ASSERT(0 == calc_eval(objs->calc, "a", &result));
	/* attempt to divide by 0 */
	ASSERT(0 == calc_eval(objs->calc, "4 / 0", &result));
}
