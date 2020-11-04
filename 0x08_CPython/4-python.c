#include "py_header.h"

/**
 * print_python_list - print some basic python info
 * @p: python object
 * Return: nothing
 */
void print_python_string(PyObject *p)
{
	fflush(stdout);
	printf("[.] string object info\n");
	if (!PyUnicode_Check(p))
	{
		printf("  [ERROR] Invalid String Object\n");
		return;
	}
	if (PyUnicode_IS_COMPACT_ASCII(p))
    	printf("  type: compact ascii\n");

	else if (PyUnicode_IS_COMPACT(p) && !PyUnicode_IS_ASCII(p))
		printf("  type: compact unicode object\n");
	
	printf("  length: %d\n", (int) PyUnicode_GET_LENGTH(p));
	printf("  value: %ls\n", PyUnicode_AS_UNICODE(p));
	fflush(stdout);
}