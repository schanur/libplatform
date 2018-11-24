#include "../shared_c/test.h"

#include "platform/lang.h"

/* #include "platform/inttypes_wrapper.h" */

static void test__at_least_one_language_defined()
{
    mu_assert(PLTF_LANG != 0);
}

static void test__cast_type_to_char()
{
    char a;
    int  b = 257;

    a = PLTF_LANG_TYPE_CAST(char, b);
    mu_assert(a == 1);
}


int main(void)
{
    test__at_least_one_language_defined();
    test__cast_type_to_char();

    return mu_test_status;
}
