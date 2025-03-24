--TEST--
Check extension functions reflection data
--SKIPIF--
<?php
$required_version = '5.0';
$required_version_less_than = '8.0';
$required_func = array();
$required_class = array();
$required_method = array();
include(__DIR__."/tests-skipcheck.inc.php");
--INI--
date.timezone=America/Los_Angeles
timecop.func_override=0
--FILE--
<?php

echo trim(new \ReflectionFunction('timecop_travel')), "\n\n";
echo trim(new \ReflectionFunction('timecop_freeze')), "\n\n";
echo trim(new \ReflectionFunction('timecop_scale')), "\n\n";
echo trim(new \ReflectionFunction('timecop_return'));
--EXPECT--
Function [ <internal:timecop> function timecop_travel ] {

  - Parameters [1] {
    Parameter #0 [ <required> $timestamp ]
  }
}

Function [ <internal:timecop> function timecop_freeze ] {

  - Parameters [1] {
    Parameter #0 [ <required> $timestamp ]
  }
}

Function [ <internal:timecop> function timecop_scale ] {

  - Parameters [1] {
    Parameter #0 [ <required> $scale ]
  }
}

Function [ <internal:timecop> function timecop_return ] {

  - Parameters [0] {
  }
}
