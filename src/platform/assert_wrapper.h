#ifndef PLATFORM_ASSERT_WRAPPER_H
#define PLATFORM_ASSERT_WRAPPER_H

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
#define RUNTIME_ASSERT__CRASH_ON_ASSERTION_FAIL

/* #define RUNTIME_ASSERT__CRASH_COMMAND(expr) (void) 1 / 0 */
/* #define RUNTIME_ASSERT__CRASH_COMMAND(expr) abort(); assert(expr) */
/* #define RUNTIME_ASSERT__CRASH_COMMAND(expr) fprintf(stderr, #expr); (void) (1 / 0); abort(); assert(expr) */
/* #define RUNTIME_ASSERT__CRASH_COMMAND(expr) fprintf(stderr, #expr); abort(); assert(0) */
#define RUNTIME_ASSERT__CRASH_COMMAND(expr) assert(expr)

#define RUNTIME_FAIL__CRASH_COMMAND abort(); assert(0)


#ifndef RUNTIME_ASSERT
  #ifndef NDEBUG
    #ifdef RUNTIME_ASSERT__CRASH_ON_ASSERTION_FAIL
      /* #include <cstdlib> */
      #define RUNTIME_ASSERT(expr) if (!(expr)) { RUNTIME_ASSERT__CRASH_COMMAND(expr); }
    #else
      #define RUNTIME_ASSERT(expr) assert(expr)
    #endif
  #else
    #define RUNTIME_ASSERT(expr) /* Assert macro ignored. */
  #endif
#else
  #error RUNTIME_ASSERT already defined
#endif

#ifndef RUNTIME_FAIL
  #define RUNTIME_FAIL RUNTIME_FAIL__CRASH_COMMAND
#else
  #error RUNTIME_FAIL already defined
#endif

#endif /* PLATFORM_ASSERT_WRAPPER_H */
