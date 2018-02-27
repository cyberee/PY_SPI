//
//  L6740_Driver.c
//  
//
//  Created by Travis Priest on 2/13/18.
//
//This is an interface for the Raspbeery Pi Spi Bus to Python

#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "PI_SPI.h"

#define _VERSION_ "0.0.5"
/*
#if PY_MAJOR_VERSION < 3
#define PyLong_AS_LONG(val) PyInt_AS_LONG(val)
#define PyLong_AsLong(val) PyInt_AsLong(val)
#endif

// Macros needed for Python 3
#ifndef PyInt_Check
#define PyInt_Check            PyLong_Check
#define PyInt_FromLong    PyLong_FromLong
#define PyInt_AsLong        PyLong_AsLong
#define PyInt_Type            PyLong_Type
#endif
*/


//spi_open is used to open the port that is used for writing the data out

static PyObject *
spi_open(PyObject *self)
{
    int a;
    a = pi_spi_open();
    if (a<0)
    {
        return Py_BuildValue("s", "could not open port");
    }
    return Py_BuildValue("s", "spi port open");
}

static PyObject *
spi_get_mode(PyObject *self)
{
    uint32_t a;
    a = pi_spi_get_mode();
    return Py_BuildValue("i", a);
}
static PyObject *
spi_get_bits(PyObject *self)
{
    uint8_t a;
    a = pi_spi_get_bits();
    return Py_BuildValue("i",a);
}
static PyObject *
spi_get_speed(PyObject *self)
{
    uint32_t a;
    a = pi_spi_get_speed();
    return Py_BuildValue("i", a);
}
static PyObject *
spi_set_mode(PyObject *self, PyObject *args)
{
    uint32_t a;
    uint32_t b;
    if (!PyArg_ParseTuple(args, "i", &a)) {
        return NULL;
    }
    b = pi_spi_set_mode(a);
    return Py_BuildValue("i", b);
}
static PyObject *
spi_set_bits(PyObject *self, PyObject *args)
{
    uint8_t a;
    uint8_t b;
    if (!PyArg_ParseTuple(args, "i", &a)) {
        return NULL;
    }
    b = pi_spi_set_bits(a);
    return Py_BuildValue("i",b);
}
static PyObject *
spi_set_speed(PyObject *self, PyObject *args)
{
    uint32_t a;
    uint32_t b;
    if (!PyArg_ParseTuple(args, "i", &a)) {
        return NULL;
    }
    b = pi_spi_set_speed(a);
    return Py_BuildValue("i", a);
}
static PyObject *
spi_read(PyObject *self, PyObject *args)
{
    int a;
    if (!PyArg_ParseTuple(args, "i", &a)) {
        return NULL;
    }
    
    return Py_BuildValue("s", "BYtes read from spi bus");
}


static PyObject *
spi_write(PyObject *self, PyObject *args)
{
    int a;
    char arr[]={'1','2'};
    pi_spi_write(1,arr);
    if (!PyArg_ParseTuple(args, "i", &a)) {
        return NULL;
    }
    return Py_BuildValue("si", "Writing spi Bus with data: ",a);
}


//spi_configure is used to configure the speed and mode of the spi port
//the spi port will be configured with the CS disabled
static PyObject *
spi_configure(PyObject * self, PyObject *args)
{
    int a;
    
    if (!PyArg_ParseTuple(args, "i", &a)) {
        return NULL;
    }
    return Py_BuildValue("si", "trying to Configure the spi bus ",a);
}

static PyObject *
spi_set_port(PyObject * self, PyObject *args)
{
    int a;
    char * port_name;
    if (!PyArg_ParseTuple(args, "s", &port_name)) {
        return NULL;
    }
    printf("In PY_SPI:port:%s\n\r",port_name);
    pi_set_spi_port(port_name);
    return Py_BuildValue("ss", "trying to open the spi bus ",port_name);
    
}

static PyObject *
version(PyObject *self)
{
    return Py_BuildValue("s", _VERSION_);
}

static char PY_Spi_docs[] = "PY_Spi( ) : opens the SPI Bus\n";

static PyMethodDef PY_Spi_funcs[] = {
    {"spi_open", (PyCFunction)spi_open,
        METH_NOARGS, PY_Spi_docs},
    {"spi_get_mode", (PyCFunction)spi_get_mode,
        METH_NOARGS, PY_Spi_docs},
    {"spi_get_bits", (PyCFunction)spi_get_bits,
        METH_NOARGS, PY_Spi_docs},
    {"spi_get_speed", (PyCFunction)spi_get_speed,
        METH_NOARGS, PY_Spi_docs},
    {"spi_set_mode", (PyCFunction)spi_set_mode,
        METH_VARARGS, PY_Spi_docs},
    {"spi_set_bits", (PyCFunction)spi_set_bits,
        METH_VARARGS, PY_Spi_docs},
    {"spi_set_speed", (PyCFunction)spi_set_speed,
        METH_VARARGS, PY_Spi_docs},
    {"spi_read", (PyCFunction)spi_read,
        METH_VARARGS, PY_Spi_docs},
    {"spi_write", (PyCFunction)spi_write,
        METH_VARARGS, PY_Spi_docs},
    {"spi_configure", (PyCFunction)spi_configure,
        METH_VARARGS, PY_Spi_docs},

    {"spi_set_port", (PyCFunction)spi_set_port,
        METH_VARARGS, PY_Spi_docs},
    
    {"version", (PyCFunction)version,
        METH_NOARGS, PY_Spi_docs},
     
    {NULL}
};

void initPY_Spi(void) { Py_InitModule3("PY_Spi", PY_Spi_funcs, "spi open test");
    
}


