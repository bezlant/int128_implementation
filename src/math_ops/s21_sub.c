#include "../s21_decimal.h"
#include "../tests/s21_decimal_test.h"
#include <stdio.h>

static void handle_exponent_sub(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result, int *code);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int code = ARITHMETIC_OK;

    int s1 = get_sign(value_1), s2 = get_sign(value_2);

    if (s1 == POS && s2 == POS) {
        if (s21_is_greater(value_1, value_2)) {
            handle_exponent_sub(value_1, value_2, result, &code);
        } else {
            handle_exponent_sub(value_2, value_1, result, &code);
            set_sign_neg(result);
        }
    } else if (s1 == POS && s2 == NEG) {
        set_sign_pos(&value_2);
        code = s21_add(value_1, value_2, result);
    } else if (s1 == NEG && s2 == POS) {
        set_sign_pos(&value_1);
        code = s21_add(value_1, value_2, result);
        set_sign_neg(result);
    } else if (s1 == NEG && s2 == NEG) {
        set_sign_pos(&value_2);
        code = s21_add(value_1, value_2, result);
    }

    code = s21_check_infinity(code, get_sign(*result));

//     // At this point decimals have equal exponent,
//     // because it was normalized by s21_normalize_exponent
    if (code && get_exponent(value_1) && get_exponent(value_2)) {
        code = 0;
        static int iter = 1;
        printf("\nNEG: [%d]\n", iter);
        printf("\n CODE: [%d]\n", code);
        printf("S1: \t%d S2\t%d\n", s1, s2);
        iter++;

        // (!) SIGNS ARE DEFINITELY LOST /* BUG: Signs are lost when doing converttation */

#define DEBUG
#ifdef DEBUG
        printf(RED "\tBank rounding (SUB) \n" ENDCOLOR);
        float a1, a2, b1, b2;

        s21_from_decimal_to_float(value_1, &a1);
        s21_from_decimal_to_float(value_2, &b1);

        printf(GRN "EXP: %d Before round:  %f \n" ENDCOLOR, get_exponent(value_1), a1);
        printf(GRN "EXP: %d Before round:  %f \n" ENDCOLOR, get_exponent(value_2), b1);
#endif

        s21_bank_rounding(&value_1, 1);
        s21_bank_rounding(&value_2, 1);

#ifdef DEBUG
        s21_from_decimal_to_float(value_1, &a2);
        s21_from_decimal_to_float(value_2, &b2);
        printf(GRN "EXP: %d After round:  %f \n" ENDCOLOR, get_exponent(value_1), a2);
        printf(GRN "EXP: %d After round:  %f \n" ENDCOLOR, get_exponent(value_2), b2);
#endif


        code = s21_sub(value_1, value_2, result);
        code = ARITHMETIC_OK;
    }

    return code;
}

static void handle_exponent_sub(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result, int *code) {
    int exp_v1 = get_exponent(value_1);
    int exp_v2 = get_exponent(value_2);

    int res_exp = min(exp_v1, exp_v2);

    s21_decimal value_2_origin = value_2;

    s21_normalize_decimal_pair(&value_1, &value_2, code);

    if (*code == S21_INFINITY) {
        printf(REDB "CAN'T NORMALIZE!\n" ENDCOLOR);
        /* Bank rounding happens when we fail to normalize compounds */
        if (s21_is_greater_or_equal(value_1, get_05())) {
            /* -1 */
            *result = binary_subtraction(value_2, get_power_of_ten(0), code);
        } else {
            /* -0 - leave as it was */
            *result = value_2_origin;
            *code = 0;
        }
    } else {
        *result = binary_subtraction(value_1, value_2, code);
    }

    set_exponent(result, res_exp);
}
