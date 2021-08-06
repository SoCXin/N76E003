#!/usr/bin/python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright 2021, Frank Zago

# Generate a color fade array

with open ("wheel.h", "w") as f:
    f.write("__code struct { uint8_t R; uint8_t G; uint8_t B; } wheel[768] = {")
    f.write("\n")

    for i in range(0, 256):
        f.write(f"{{ {255 - i}, {i}, 0 }},")
        if i % 4 == 3:
            f.write("\n")
        else:
            f.write(" ")

    for i in range(0, 256):
        f.write(f"{{ 0, {255 - i}, {i} }},")
        if i % 4 == 3:
            f.write("\n")
        else:
            f.write(" ")

    for i in range(0, 256):
        f.write(f"{{ {i}, 0, {255 - i}, }},")
        if i % 4 == 3:
            f.write("\n")
        else:
            f.write(" ")

    f.write("};\n")
