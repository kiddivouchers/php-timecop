--TEST--
Test for timecop_scale (invalid arguments)
--SKIPIF--
<?php
$required_func = array("timecop_scale");
$required_version = '7.0';
include(__DIR__."/tests-skipcheck.inc.php");
--INI--
date.timezone=America/Los_Angeles
timecop.func_override=0
--FILE--
<?php
declare(strict_types=1);

foreach (['', (object) [], '1234', 4.5, true, -10] as $input) {
    try {
        var_dump(timecop_scale($input));
    } catch (TypeError $e) {
        echo $e->getMessage(), "\n";
    }
}
--EXPECT--
timecop_scale(): Argument #1 ($scale) must be of type int, string given
timecop_scale(): Argument #1 ($scale) must be of type int, stdClass given
timecop_scale(): Argument #1 ($scale) must be of type int, string given
timecop_scale(): Argument #1 ($scale) must be of type int, float given
timecop_scale(): Argument #1 ($scale) must be of type int, bool given
bool(false)
