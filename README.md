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
- PHP: 8.0.x - 8.5.x
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
  - `DateTime::createFromFormat()`
  - `DateTimeImmutable::_construct()`
  - `DateTimeImmutable::createFromFormat()`
  - `date_create()`
  - `date_create_from_format()`
  - `date_create_immutable()`
  - `date_create_immutable_from_format()`
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

See https://github.com/kiddivouchers/php-timecop/releases

## LICENSE
#
The MIT License

Copyright (c) 2012-2017 Yoshio HANAWA
Copyright (c) 2019-2025 Wider Plan Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
