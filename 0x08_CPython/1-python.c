#include <stdio.h>
#include <Python.h>

/**
 * print_python_list - print some basic python info
 * @p: python object
 * Return: nothing
 */
void print_python_list(PyObject *p)
{
	(void)p;
	int i = 0, size = ((PyVarObject *) p)->ob_size;
	int allocated = ((PyListObject *) p)->allocated;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %d\n", size);
	printf("[*] Allocated = %d\n", allocated);

	for (i = 0; i < size; i++)
		printf("Element %d: %s\n", i, (PyList_GetItem(p, i)->ob_type)->tp_name);
}
