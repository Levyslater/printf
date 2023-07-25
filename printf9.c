#include "main.h"

/**
 * is_digit - checks if a char is a digit
 * @t: Char to be evaluated
 *
 * Return: 1 if t is a digit, 0 otherwise
 */
int is_digit(char t)
{
	if (t >= '0' && t <= '9')
		return (1);

	return (0);
}
/**
 * convert_size_unsgnd - resize a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of number
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
/**
 * convert_size_number - resize a number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of number
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}
/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @b: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int b)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[b++] = '\\';
	buffer[b++] = 'x';

	buffer[b++] = map_to[ascii_code / 16];
	buffer[b] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_printable - determines if a char is printable
 * @t: Char to be evaluated.
 * Return: 1 if t is printable, 0 otherwise
 */
int is_printable(char t)
{
	if (t >= 32 && t < 127)
		return (1);

	return (0);
}
