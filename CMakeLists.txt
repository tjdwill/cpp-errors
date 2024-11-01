cmake_minimum_required(VERSION 3.20)
project(cpperrors)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(BUILD_SHARED_LIBS "Build using Shared Libraries" ON)
find_package(cpptrace)


add_library(cpperrors src/exception.cpp src/exception.hpp)
target_link_libraries(cpperrors PUBLIC cpptrace::cpptrace)

add_executable(TestExcept tests/exception.t.cpp)
target_link_libraries(TestExcept PRIVATE cpperrors)
add_test(NAME general_exception COMMAND TestExcept)

add_executable(TestTyped tests/typederr.t.cpp)
target_link_libraries(TestTyped PRIVATE cpperrors)
add_test(NAME typed_exception COMMAND TestTyped)
