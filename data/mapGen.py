import os
path = "data"
obj = os.scandir(path)



def create_array(name, target):
    f = open(path + "/maps/map.txt", "r")
    file.write('\nconstexpr uint32_t ' + name + '[] PROGMEM = {\n')

    count = 0

    for line in f:
        string_b = ",\n\t0b"

        if count == 0:
            string_b = "\t0b"
        count += 1
        temp = line.split(" ")
        byte = []
        for bit in temp:
            if bit[len(bit) -1] == "\n":
                bit = bit[:-1]

            if bit == target:
                byte.append(1)
            else:
                byte.append(0)

        file.write(string_b + ''.join(str(x) for x in byte))

    file.write('\n};\n')


if __name__ == '__main__':
    file = open("include/mapComponents.h", "w")
    file.write('#pragma once\n')

    create_array("walls", "S")
    create_array("chests", "C")
