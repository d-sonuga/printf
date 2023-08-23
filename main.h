#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* Flags */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* Sizes */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Represents a format specifier.
 * @fmt: Defines how data should be printed or formatted.
 * @fn: The function associated with the format specifier.
 */

struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

typedef struct fmt fmt_t;

/* Core printf function */
int _printf(const char *format, ...);

/* Handlers for format specifiers */
typedef int (*specifier_handler)(va_list, char[], int, int, int, int);

int print_char(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
			int flags, int width, int precision, int size);

/* ... Other specifier handlers ...*/

/* printable */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);
int is_printable(char c);
int append_hexa_code(char c, char buffer[], int index);
int is_digit(char c);

/* Added this so that the printable.c errors will be resolved. */
int write_unsgnd(int is_negative, int ind, char outputbuffer[], int flags, int width, int precision, int size);

int write_pointer(char outputbuffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start);

#endif /* MAIN_H */
