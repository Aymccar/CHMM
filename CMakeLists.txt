cmake_minimum_required(VERSION 3.9)

project(CHMM)

set(CMAKE_CXX_FLAGS "-O3")
find_package(Eigen3 REQUIRED)

add_library(chmm
    src/CHMM.cpp
    src/State.cpp
)
target_include_directories(chmm
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(probably
    src/probably.cpp
)
target_link_libraries(probably
    PRIVATE Eigen3::Eigen
)
target_include_directories(probably
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (BUILD_EXAMPLE)
    add_executable(chmm_test
        src/main.cpp
    )
    target_link_libraries(chmm_test
        PRIVATE chmm
        PRIVATE probably
        PRIVATE Eigen3::Eigen
    )
    target_include_directories(chmm_test
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endif()
