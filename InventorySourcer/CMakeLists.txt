cmake_minimum_required(VERSION 3.12)
project(InventorySourcer)

find_package(pybind11 REQUIRED)

# This helper function handles the extension naming and compiler settings automatically
pybind11_add_module(_inventory_sourcer main.cpp)