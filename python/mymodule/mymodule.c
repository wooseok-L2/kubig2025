// gcc -shared -fPIC -o mymodule.cpython-310-x86_64-linux-gnu.so mymodule.c -I/usr/include/python3.10 -lpython3.10
#define PY_SSYZE_T_CLEAN
#include <Python.h>

// 클래스 인스턴스 구조체
typedef struct
{
    PyObject_HEAD PyObject *name;
} HelloObject;

// def main():
static PyObject *Hello_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    HelloObject *self;
    self = (HelloObject *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->name = PyUnicode_FromString("");
        if (self->name == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }
    }
    return (PyObject *)self;
}

// init
static int Hello_init(HelloObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *name = NULL;
    static char *kwlist[] = {"name", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "U", kwlist, &name))
        return -1;

    Py_INCREF(name);
    Py_DECREF(self->name);
    self->name = name;
    return 0;
}

// def hello_greet():
static PyObject *Hello_greet(HelloObject *self, PyObject *Py_UNUSED(ignored))
{
    return PyUnicode_FromFormat("hello, %U!", self->name);
}

static PyMethodDef Hello_methods[] = {
    {"greet", (PyCFunction)Hello_greet, METH_NOARGS, "Greet the person."},
    {NULL}};

static PyTypeObject HelloType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "mymodule.hello",
    .tp_basicsize = sizeof(HelloObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Hello objects",
    .tp_new = Hello_new,
    .tp_init = (initproc)Hello_init,
    .tp_dealloc = (destructor)PyObject_Del,
    .tp_methods = Hello_methods,
};

// print_hello 함수 정의
static PyObject *print_hello(PyObject *self, PyObject *args)
{
    printf("Hello from C extension!\n");
    Py_RETURN_NONE;
}

// 모듈에 포함될 함수 목록
static PyMethodDef MyModuleMethods[] = {
    {"print_hello", print_hello, METH_NOARGS, "Prints a hello message."},
    {NULL, NULL, 0, NULL} // Sentinel
};

static PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "mymodule",
    .m_doc = "C type module example",
    .m_size = -1,
    .m_methods = MyModuleMethods,
};

PyMODINIT_FUNC PyInit_mymodule(void)
{
    PyObject *m;
    if (PyType_Ready(&HelloType) < 0)
        return NULL;

    m = PyModule_Create(&mymodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&HelloType);
    if (PyModule_AddObject(m, "Hello", (PyObject *)&HelloType) < 0)
    {
        Py_DECREF(&HelloType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}