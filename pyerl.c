#include <Python.h>
#include "structmember.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ei.h>
#include <erl_interface.h>
#include "eterm.h"

static char pyerl_doc[] = "Erlang Interface for Python\n";

static PyObject *
pyerl_init(PyObject *self, PyObject *args)
{
	int x = 0;
	int y = 0;
	if(!PyArg_ParseTuple(args, "|ii", &x, &y)){
		return NULL;
	}
	erl_init((void *)x, y);
	Py_RETURN_NONE;
}

static PyObject *
pyerl_set_compat_rel(PyObject *self, PyObject *args)
{
	unsigned int rel;
	if(!PyArg_ParseTuple(args, "I", &rel)){
		return NULL;
	}
	erl_set_compat_rel(rel);
	Py_RETURN_NONE;
}

static PyObject *
pyerl_connect_init(PyObject *self, PyObject *args)
{
	int ret;
	int number;
	char *cookie;
	short creation;

	if (!PyArg_ParseTuple(args, "isi", &number, &cookie, &creation))
		return NULL;
	ret = erl_connect_init(number, cookie, creation);
	return Py_BuildValue("i", ret);
}

static PyObject *
pyerl_connect_xinit(PyObject *self, PyObject *args)
{
	int ret;
	char *host, *alive, *node, *addr;
	char *cookie;
	short creation;
	struct in_addr ia;

	if (!PyArg_ParseTuple(args, "sssssi",
						  &host, &alive, &node, &addr, &cookie, &creation))
		return NULL;
	ia.s_addr = inet_addr(addr);
	ret = erl_connect_xinit(host ,alive, node, &ia, cookie, creation);
	return Py_BuildValue("i", ret);
}

static PyObject *
pyerl_connect(PyObject *self, PyObject *args)
{
	int ret;
	char *node;

	if (!PyArg_ParseTuple(args, "s", &node))
		return NULL;
	ret = erl_connect(node);
	return Py_BuildValue("i", ret);
}

static PyObject *
pyerl_xconnect(PyObject *self, PyObject *args)
{
	int ret;
	char *addr, *alive;
	struct in_addr ia;

	if (!PyArg_ParseTuple(args, "ss", &addr, &alive))
		return NULL;
	ia.s_addr = inet_addr(addr);
	ret = erl_xconnect(&ia, alive);
	return Py_BuildValue("i", ret);
}

static PyObject *
pyerl_close_connection(PyObject *self, PyObject *args)
{
	int ret;
	int fd;
	if(!PyArg_ParseTuple(args, "i", &fd)){
		return NULL;
	}
	ret = erl_close_connection(fd);
	return Py_BuildValue("i", ret);
}

static PyMethodDef methods[] = {
	{"init", pyerl_init, METH_VARARGS,
	 "This function must be called before any of the others in the pyerl module in order to initialize the module functions. The arguments must be specified as init(0, 0)."
	},
	{"set_compat_rel", pyerl_set_compat_rel, METH_VARARGS, NULL},
	{"connect_init", pyerl_connect_init, METH_VARARGS, NULL},
	{"connect_xinit", pyerl_connect_xinit, METH_VARARGS, NULL},
	{"connect", pyerl_connect, METH_VARARGS, NULL},
	{"xconnect", pyerl_xconnect, METH_VARARGS, NULL},
	{"close_connection", pyerl_close_connection, METH_VARARGS, NULL},

	{NULL, NULL}
};

void initpyerl(void)
{
	PyObject *m;
	EtermType.tp_new = PyType_GenericNew;
	if (PyType_Ready(&EtermType) < 0)
		return;

	m = Py_InitModule3("pyerl", methods, pyerl_doc);
	if (m == NULL)
		return;
	Py_INCREF(&EtermType);
	PyModule_AddObject(m, "Eterm", (PyObject *)&EtermType);
}
