--TEST--
Function overrideing test for mktime()
--SKIPIF--
<?php
$required_func = array("timecop_freeze");
$required_version = '8.0';
include(__DIR__."/tests-skipcheck.inc.php");
--INI--
date.timezone=America/Los_Angeles
timecop.func_override=1
--FILE--
<?php
timecop_freeze(172840); // "1970-01-02T16:00:40-08:00"
var_dump(mktime(4));
var_dump(mktime(4,6));
var_dump(mktime(4,6,41));
var_dump(mktime(4,6,41,1));
var_dump(mktime(4,6,41,1,1));
var_dump(mktime(12,33,20,5,3,1976));
--EXPECT--
int(129640)
int(130000)
int(130001)
int(130001)
int(43601)
int(200000000)
