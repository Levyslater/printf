#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints unsigned
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: total chars printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int b = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[b--] = (num % 10) + '0';
		num /= 10;
	}

	b++;

	return (write_unsgnd(0, b, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints octal
 * @types: types
 * @buffer: Buffer
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: all chars printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int b = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[b--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[b--] = '0';

	b++;

	return (write_unsgnd(0, b, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints hexadeciamal
 * @types: types
 * @buffer: Buffer
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: all chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'z', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints hexa upper
 * @types: types
 * @buffer: Buffer
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: all chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'z', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints hexa
 * @types: types
 * @map_to: map to
 * @buffer: Buffer
 * @flags: flags
 * @flag_ch: flags
 * @width: width
 * @precision: Precision
 * @size: specifier
 * @size: specification
 * Return: all chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int b = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[b--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[b--] = flag_ch;
		buffer[b--] = '0';
	}

	b++;

	return (write_unsgnd(0, b, buffer, flags, width, precision, size));
}
