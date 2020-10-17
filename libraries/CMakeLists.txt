add_subdirectory(appbase)
add_subdirectory(berkeley-softfloat-3)
add_subdirectory(builtins)
add_subdirectory(chain)
add_subdirectory(chainbase)
add_subdirectory(eos-vm)
add_subdirectory(fc)
add_subdirectory(testing)
add_subdirectory(version)
add_subdirectory(wabt)
add_subdirectory(wasm-jit)
add_subdirectory(yubihsm-shell)

add_library(
    test_lib
    test_lib/test.cpp
    test_lib/test.h
)

target_include_directories(test_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
