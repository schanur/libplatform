#include "../shared_c/test.h"

#include "platform/time.h"


static void test__byte_order__SLEEP_SEC()
{
    SLEEP_SEC(1);
}

static void test__byte_order__SLEEP_MSEC()
{
    SLEEP_MSEC(1);
}

int main(void)
{
    test__byte_order__SLEEP_SEC();
    test__byte_order__SLEEP_MSEC();

    return 0;
}
