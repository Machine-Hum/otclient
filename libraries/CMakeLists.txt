add_subdirectory(fc)
add_subdirectory(chain)
add_subdirectory(chainbase)

# add_subdirectory(version)

add_library(
    test_lib
    test_lib/test.cpp
    test_lib/test.h
)

target_include_directories(test_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
