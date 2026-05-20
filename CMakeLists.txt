cmake_minimum_required(VERSION 3.10)
project(StudentuDuomenys)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Pagrindinis vykdomasis failas
add_executable(student_program 
    main.cpp
    functions.cpp
    Studentas.cpp)

enable_testing()
add_subdirectory(tests)