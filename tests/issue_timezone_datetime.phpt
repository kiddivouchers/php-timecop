--TEST--
Test that DateTime/DateTimeImmutable respects timezone when no time info provided
--SKIPIF--
<?php
if (!function_exists('timecop_travel')) die('skip timecop not available');
--INI--
date.timezone=Europe/Paris
timecop.func_override=1
--FILE--
<?php
// When Timecop is active, creating a DateTime with a date string (no time)
// and a specific timezone should interpret 00:00:00 in that timezone,
// not in the default timezone.

\Timecop::travel(new \DateTime());

$dtStart = new DateTimeImmutable('2026-01-30', new DateTimeZone('UTC'));
$dtStart2 = new DateTime('2026-01-30', new DateTimeZone('UTC'));

// Expected: 2026-01-30 00:00:00 UTC
// Bug was: 2026-01-29 23:00:00 UTC (midnight Paris time converted to UTC)

echo "DateTimeImmutable: ".$dtStart->format('Y-m-d H:i:s T')."\n";
echo "DateTime: ".$dtStart2->format('Y-m-d H:i:s T')."\n";

// Also test with different timezones
$dtTokyo = new DateTimeImmutable('2026-01-30', new DateTimeZone('Asia/Tokyo'));
echo "Asia/Tokyo: ".$dtTokyo->format('Y-m-d H:i:s T')."\n";

// Ensure original timezone is restored
echo "Default TZ after: ".date_default_timezone_get()."\n";

\Timecop::return();
--EXPECT--
DateTimeImmutable: 2026-01-30 00:00:00 UTC
DateTime: 2026-01-30 00:00:00 UTC
Asia/Tokyo: 2026-01-30 00:00:00 JST
Default TZ after: Europe/Paris
