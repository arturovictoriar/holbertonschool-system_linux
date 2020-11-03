#include "py_header.h"

/**
 * print_python_float - print some basic python info
 * @p: python object
 * Return: nothing
 */
void print_python_float(PyObject *p)
{
	int fla = Py_DTSF_ADD_DOT_0, typ = Py_DTST_INFINITE;
	char *s = NULL;

	printf("[.] float object info\n");
	if (!my_Float_Check(p))
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}
	s = PyOS_double_to_string(my_Float_AS_DOUBLE(p), 'g', 16, fla, &typ);
	if (s)
		printf("  value: %s\n", s);
	fflush(stdout);
}

/**
 * print_python_bytes - print some basic python info
 * @p: python object
 * Return: nothing
 */
void print_python_bytes(PyObject *p)
{
	int size = 0, max_size = 0, i = 0;
	char *s = NULL;

	printf("[.] bytes object info\n");
	if (!my_Bytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	size = my_Bytes_GET_SIZE(p);
	s = my_Bytes_AS_STRING(p);
	printf("  size: %d\n", size);
	printf("  trying string: %s\n", s);
	max_size = (size < 10) ? size + 1 : 10;
	printf("  first %d bytes: ", max_size);
	for (i = 0; i < max_size; i++)
	{
		if (i == 0)
			printf("%.2x", (unsigned char)s[i]);
		else
			printf(" %.2x", (unsigned char)s[i]);
	}
	printf("\n");
	fflush(stdout);
}

/**
 * print_python_list - print some basic python info
 * @p: python object
 * Return: nothing
 */
void print_python_list(PyObject *p)
{
	(void)p;
	int i = 0, size = my_SIZE(p);
	int allocated = my_allocated(p);

	if (!my_List_Check(p))
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %d\n", size);
	printf("[*] Allocated = %d\n", allocated);

	for (i = 0; i < size; i++)
	{
		printf("Element %d: %s\n", i,
			   ((((PyListObject *)p)->ob_item[i])->ob_type)->tp_name);
		if (!strcmp(((((PyListObject *)p)->ob_item[i])->ob_type)->tp_name, "bytes"))
			print_python_bytes((((PyListObject *)p)->ob_item[i]));
		if (!strcmp(((((PyListObject *)p)->ob_item[i])->ob_type)->tp_name, "float"))
			print_python_float((((PyListObject *)p)->ob_item[i]));
	}
	fflush(stdout);
}
