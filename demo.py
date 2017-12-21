import struct
import example

# Define a structure of three bytes for the data...
pybuf = struct.pack('BBB', 0x49, 0x4A, 0x4B)

# Create the blank object
e = example.ExampleClass()

# Call the object's print method it to show it's blank...
print("Printing:")
print("=========")
e.print()
print()

# Set the data using the set method & print
print("Set Data:")
print("=========")
e.set_data(0x41, 0x42, 0x43)
print()

print("Printing:")
print("=========")
e.print()
print()

# Call the export method & print bytes in hex...
print("Exporter:")
print("=========")
t = e.exporter()

print("Size = {}".format(len(t)))
for i in t:
    print("0x{:02X}".format(i))
print()

# Now call the import method using the data we defined at the top...
print("Importer:")
print("=========")
e.importer(pybuf.decode())
print()

# ...and print it.
print("Printing:")
print("=========")
e.print()
print()

# Lastly we'll do the export again, to show it's changed as expected...
print("Exporter:")
print("=========")
t = e.exporter()

print("Size = {}".format(len(t)))

for i in t:
    print("0x{:02X}".format(i))

# ... and ascertain that the data we get back is the same as the data we put in.
if t == pybuf:
    print()
    print("t == pybuff")

