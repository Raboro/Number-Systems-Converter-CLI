# Number-Systems-Converter-CLI

## Install
Just use ``make`` in your terminal:
````bash
$ make
````

Or do it manually by using the following command in your terminal:
````bash
$ gcc -Wall -Wextra -o ns.exe main.c
````
After that link it to your system. For example windows users need to add ``ns.exe`` to the system environment variables.

## Conversion
Important is to write ``.`` at the end even if your number is no floating-point number. \
Type ``ns`` followed by ``-i`` for the number system your number is in. After that type ``-t`` for the number system(-s) you wanna convert into.
Finally type ``-n`` followed by the number you wanna convert.

e.g. with one conversion:
````bash
$ ns -i 10 -t 2 -n 5.
> Input number 5.000000 converted:
  into base 2 => +101
````

e.g. with multiple conversions:
````bash
$ ns -i 10 -t 2,3,5 -n 5.
> Input number 5.000000 converted:
  into base 2 => +101
  into base 3 => +12
  into base 5 => +10
````

e.g. with floating-point number:
````bash
$ ns -i 10 -t 2,3,5 -n 5.
> Input number 5.300000 converted:
  into base 2 => +101.010011
  into base 3 => +12.022002
  into base 5 => +10.122222
````

e.g. with negative floating-point number:
````bash
$ ns -i 10 -t 2,3,5 -n 5. -m
> Input number 5.300000 converted:
  into base 2 => -101.010011
  into base 3 => -12.022002
  into base 5 => -10.122222
````

Type ``ns -h`` for help:
````bash
$ ns -h
> Usage:
    ns -h
    ns -i [SOURCE_BASE] -t [TARGET_BASES] -n [NUMBER]
    ns -i [SOURCE_BASE] -t [TARGET_BASES] -n [NUMBER] -m
  Options:
    -h, --help               Display this help message
    -i, --input-base BASE    Source number base
    -t, --target-bases BASES Comma-separated list of target bases
    -n, --number NUMBER      Number to convert
    -m, --minus              If present then - else +
````