#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>

#include "example.h"

void example_class_import_wrap(ExampleClass& self, boost::python::object py_buffer)
{
  namespace python = boost::python;
  python::stl_input_iterator<char> begin(py_buffer), end;
  
  // Copy the py_buffer into a local buffer with known continguous memory.
  std::vector<char> buffer(begin, end);

  // Cast and delegate to the printBuffer member function.
  self.import(reinterpret_cast<unsigned char*>(&buffer[0]), buffer.size());
}

PyObject* example_class_export_wrap(ExampleClass& self)
{
    PyObject* pymemview;
    unsigned char* export_data;

    export_data = self.exporter();

    pymemview = PyMemoryView_FromMemory((char*) export_data, 3, PyBUF_READ);
    return PyBytes_FromObject(pymemview);
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
