/*
MIT License

Copyright (c) 2012-2017 Yoshio HANAWA
Copyright (c) 2019-2024 Wider Plan Ltd
Copyright (c) 2024 Sylvain Filteau

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#ifndef PHP_TIMECOP_H
#define PHP_TIMECOP_H

#define PHP_TIMECOP_VERSION "1.7.0"

extern zend_module_entry timecop_module_entry;
#define phpext_timecop_ptr &timecop_module_entry

#ifdef PHP_WIN32
#	define PHP_TIMECOP_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_TIMECOP_API __attribute__ ((visibility("default")))
#else
#	define PHP_TIMECOP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#ifndef PHP_WIN32
#include <time.h>
#else
#include "win32/time.h"
#endif

#include "Zend/zend_interfaces.h"
#include "tc_timeval.h"

PHP_MINIT_FUNCTION(timecop);
PHP_MSHUTDOWN_FUNCTION(timecop);
PHP_RINIT_FUNCTION(timecop);
PHP_RSHUTDOWN_FUNCTION(timecop);
PHP_MINFO_FUNCTION(timecop);

PHP_FUNCTION(timecop_freeze);
PHP_FUNCTION(timecop_travel);
PHP_FUNCTION(timecop_scale);
PHP_FUNCTION(timecop_return);
PHP_FUNCTION(timecop_time);
PHP_FUNCTION(timecop_mktime);
PHP_FUNCTION(timecop_gmmktime);
PHP_FUNCTION(timecop_date);
PHP_FUNCTION(timecop_gmdate);
PHP_FUNCTION(timecop_idate);
PHP_FUNCTION(timecop_getdate);
PHP_FUNCTION(timecop_localtime);
PHP_FUNCTION(timecop_strtotime);
PHP_FUNCTION(timecop_strftime);
PHP_FUNCTION(timecop_gmstrftime);
#ifdef HAVE_GETTIMEOFDAY
PHP_FUNCTION(timecop_microtime);
PHP_FUNCTION(timecop_gettimeofday);
#endif
PHP_FUNCTION(timecop_unixtojd);
PHP_FUNCTION(timecop_date_create);
PHP_FUNCTION(timecop_date_create_from_format);
PHP_FUNCTION(timecop_date_create_immutable);
PHP_FUNCTION(timecop_date_create_immutable_from_format);

PHP_METHOD(TimecopDateTime, __construct);
PHP_METHOD(TimecopOrigDateTime, __construct);
PHP_METHOD(TimecopDateTimeImmutable, __construct);
PHP_METHOD(TimecopOrigDateTimeImmutable, __construct);

PHP_METHOD(Timecop, freeze);
PHP_METHOD(Timecop, travel);

typedef enum timecop_mode_t {
	TIMECOP_MODE_REALTIME,
	TIMECOP_MODE_FREEZE,
	TIMECOP_MODE_TRAVEL
} timecop_mode_t;

ZEND_BEGIN_MODULE_GLOBALS(timecop)
	long func_override;
	long sync_request_time;
	zval orig_request_time;
	timecop_mode_t timecop_mode;
	tc_timeval freezed_time;
	tc_timeval travel_origin;
	tc_timeval travel_offset;
	zend_long scaling_factor;
	zend_class_entry *ce_DateTimeZone;
	zend_class_entry *ce_DateTimeInterface;
	zend_class_entry *ce_DateTime;
	zend_class_entry *ce_TimecopDateTime;
	zend_class_entry *ce_DateTimeImmutable;
	zend_class_entry *ce_TimecopDateTimeImmutable;
ZEND_END_MODULE_GLOBALS(timecop)

#if ZEND_DEBUG
#  define TIMECOP_ASSERT(c) assert(c)
#else
#  define TIMECOP_ASSERT(c)
#endif /* ZEND_DEBUG */

#define SAVE_FUNC_PREFIX "timecop_orig_"
#define OVRD_FUNC_PREFIX "timecop_"

#define OVRD_CLASS_PREFIX "timecop"

#define ORIG_FUNC_NAME(fname) \
	(TIMECOP_G(func_override) ? (SAVE_FUNC_PREFIX fname) : fname)

#define TIMECOP_OFE(fname) {fname, OVRD_FUNC_PREFIX fname, SAVE_FUNC_PREFIX fname}
#define TIMECOP_OCE(cname, mname) \
	{cname, mname, OVRD_CLASS_PREFIX cname, SAVE_FUNC_PREFIX mname}

/*
 * Trick for guarding the multi-referenced internal function from function destructor on PHP 7.2.0+
 * See: https://github.com/hnw/php-timecop/issues/29#issuecomment-332171527
 */
#if PHP_VERSION_ID >= 70200
#  define FIX_FUNCTION_ARG_INFO_DTOR(zend_func) zend_func->common.arg_info = NULL;
#else
#  define FIX_FUNCTION_ARG_INFO_DTOR(zend_func)
#endif

struct timecop_override_func_entry {
	char *orig_func;
	char *ovrd_func;
	char *save_func;
};

struct timecop_override_class_entry {
	char *orig_class;
	char *orig_method;
	char *ovrd_class;
	char *save_method;
};

#define call_php_method_with_0_params(obj, ce, method_name, retval) \
	_call_php_method_with_0_params(obj, ce, method_name, retval TSRMLS_CC)

#define call_php_method_with_1_params(obj, ce, method_name, retval, arg1)	\
	_call_php_method_with_1_params(obj, ce, method_name, retval, arg1 TSRMLS_CC)

#define call_php_method_with_2_params(obj, ce, method_name, retval, arg1, arg2) \
	_call_php_method_with_2_params(obj, ce, method_name, retval, arg1, arg2 TSRMLS_CC)

#define call_php_function_with_0_params(function_name, retval) \
	_call_php_method_with_0_params(NULL, NULL, function_name, retval TSRMLS_CC)

#define call_php_function_with_1_params(function_name, retval, arg1) \
	_call_php_method_with_1_params(NULL, NULL, function_name, retval, arg1 TSRMLS_CC)

#define call_php_function_with_2_params(function_name, retval, arg1, arg2) \
	_call_php_method_with_2_params(NULL, NULL, function_name, retval, arg1, arg2 TSRMLS_CC)

#define call_php_function_with_3_params(function_name, retval, arg1, arg2, arg3) \
	_call_php_function_with_3_params(function_name, retval, arg1, arg2, arg3 TSRMLS_CC)

/* In every utility function you add that needs to use variables
   in php_timecop_globals, call TSRMLS_FETCH(); after declaring other
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as TIMECOP_G(variable).  You are
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

/* Redeclare macros as no-ops which were removed in PHP 8. */
#if PHP_VERSION_ID >= 80000
#define TSRMLS_D void
#define TSRMLS_DC
#define TSRMLS_C
#define TSRMLS_CC
#define TSRMLS_FETCH()
#endif

#define TIMECOP_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(timecop, v)
#if defined(ZTS) && defined(COMPILE_DL_TIMECOP)
   ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif	/* PHP_TIMECOP_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
