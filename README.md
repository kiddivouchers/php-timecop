# Timecop for PHP

## FORK

Fork of [original package](https://github.com/hnw/php-timecop) maintained by [Wider Plan](https://www.widerplan.com/).

## DESCRIPTION

A PHP extension providing "time travel" and "time freezing" capabilities, inspired by [ruby timecop gem](https://github.com/travisjeffery/timecop).

## INSTALL (with phpize)

```
git clone https://github.com/kiddivouchers/php-timecop.git
cd php-timecop
phpize
./configure
make
make install
```

After install, add these lines to your `php.ini` .

```ini
extension=timecop.so
```

## SYSTEM REQUIREMENTS

- OS: Linux, macOS
- PHP: 5.6.x - 8.4.x
- SAPI: Apache, CLI
  - Other SAPIs are not tested, but there is no SAPI-dependent code.
- non-ZTS(recommended), ZTS

## FEATURES

- Freeze time to a specific point.
- Travel back to a specific point in time, but allow time to continue moving forward from there.
- Scale time by a given scaling factor that will cause time to move at an accelerated pace.
- Override the following PHP stock functions and methods, which supports freezing or traveling time.
  - `time()`
  - `mktime()`
  - `gmmktime()`
  - `date()`
  - `gmdate()`
  - `idate()`
  - `getdate()`
  - `localtime()`
  - `strtotime()`
  - `strftime()` (PHP < 8.4.0)
  - `gmstrftime()` (PHP < 8.4.0)
  - `microtime()`
  - `gettimeofday()`
  - `unixtojd()`
  - `DateTime::_construct()`
  - `DateTime::createFromFormat()` (PHP >= 5.3.0)
  - `DateTimeImmutable::_construct()` (PHP >= 5.5.0)
  - `DateTimeImmutable::createFromFormat()` (PHP >= 5.5.0)
  - `date_create()`
  - `date_create_from_format()` (PHP >= 5.3.0)
  - `date_create_immutable()` (PHP >= 5.5.0)
  - `date_create_immutable_from_format()` (PHP >= 5.5.0)
- Rewrite value of the following global variables when the time has been moved.
  - `$_SERVER['REQUEST_TIME']`

## USAGE

```php
<?php
var_dump(date("Y-m-d")); // todays date
timecop_freeze(0);
var_dump(gmdate("Y-m-d H:i:s")); // string(19) "1970-01-01 00:00:00"
var_dump(strtotime("+100000 sec")); // int(100000)
```

### The difference between `timecop_freeze()` and `timecop_travel()`

`timecop_freeze()` is used to statically mock the concept of now. As your program executes, `time()` will not change unless you make subsequent calls to `timecop_freeze/travel/scale/return`. `timecop_travel()`, on the other hand, computes an offset between what we currently think `time()` is and the time passed in. It uses this offset to simulate the passage of time. To demonstrate, consider the following code snippets:

```php
<?php
$new_time = mktime(12, 0, 0, 9, 1, 2008);
timecop_freeze($new_time);
sleep(10);
var_dump($new_time == time()); // bool(true)

timecop_return(); // "turn off" php-timecop

timecop_travel($new_time);
sleep(10);
var_dump($new_time == time()); // bool(false)
```

## Timecop Scale

`timecop_scale($scaling_factor)` make time move at an accelerated pace. With this function, you can emulate long-span integration test and reduce execution time of time-dependent unit test.

```php
<?php
Timecop::freeze(new DateTime("2017-01-01 00:00:00"));
Timecop::scale(50); // time goes x50 faster
usleep(100000); // 100ms
var_dump((new DateTime())->format("c")); // string(25) "2017-01-01T00:00:05+00:00"
```

## CHANGELOG

### version 1.7.0, 2025/03/21
- Support PHP 8.4
- Remove `gmstrftime()` and `strftime()` support on PHP ≥ 8.4

### version 1.6.0, 2024/02/09
- Support PHP 8.3

### version 1.5.0, 2022/12/29
- Support PHP 8.2

### version 1.4.0, 2022/01/06
- Support PHP 8.1
- Fix reflection mismatches between native PHP and timecop overrides

### version 1.3.1, 2021/07/13
- Fixes problems when non standard timezone identifiers are used. ([#52](https://github.com/hnw/php-timecop/issues/52))

### version 1.3.0, 2021/06/21
- Support PHP 8.0
- Fixed memory leak
- Code cleanup

### version 1.2.10-wp3, 2019/12/06
- Support PHP 7.4.

### version 1.2.10-wp2, 2019/10/22
- Fix incorrect class returned with DateTimeImmutable::createFromFormat() and
  pipe character.

### version 1.2.10-wp1, 2019/10/04
- Fix test failure when using PHP 7.3 ([#42](https://github.com/hnw/php-timecop/issues/42))
- Fix some ZTS issues ([PR #45](https://github.com/hnw/php-timecop/pull/45))
- Ensure strict types are respected ([#43](https://github.com/hnw/php-timecop/issues/43))

### version 1.2.10(beta), 2017/11/23

- Fix "double free" bug on PHP 7.2.0 ([#32](https://github.com/hnw/php-timecop/issues/32))

### version 1.2.8(beta), 2017/7/7

- Publish on PECL
- Support Windows (experimental)

### version 1.2.6(beta), 2017/7/4

- Bug fixed: Calling timecop_freeze() on a fast machine sometimes fails to stop the microsecond part of current time.
- Support PHP 7.2.0+

### version 1.2.4(beta), 2017/6/8

- Fix [#18](https://github.com/hnw/php-timecop/issues/18) (Fix date_create_from_format when using `|` char)
- Fix `timecop_date_create()`: The previous version of `timecop_date_create("@[unix timestamp]")` returns +1 hour time on PHP 5.3.9 - 5.4.7 only during the DST.

### version 1.2.3(beta), 2017/1/8
- Fix `timecop_date_create_from_format()`: support time travelling
  - Now portions of the generated time not provided in `format` will be set to the travelled time
  - The previous version is completely same behavior as `date_create_from_format()`.
- Remove `TimecopDateTime::getTimestamp()`, `TimecopDateTime::setTimestamp()` on PHP 5.2.x

### version 1.2.2(alpha), 2017/1/4
- Implement `TimecopDateTimeImmutable` class and `timecop_date_create_immutable()`, `timecop_date_create_immutable_from_format()` functions.
- Now `timecop_date_create_from_format()` returns `DateTime` instance

### version 1.2.0(alpha), 2016/12/30
- Big internal change (without BC break): handle microseconds accurately in time traveling.
- Now `timecop_freeze()` and `timecop_travel()` accepts either `DateTimeInterface` or `int`.
  - With `DateTimeInterface` argument, freezed/traveled time would have fraction of second.
- Implement `timecop_scale()`: Make time go faster.
- Implement `Timecop::***()` as alias of `timecop_***()`. (For `freeze`, `travel`, `return`, `scale`)

### version 1.1.3, 2016/12/27
- Fix crash when non-object passed as 2nd argument of TimecopDateTime::__construct() (Fix [#9](https://github.com/hnw/php-timecop/issues/9))'
- Add CI environment (CentOS, Ubuntu 32-bit, PHP 7.1)

### version 1.1.2(alpha), 2016/04/23
- Fix for stock PHP on Ubuntu

### version 1.1.0(alpha), 2016/04/18
- Support PHP 7.0.x
- Now `new DateTime()` always returns `DateTime` instance
  - The previous version returns `TimecopDateTime` instance when `timecop.func_override=1`.
- Implement `timecop_gettimeofday()` and  `timecop_microtime()`

### version 1.0.6, 2016/04/15
- Fix #10 (Timecop segfaults when set_error_handler throws an exception)

### version 1.0.5, 2013/11/26
- Fix `TimecopDateTime::createFromFormat()` to reutrn `TimecopDateTime` instance on PHP >= 5.3.4
  - The previous version returns `DateTime` instance
  - Implement identical function `timecop_date_create_from_format()`
  - BUG: not supporting "relative formats" for this method currently.
- Fix behavior of `TimecopDateTime::_construct()` when its 2nd argument is specified.

### version 1.0.4, 2013/03/11
- Fix SIGSEGV in `TimecopDateTime::__construct()` called with NULL as 1st argument

### version 1.0.3, 2013/03/09

- Fix the time traveling implementation for `TimecopDateTime::__construct()`
- Fix `timecop_date_create()` to return `TimecopDateTime` instance
  - The previous version returns `DateTime` instance
- Add `TimecopDateTime::getTimestamp()`, `TimecopDateTime::setTimestamp()` only for PHP 5.2.x

### version 1.0.2, 2013/03/06

- Implement `timecop_date_create()`

### Version 1.0.1, 2013/03/04

- Implement time traveling feature for `TimecopDateTime::__construct()` with 1 or 2 arguments
  - The previous version works correctly only for no arguments calling: "new TimecopDateTime()"

### version 1.0.0, 2012/11/21

- Fix memory leak

### version 0.0.1, 2012/06/19

- Initial Release

## LICENSE
#
The MIT License

Copyright (c) 2012-2017 Yoshio HANAWA
Copyright (c) 2019-2024 Wider Plan Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
