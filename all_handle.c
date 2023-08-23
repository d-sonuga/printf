#include "main.h"

/* Declared these here so that functions implemented earlier can use it */
int write_num(int ind, char outputbuffer[], int flags, int width, int prec, int length, char padd, char extra_c);
int write_pointer(char outputbuffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start);

/**
* handle_write_char - Handles printing a single character with padding
* @c: The character to be printed
* @outputbuffer: Buffer array to handle print
* @flags: Active formatting flags
* @width: Field width
* @precision: Precision specification
* @size: Size specifier
*
* Return: Number of characters printed.
*/
int handle_write_char(char c, char outputbuffer[], int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);
	if (flags & F_ZERO)
	{
		padd = '0';
		outputbuffer[i++] = c;
		outputbuffer[i] = '\0';
		if (width > 1)
		{
			outputbuffer[BUFF_SIZE - 1] = '\0';
			for (i = 0; i < width - 1; i++)
			{
				outputbuffer[BUFF_SIZE - i - 2] = padd;
				if (flags & F_MINUS)
					return (write(1, &outputbuffer[0], 1) +
							write(1, &outputbuffer[BUFF_SIZE - i - 1], width - 1));
					else
						return (write(1, &outputbuffer[BUFF_SIZE - i - 1], width - 1) +
								write(1, &outputbuffer[0], 1));
			}
		}
	}
	return (write(1, &outputbuffer[0], 1));
}
/**
* write_number - Handles printing various types of numbers with padding and signs
* @is_negative: Indicates if the number is negative
* @ind: Index at which the number starts in the outputbuffer
* @outputbuffer: Buffer array to handle print
* @flags: Active formatting flags
* @width: Field width
* @precision: Precision specification
* @size: Size specifier
*
* Return: Number of characters printed.
*/
int write_number(int is_negative, int ind, char outputbuffer[], int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';
	return (write_num(ind, outputbuffer, flags, width, precision, length, padd, extra_ch));
}
/**
* write_num - Handles printing numbers with optional padding, precision, and signs
* @ind: Index at which the number starts in the outputbuffer
* @outputbuffer: Buffer array to handle print
* @flags: Active formatting flags
* @width: Field width
* @prec: Precision specification
* @length: Number length
* @padd: Padding character
* @extra_c: Extra character (for signs)
*
* Return: Number of characters printed.
 */
int write_num(int ind, char outputbuffer[], int flags, int width, int prec, int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && outputbuffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && outputbuffer[ind] == '0')
		outputbuffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
	{
		outputbuffer[--ind] = '0', length++;
		if (extra_c != 0)
			length++;
		if (width > length)
		{
			for (i = 1; i < width - length + 1; i++)
			{
				outputbuffer[i] = padd;
				outputbuffer[i] = '\0';
				if (flags & F_MINUS && padd == ' ')/* Assign extra char to the left of outputbuffer */
				{
					if (extra_c)
						outputbuffer[--ind] = extra_c;
					return (write(1, &outputbuffer[ind], length) + write(1, &outputbuffer[1], i - 1));
				}
				else if (!(flags & F_MINUS) && padd == ' ')/* Extra char to left of buff */
				{
					if (extra_c)
						outputbuffer[--ind] = extra_c;
					return (write(1, &outputbuffer[1], i - 1) + write(1, &outputbuffer[ind], length));
				}
				else if (!(flags & F_MINUS) && padd == '0')/* Extra char to left of padd */
				{
					if (extra_c)
						outputbuffer[--padd_start] = extra_c;
					return (write(1, &outputbuffer[padd_start], i - padd_start) +
							write(1, &outputbuffer[ind], length - (1 - padd_start)));
				}
			}
		}
	}
	if (extra_c)
		outputbuffer[--ind] = extra_c;
	return (write(1, &outputbuffer[ind], length));
}
/**
* write_unsgnd - Handles printing unsigned numbers with optional padding
* @is_negative: Number indicating if the num is negative
* @ind: Index at which the number starts in the outputbuffer
*@outputbuffer: Buffer array to handle print
* @flags: Active formatting flags
* @width: Field width
* @precision: Precision specification
* @size: Size specifier
*
* Return: Number of characters printed.
*/
int write_unsgnd(int is_negative, int ind, char outputbuffer[], int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);
	if (precision == 0 && ind == BUFF_SIZE - 2 && outputbuffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		outputbuffer[--ind] = '0';
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (width > length)
	{
		for (i = 0; i < width - length; i++)
		{
			outputbuffer[i] = padd;
			outputbuffer[i] = '\0';
			if (flags & F_MINUS) /* Assign extra char to left of outputbuffer [outputbuffer > padd] */
			{
				return (write(1, &outputbuffer[ind], length) + write(1, &outputbuffer[0], i));
			}
			else /* Assign extra char to left of padding [padd > outputbuffer] */
			{
				return (write(1, &outputbuffer[0], i) + write(1, &outputbuffer[ind], length));
			}
		}
	}
	return (write(1, &outputbuffer[ind], length));
}
/**
* write_pointer - Handles printing memory addresses with optional padding
* @outputbuffer: Buffer array to handle print
* @ind: Index at which the number starts in the outputbuffer
* @length: Length of number
* @width: Field width
* @flags: Active formatting flags
* @padd: Char representing the padding
 * @extra_c: Char representing extra char
* @padd_start: Index at which padding should start
*
* Return: Number of characters printed.
*/
int write_pointer(char outputbuffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
		{
			outputbuffer[i] = padd;
			outputbuffer[i] = '\0';
			if (flags & F_MINUS && padd == ' ')/* Assign extra char to the left of outputbuffer */
			{
				outputbuffer[--ind] = 'x';
				outputbuffer[--ind] = '0';
				if (extra_c)
					outputbuffer[--ind] = extra_c;
				return (write(1, &outputbuffer[ind], length) + write(1, &outputbuffer[3], i - 3));
			}
			else if (!(flags & F_MINUS) && padd == ' ')/* Extra char to the left of outputbuffer */
			{
				outputbuffer[--ind] = 'x';
				outputbuffer[--ind] = '0';
				if (extra_c)
					outputbuffer[--ind] = extra_c;
				return (write(1, &outputbuffer[3], i - 3) + write(1, &outputbuffer[ind], length));
			}
			else if (!(flags & F_MINUS) && padd == '0')/* Extra char to the left of padd */
			{
				if (extra_c)
					outputbuffer[--padd_start] = extra_c;
				outputbuffer[1] = '0';
				outputbuffer[2] = 'x';
				return (write(1, &outputbuffer[padd_start], i - padd_start) +
				write(1, &outputbuffer[ind], length - (1 - padd_start) - 2));
			}
		}
	}
	outputbuffer[--ind] = 'x';
	outputbuffer[--ind] = '0';
	if (extra_c)
		outputbuffer[--ind] = extra_c;
	return (write(1, &outputbuffer[ind], BUFF_SIZE - ind - 1));
}

/* Other Functions */

