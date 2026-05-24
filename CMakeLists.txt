cmake_minimum_required(VERSION 3.10)
project(StudentuDuomenys)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(student_program 
    main.cpp
    functions.cpp
    Studentas.cpp
  "Vector.h")

enable_testing()

add_subdirectory(unit_tests)