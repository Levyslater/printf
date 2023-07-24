#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - we have to print a char
 * @types: there are the list a of arguments
 * @buffer: Buffer
 * @flags:   flags
 * @width: Width
 * @precision: Precision
 * @size: the Size
 * Return: total chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string -we have to prints a string
 * @types: all arguments
 * @buffer: Buffer
 * @flags:  Calculate flags
 * @width: width
 * @precision: Precision specification
 * @size: total specified
 * Return: total chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, b;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (b = width - length; b > 0; b--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (b = width - length; b > 0; b--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: total arguments
 * @buffer: Buffer
 * @flags:  Calculates flags
 * @width: all width.
 * @precision: Precision
 * @size:size
 * Return: all chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @types: allarguments
 * @buffer: buffer
 * @flags:  Calculates flags
 * @width: width
 * @precision: Precision]
 * @size: Size
 * Return: total sum of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int b = BUFF_SIZE - 2;
	int is_negative = 0;
	long int c = va_arg(types, long int);
	unsigned long int num;

	c = convert_size_number(c, size);

	if (c == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)c;

	if (c < 0)
	{
		num = (unsigned long int)((-1) * c);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[b--] = (num % 10) + '0';
		num /= 10;
	}

	b++;

	return (write_number(is_negative, b, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints binary
 * @types: types
 * @buffer: Buffer
 * @flags: flags
 * @width: width.
 * @precision: Precision
 * @size: Size
 * Return: total char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int c, a, b, sum;
	unsigned int d[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	c = va_arg(types, unsigned int);
	a = 2147483648; /* (2 ^ 31) */
	d[0] = c / a;
	for (b = 1; b < 32; b++)
	{
		a /= 2;
		d[b] = (c / d) % 2;
	}
	for (b = 0, sum = 0, count = 0; b < 32; b++)
	{
		sum += d[b];
		if (sum || b == 31)
		{
			char x = '0' + d[b];

			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
