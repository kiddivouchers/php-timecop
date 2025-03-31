/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 46f7105217d927814bac47071b66e9a47be202e8 */

#if PHP_VERSION_ID >= 80200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_timecop_freeze, 0, 1, IS_TRUE, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, timestamp, DateTimeInterface, MAY_BE_LONG, NULL)
ZEND_END_ARG_INFO()

#define arginfo_timecop_travel arginfo_timecop_freeze

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_timecop_scale, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_timecop_return, 0, 0, IS_TRUE, 0)
ZEND_END_ARG_INFO()
#endif

#if !(PHP_VERSION_ID >= 80200)
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_timecop_freeze, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, timestamp, DateTimeInterface, MAY_BE_LONG, NULL)
ZEND_END_ARG_INFO()

#define arginfo_timecop_travel arginfo_timecop_freeze

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_timecop_scale, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_timecop_return, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_timecop_time, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_timecop_mktime, 0, 1, MAY_BE_LONG|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, hour, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, minute, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, second, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, month, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, day, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, year, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_timecop_gmmktime arginfo_timecop_mktime

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_timecop_date, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, timestamp, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_timecop_gmdate arginfo_timecop_date

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_timecop_idate, 0, 1, MAY_BE_LONG|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, timestamp, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_timecop_localtime, 0, 0, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, timestamp, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, associative, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_timecop_strtotime, 0, 1, MAY_BE_LONG|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, datetime, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, baseTimestamp, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID < 80400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_timecop_strftime, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, timestamp, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_timecop_gmstrftime arginfo_timecop_strftime
#endif

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_timecop_microtime, 0, 0, MAY_BE_STRING|MAY_BE_DOUBLE)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, as_float, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_timecop_gettimeofday, 0, 0, MAY_BE_ARRAY|MAY_BE_DOUBLE)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, as_float, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_timecop_unixtojd, 0, 0, MAY_BE_LONG|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, timestamp, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_timecop_getdate, 0, 0, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, timestamp, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(arginfo_timecop_date_create, 0, 0, DateTime, MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, datetime, IS_STRING, 0, "\"now\"")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, timezone, DateTimeZone, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(arginfo_timecop_date_create_from_format, 0, 2, DateTime, MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, datetime, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, timezone, DateTimeZone, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(arginfo_timecop_date_create_immutable, 0, 0, DateTimeImmutable, MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, datetime, IS_STRING, 0, "\"now\"")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, timezone, DateTimeZone, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(arginfo_timecop_date_create_immutable_from_format, 0, 2, DateTimeImmutable, MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, datetime, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, timezone, DateTimeZone, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_TimecopDateTime___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, datetime, IS_STRING, 0, "\"now\"")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, timezone, DateTimeZone, 1, "null")
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 80100
ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_OBJ_TYPE_MASK_EX(arginfo_class_TimecopDateTime_createFromFormat, 0, 2, DateTime, MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, datetime, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, timezone, DateTimeZone, 1, "null")
ZEND_END_ARG_INFO()
#endif

#if !(PHP_VERSION_ID >= 80100)
ZEND_BEGIN_ARG_INFO_EX(arginfo_class_TimecopDateTime_createFromFormat, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, datetime, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, timezone, DateTimeZone, 1, "null")
ZEND_END_ARG_INFO()
#endif

#define arginfo_class_TimecopDateTimeImmutable___construct arginfo_class_TimecopDateTime___construct

#if PHP_VERSION_ID >= 80100
ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_OBJ_TYPE_MASK_EX(arginfo_class_TimecopDateTimeImmutable_createFromFormat, 0, 2, DateTimeImmutable, MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, datetime, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, timezone, DateTimeZone, 1, "null")
ZEND_END_ARG_INFO()
#endif

#if !(PHP_VERSION_ID >= 80100)
#define arginfo_class_TimecopDateTimeImmutable_createFromFormat arginfo_class_TimecopDateTime_createFromFormat
#endif

