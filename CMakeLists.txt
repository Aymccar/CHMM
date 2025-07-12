cmake_minimum_required(VERSION 3.9)

project(CHMM)

# Create the CHMM library
add_library(chmm
    src/CHMM.cpp
    src/State.cpp
)

# Create the test executable
add_executable(chmm_test
    src/main.cpp
)

# Link the library to the executable
target_link_libraries(chmm_test
    PRIVATE chmm
)

# Set include directories
target_include_directories(chmm
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(chmm_test
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

