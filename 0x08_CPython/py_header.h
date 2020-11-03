#ifndef MYPY_HEADER
#define MYPY_HEADER

#include <stdio.h>
#include <assert.h>
#include <Python.h>
#include <string.h>
#include <stdlib.h>

#define my_SIZE(p) (((PyVarObject *)(p))->ob_size)
#define my_TYPE(p) (((PyObject *)(p))->ob_type)
#define my_allocated(p) (((PyListObject *)p)->allocated)

#define my_Bytes_Check(op) \
	PyType_FastSubclass(my_TYPE(op), Py_TPFLAGS_BYTES_SUBCLASS)
#define my_Bytes_AS_STRING(op) (assert(my_Bytes_Check(op)), \
								  (((PyBytesObject *)(op))->ob_sval))
#define my_Bytes_GET_SIZE(op) (assert(my_Bytes_Check(op)), my_SIZE(op))

/**
 * _my_IS_TYPE - check is an object have a type
 * @ob: python object
 * @type: type of the python object
 * Return: true on success, false otherwise
 */
static inline int _my_IS_TYPE(const PyObject *ob, const PyTypeObject *type)
{
	return (my_TYPE(ob) == type);
}
#define my_IS_TYPE(ob, type) _my_IS_TYPE(_PyObject_CAST_CONST(ob), type)
#define my_Object_TypeCheck(ob, tp) \
	(my_IS_TYPE(ob, tp) || PyType_IsSubtype(my_Py_TYPE(ob), (tp)))
#define my_Float_Check(op) my_Object_TypeCheck(op, &PyFloat_Type)
#define my_Float_AS_DOUBLE(op) (((PyFloatObject *)(op))->ob_fval)
#define _PyObject_CAST_CONST(op) ((const PyObject *)(op))

#define my_List_Check(op) \
	PyType_FastSubclass(my_TYPE(op), Py_TPFLAGS_LIST_SUBCLASS)

#endif
