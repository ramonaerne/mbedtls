/**
 * \file platform.h
 *
 * \brief This file contains the definitions and functions of the
 *        Mbed TLS platform abstraction layer.
 *
 *        The platform abstraction layer removes the need for the library
 *        to directly link to standard C library functions or operating
 *        system services, making the library easier to port and embed.
 *        Application developers and users of the library can provide their own
 *        implementations of these functions, or implementations specific to
 *        their platform, which can be statically linked to the library or
 *        dynamically configured at runtime.
 *
 *        When all compilation options related to platform abstraction are
 *        disabled, this header just defines `mbedtls_xxx` function names
 *        as aliases to the standard `xxx` function.
 *
 *        Most modules in the library and example programs are expected to
 *        include this header.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */
#ifndef MBEDTLS_PLATFORM_H
#define MBEDTLS_PLATFORM_H
#include "mbedtls/private_access.h"
#include "mbedtls/build_info.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name SECTION: Module settings
 *
 * The configuration options you can set for this module are in this section.
 * Either change them in mbedtls_config.h or define them on the compiler command line.
 * \{
 */

#include <stdio.h>
#include <stdlib.h>

#define MBEDTLS_PLATFORM_STD_SNPRINTF   snprintf /**< The default \c snprintf function to use.  */
#define MBEDTLS_PLATFORM_STD_VSNPRINTF   vsnprintf /**< The default \c vsnprintf function to use.  */
#define MBEDTLS_PLATFORM_STD_PRINTF   printf /**< The default \c printf function to use. */
#define MBEDTLS_PLATFORM_STD_FPRINTF fprintf /**< The default \c fprintf function to use. */
#define MBEDTLS_PLATFORM_STD_CALLOC   calloc /**< The default \c calloc function to use. */
#define MBEDTLS_PLATFORM_STD_FREE       free /**< The default \c free function to use. */
#define MBEDTLS_PLATFORM_STD_SETBUF   setbuf /**< The default \c setbuf function to use. */
#define MBEDTLS_PLATFORM_STD_EXIT      exit /**< The default \c exit function to use. */
#define MBEDTLS_PLATFORM_STD_TIME       time    /**< The default \c time function to use. */
#define MBEDTLS_PLATFORM_STD_EXIT_SUCCESS  EXIT_SUCCESS /**< The default exit value to use. */
#define MBEDTLS_PLATFORM_STD_EXIT_FAILURE  EXIT_FAILURE /**< The default exit value to use. */

/** \} name SECTION: Module settings */

#undef mbedtls_free
#undef mbedtls_calloc
#define mbedtls_free       free
#define mbedtls_calloc     calloc
#define mbedtls_fprintf    fprintf
#undef mbedtls_printf
#define mbedtls_printf     printf
#undef mbedtls_snprintf
#define mbedtls_snprintf   MBEDTLS_PLATFORM_STD_SNPRINTF
#undef mbedtls_vsnprintf
#define mbedtls_vsnprintf   vsnprintf

#undef mbedtls_setbuf
#define mbedtls_setbuf    setbuf
#undef mbedtls_exit
#define mbedtls_exit   exit

/*
 * The default exit values
 */
#define MBEDTLS_EXIT_SUCCESS MBEDTLS_PLATFORM_STD_EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE MBEDTLS_PLATFORM_STD_EXIT_FAILURE

/**
 * \brief   The platform context structure.
 *
 * \note    This structure may be used to assist platform-specific
 *          setup or teardown operations.
 */
typedef struct mbedtls_platform_context {
    char MBEDTLS_PRIVATE(dummy); /**< A placeholder member, as empty structs are not portable. */
}
mbedtls_platform_context;

/**
 * \brief   This function performs any platform-specific initialization
 *          operations.
 *
 * \note    This function should be called before any other library functions.
 *
 *          Its implementation is platform-specific, and unless
 *          platform-specific code is provided, it does nothing.
 *
 * \note    The usage and necessity of this function is dependent on the platform.
 *
 * \param   ctx     The platform context.
 *
 * \return  \c 0 on success.
 */
int mbedtls_platform_setup(mbedtls_platform_context *ctx);
/**
 * \brief   This function performs any platform teardown operations.
 *
 * \note    This function should be called after every other Mbed TLS module
 *          has been correctly freed using the appropriate free function.
 *
 *          Its implementation is platform-specific, and unless
 *          platform-specific code is provided, it does nothing.
 *
 * \note    The usage and necessity of this function is dependent on the platform.
 *
 * \param   ctx     The platform context.
 *
 */
void mbedtls_platform_teardown(mbedtls_platform_context *ctx);

#ifdef __cplusplus
}
#endif

#endif /* platform.h */
