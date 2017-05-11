#ifndef MU_TEST_FRAMEWORK
#define MU_TEST_FRAMEWORK

#include <stdio.h>

#define mu_assert(condition)                                            \
    do {                                                                \
        if (!(condition)) {                                             \
            mu_test_status = 1;                                         \
            fprintf(stderr,                                             \
                    "Test assertion failed:\n"                          \
                    "  Condition: %s\n"                                 \
                    "  File:      %s\n"                                 \
                    "  Function:  %s\n"                                 \
                    "  Line:      %i\n",                                \
                    #condition, __FILE__, __func__, __LINE__);          \
        }                                                               \
    } while (0)

volatile static int mu_test_status = 0;

#endif /* MU_TEST_FRAMEWORK */
