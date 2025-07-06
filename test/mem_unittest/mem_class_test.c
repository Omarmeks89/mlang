#include <check.h>

#include "../../mem/mem_class.h"

START_TEST(test_valid_class_1)
{
    int exp_size = 64;
    int res = get_obj_memclass_size((size_t) 59);

    ck_assert_int_eq(res, exp_size);
}
END_TEST

START_TEST(test_valid_class_2)
{
    int exp_size = 3264;
    int res = get_obj_memclass_size((size_t) 3059);

    ck_assert_int_eq(res, exp_size);
}
END_TEST

START_TEST(test_valid_class_3)
{
    int exp_size = 8;
    int res = get_obj_memclass_size((size_t) 5);

    ck_assert_int_eq(res, exp_size);
}
END_TEST

START_TEST(test_valid_class_4)
{
    int exp_size = 16320;
    int res = get_obj_memclass_size((size_t) 15315);

    ck_assert_int_eq(res, exp_size);
}
END_TEST

START_TEST(test_max_class_not_bigobj)
{
    int exp_size = 16320;
    int res = get_obj_memclass_size((size_t) 16320);

    ck_assert_int_eq(res, exp_size);
}
END_TEST

START_TEST(test_invalid_class_null_size)
{
    /* expected NULSIZE if we set 0 as object size */
    int exp_size = -2;
    int res = get_obj_memclass_size((size_t) 0);

    ck_assert_int_eq(res, exp_size);
}
END_TEST

START_TEST(test_class_marked_as_bigobj_1)
{
    /* expected NULSIZE if we set 0 as object size */
    int exp_size = -1;
    int res = get_obj_memclass_size((size_t) 100500);

    ck_assert_int_eq(res, exp_size);
}

START_TEST(test_class_marked_as_bigobj_2)
{
    /* expected NULSIZE if we set 0 as object size */
    int exp_size = -1;
    int res = get_obj_memclass_size((size_t) 16321);

    ck_assert_int_eq(res, exp_size);
}

/* === runners === */
SRunner * create_runner()
{
    SRunner *sr = NULL;
    Suite   *s  = NULL;
    TCase   *tc = NULL;

    s = suite_create("test_mem_classifier");

    tc = tcase_create("mem classifier tests");

    tcase_add_test(tc, test_valid_class_1);
    tcase_add_test(tc, test_valid_class_2);
    tcase_add_test(tc, test_valid_class_3);
    tcase_add_test(tc, test_valid_class_4);
    tcase_add_test(tc, test_max_class_not_bigobj);

    tcase_add_test(tc, test_invalid_class_null_size);
    tcase_add_test(tc, test_class_marked_as_bigobj_1);
    tcase_add_test(tc, test_class_marked_as_bigobj_2);

    suite_add_tcase(s, tc);
    sr = srunner_create(s);

    return sr;
}

int main(void)
{
    int fq = 0;

    SRunner * sr = create_runner();
    srunner_run_all(sr, CK_VERBOSE);

    fq = srunner_ntests_failed(sr);
    return (fq == 0) ? 0 : 1;
}
