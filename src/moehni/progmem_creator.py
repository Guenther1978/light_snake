# Writes the intensities to one header file

import math

f = open("intensities.h", "w")
size = 256
max_value = 4095

i = 0;

offset_0 = 125

for i in range(5):
    name = "const PROGMEM uint16_t intensities_" + str(i) + "[] = {";
    f.write(name)
    offset = offset_0 * 2**i
    expo = math.log(max_value - offset)/(size - 1)
    for index in range(size):
        value = round(math.exp(index * expo)) + offset
        print(index, value)
        f.write(str(value))
        f.write(", ")
    f.write("};\n")

f.close()
