#include <cstdint>

class ExampleClass
{
public:

  ExampleClass();
  void print_state();
  unsigned char* exporter();
  void set_data(uint8_t, uint8_t, uint8_t);
  void import(unsigned char*, int);

private:
  uint8_t a;
  uint8_t b;
  uint8_t c;

};