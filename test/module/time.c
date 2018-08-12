#include "../shared_c/test.h"

#include "platform/time.h"


static void test__time__SLEEP_SEC()
{
    SLEEP_SEC(1);
}


#ifdef _SOURCE_POSIX
static void test__time__SLEEP_MSEC()
{
    SLEEP_MSEC(1);

}

static void test__time__SLEEP_USEC()
{
    SLEEP_USEC(1);
}


static void test__time__SLEEP_NSEC()
{
    SLEEP_NSEC(1);
}


static void test__time__SLEEP_MSEC_CHECK()
{
    int     err;
    int64_t remaining;
    int64_t time = 1;
    SLEEP_MSEC(1);
}

static void test__time__SLEEP_USEC_CHECK()
{
    int     err;
    int64_t remaining;
    int64_t time = 1;
    SLEEP_USEC(1);
}

static void test__time__SLEEP_NSEC_CHECK()
{
    int     err;
    int64_t remaining;
    int64_t time = 1;
    SLEEP_NSEC(1);
}

#endif


int main(void)
{
    test__time__SLEEP_SEC();

#ifdef _SOURCE_POSIX
    test__time__SLEEP_MSEC();
    test__time__SLEEP_USEC();
    test__time__SLEEP_NSEC();

    test__time__SLEEP_MSEC_CHECK();
    test__time__SLEEP_USEC_CHECK();
    test__time__SLEEP_NSEC_CHECK();
#endif

    return 0;
}
