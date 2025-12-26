--TEST--
Test that DateTime/DateTimeImmutable respects timezone in constructor
--SKIPIF--
<?php
if (!function_exists('timecop_travel')) die('skip timecop not available');
--INI--
date.timezone=Europe/Paris
timecop.func_override=1
--FILE--
<?php
// When Timecop is active, creating a DateTime with a date string
// and a specific timezone should interpret time in that timezone,
// not in the default timezone.

\Timecop::travel(new \DateTime());

echo "=== Test 1: Date only (no time info) ===\n";
$date = new DateTimeImmutable('2026-01-30', new DateTimeZone('UTC'));
$date2 = new DateTime('2026-01-30', new DateTimeZone('UTC'));

// Expected: 2026-01-30 00:00:00 UTC
// Bug was: 2026-01-29 23:00:00 UTC (midnight Paris time converted to UTC)

echo "DateTimeImmutable: ".$date->format('Y-m-d H:i:s T')."\n";
echo "DateTime: ".$date2->format('Y-m-d H:i:s T')."\n";

// Also test with different timezones
$dateTokyo = new DateTimeImmutable('2026-01-30', new DateTimeZone('Asia/Tokyo'));
echo "Asia/Tokyo: ".$dateTokyo->format('Y-m-d H:i:s T')."\n";

echo "\n=== Test 2: Date with time info ===\n";
$dateWithTime = new DateTimeImmutable('2026-01-30 12:00:00', new DateTimeZone('UTC'));
$dateWithTime2 = new DateTime('2026-01-30 12:00:00', new DateTimeZone('UTC'));

echo "DateTimeImmutable: ".$dateWithTime->format('Y-m-d H:i:s T')."\n";
echo "DateTime: ".$dateWithTime2->format('Y-m-d H:i:s T')."\n";

// Test with Tokyo timezone and explicit time
$dateTokyoWithTime = new DateTimeImmutable('2026-01-30 12:00:00', new DateTimeZone('Asia/Tokyo'));
echo "Asia/Tokyo: ".$dateTokyoWithTime->format('Y-m-d H:i:s T')."\n";

// Ensure original timezone is restored
echo "\nDefault TZ after: ".date_default_timezone_get()."\n";

\Timecop::return();
--EXPECT--
=== Test 1: Date only (no time info) ===
DateTimeImmutable: 2026-01-30 00:00:00 UTC
DateTime: 2026-01-30 00:00:00 UTC
Asia/Tokyo: 2026-01-30 00:00:00 JST

=== Test 2: Date with time info ===
DateTimeImmutable: 2026-01-30 12:00:00 UTC
DateTime: 2026-01-30 12:00:00 UTC
Asia/Tokyo: 2026-01-30 12:00:00 JST

Default TZ after: Europe/Paris
