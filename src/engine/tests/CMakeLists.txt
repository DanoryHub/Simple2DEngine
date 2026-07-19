add_executable(
        unit_tests
        Vector/vector_test.cpp
)

target_link_libraries(
        unit_tests
        PRIVATE
        gtest
        gtest_main
        Engine
)

include(GoogleTest)
gtest_discover_tests(unit_tests)