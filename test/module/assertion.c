#include "../shared_c/test.h"

#include "platform/assertion.h"


static void test__assert_wrapper__runtime_assertion_can_pass()
{
    ASSERT_RT(1);
}

static void test__assert_wrapper__compile_time_assertion_can_pass()
{
    ASSERT_CT(1);
}


int main(void)
{
    test__assert_wrapper__runtime_assertion_can_pass();
    test__assert_wrapper__compile_time_assertion_can_pass();

    return 0;
}
