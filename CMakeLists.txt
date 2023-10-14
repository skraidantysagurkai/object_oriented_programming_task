cmake_minimum_required(VERSION 3.26)
project(OP)

set(CMAKE_CXX_STANDARD 11)

add_executable(OP main.cpp
        libraries.h
        Student.cpp
        Student.h
        TextReader.cpp
        TextReader.h
        UserInterface.cpp
        UserInterface.h
        FileGenerator.cpp
        FileGenerator.h
)
