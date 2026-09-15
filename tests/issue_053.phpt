--TEST--
Check opcache preloading does not crash #53 (https://github.com/kiddivouchers/php-timecop/issues/53)
--SKIPIF--
<?php
$required_version = "8.0";
include(__DIR__."/tests-skipcheck.inc.php");
extension_loaded('Zend OPcache') or die('skip Zend OPcache module not available');
--INI--
date.timezone=GMT
opcache.enable_cli=on
opcache.preload=tests/preload.php
timecop.func_override=1
--FILE--
<?php

var_dump(opcache_get_status()['opcache_enabled']);
var_dump(extension_loaded('timecop'));
var_dump(class_exists('Timecop'));
var_dump((new \ReflectionClass('Timecop'))->isUserDefined());
\Timecop::return();
--EXPECT--
Warning: PHP Startup: Timecop function overrides disabled when opcache is preloaded. in Unknown on line 0
bool(true)
bool(true)
bool(true)
bool(false)
