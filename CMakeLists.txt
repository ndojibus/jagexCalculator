cmake_minimum_required(VERSION 3.0)
project(JagexCalculatorTest)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
add_library(Calculator src/Calculator.hpp src/Calculator.cpp)
add_executable(Main main/main.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(Main Calculator)

set (gtest_force_shared_crt ON CACHE BOOL "MSVC defaults to shared CRT" FORCE)
add_subdirectory(third_party/googletest)
target_compile_definitions(gtest
  PUBLIC
    GTEST_LANG_CXX20
    GTEST_HAS_TR1_TUPLE=0
)
add_executable(CalculatorTest)
target_sources(CalculatorTest
  PRIVATE
    test/calculatorTests.cpp
)
set_target_properties(CalculatorTest PROPERTIES COMPILE_FLAGS "${cxx_strict}")
target_link_libraries(CalculatorTest gtest gtest_main Calculator)