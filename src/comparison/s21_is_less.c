#include "../s21_decimal.h"

static bool s21_is_less_positive(s21_decimal a, s21_decimal b);

/*
    We assume that 1 (dec) is represented like this in s21_decimal:

    000001 000000 000000 000000
    (3) 0000 (uint)
    (2) 0000 (uint)
    (1) 0000 (uint)
    (0) 0001 (uint)

    Thus, we have the right to compare raw value of unsigned ints.
*/

int s21_is_less(s21_decimal a, s21_decimal b) {
    if (both_all_zeroes(a, b)) {
        return false;
    }

    bool sign1 = get_sign(a), sign2 = get_sign(b);

    /* POS < NEG */
    if (!sign1 && sign2) {
        return false;
    }

    /* NEG < NEG */
    if (sign1 && sign2) {
        set_sign_pos(&a);
        set_sign_pos(&b);
        return s21_is_greater(a, b);
    }

    /* NEG < POS */
    if (sign1 && !sign2) {
        return true;
    }

    int res = s21_is_less_positive(a, b);

    return res;
}

static bool s21_is_less_positive(s21_decimal a, s21_decimal b) {
    int overflow = 0;
    s21_normalize_decimal_pair(&a, &b, &overflow);

    if (overflow) {
        int e1 = get_exponent(a), e2 = get_exponent(b);
        return (e1 < e2);
    }

    for (int i = 2; i >= 0; i--) {
        if (a.bits[i] == b.bits[i]) {
            continue;
        } else {
            return a.bits[i] < b.bits[i];
        }
    }

    return false;
}
