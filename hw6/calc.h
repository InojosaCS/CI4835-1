#ifndef CALC_H
#define CALC_H

#include "parser.h"
/*
 * Note: you should NOT need to modify anything in this header file.
 */

/* Forward declaration of the struct Calc data type. */
struct Calc;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * You should implement these functions in calc.c or calc.cpp
 * (according to whether you are programming in C or C++.)
 * If you define them in C++, make sure they have extern "C"
 * linkage.
 */
struct Calc *calc_create(void);
void calc_destroy(struct Calc *calc);
int calc_eval(struct Calc *calc, const char *expr, int *result);

#ifdef __cplusplus
}
#endif

#endif /* CALC_H */
