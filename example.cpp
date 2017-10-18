#include <cstdio>
#include <vector>
#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>

#include "example.h"

ExampleClass::ExampleClass()
{
  a = 0;
  b = 0;
  c = 0;
}

void ExampleClass::print_state()
{
  printf("A = 0x%.2X\nB = 0x%.2X\nC = 0x%.2X\n", a, b, c);
}

unsigned char* ExampleClass::exporter()
{
  unsigned char* x = new unsigned char[3];
  x[0]=a;
  x[1]=b;
  x[2]=c;
  return x;
}

void ExampleClass::set_data(uint8_t x, uint8_t y, uint8_t z)
{
  a = x;
  b = y;
  c = z;
}

void ExampleClass::import(unsigned char* buf, int size)
{
  if (size==3)
  {
    a = buf[0];
    b = buf[1];
    c = buf[2];
  }
}

void example_class_import_wrap(ExampleClass& self, boost::python::object py_buffer)
{
  namespace python = boost::python;
  // `str` objects do not implement the iterator protcol (__iter__),
  // but do implement the sequence protocol (__getitem__).  Use the
  // `iter()` builtin to create an iterator for the buffer.
  // >>> __builtins__.iter(py_buffer)

//  python::object locals(python::borrowed(PyEval_GetLocals()));
//  python::object py_iter = locals["__builtins__"].attr("iter");
//  python::stl_input_iterator<char> begin(py_iter(py_buffer)), end;

  python::stl_input_iterator<char> begin(py_buffer), end;
  
  // Copy the py_buffer into a local buffer with known continguous memory.
  std::vector<char> buffer(begin, end);

  // Cast and delegate to the printBuffer member function.
  self.import(reinterpret_cast<unsigned char*>(&buffer[0]), buffer.size());
}

PyObject* example_class_export_wrap(ExampleClass& self)
{
    PyObject* pymemview;
    unsigned char* bob;

    bob = self.exporter();

    pymemview = PyMemoryView_FromMemory((char*) bob, 3, PyBUF_READ);
    return pymemview;
}

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;
  python::class_<ExampleClass>("ExampleClass")
    .def("print", &ExampleClass::print_state)
    .def("exporter", &example_class_export_wrap)
    .def("set_data", &ExampleClass::set_data)
    .def("importer", &example_class_import_wrap)
    ;
}