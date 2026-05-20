cmake_minimum_required(VERSION 3.10)
project(StudentuDuomenys)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(GTest CONFIG REQUIRED)

# Pagrindinis vykdomasis failas
add_executable(student_program 
    main.cpp
    functions.cpp
    Studentas.cpp)

# Testu vykdomasis failas
add_executable(run_tests 
    test_studentas.cpp
    Studentas.cpp)

target_link_libraries(run_tests PRIVATE GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(run_tests)