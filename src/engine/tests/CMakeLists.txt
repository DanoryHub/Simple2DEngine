add_executable(
        unit_tests
        Vector/Vector_test.cpp
        GameObject/GameObject_test.cpp
        GameScene/GameScene_test.cpp
        Placeable/Placeable_test.cpp
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