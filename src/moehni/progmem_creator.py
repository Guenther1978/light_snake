# Writes the intensities to one header file

import math

size = 240
max_value = 4095
offset = 100
expo = math.log(max_value - offset)/(size - 1)

f = open("intensities.h", "w")
f.write("const PROGMEM uint16_t intensities[] = {")

for index in range(size):
        value = round(math.exp(index * expo)) + offset
        print(index, value)
        f.write(str(value))
        f.write(", ")

f.write("};\n")
f.close()
