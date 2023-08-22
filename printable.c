#include "main.h"

/**
* print_unsigned - Prints an unsigned number in specified format
* @types: List of arguments
* @outputbuffer: Buffer array to handle print
* @flags: Active formatting flags
* @width: Field width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of chars printed.
*/
int print_unsigned(va_list types, char outputbuffer[], int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);
	if (num == 0)
		outputbuffer[i--] = '0';
		outputbuffer[BUFF_SIZE - 1] = '\0';
		while (num > 0)
		{
			outputbuffer[i--] = (num % 10) + '0';
			num /= 10;
			}
			i++;
			return (write_unsgnd(0, i, outputbuffer, flags, width, precision, size));
			}
/**
* print_octal - Prints an unsigned number in octal notation
* @types: List of arguments
* @outputbuffer: Buffer array to handle print
* @flags: Active formatting flags
* @width: Field width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of chars printed
*/
int print_octal(va_list types, char outputbuffer[], int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);
	num = convert_size_unsgnd(num, size);
	if (num == 0)
		outputbuffer[i--] = '0';
		outputbuffer[BUFF_SIZE - 1] = '\0';
		while (num > 0)
			outputbuffer[i--] = (num % 8) + '0';
			num /= 8;
			}
			if (flags & F_HASH && init_num != 0)
				outputbuffer[i--] = '0';
				i++;
				return (write_unsgnd(0, i, outputbuffer, flags, width, precision, size));
/**
* print_hexadecimal - Prints an unsigned number in hexadecimal notation
* @types: List of arguments
* @outputbuffer: Buffer array to handle print
* @flags: Active formatting flags
* @width: Field width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of chars printed
*/
int print_hexadecimal(va_list types, char outputbuffer[], int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", outputbuffer, flags, 'x', width, precision, size));
	}
