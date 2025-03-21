--TEST--
Check reflection data for overridden functions
--SKIPIF--
<?php
$required_version = '8.4.0';
$required_func = array();
$required_class = array();
$required_method = array();
include(__DIR__."/tests-skipcheck.inc.php");
--INI--
date.timezone=America/Los_Angeles
timecop.func_override=0
--FILE--
<?php

$functions = [
	'time' => 'timecop_time',
	'date' => 'timecop_date',
	'gmdate' => 'timecop_gmdate',
	'idate' => 'timecop_idate',
	'getdate' => 'timecop_getdate',
	'localtime' => 'timecop_localtime',
	'strtotime' => 'timecop_strtotime',
	'date_create' => 'timecop_date_create',
	'date_create_from_format' => 'timecop_date_create_from_format',
	'date_create_immutable' => 'timecop_date_create_immutable',
	'date_create_immutable_from_format' => 'timecop_date_create_immutable_from_format',
];

require __DIR__.'/check-func-refl.inc.php';

--EXPECT--
Checking time vs timecop_time
Checking date vs timecop_date
Checking gmdate vs timecop_gmdate
Checking idate vs timecop_idate
Checking getdate vs timecop_getdate
Checking localtime vs timecop_localtime
Checking strtotime vs timecop_strtotime
Checking date_create vs timecop_date_create
Checking date_create_from_format vs timecop_date_create_from_format
Checking date_create_immutable vs timecop_date_create_immutable
Checking date_create_immutable_from_format vs timecop_date_create_immutable_from_format
