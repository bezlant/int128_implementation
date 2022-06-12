#include "../s21_decimal_test.h"

/* START_TEST(loop_division_mpz) { */
/*     s21_decimal val = {0}; */
/*     s21_decimal divisor = {0}; */
/*     s21_decimal res = {0}; */

/*     mpz_t mpz_val; */
/*     mpz_init(mpz_val); */
/*     mpz_set_ui(mpz_val, 0); */

/*     mpz_t mpz_divisor; */
/*     mpz_init(mpz_divisor); */
/*     mpz_set_ui(mpz_divisor, 0); */

/*     mpz_t mpz_res; */
/*     mpz_init(mpz_res); */
/*     mpz_set_ui(mpz_res, 0); */

/*     get_random_pair(&val, &mpz_val, 1); */
/*     get_random_pair(&divisor, &mpz_divisor, 1); */

/* #define DEBUG */
/* #ifdef DEBUG */
/*     printf("val = "); */
/*     print_bits_r(val); */
/*     printf("divisor = "); */
/*     print_bits_r(divisor); */
/*     printf("mpz_val = "); */
/*     print_bits_r(convert_gmp_to_decimal(mpz_val)); */
/*     printf("mpz_divisor = "); */
/*     print_bits_r(convert_gmp_to_decimal(mpz_divisor)); */
/* #endif */

/* NOTE: GMP library works incorrectly or other functioned needed */
/* mpz_fdiv_q(mpz_res, mpz_val, mpz_divisor); */
/* s21_div(val, divisor, &res); */

/* #ifdef DEBUG */
/* puts("-------------RESULT----------------"); */
/* printf("mpz_res = "); */
/* print_bits_r(convert_gmp_to_decimal(mpz_res)); */
/* printf("res = "); */
/* print_bits_r(res); */
/* puts("-------------RESULT----------------"); */
/* #endif */

/* ck_assert_int_eq(s21_is_equal(res, convert_gmp_to_decimal(mpz_res)), TRUE);
 */

/* mpz_clear(mpz_val); */
/* mpz_clear(mpz_divisor); */
/* mpz_clear(mpz_res); */
/* } */
/* END_TEST */

/* START_TEST(div_test1) { */
/* // */
/* s21_decimal v1, v2, div; */

/* init_zero(&v1); */
/* init_zero(&v2); */
/* // for (int i = 0; i < 96; ++i) set_bit_1(&v1, i); */
/* // set_bit_0(&v1, 92); */
/* // set_bit_0(&v1, 93); */
/* // set_bit_0(&v1, 94); */
/* // set_bit_0(&v1, 95); */
/* for (int i = 0; i < 60; ++i) { */
/*     if (rand() % 2) */
/*         set_bit_1(&v1, i); */
/* } */
/* // for (int i = 0; i < 78; ++i) { */
/* // if (rand() % 2) set_bit_1(&v2, i); */
/* // } */

/* // set_bit_1(&v1, _i); */
/* // set_bit_1(&v2, _i); */
/* // s21_from_int_to_decimal(15, &v1); */
/* s21_from_int_to_decimal(1, &v2); */

/* set_exponent(&v1, 1); */
/* set_exponent(&v2, 12); */
/* int code = s21_div(v1, v2, &div); */

/* printf("\nNUMBERS:\n"); */
/* printf("EXP = %d ", get_exponent(v1)); */
/* print_bits_r(v1); */
/* printf("EXP = %d ", get_exponent(v2)); */
/* print_bits_r(v2); */
/* printf("EXP = %d ", get_exponent(div)); */
/* print_bits_r(div); */
/* printf("\n"); */

/* printf("ERR : %d\n", code); */
/* // ck_assert_int_eq(get_bit(div, 1), 1); */
/* // ck_assert_int_eq(1, 0); */
/* } */
/* END_TEST */

START_TEST(gcc_128_bits) {
    long long long_a = get_random_ll() * rand();
    long long long_b = get_random_ll() * rand();
    printf("long_a  =%lld\n", long_a);
    printf("long_b  =%lld\n", long_b);
    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t div = a / b;
    s21_decimal res128 = bigint_to_decimal(div);

    s21_decimal dec_a = ll_to_decimal(long_a);

    print_bits_r(dec_a);
    s21_decimal dec_b = ll_to_decimal(long_b);
    s21_decimal dec_div = {0};

    print_bits_r(dec_b);

    s21_div(dec_a, dec_b, &dec_div);

    printf("dec_div=");
    print_bits_r(dec_div);
    printf("res128_=");
    print_bits_r(res128);

    ck_assert_int_eq(s21_is_equal(res128, dec_div), TRUE);
}

START_TEST(divison_by_one) {
    s21_decimal a = {0};
    s21_decimal b = {0};

    a.bits[0] = get_rand(0, INT_MAX);
    a.bits[1] = get_rand(0, INT_MAX);
    a.bits[2] = get_rand(0, INT_MAX);

    set_bit_1(&b, 0);


    // print_bits_r(a);
    // print_bits_r(b);
    s21_decimal res = {0};
    int code = s21_div(a, b, &res);
    // print_bits_r(res);
    // printf("CODE : %d\n", code);

    ck_assert_int_eq(a.bits[0], res.bits[0]);
    ck_assert_int_eq(a.bits[1], res.bits[1]);
    ck_assert_int_eq(a.bits[2], res.bits[2]);
}
END_TEST

START_TEST(divison_by_two) {
    s21_decimal a = {0};
    s21_decimal b = {0};

    // set_bit_1(&a, 1);
    // set_bit_1(&a, 3);

    a.bits[0] = 10;
    b.bits[0] = 2;

    print_bits_r(a);
    print_bits_r(b);

    printf("A IS LESS B: %d \n", s21_is_less(a, b));
    printf("A IS GREATER B: %d \n", s21_is_greater(a, b));

    s21_decimal res = {0};
    int code = s21_div(a, b, &res);
    printf("CODE : %d\n", code);
    print_bits_r(res);
}
END_TEST


Suite *suite_s21_div(void) {
    Suite *s = suite_create("suite_s21_div");
    TCase *tc = tcase_create("s21_div_tc");

    /* tcase_add_loop_test(tc, div_test1, 0, 1); */
    /* tcase_add_loop_test(tc, loop_division_mpz, 0, 10000); */
    // tcase_add_loop_test(tc, gcc_128_bits, 0, 1);
    // tcase_add_loop_test(tc, divison_by_one, 0, 5);
    tcase_add_loop_test(tc, divison_by_two, 0, 1);

    suite_add_tcase(s, tc);
    return s;
}
