import struct
import example

pybuf = struct.pack('BBB', 0x49, 0x4A, 0x4B)
e = example.ExampleClass()

print("Printing:")
print("=========")
e.print()
print()

print("Set Data:")
print("=========")
e.set_data(0x41, 0x42, 0x43)
print()

print("Printing:")
print("=========")
e.print()
print()

print("Exporter:")
print("=========")
t = e.exporter().tobytes()

print("Size = {}".format(len(t)))
#print(t.decode())
for i in t:
    print("0x{:02X}".format(i))
print()

print("Importer:")
print("=========")
e.importer(pybuf.decode())
print()

print("Printing:")
print("=========")
e.print()
print()

print("Exporter:")
print("=========")
t = e.exporter().tobytes()

print("Size = {}".format(len(t)))
#print(t.decode())
for i in t:
    print("0x{:02X}".format(i))

if t == pybuf:
    print()
    print("t == pybuff")
