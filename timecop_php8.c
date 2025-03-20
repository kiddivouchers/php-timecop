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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "php_timecop.h"

#ifdef ZFS
#include "TSRM.h"
#endif

ZEND_DECLARE_MODULE_GLOBALS(timecop)

static void timecop_globals_ctor(zend_timecop_globals *globals) {
	/* Initialize your global struct */
	globals->func_override = 1;
	globals->sync_request_time = 1;
	ZVAL_NULL(&globals->orig_request_time);
	globals->timecop_mode = TIMECOP_MODE_REALTIME;
	globals->freezed_time.sec = 0;
	globals->freezed_time.usec = 0;
	globals->travel_origin.sec = 0;
	globals->travel_origin.usec = 0;
	globals->travel_offset.sec = 0;
	globals->travel_offset.usec = 0;
	globals->scaling_factor = 1;
	globals->ce_DateTimeZone = NULL;
	globals->ce_DateTimeInterface = NULL;
	globals->ce_DateTime = NULL;
	globals->ce_TimecopDateTime = NULL;
	globals->ce_DateTimeImmutable = NULL;
	globals->ce_TimecopDateTimeImmutable = NULL;
}

static const struct timecop_override_func_entry timecop_override_func_table[] = {
	TIMECOP_OFE("time"),
	TIMECOP_OFE("mktime"),
	TIMECOP_OFE("gmmktime"),
	TIMECOP_OFE("date"),
	TIMECOP_OFE("gmdate"),
	TIMECOP_OFE("idate"),
	TIMECOP_OFE("getdate"),
	TIMECOP_OFE("localtime"),
	TIMECOP_OFE("strtotime"),
	TIMECOP_OFE("strftime"),
	TIMECOP_OFE("gmstrftime"),
#ifdef HAVE_GETTIMEOFDAY
	TIMECOP_OFE("microtime"),
	TIMECOP_OFE("gettimeofday"),
#endif
	TIMECOP_OFE("unixtojd"),
	TIMECOP_OFE("date_create"),
	TIMECOP_OFE("date_create_from_format"),
	TIMECOP_OFE("date_create_immutable"),
	TIMECOP_OFE("date_create_immutable_from_format"),
	{NULL, NULL, NULL}
};

static const struct timecop_override_class_entry timecop_override_class_table[] = {
	TIMECOP_OCE("datetime", "__construct"),
	TIMECOP_OCE("datetime", "createfromformat"),
	TIMECOP_OCE("datetimeimmutable", "__construct"),
	TIMECOP_OCE("datetimeimmutable", "createfromformat"),
	{NULL, NULL, NULL, NULL}
};

#include "timecop_php8_arginfo.h"

/* {{{ timecop_functions[] */
const zend_function_entry timecop_functions[] = {
	PHP_FE(timecop_freeze, arginfo_timecop_freeze)
	PHP_FE(timecop_travel, arginfo_timecop_travel)
	PHP_FE(timecop_scale, arginfo_timecop_scale)
	PHP_FE(timecop_return, arginfo_timecop_return)
	PHP_FE(timecop_time, arginfo_timecop_time)
	PHP_FE(timecop_mktime, arginfo_timecop_mktime)
	PHP_FE(timecop_gmmktime, arginfo_timecop_gmmktime)
	PHP_FE(timecop_date, arginfo_timecop_date)
	PHP_FE(timecop_gmdate, arginfo_timecop_gmdate)
	PHP_FE(timecop_idate, arginfo_timecop_idate)
	PHP_FE(timecop_getdate, arginfo_timecop_getdate)
	PHP_FE(timecop_localtime, arginfo_timecop_localtime)
	PHP_FE(timecop_strtotime, arginfo_timecop_strtotime)
#if PHP_VERSION_ID >= 80400
	ZEND_RAW_FENTRY("timecop_strftime", zif_timecop_strftime, arginfo_timecop_strftime, ZEND_ACC_DEPRECATED, NULL, NULL)
	ZEND_RAW_FENTRY("timecop_gmstrftime", zif_timecop_gmstrftime, arginfo_timecop_gmstrftime, ZEND_ACC_DEPRECATED, NULL, NULL)
#elif PHP_VERSION_ID >= 80100
	PHP_DEP_FE(timecop_strftime, arginfo_timecop_strftime)
	PHP_DEP_FE(timecop_gmstrftime, arginfo_timecop_gmstrftime)
#else
	PHP_FE(timecop_strftime, arginfo_timecop_strftime)
	PHP_FE(timecop_gmstrftime, arginfo_timecop_gmstrftime)
#endif
#ifdef HAVE_GETTIMEOFDAY
	PHP_FE(timecop_microtime, arginfo_timecop_microtime)
	PHP_FE(timecop_gettimeofday, arginfo_timecop_gettimeofday)
#endif
	PHP_FE(timecop_unixtojd, arginfo_timecop_unixtojd)
	PHP_FE(timecop_date_create, arginfo_timecop_date_create)
	PHP_FE(timecop_date_create_from_format, arginfo_timecop_date_create_from_format)
	PHP_FE(timecop_date_create_immutable, arginfo_timecop_date_create_immutable)
	PHP_FE(timecop_date_create_immutable_from_format, arginfo_timecop_date_create_immutable_from_format)
	{NULL, NULL, NULL}
};
/* }}} */

/* declare method parameters, */

/* each method can have its own parameters and visibility */
static zend_function_entry timecop_funcs_timecop[] = {
	PHP_ME_MAPPING(freeze, timecop_freeze, arginfo_timecop_travel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(travel, timecop_travel, arginfo_timecop_travel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(scale,  timecop_scale,  arginfo_timecop_scale,  ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(return, timecop_return, arginfo_timecop_return, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};

static zend_function_entry timecop_funcs_date[] = {
	PHP_ME(TimecopDateTime, __construct, arginfo_class_TimecopDateTime___construct,
		   ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(createFromFormat, timecop_date_create_from_format, arginfo_class_TimecopDateTime_createFromFormat,
				   ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};

static zend_function_entry timecop_funcs_orig_date[] = {
	PHP_ME(TimecopOrigDateTime, __construct, arginfo_class_TimecopDateTime___construct,
		   ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

static zend_function_entry timecop_funcs_immutable[] = {
	PHP_ME(TimecopDateTimeImmutable, __construct, arginfo_class_TimecopDateTimeImmutable___construct,
		   ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(createFromFormat, timecop_date_create_immutable_from_format, arginfo_class_TimecopDateTimeImmutable_createFromFormat,
				   ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};

static zend_function_entry timecop_funcs_orig_immutable[] = {
	PHP_ME(TimecopOrigDateTimeImmutable, __construct, arginfo_class_TimecopDateTimeImmutable___construct,
		   ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

#define MKTIME_NUM_ARGS 6

#define TIMECOP_CALL_FUNCTION(func_name, index_to_fill_timestamp) \
	_timecop_call_function(INTERNAL_FUNCTION_PARAM_PASSTHRU, ORIG_FUNC_NAME(func_name), index_to_fill_timestamp);

#define TIMECOP_CALL_MKTIME(mktime_func_name, date_func_name) \
	_timecop_call_mktime(INTERNAL_FUNCTION_PARAM_PASSTHRU, ORIG_FUNC_NAME(mktime_func_name), ORIG_FUNC_NAME(date_func_name));

static void timecop_globals_ctor(zend_timecop_globals *globals);

static int register_timecop_classes();
static int timecop_func_override();
static int timecop_class_override();
static int timecop_func_override_clear();
static int timecop_class_override_clear();

static int update_request_time(zend_long unixtime);
static int restore_request_time();

static int fill_mktime_params(zval *fill_params, const char *date_function_name, int from);
static int get_formatted_mock_time(zval *time, zval *timezone_obj, zval *retval_time, zval *retval_timezone);
static long get_mock_fraction(zval *time, zval *timezone_obj);

static void _timecop_call_function(INTERNAL_FUNCTION_PARAMETERS, const char *function_name, int index_to_fill_timestamp);
static void _timecop_call_mktime(INTERNAL_FUNCTION_PARAMETERS, const char *mktime_function_name, const char *date_function_name);

static int get_mock_timeval(tc_timeval *fixed, const tc_timeval *now);
static inline zend_long mock_timestamp();

static int get_timeval_from_datetime(tc_timeval *tp, zval *dt);
static int get_current_time(tc_timeval *now);

static void _timecop_orig_datetime_constructor(INTERNAL_FUNCTION_PARAMETERS, int immutable);
static inline void _timecop_date_create(INTERNAL_FUNCTION_PARAMETERS, int immutable);
static inline void _timecop_datetime_constructor(INTERNAL_FUNCTION_PARAMETERS, int immutable);
static void _timecop_datetime_constructor_ex(INTERNAL_FUNCTION_PARAMETERS, zval *obj, int immutable);

static inline zval* _call_php_method_with_0_params(zval *object_pp, zend_class_entry *obj_ce, const char *method_name, zval *retval_ptr);
static inline zval* _call_php_method_with_1_params(zval *object_pp, zend_class_entry *obj_ce, const char *method_name, zval *retval_ptr, zval *arg1);
static inline zval* _call_php_method_with_2_params(zval *object_pp, zend_class_entry *obj_ce, const char *method_name, zval *retval_ptr, zval *arg1, zval *arg2);
static inline zval* _call_php_method(zval *object_pp, zend_class_entry *obj_ce, const char *method_name, zval *retval_ptr, int param_count, zval* arg1, zval* arg2);
static void _call_php_function_with_3_params(const char *function_name, zval *retval_ptr, zval *arg1, zval *arg2, zval *arg3);
static inline void _call_php_function_with_params(const char *function_name, zval *retval_ptr, uint32_t param_count, zval params[]);

static const zend_module_dep timecop_module_deps[] = {
	ZEND_MOD_REQUIRED("Date")
    ZEND_MOD_END
};

/* {{{ timecop_module_entry
 */
zend_module_entry timecop_module_entry = {
    STANDARD_MODULE_HEADER_EX,
    NULL,
    timecop_module_deps,
	"timecop",
	timecop_functions,
	PHP_MINIT(timecop),
	PHP_MSHUTDOWN(timecop),
	PHP_RINIT(timecop),
	PHP_RSHUTDOWN(timecop),
	PHP_MINFO(timecop),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_TIMECOP_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TIMECOP
#  ifdef ZTS
   ZEND_TSRMLS_CACHE_DEFINE();
#  endif
ZEND_GET_MODULE(timecop)
#endif

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("timecop.func_override", "1",
    PHP_INI_SYSTEM, OnUpdateLong, func_override, zend_timecop_globals, timecop_globals)
    STD_PHP_INI_ENTRY("timecop.sync_request_time", "1",
    PHP_INI_SYSTEM, OnUpdateLong, sync_request_time, zend_timecop_globals, timecop_globals)
PHP_INI_END()
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(timecop)
{
	ZEND_INIT_MODULE_GLOBALS(timecop, timecop_globals_ctor, NULL);
	REGISTER_INI_ENTRIES();
	register_timecop_classes();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(timecop)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION(timecop) */
PHP_RINIT_FUNCTION(timecop)
{
#if defined(COMPILE_DL_TIMECOP) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	if (TIMECOP_G(func_override)) {
		if (SUCCESS != timecop_func_override() ||
			SUCCESS != timecop_class_override()) {
			return FAILURE;
		}
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION(timecop) */
PHP_RSHUTDOWN_FUNCTION(timecop)
{
	if (TIMECOP_G(func_override)) {
		timecop_func_override_clear();
		timecop_class_override_clear();
	}

	if (Z_TYPE(TIMECOP_G(orig_request_time)) != IS_NULL) {
		restore_request_time();
	}

	TIMECOP_G(timecop_mode) = TIMECOP_MODE_REALTIME;
	TIMECOP_G(scaling_factor) = 1;

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(timecop)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "timecop", "enabled");
	php_info_print_table_row(2, "Version", PHP_TIMECOP_VERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

static int register_timecop_classes()
{
	zend_class_entry ce;
	zend_class_entry *tmp, *date_ce, *timezone_ce, *immutable_ce, *interface_ce;

	date_ce = zend_hash_str_find_ptr(CG(class_table), "datetime", sizeof("datetime")-1);
	if (date_ce == NULL) {
		/* DateTime must be initialized before */
		php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
						 "timecop couldn't find class %s.", "DateTime");
		return SUCCESS;
	}

	timezone_ce = zend_hash_str_find_ptr(CG(class_table), "datetimezone", sizeof("datetimezone")-1);
	if (timezone_ce == NULL) {
		/* DateTime must be initialized before */
		php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
						 "timecop couldn't find class %s.", "DateTimeZone");
		return SUCCESS;
	}

	immutable_ce = zend_hash_str_find_ptr(CG(class_table), "datetimeimmutable", sizeof("datetimeimmutable")-1);
	if (immutable_ce == NULL) {
		/* DateTimeImmutable must be initialized before */
		php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
						 "timecop couldn't find class %s.", "DateTimeImmutable");
		return SUCCESS;
	}

	interface_ce = zend_hash_str_find_ptr(CG(class_table), "datetimeinterface", sizeof("datetimeinterface")-1);
	if (interface_ce == NULL) {
		/* DateTimeInterface must be initialized before */
		php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
						 "timecop couldn't find interface %s.", "DateTimeInterface");
		return SUCCESS;
	}

	INIT_CLASS_ENTRY(ce, "Timecop", timecop_funcs_timecop);
	zend_register_internal_class(&ce);

	TIMECOP_G(ce_DateTimeZone) = timezone_ce;
	TIMECOP_G(ce_DateTimeInterface) = interface_ce;

	/* replace DateTime */
	INIT_CLASS_ENTRY(ce, "TimecopDateTime", timecop_funcs_date);
	tmp = zend_register_internal_class_ex(&ce, date_ce);
	tmp->create_object = date_ce->create_object;

	TIMECOP_G(ce_DateTime) = date_ce;
	TIMECOP_G(ce_TimecopDateTime) = tmp;

	INIT_CLASS_ENTRY(ce, "TimecopOrigDateTime", timecop_funcs_orig_date);
	tmp = zend_register_internal_class_ex(&ce, date_ce);
	tmp->create_object = date_ce->create_object;

	/* replace DateTimeImmutable */
	INIT_CLASS_ENTRY(ce, "TimecopDateTimeImmutable", timecop_funcs_immutable);
	tmp = zend_register_internal_class_ex(&ce, immutable_ce);
	tmp->create_object = immutable_ce->create_object;

	TIMECOP_G(ce_DateTimeImmutable) = immutable_ce;
	TIMECOP_G(ce_TimecopDateTimeImmutable) = tmp;

	INIT_CLASS_ENTRY(ce, "TimecopOrigDateTimeImmutable", timecop_funcs_orig_immutable);
	tmp = zend_register_internal_class_ex(&ce, immutable_ce);
	tmp->create_object = immutable_ce->create_object;

	return SUCCESS;
}

static int timecop_func_override()
{
	const struct timecop_override_func_entry *p;
	zend_function *zf_orig, *zf_ovrd, *zf_save;

	p = &(timecop_override_func_table[0]);
	while (p->orig_func != NULL) {
		zf_orig = zend_hash_str_find_ptr(CG(function_table), p->orig_func, strlen(p->orig_func));
		if (zf_orig == NULL) {
			/* Do nothing. Because some functions are introduced by optional extensions. */
			p++;
			continue;
		}

		zf_ovrd = zend_hash_str_find_ptr(CG(function_table), p->ovrd_func, strlen(p->ovrd_func));
		if (zf_ovrd == NULL) {
			php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
							 "timecop couldn't find function %s.", p->ovrd_func);
			p++;
			continue;
		}

		zf_save = zend_hash_str_find_ptr(CG(function_table), p->save_func, strlen(p->save_func));
		if (zf_save != NULL) {
			php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
							 "timecop couldn't create function %s because already exists.",
							 p->save_func);
			p++;
			continue;
		}

		TIMECOP_ASSERT(zf_orig->type == ZEND_INTERNAL_FUNCTION);
		TIMECOP_ASSERT(zf_ovrd->type == ZEND_INTERNAL_FUNCTION);

		zend_hash_str_add_mem(CG(function_table), p->save_func, strlen(p->save_func),
							  zf_orig, sizeof(zend_function));
		function_add_ref(zf_orig);

		FIX_FUNCTION_ARG_INFO_DTOR(zf_orig);
		zend_hash_str_update_mem(CG(function_table), p->orig_func, strlen(p->orig_func),
								 zf_ovrd, sizeof(zend_function));
		function_add_ref(zf_ovrd);

		p++;
	}
	return SUCCESS;
}

static int timecop_class_override()
{
	const struct timecop_override_class_entry *p;
	zend_class_entry *ce_orig, *ce_ovrd;
	zend_function *zf_orig, *zf_ovrd, *zf_save, *zf_new;

	p = &(timecop_override_class_table[0]);
	while (p->orig_class != NULL) {
		ce_orig = zend_hash_str_find_ptr(CG(class_table), p->orig_class, strlen(p->orig_class));
		if (ce_orig == NULL) {
			php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
							 "timecop couldn't find class %s.", p->orig_class);
			p++;
			continue;
		}

		ce_ovrd = zend_hash_str_find_ptr(CG(class_table), p->ovrd_class, strlen(p->ovrd_class));
		if (ce_ovrd == NULL) {
			php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
							 "timecop couldn't find class %s.", p->ovrd_class);
			p++;
			continue;
		}

		zf_orig = zend_hash_str_find_ptr(&ce_orig->function_table,
										 p->orig_method, strlen(p->orig_method));
		if (zf_orig == NULL) {
			php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
							 "timecop couldn't find method %s::%s.",
							 p->orig_class, p->orig_method);
			p++;
			continue;
		}

		zf_ovrd = zend_hash_str_find_ptr(&ce_ovrd->function_table,
										 p->orig_method, strlen(p->orig_method));
		if (zf_ovrd == NULL) {
			php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
							 "timecop couldn't find method %s::%s.",
							 p->ovrd_class, p->orig_method);
			p++;
			continue;
		}

		zf_save = zend_hash_str_find_ptr(&ce_orig->function_table,
										 p->save_method, strlen(p->save_method));
		if (zf_save != NULL) {
			php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
							 "timecop couldn't create method %s::%s because already exists.",
							 p->orig_class, p->save_method);
			p++;
			continue;
		}

		TIMECOP_ASSERT(zf_orig->type == ZEND_INTERNAL_FUNCTION);
		TIMECOP_ASSERT(ce_orig->type & ZEND_INTERNAL_CLASS);
		TIMECOP_ASSERT(zf_ovrd->type == ZEND_INTERNAL_FUNCTION);
		TIMECOP_ASSERT(ce_ovrd->type & ZEND_INTERNAL_CLASS);

		zend_hash_str_add_mem(&ce_orig->function_table,
							  p->save_method, strlen(p->save_method),
							  zf_orig, sizeof(zend_function));
		function_add_ref(zf_orig);

		zf_new = zend_hash_str_update_mem(&ce_orig->function_table,
										  p->orig_method, strlen(p->orig_method),
										  zf_ovrd, sizeof(zend_function));
		function_add_ref(zf_ovrd);

		TIMECOP_ASSERT(zf_new != NULL);
		TIMECOP_ASSERT(zf_new != zf_orig);

		if (strcmp(p->orig_method, "__construct") == 0) {
			ce_orig->constructor = zf_new;
		}
		p++;
	}
	return SUCCESS;
}

/*  clear function overriding. */
static int timecop_func_override_clear()
{
	const struct timecop_override_func_entry *p;
	zend_function *zf_orig, *zf_ovld;

	p = &(timecop_override_func_table[0]);
	while (p->orig_func != NULL) {
		zf_orig = zend_hash_str_find_ptr(CG(function_table),
										 p->save_func, strlen(p->save_func));
		zf_ovld = zend_hash_str_find_ptr(CG(function_table),
										 p->orig_func, strlen(p->orig_func));
		if (zf_orig == NULL || zf_ovld == NULL) {
			p++;
			continue;
		}

		FIX_FUNCTION_ARG_INFO_DTOR(zf_ovld);
		zend_hash_str_update_mem(CG(function_table), p->orig_func, strlen(p->orig_func),
								 zf_orig, sizeof(zend_function));
		function_add_ref(zf_orig);

		FIX_FUNCTION_ARG_INFO_DTOR(zf_orig);
		zend_hash_str_del(CG(function_table), p->save_func, strlen(p->save_func));

		p++;
	}
	return SUCCESS;
}

static int timecop_class_override_clear()
{
	const struct timecop_override_class_entry *p;
	zend_class_entry *ce_orig;
	zend_function *zf_orig;

	p = &(timecop_override_class_table[0]);
	while (p->orig_class != NULL) {
		ce_orig = zend_hash_str_find_ptr(CG(class_table),
										 p->orig_class, strlen(p->orig_class));
		if (ce_orig == NULL) {
			php_error_docref("https://github.com/hnw/php-timecop", E_WARNING,
							 "timecop couldn't find class %s.", p->orig_class);
			p++;
			continue;
		}

		zf_orig = zend_hash_str_find_ptr(&ce_orig->function_table,
										 p->save_method, strlen(p->save_method));
		if (zf_orig == NULL) {
			php_error_docref("https://github.com/
