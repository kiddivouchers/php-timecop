<?php
/*
MIT License

Copyright (c) 2012-2017 Yoshio HANAWA
Copyright (c) 2021 Wider Plan Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#if PHP_VERSION_ID >= 80200
function timecop_freeze(\DateTimeInterface|int $timestamp): true {}
function timecop_travel(\DateTimeInterface|int $timestamp): true {}
function timecop_scale(int $scale): bool {}
function timecop_return(): true {}
#else
function timecop_freeze(\DateTimeInterface|int $timestamp): bool {}
function timecop_travel(\DateTimeInterface|int $timestamp): bool {}
function timecop_scale(int $scale): bool {}
function timecop_return(): bool {}
#endif

function timecop_time(): int {}

function timecop_mktime(
    int $hour,
    ?int $minute = null,
    ?int $second = null,
    ?int $month = null,
    ?int $day = null,
    ?int $year = null
): int|false {}

function timecop_gmmktime(
    int $hour,
    ?int $minute = null,
    ?int $second = null,
    ?int $month = null,
    ?int $day = null,
    ?int $year = null
): int|false {}

function timecop_date(string $format, ?int $timestamp = null): string {}
function timecop_gmdate(string $format, ?int $timestamp = null): string {}
function timecop_idate(string $format, ?int $timestamp = null): int|false {}
function timecop_localtime(?int $timestamp = null, bool $associative = false): array {}
function timecop_strtotime(string $datetime, ?int $baseTimestamp = null): int|false {}
#if PHP_VERSION_ID < 80400
function timecop_strftime(string $format, ?int $timestamp = null): string|false {}
function timecop_gmstrftime(string $format, ?int $timestamp = null): string|false {}
#endif
function timecop_microtime(bool $as_float = false): string|float {}
function timecop_gettimeofday(bool $as_float = false): array|float {}
function timecop_unixtojd(?int $timestamp = null): int|false {}
function timecop_getdate(?int $timestamp = null): array {}
function timecop_date_create(string $datetime = "now", ?DateTimeZone $timezone = null): DateTime|false {}
function timecop_date_create_from_format(string $format, string $datetime, ?DateTimeZone $timezone = null): DateTime|false {}
function timecop_date_create_immutable(string $datetime = "now", ?DateTimeZone $timezone = null): DateTimeImmutable|false {}
function timecop_date_create_immutable_from_format(string $format, string $datetime, ?DateTimeZone $timezone = null): DateTimeImmutable|false {}

class TimecopDateTime extends DateTime
{
    public function __construct(string $datetime = "now", ?DateTimeZone $timezone = null)
    {

    }

#if PHP_VERSION_ID >= 80100
    /** @tentative-return-type */
    public static function createFromFormat(string $format, string $datetime, ?DateTimeZone $timezone = null): DateTime|false
    {

    }
#else
    /** @return DateTime|false */
    public static function createFromFormat(string $format, string $datetime, ?DateTimeZone $timezone = null)
    {

    }
#endif
}

class TimecopDateTimeImmutable extends DateTimeImmutable
{
    public function __construct(string $datetime = "now", ?DateTimeZone $timezone = null)
    {

    }

#if PHP_VERSION_ID >= 80100
    /** @tentative-return-type */
    public static function createFromFormat(string $format, string $datetime, ?DateTimeZone $timezone = null): DateTimeImmutable|false
    {

    }
#else
    /** @return DateTimeImmutable|false */
    public static function createFromFormat(string $format, string $datetime, ?DateTimeZone $timezone = null)
    {

    }
#endif
}
