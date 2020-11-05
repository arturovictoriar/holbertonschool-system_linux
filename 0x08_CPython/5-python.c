#include "py_header.h"

/**
 * my_Long_AsLongAndOverflow - convert a pylongobject to unsigned long int
 * @vv: python object
 * @overflow: flag to set if the number overflow the unsigned long int
 * @s: number sign
 * Return: a unsigned long int
 */
unsigned long my_Long_AsLongAndOverflow(PyObject *vv, int *overflow, int *s)
{
	PyLongObject *v = NULL;
	unsigned long x = 0, prev = 0, res = 0;
	Py_ssize_t i = 0, flag1 = 0;

	*overflow = 0, *s = 1, v = (PyLongObject *)vv, res = 0,	i = my_SIZE(v);

	switch (i)
	{
	case 0:
		res = 0;
		break;
	case 1:
		res = v->ob_digit[0];
		break;
	default:
		*s = 1, x = 0;
		if (i < 0)
			*s = -1, i = -(i);

		while (--i >= 0)
		{
			prev = x;
			x = (x << PyLong_SHIFT) | v->ob_digit[i];
			if ((x >> PyLong_SHIFT) != prev)
			{
				*overflow = *s, flag1 = 1;
				break;
			}
		}

		if (!flag1)
			res = x;
	}
	return (res);
}

/**
 * print_python_int - print some basic python info
 * @p: python object
 * Return: nothing
 */
void print_python_int(PyObject *p)
{
	unsigned long n = 0;
	int overflow = 0, s = 1;

	fflush(stdout);
	if (!PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}

	n = my_Long_AsLongAndOverflow(p, &overflow, &s);
	if (!overflow)
		if (s == 1)
			printf("%lu\n", n);
		else
			printf("-%lu\n", n);
	else
		printf("C unsigned long int overflow\n");
	fflush(stdout);
}
