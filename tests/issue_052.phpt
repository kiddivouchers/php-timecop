--TEST--
Check timezone '+00:00' being allowed
--SKIPIF--
<?php
$required_func = array("timecop_freeze");
include(__DIR__."/tests-skipcheck.inc.php");
--INI--
date.timezone=America/Los_Angeles
timecop.func_override=1
--FILE--
<?php
$dt1 = new \DateTime('@0', new \DateTimeZone('+00:00'));
var_dump($dt1->format("Y-m-d H:i:s.uP"));

timecop_freeze(0);
$dt2 = new \DateTime('@0', new \DateTimeZone('+00:00'));
var_dump($dt2->format("Y-m-d H:i:s.uP"));
--EXPECT--
string(32) "1970-01-01 00:00:00.000000+00:00"
string(32) "1970-01-01 00:00:00.000000+00:00"
