#!/usr/bin/python

import sys, os

if (len(sys.argv) != 2):
    raise Exception('usage: python3 set_extension_name.py <name_for_extension>')

string_to_find = "boilerplate"
string_to_replace = sys.argv[1]

def replace(file_name, to_find, to_replace):
    with open(file_name, 'r') as file :
        filedata = file.read()
    filedata = filedata.replace(to_find, to_replace)
    with open(file_name, 'w') as file:
        file.write(filedata)

# replace occurances
replace("./CMakeLists.txt", string_to_find, string_to_replace)
replace("./src/CMakeLists.txt", string_to_find, string_to_replace)
replace("./src/boilerplate_extension.cpp", string_to_find, string_to_replace)
replace("./src/boilerplate_extension.cpp", string_to_find.capitalize(), string_to_replace.capitalize())
replace("./src/include/boilerplate_extension.hpp", string_to_find, string_to_replace)
replace("./src/include/boilerplate_extension.hpp", string_to_find.capitalize(), string_to_replace.capitalize())

# rename files
os.rename(f'src/{string_to_find}_extension.cpp',f'src/{string_to_replace}_extension.cpp')
os.rename(f'src/include/{string_to_find}_extension.hpp',f'src/include/{string_to_replace}_extension.hpp')
