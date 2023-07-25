#include "main.h"

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print rot13 array of characters
 * @types: types
 * @buffer: Buffer
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: total chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char z;
	char *str;
	unsigned int b, k;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (b = 0; str[b]; b++)
	{
		for (k = 0; in[k]; k++)
		{
			if (in[k] == str[b])
			{
				z = out[k];
				write(1, &z, 1);
				count++;
				break;
			}
		}
		if (!in[k])
		{
			z = str[b];
			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints pointer
 * @types: types
 * @buffer: Buffer
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: total chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}
/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse
 * @types: types
 * @buffer: Buffer
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: all chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int b, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (b = 0; str[b]; b++)
		;

	for (b = b - 1; b >= 0; b--)
	{
		char x = str[b];

		write(1, &x, 1);
		count++;
	}
	return (count);
}
/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints non printable
 * @types: types
 * @buffer: Buffer
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: all chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int b = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[b] != '\0')
	{
		if (is_printable(str[b]))
			buffer[b + offset] = str[b];
		else
			offset += append_hexa_code(str[b], buffer, b + offset);

		b++;
	}

	buffer[b + offset] = '\0';

	return (write(1, buffer, b + offset));
}
