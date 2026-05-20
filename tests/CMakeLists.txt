find_package(GTest REQUIRED)

add_executable(run_tests 
    main.cpp
    test_studentas.cpp
    ../Studentas.cpp
)

target_include_directories(run_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(run_tests 
    GTest::gtest 
    GTest::gtest_main
    ${CMAKE_THREAD_LIBS_INIT}
)

add_test(NAME StudentasTest COMMAND run_tests)