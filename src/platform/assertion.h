#ifndef PLATFORM_ASSERTION_H
#define PLATFORM_ASSERTION_H

/**********************************************************************/
/*                        Run time assertions                         */
/**********************************************************************/

#include <stdlib.h> /* abort() */

#include <assert.h>

/**
 * If ASSERT__CRASH_ON_ASSERTION_FAIL is defined, crash the
 * application in case the test expression evaluates to false.  The
 * purpose of RUNTIME_ASSERT__CRASH_ON_ASSERTION_FAIL is that it can
 * be much simpler to retrieve a correct stacktrace if the application
 * is just crashing instead of getting terminated by std default
 * assert macro.
 */
/* #define ASSERT_RT__CRASH_ON_ASSERTION_FAIL */

/* Crash method by which the application is halted. */
#define ASSERT_RT__CRASH_METHOD_DIV_BY_ZERO
/* #define ASSERT_RT__CRASH_METHOD_ABORT */

#ifdef ASSERT_RT__CRASH_METHOD_DIV_BY_ZERO
  #define ASSERT_RT__CRASH_COMMAND(expr) (void) 1 / 0
#endif
#ifdef ASSERT_RT__CRASH_METHOD_ABORT
  #define ASSERT_RT__CRASH_COMMAND(expr) abort(); assert(expr) /* assert is a backup just in case abort does not work as expected. */
#endif

/* #define ASSERT_RT__CRASH_COMMAND(expr) fprintf(stderr, #expr); (void) (1 / 0); abort(); assert(expr) */
/* #define ASSERT_RT__CRASH_COMMAND(expr) fprintf(stderr, #expr); abort(); assert(0) */

#define FAIL_RT__CRASH_COMMAND abort(); assert(0)


#ifndef ASSERT_RT
  #ifndef NDEBUG
    #ifdef ASSERT_RT__CRASH_ON_ASSERTION_FAIL
      /* #include <cstdlib> */
      #define ASSERT_RT(expr) if (!(expr)) { ASSERT_RT__CRASH_COMMAND(expr); }
    #else
      #define ASSERT_RT(expr) assert(expr)
    #endif /* #ifdef ASSERT_RT__CRASH_ON_ASSERTION_FAIL */
  #else
    #define ASSERT_RT(expr) /* Assert macro ignored in release build. */
  #endif/* #ifndef NDEBUG */
#else
  #error RUNTIME_ASSERT already defined
#endif /* #ifndef ASSERT_RT */

#ifndef FAIL_RT
  #define FAIL_RT FAIL_RT__CRASH_COMMAND
#else
  #error FAIL_RT already defined
#endif /* #ifndef FAIL_RT */


/**********************************************************************/
/*                      Compile time assertions                       */
/**********************************************************************/

#ifdef __STDC_VERSION__
  #if __STDC_VERSION__ >= 201112L
    #define PL_PRIVATE_C11_STATIC_ASSERT_AVAILABLE
  #endif /* #if __STDC_VERSION__ >= 201112L */

#endif /* #ifdef __STDC_VERSION__ */

#ifdef PL_PRIVATE_C11_STATIC_ASSERT_AVAILABLE
    #define ASSERT_CT(expr) static_assert(expr, "Assertion failed at compile time.")
#else
    #define ASSERT_CT(expr) switch(0) { case 0: case expr:; }
#endif /* #ifdef PL_PRIVATE_C11_STATIC_ASSERT_AVAILABLE */


#endif /* PLATFORM_ASSERTION_H */
