/**
 * \file platform_util.h
 *
 * \brief Common and shared functions used by multiple modules in the Mbed TLS
 *        library.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */
#ifndef MBEDTLS_PLATFORM_UTIL_H
#define MBEDTLS_PLATFORM_UTIL_H

#include "mbedtls/build_info.h"

#include <stddef.h>
#if defined(MBEDTLS_HAVE_TIME_DATE)
#include "mbedtls/platform_time.h"
#include <time.h>
#endif /* MBEDTLS_HAVE_TIME_DATE */

#ifdef __cplusplus
extern "C" {
#endif

/* Internal helper macros for deprecating API constants. */
#define MBEDTLS_DEPRECATED
#define MBEDTLS_DEPRECATED_STRING_CONSTANT(VAL) VAL
#define MBEDTLS_DEPRECATED_NUMERIC_CONSTANT(VAL) VAL

/* Implementation of the check-return facility.
 * See the user documentation in mbedtls_config.h.
 *
 * Do not use this macro directly to annotate function: instead,
 * use one of MBEDTLS_CHECK_RETURN_CRITICAL or MBEDTLS_CHECK_RETURN_TYPICAL
 * depending on how important it is to check the return value.
 */
#if defined(__GNUC__)
#define MBEDTLS_CHECK_RETURN __attribute__((__warn_unused_result__))
#else
#define MBEDTLS_CHECK_RETURN
#endif

/** Critical-failure function
 *
 * This macro appearing at the beginning of the declaration of a function
 * indicates that its return value should be checked in all applications.
 * Omitting the check is very likely to indicate a bug in the application
 * and will result in a compile-time warning if #MBEDTLS_CHECK_RETURN
 * is implemented for the compiler in use.
 *
 * \note  The use of this macro is a work in progress.
 *        This macro may be added to more functions in the future.
 *        Such an extension is not considered an API break, provided that
 *        there are near-unavoidable circumstances under which the function
 *        can fail. For example, signature/MAC/AEAD verification functions,
 *        and functions that require a random generator, are considered
 *        return-check-critical.
 */
#define MBEDTLS_CHECK_RETURN_CRITICAL MBEDTLS_CHECK_RETURN

/** Ordinary-failure function
 *
 * This macro appearing at the beginning of the declaration of a function
 * indicates that its return value should be generally be checked in portable
 * applications. Omitting the check will result in a compile-time warning if
 * #MBEDTLS_CHECK_RETURN is implemented for the compiler in use and
 * #MBEDTLS_CHECK_RETURN_WARNING is enabled in the compile-time configuration.
 *
 * You can use #MBEDTLS_IGNORE_RETURN to explicitly ignore the return value
 * of a function that is annotated with #MBEDTLS_CHECK_RETURN.
 *
 * \note  The use of this macro is a work in progress.
 *        This macro will be added to more functions in the future.
 *        Eventually this should appear before most functions returning
 *        an error code (as \c int in the \c mbedtls_xxx API or
 *        as ::psa_status_t in the \c psa_xxx API).
 */
#define MBEDTLS_CHECK_RETURN_TYPICAL

/** Benign-failure function
 *
 * This macro appearing at the beginning of the declaration of a function
 * indicates that it is rarely useful to check its return value.
 *
 * This macro has an empty expansion. It exists for documentation purposes:
 * a #MBEDTLS_CHECK_RETURN_OPTIONAL annotation indicates that the function
 * has been analyzed for return-check usefulness, whereas the lack of
 * an annotation indicates that the function has not been analyzed and its
 * return-check usefulness is unknown.
 */
#define MBEDTLS_CHECK_RETURN_OPTIONAL

/** \def MBEDTLS_IGNORE_RETURN
 *
 * Call this macro with one argument, a function call, to suppress a warning
 * from #MBEDTLS_CHECK_RETURN due to that function call.
 */
#if !defined(MBEDTLS_IGNORE_RETURN)
/* GCC doesn't silence the warning with just (void)(result).
 * (void)!(result) is known to work up at least up to GCC 10, as well
 * as with Clang and MSVC.
 *
 * https://gcc.gnu.org/onlinedocs/gcc-3.4.6/gcc/Non_002dbugs.html
 * https://stackoverflow.com/questions/40576003/ignoring-warning-wunused-result
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66425#c34
 */
#define MBEDTLS_IGNORE_RETURN(result) ((void) !(result))
#endif

/* If the following macro is defined, the library is being built by the test
 * framework, and the framework is going to provide a replacement
 * mbedtls_platform_zeroize() using a preprocessor macro, so the function
 * declaration should be omitted.  */
#if !defined(MBEDTLS_TEST_DEFINES_ZEROIZE) //no-check-names
/**
 * \brief       Securely zeroize a buffer
 *
 *              The function is meant to wipe the data contained in a buffer so
 *              that it can no longer be recovered even if the program memory
 *              is later compromised. Call this function on sensitive data
 *              stored on the stack before returning from a function, and on
 *              sensitive data stored on the heap before freeing the heap
 *              object.
 *
 *              It is extremely difficult to guarantee that calls to
 *              mbedtls_platform_zeroize() are not removed by aggressive
 *              compiler optimizations in a portable way. For this reason, Mbed
 *              TLS provides the configuration option
 *              MBEDTLS_PLATFORM_ZEROIZE_ALT, which allows users to configure
 *              mbedtls_platform_zeroize() to use a suitable implementation for
 *              their platform and needs
 *
 * \param buf   Buffer to be zeroized
 * \param len   Length of the buffer in bytes
 *
 */
void mbedtls_platform_zeroize(void *buf, size_t len);
#endif

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_PLATFORM_UTIL_H */
