include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

#studentas tests
add_executable(run_student_tests
    test_studentas.cpp
    ../functions.cpp
    ../Studentas.cpp
)

target_include_directories(run_student_tests PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(run_student_tests
    gtest
    gtest_main
)

add_test(NAME StudentasTest COMMAND run_student_tests)

#vector tests
add_executable(run_vector_tests
    test_vector.cpp
)

target_include_directories(run_vector_tests PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(run_vector_tests
    gtest
    gtest_main
)

add_test(NAME VectorTest COMMAND run_vector_tests)