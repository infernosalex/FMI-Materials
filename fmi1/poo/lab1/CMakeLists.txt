cmake_minimum_required(VERSION 3.30)
project(tema_poo)

set(CMAKE_CXX_STANDARD 20)

# Download and configure Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add compiler flags for better debugging and warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Main executable (without tests)
add_executable(tema_poo
    main.cpp
    vector_tests.cpp
    polynomial_tests.cpp
    polynomial.cpp
)

# Test executable with Google Test
add_executable(tests
    polynomial.cpp
    test_hw3.cpp
)

# Link Google Test to the test executable
target_link_libraries(tests
    gtest
    gtest_main
    pthread
)

# Include Google Test in the project
include(GoogleTest)
gtest_discover_tests(tests)

# Optional: Add custom target for running tests
add_custom_target(run_tests
    COMMAND tests
    DEPENDS tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running Google Tests"
)
