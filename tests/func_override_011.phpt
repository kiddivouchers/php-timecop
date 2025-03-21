--TEST--
Function overrideing test for gmstrftime
--SKIPIF--
<?php
$required_version_less_than = '8.4.0';
$required_func = array("timecop_strtotime", "timecop_freeze");
include(__DIR__."/tests-skipcheck.inc.php");
--INI--
date.timezone=America/Los_Angeles
timecop.func_override=1
--FILE--
<?php
require __DIR__.'/functions.inc.php';

timecop_freeze(timecop_strtotime("2012-02-29 01:23:45 GMT"));

execute(decorateIfTrue(
    PHP_VERSION_ID >= 80100,
    function (\Closure $callback) {
        return decorateIgnoreDeprecation(
            'Function gmstrftime() is deprecated',
            decorateIgnoreDeprecation(
                'Function timecop_gmstrftime() is deprecated',
                $callback
            )
        );
    },
    function () {
        var_dump(gmstrftime("%Y-%m-%d %H:%M:%S"));
    }
));
--EXPECT--
string(19) "2012-02-29 01:23:45"
