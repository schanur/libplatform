#ifndef PLATFORM_ASSERTION_H
#define PLATFORM_ASSERTION_H

/**
 * The purpose of this module is that it can be much simpler to
 * retrieve a correct stacktrace if the application is just crashing
 * instead of getting terminated by std default assert macro. If
 * ASSERT__CRASH_ON_ASSERTION_FAIL is defined. Crash the application
 * in case the test expression evaluates to false.
 */

#include <stdlib.h> /* abort() */

#include <assert.h>

/**
 * If RUNTIME_ASSERT__CRASH_ON_ASSERTION_FAIL is defined, we crash the
 * application. It is replaces by the usual "assert" macro otherwise.
 */
/* #define ASSERT_RT__CRASH_ON_ASSERTION_FAIL */

/* #define ASSERT_RT__CRASH_COMMAND(expr) (void) 1 / 0 */
/* #define ASSERT_RT__CRASH_COMMAND(expr) abort(); assert(expr) */
/* #define ASSERT_RT__CRASH_COMMAND(expr) fprintf(stderr, #expr); (void) (1 / 0); abort(); assert(expr) */
/* #define ASSERT_RT__CRASH_COMMAND(expr) fprintf(stderr, #expr); abort(); assert(0) */
#define ASSERT_RT__CRASH_COMMAND(expr) assert(expr)

#define FAIL_RT__CRASH_COMMAND abort(); assert(0)


#ifndef ASSERT_RT
  #ifndef NDEBUG
    #ifdef ASSERT_RT__CRASH_ON_ASSERTION_FAIL
      /* #include <cstdlib> */
      #define ASSERT_RT(expr) if (!(expr)) { ASSERT_RT__CRASH_COMMAND(expr); }
    #else
      #define ASSERT_RT(expr) assert(expr)
    #endif
  #else
    #define ASSERT_RT(expr) /* Assert macro ignored. */
  #endif
#else
  #error RUNTIME_ASSERT already defined
#endif

#ifndef FAIL_RT
  #define FAIL_RT FAIL_RT__CRASH_COMMAND
#else
  #error FAIL_RT already defined
#endif

#endif /* PLATFORM_ASSERTION_H */
