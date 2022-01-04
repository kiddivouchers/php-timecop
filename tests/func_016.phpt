--TEST--
Test for timecop_freeze (invalid arguments)
--SKIPIF--
<?php
$required_func = array("timecop_freeze");
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
        var_dump(timecop_freeze($input));
    } catch (TypeError $e) {
        echo $e->getMessage(), "\n";
    }
}
--EXPECTREGEX--
timecop_freeze\(\): Argument #1 \(\$timestamp\) must be of type DateTimeInterface|int, (N\/A|string) given
timecop_freeze\(\): Argument #1 \(\$timestamp\) must be of type DateTimeInterface|int, (N\/A|stdClass) given
timecop_freeze\(\): Argument #1 \(\$timestamp\) must be of type DateTimeInterface|int, (N\/A|string) given
timecop_freeze\(\): Argument #1 \(\$timestamp\) must be of type DateTimeInterface|int, (N\/A|float) given
timecop_freeze\(\): Argument #1 \(\$timestamp\) must be of type DateTimeInterface|int, (N\/A|bool) given
