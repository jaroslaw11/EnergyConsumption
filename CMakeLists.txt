﻿# CMakeList.txt: проект CMake для EnergyConsumption; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("EnergyConsumption")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Добавьте источник в исполняемый файл этого проекта.
add_executable (EnergyConsumption "EnergyConsumption.cpp" "EnergyConsumption.h" "forecast.hpp" "forecast.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

