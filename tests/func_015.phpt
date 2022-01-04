--TEST--
Test for timecop_travel (invalid arguments)
--SKIPIF--
<?php
$required_func = array("timecop_travel");
$required_version = '7.0';
include(__DIR__."/tests-skipcheck.inc.php");
--INI--
date.timezone=America/Los_Angeles
timecop.func_override=0
--FILE--
<?php
declare(strict_types=1);

foreach (['', (object) [], '1234', 4.5, true] as $input) {
    try {
        var_dump(timecop_travel($input));
    } catch (TypeError $e) {
        echo $e->getMessage(), "\n";
    }
}
--EXPECT--
timecop_travel(): Argument #1 ($timestamp) must be of type DateTimeInterface|int, string given
timecop_travel(): Argument #1 ($timestamp) must be of type DateTimeInterface|int, stdClass given
timecop_travel(): Argument #1 ($timestamp) must be of type DateTimeInterface|int, string given
timecop_travel(): Argument #1 ($timestamp) must be of type DateTimeInterface|int, float given
timecop_travel(): Argument #1 ($timestamp) must be of type DateTimeInterface|int, bool given
