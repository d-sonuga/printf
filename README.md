# Custom Printf Implementation

This is a custom implementation of the printf function in C, which supports various conversion specifiers and flags. It follows the requirements and constraints provided in the project guidelines.

## Table of Contents
- [Introduction](#introduction)
- [Usage](#usage)
- [Supported Conversion Specifiers](#supported-conversion-specifiers)
- [Installation](#installation)
- [Examples](#examples)
- [Authors](#authors)
- [License](#license)

## Introduction

The `printf` function is a standard C library function used for formatted output. This project aims to create a custom implementation of the printf function while adhering to specific constraints and guidelines.

The custom `printf` implementation supports the following features:
- Basic conversion specifiers: `%c`, `%s`, and `%%`
- Decimal and integer conversion specifiers: `%d`, `%i`
- Unsigned decimal conversion specifier: `%u`
- Octal and hexadecimal conversion specifiers: `%o`, `%x`, `%X`
- Custom conversion specifiers: `%b` (binary), `%S` (string with non-printable characters handling), `%p` (memory address), `%r` (reversed string), `%R` (rot13-encoded string)

## Usage

To use the custom `printf` function, include the `main.h` header file in your C program:

```c
#include "main.h"




Supported Conversion Specifiers
%c: Print a character
%s: Print a string
%%: Print a literal percent character
%d, %i: Print a decimal or integer number
%u: Print an unsigned decimal number
%o: Print an octal number
%x, %X: Print a hexadecimal number
%b: Print a binary number (custom)
%S: Print a string with non-printable characters handling (custom)
%p: Print a memory address (custom)
%r: Print a reversed string (custom)
%R: Print a rot13-encoded string (custom)


Installation
To compile and use the custom printf function, follow these steps:

1.Clone the repository:
git clone <https://github.com/Priscaezefili/printf>


Navigate to the repository directory:

cd printf


3.Compile the source files using GCC:

gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o my_printf


4.Run the compiled executable:

./my_printf


Examples

#include "main.h"

int main(void)
{
    _printf("Hello, %s!\n", "world");
    _printf("Decimal: %d\n", 123);
    _printf("Hexadecimal: %x\n", 255);
    _printf("Binary: %b\n", 42);
    _printf("Reversed: %r\n", "hello");
    _printf("Rot13: %R\n", "example");
    
    return (0);
}


Authors

Priscaezefili
Trendswave

License

This project is licensed under the MIT license
