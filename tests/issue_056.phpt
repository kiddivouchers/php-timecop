--TEST--
Function overrides do not break extending built in objects #56 (https://github.com/kiddivouchers/php-timecop/issues/56)
--SKIPIF--
<?php
include(__DIR__."/tests-skipcheck.inc.php");
--INI--
date.timezone=GMT
timecop.func_override=1
--FILE--
<?php

final class MyImmutableDate extends \DateTimeImmutable
{
    public static function createFromFormat(string $format, string $datetime, ?\DateTimeZone $timezone = null): static
    {
        return parent::createFromFormat($format, $datetime, $timezone);
    }
}

final class MyMutableDate extends \DateTime
{
    public static function createFromFormat(string $format, string $datetime, ?\DateTimeZone $timezone = null): static
    {
        return parent::createFromFormat($format, $datetime, $timezone);
    }
}

var_dump(MyMutableDate::createFromFormat('!Y', '2020'));
var_dump(MyImmutableDate::createFromFormat('!Y', '2020'));
--EXPECT--
object(MyMutableDate)#1 (3) {
  ["date"]=>
  string(26) "2020-01-01 00:00:00.000000"
  ["timezone_type"]=>
  int(3)
  ["timezone"]=>
  string(3) "GMT"
}
object(MyImmutableDate)#1 (3) {
  ["date"]=>
  string(26) "2020-01-01 00:00:00.000000"
  ["timezone_type"]=>
  int(3)
  ["timezone"]=>
  string(3) "GMT"
}
