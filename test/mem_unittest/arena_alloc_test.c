#include <check.h>

#include "../../mem/amalloc.h"

START_TEST(test_init_arena)
{
    memobj__arena arena = init_arena(0);

    ck_assert_ptr_nonnull(arena);

    /* arena have to be destroyed with macro to avoid uaf ptr */
    amalloc_destroy_arena(arena, DEFAULT_ARENA_SIZE);

    ck_assert_ptr_null(arena);
}
END_TEST

SRunner * create_runner()
{
    SRunner *sr = NULL;
    Suite   *s  = NULL;
    TCase   *tc = NULL;

    s = suite_create("test_init_mem_arena");

    tc = tcase_create("mem arena init test");

    tcase_add_test(tc, test_init_arena);

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
