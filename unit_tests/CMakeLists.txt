include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_executable(run_tests
    main.cpp
    test_studentas.cpp
    ../Studentas.cpp
    ../functions.cpp
)

target_include_directories(run_tests PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(run_tests
    gtest
    gtest_main
)

enable_testing()

add_test(NAME StudentasTest COMMAND run_tests)