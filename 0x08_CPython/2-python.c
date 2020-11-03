#include "py_header.h"

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
	if (!my_PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	size = my_PyBytes_GET_SIZE(p);
	s = my_PyBytes_AS_STRING(p);
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
}

/**
 * print_python_list - print some basic python info
 * @p: python object
 * Return: nothing
 */
void print_python_list(PyObject *p)
{
	(void)p;
	int i = 0, size = my_Py_SIZE(p);
	int allocated = my_Py_allocated(p);

	if (!my_PyList_Check(p))
	{
		PyErr_BadInternalCall();
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
	}
}
