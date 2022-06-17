#ifndef SRC_BINARY_API_S21_CORE_H_
#define SRC_BINARY_API_S21_CORE_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;

// checks if a bit is set
#define IS_SET(X, POS) ((X >> POS) & 1U)
// sets the bit to 1 at a give position
#define ADD_BIT(X, POS) ((X) |= (1U << (POS)))
// sets multiple bits at poisition by the givev bit value
#define SET_BIT(X, BIT, POS) (X |= (BIT << POS))
// bit becomes 0 P.S. ALL INT NUMBER BECOMES 0 !
#define INIT_ZERO(X) (X &= (0U << 32))
// real zero_bit
#define ZERO_BIT(X, POS) (X &= ~(1UL << POS));

/* BUG #77 I'm pretty sure these values are wrong. Double check this */
#define MAX_DECIMAL 7.92281625143e+28
#define MIN_DECIMAL -7.92281625143e+28

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

typedef enum {
    POS = 0,
    NEG = 1
} arithmetic_consts;

typedef enum {
    FALSE = 0,
    TRUE = 1,
} comparison_result;

typedef enum {
    CONVERTATION_OK = 0,
    CONVERTATION_ERROR = 1
} convertation_result;

/* returns 0 meaning positive 1 negative */
bool get_sign(s21_decimal decimal);
void set_sign_neg(s21_decimal *decimal);
void set_sign_pos(s21_decimal *decimal);
void set_sign(s21_decimal *decimal, int sign);

/* exponent handling */
int get_exponent(s21_decimal decimal);
void set_exponent(s21_decimal *decimal, int new_exponent);

/* bit setters */
void set_bit_1(s21_decimal *n, int pos);
void set_bit_0(s21_decimal *n, int pos);
int get_bit(s21_decimal n, int pos);

void s21_normalize_decimal_pair(s21_decimal *a, s21_decimal *b, int *overflow);

/* binary operations */
s21_decimal bit_and(s21_decimal a, s21_decimal b);
s21_decimal bit_or(s21_decimal a, s21_decimal b);
s21_decimal bit_xor(s21_decimal a, s21_decimal b);
s21_decimal bit_not(s21_decimal a);

s21_decimal binary_addition(s21_decimal value_1, s21_decimal value_2, int *err);
s21_decimal binary_subtraction(s21_decimal value_1, s21_decimal value_2,
                               int *err);
s21_decimal binary_multiplication(s21_decimal value_1, s21_decimal value_2,
                                  int *err);
s21_decimal binary_division(s21_decimal value_1, s21_decimal value_2,
                            int *code);

void shiftnr(s21_decimal *a, int n);
void shiftr(s21_decimal *a);
int shiftnl(s21_decimal *a, int n);
s21_decimal shiftnl_ret(s21_decimal a, int n);
s21_decimal shiftnr_ret(s21_decimal a, int n);
int shiftl(s21_decimal *a);

int eq_zero(s21_decimal value);
int byte_len(s21_decimal n);
s21_decimal get_0(void);
s21_decimal get_05(void);
int max(int a, int b);
int min(int a, int b);
void s21_swap(s21_decimal *a, s21_decimal *b);
s21_decimal get_power_of_ten(int pow);
uint32_t reverse_bits(uint32_t n);

int s21_integer_div_wrapper(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);

bool both_all_zeroes(s21_decimal a, s21_decimal b);

/* Abs comparison */

int s21_is_less_abs(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal_abs(s21_decimal a, s21_decimal b);
int s21_is_greater_abs(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal_abs(s21_decimal a, s21_decimal b);
int s21_is_equal_abs(s21_decimal a, s21_decimal b);
int s21_is_not_equal_abs(s21_decimal a, s21_decimal b);

int s21_check_infinity(int code, int sign);

float add_exponent(float val, int exp);

int s21_integer_div_wrapper(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);

static const char *const binary_powers_of_ten[29] = {
    [0] =
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
    [1] =
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001010",
    [2] =
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001100100",
    [3] =
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111101000",
    [4] =
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000010011100010000",
    [5] =
        "000000000000000000000000000000000000000000000000000000000000000000000000000000011000011010100000",
    [6] =
        "000000000000000000000000000000000000000000000000000000000000000000000000000011110100001001000000",
    [7] =
        "000000000000000000000000000000000000000000000000000000000000000000000000100110001001011010000000",
    [8] =
        "000000000000000000000000000000000000000000000000000000000000000000000101111101011110000100000000",
    [9] =
        "000000000000000000000000000000000000000000000000000000000000000000111011100110101100101000000000",
    [10] =
        "000000000000000000000000000000000000000000000000000000000000001001010100000010111110010000000000",
    [11] =
        "000000000000000000000000000000000000000000000000000000000001011101001000011101101110100000000000",
    [12] =
        "000000000000000000000000000000000000000000000000000000001110100011010100101001010001000000000000",
    [13] =
        "000000000000000000000000000000000000000000000000000010010001100001001110011100101010000000000000",
    [14] =
        "000000000000000000000000000000000000000000000000010110101111001100010000011110100100000000000000",
    [15] =
        "000000000000000000000000000000000000000000000011100011010111111010100100110001101000000000000000",
    [16] =
        "000000000000000000000000000000000000000000100011100001101111001001101111110000010000000000000000",
    [17] =
        "000000000000000000000000000000000000000101100011010001010111100001011101100010100000000000000000",
    [18] =
        "000000000000000000000000000000000000110111100000101101101011001110100111011001000000000000000000",
    [19] =
        "000000000000000000000000000000001000101011000111001000110000010010001001111010000000000000000000",
    [20] =
        "000000000000000000000000000001010110101111000111010111100010110101100011000100000000000000000000",
    [21] =
        "000000000000000000000000001101100011010111001001101011011100010111011110101000000000000000000000",
    [22] =
        "000000000000000000000010000111100001100111100000110010011011101010110010010000000000000000000000",
    [23] =
        "000000000000000000010101001011010000001011000111111000010100101011110110100000000000000000000000",
    [24] =
        "000000000000000011010011110000100001101111001110110011001110110110100001000000000000000000000000",
    [25] =
        "000000000000100001000101100101010001011000010100000000010100100001001010000000000000000000000000",
    [26] =
        "000000000101001010110111110100101101110011001000000011001101001011100100000000000000000000000000",
    [27] =
        "000000110011101100101110001111001001111111010000100000000011110011101000000000000000000000000000",
    [28] =
        "001000000100111111001110010111100011111000100101000000100110000100010000000000000000000000000000",
};

#endif  // SRC_BINARY_API_S21_CORE_H_
