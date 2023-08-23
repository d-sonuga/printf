#include "main.h"

void print_output_buffer(char outputbuffer[], int *output_buff_ind);

/**
* print_pointer - Prints the value of a pointer
* @types: List of arguments
* @outputbuffer: Buffer array used to handle print
* @flags: Active formatting flags
* @width: Field width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of characters printed.
*/
int print_pointer(va_list types, char outputbuffer[], int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);
	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	outputbuffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	num_addrs = (unsigned long)addrs;
	while (num_addrs > 0)
	{
		outputbuffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
		if ((flags & F_ZERO) && !(flags & F_MINUS))
		{
			padd = '0';
			if (flags & F_PLUS)
				extra_c = '+', length++;
			else if (flags & F_SPACE)
				extra_c = ' ', length++;
			ind++;
		}
	}
	return (write_pointer(outputbuffer, ind, length, width, flags, padd, extra_c, padd_start));
}
/*PRINT NON PRINTABLE*/
/**
* print_non_printable - Prints ASCII codes in hexa of non printable character
* @types: List of arguments
* @outputbuffer: Buffer array used to handle print
* @flags: Active formatting flags
* @width: Field width
* @precision: Precision specification
* @size: Size specifier
 Return: Number of characters printed
*/
int print_non_printable(va_list types, char outputbuffer[], int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			outputbuffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], outputbuffer, i + offset);
		i++;
	}
	outputbuffer[i + offset] = '\0';
	return (write(1, outputbuffer, i + offset));
}
/* Rest of the functions */

/**
* print_output_buffer - Prints the contents of the output buffer if it exists
* @outputbuffer: Array of chars
* @output_buff_ind: Index at which to add the next char, represents the length
*/
void print_output_buffer(char outputbuffer[], int *output_buff_ind)
{
	if (*output_buff_ind > 0)
		write(1, &outputbuffer[0], *output_buff_ind);
	*output_buff_ind = 0;
}
