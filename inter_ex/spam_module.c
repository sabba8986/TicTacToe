#define PY_SSIZE_T_CLEAN
#include <python3.10/Python.h>
#include <stdlib.h>


static PyObject* spam_system(PyObject* self, PyObject* args){
    const char* command;
    int result;

    
    if(!PyArg_ParseTuple(args, "z", &command)){
        return NULL;
    }

    result = system(command);
    return PyLong_FromLong(result);
}


static PyMethodDef spam_methods[] = {
    {"system", spam_system, METH_VARARGS, "To execute a command from the system shell."},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef spam_module = {
    PyModuleDef_HEAD_INIT, 
    "spam",
    NULL, 
    -1, 
    spam_methods
};


PyMODINIT_FUNC PyInit_spam(){
    return PyModule_Create(&spam_module);
}
