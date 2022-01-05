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

// Simplified version of:
// https://github.com/symfony/polyfill/blob/6db783b3a48077f7102b6d7be6314d871eb7898c/src/Php80/Php80.php#L28-L58
function var_type($value): string
{
    switch (true) {
        case null === $value: return 'null';
        case \is_bool($value): return 'bool';
        case \is_string($value): return 'string';
        case \is_array($value): return 'array';
        case \is_int($value): return 'int';
        case \is_float($value): return 'float';
        case \is_object($value): return \get_class($value);
    }

    return 'unknown';
}

foreach (['', (object) [], '1234', 4.5, true, new \DateTimeImmutable(), new \DateTime(), 64] as $input) {
    try {
        var_dump(timecop_travel($input));
    } catch (TypeError $e) {
        $message = $e->getMessage();

        // Workaround exception message not including type in PHP 7 so the same test can be used for both.
        if (PHP_MAJOR_VERSION === 7) {
            $message = str_replace('N/A given', var_type($input).' given', $message);
        }

        echo $message, "\n";
    }
}
--EXPECT--
timecop_travel(): Argument #1 ($timestamp) must be of type DateTimeInterface|int, string given
timecop_travel(): Argument #1 ($timestamp) must be of type DateTimeInterface|int, stdClass given
timecop_travel(): Argument #1 ($timestamp) must be of type DateTimeInterface|int, string given
timecop_travel(): Argument #1 ($timestamp) must be of type DateTimeInterface|int, float given
timecop_travel(): Argument #1 ($timestamp) must be of type DateTimeInterface|int, bool given
bool(true)
bool(true)
bool(true)
