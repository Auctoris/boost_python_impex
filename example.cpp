#include <cstdio>
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
