cmake_minimum_required(VERSION 3.5)

project(PassWordgenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PassWordgenerator main.cpp ToDo.hpp)

install(TARGETS PassWordgenerator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
