cmake_minimum_required(VERSION 3.16)
project(C-compiler)

set(CMAKE_CXX_STANDARD 17)

include_directories("Reader/" "Core/")

set(READER_SOURCE Reader/code_reader.h)
set(CORE_SOURCE Core/compiler.cpp)

add_library(CatchLib Catch/catch.h Catch/catch.cpp)
add_library(ReaderLib Reader/code_reader.cpp Reader/code_reader.h)

add_executable(C-compiler Core/compiler.cpp)

add_executable(ReaderTest Reader/test/ReaderTest.cpp)
target_link_libraries(ReaderTest ReaderLib)


set(TEST_TARGETS
        ReaderTest
)

target_link_libraries(${TEST_TARGETS} CatchLib)