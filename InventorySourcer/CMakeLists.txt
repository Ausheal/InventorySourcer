cmake_minimum_required(VERSION 3.12)
project(InventorySourcer)

set(CMAKE_CXX_STANDARD 11)

# Find your Python interpreter and pybind11
execute_process(
    COMMAND "${Python_EXECUTABLE}" -c "import pybind11; print(pybind11.get_cmake_dir())"
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

# This helper function handles the extension naming and compiler settings automatically
pybind11_add_module(_inventory_sourcer main.cpp)