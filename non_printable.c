#include "main.h"

/**
* get_precision - Calculate the precision for printing
* @format: Formatted string to analyze for precision
* @i: Pointer to the current position in the format string
* @list: va_list of arguments
* Return: Calculated precision value
*/
int get_precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = -1;

	if (format[curr_i] != '.')
	{
		return (precision);
		}
		precision = 0;
		for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
		{
			if (is_digit(format[curr_i]))
			{
				precision *= 10;
				precision += format[curr_i] - '0';
			}
			else if (format[curr_i] == '*')
			{
				curr_i++;
				precision = va_arg(list, int);
				break;
			}
			else
			{
				break;
			}
		}
	*i = curr_i - 1;
	return (precision);
}
