--TEST--
Test for timecop_gmmktime()
--SKIPIF--
<?php
$required_func = array("timecop_freeze", "timecop_gmmktime");
$required_version = '8.0';
include(__DIR__."/tests-skipcheck.inc.php");
--INI--
date.timezone=America/Los_Angeles
timecop.func_override=0
--FILE--
<?php
timecop_freeze(86440); // "1970-01-02T00:00:40+00:00"
var_dump(timecop_gmmktime(12));
var_dump(timecop_gmmktime(12,6));
var_dump(timecop_gmmktime(12,6,41));
var_dump(timecop_gmmktime(12,6,41,1));
var_dump(timecop_gmmktime(12,6,41,1,1));
var_dump(timecop_gmmktime(19,33,20,5,3,1976));
--EXPECT--
int(129640)
int(130000)
int(130001)
int(130001)
int(43601)
int(200000000)
