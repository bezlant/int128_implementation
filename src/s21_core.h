#include "s21_decimal.h"

#ifndef S21_DECIMAL_CORE_H
#define S21_DECIMAL_CORE_H

#include <math.h>

// checks if a bit is set
#define IS_SET(X, POS) ((X >> POS) & 1U)
// sets the bit to 1 at a give position
#define ADD_BIT(X, POS) (X |= (1U << POS))
// sets multiple bits at poisition by the givev bit value
#define SET_BIT(X, BIT, POS) (X |= (BIT << POS))
// bit becomes 0
#define ZERO_BIT(X, POS) (X &= (0U << POS))

typedef enum {
    D_START_EXP = 16,  // Beginning of the Exponent Bits
    D_END_EXP = 23,    // End of the Exponent Bits
    D_MAX_EXP_VAL = 28,
    D_SIGN = 31,  // Sign Bits
} s21_decimal_const;

typedef enum {
    ARITHMETIC_OK = 0,
    S21_INFINITY = 1,
    S21_NEGATIVE_INFINITY = 2,
    S21_NAN = 3
} arithmetic_result;

typedef struct {
    unsigned int bits[4];
} s21_decimal;

typedef enum {
    FALSE = 0,
    TRUE = 1,
} comparison_result;

typedef enum {
    CONVERTATION_OK = 0,
    CONVERTATION_ERROR = 1
} convertation_result;

void init_decimal(s21_decimal *decimal);
// returns 0 meaning positive 1 negative
bool get_sign(s21_decimal decimal);
void set_sign(s21_decimal *decimal);
int get_exponent(s21_decimal decimal);
void set_exponent(s21_decimal *decimal, int new_exponent);
s21_decimal add(s21_decimal a, s21_decimal b);
s21_decimal add_integers(s21_decimal a, s21_decimal b);
s21_decimal add_floats(s21_decimal a, s21_decimal b);
s21_decimal add_floats(s21_decimal a, s21_decimal b);
s21_decimal sum_right(s21_decimal a, s21_decimal b);
s21_decimal sum_left(s21_decimal a, s21_decimal b);
int check_overflow(s21_decimal val, int exponent);

#endif  // S21_DECIMAL_CORE_H
