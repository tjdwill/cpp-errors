cmake_minimum_required(VERSION 3.20)
project(cpperror)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cpptrace REQUIRED)

set(SOURCES src/exception.cpp src/exception.hpp)

add_library(cpperrors SHARED ${SOURCES})
target_link_libraries(cpperrors cpptrace::cpptrace)

add_executable(generr
    tests/exception.t.cpp
    ${SOURCES}
)
target_link_libraries(generr cpperrors)

add_executable(typederr
    tests/typederr.t.cpp
    ${SOURCES}
)
target_link_libraries(typederr cpperrors)
