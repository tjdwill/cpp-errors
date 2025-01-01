cmake_minimum_required(VERSION 3.20)
project(cpperrors
    VERSION 0.1.0
    DESCRIPTION "A convenient general exception for C++"
    HOMEPAGE_URL "https://github.com/tjdwill/cpp-errors"
    LANGUAGES CXX
)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#option(BUILD_SHARED_LIBS "Build using Shared Libraries" ON)
include(FetchContent)
FetchContent_Declare(
  cpptrace
  GIT_REPOSITORY    https://github.com/jeremy-rifkin/cpptrace.git
  GIT_TAG           4354eb21ea3565a73afdf32ec0ba768fd648c425)
FetchContent_MakeAvailable(cpptrace)

add_library(cpperrors src/exception.cpp src/exception.hpp)
target_link_libraries(cpperrors PUBLIC cpptrace::cpptrace)

add_executable(TestExcept tests/exception.t.cpp)
target_link_libraries(TestExcept PRIVATE cpperrors)
add_test(NAME general_exception COMMAND TestExcept)

add_executable(TestTyped tests/typederr.t.cpp)
target_link_libraries(TestTyped PRIVATE cpperrors)
add_test(NAME typed_exception COMMAND TestTyped)
