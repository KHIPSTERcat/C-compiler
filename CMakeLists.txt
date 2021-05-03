cmake_minimum_required(VERSION 3.16)
project(C-compiler)

set(CMAKE_CXX_STANDARD 17)

include_directories("Reader/" "Core/")

set(READER_SOURCE Reader/code_reader.hpp)


add_library(testLib INTERFACE)
target_include_directories(
        testLib
        INTERFACE $<BUILD_INTERFACE:/Libs>
        $<INSTALL_INTERFACE:catch.h>)
target_compile_features(testLib INTERFACE cxx_std_17)

add_library(ReaderLib INTERFACE)
target_include_directories(
        testLib
        INTERFACE $<BUILD_INTERFACE:/Libs>
        $<INSTALL_INTERFACE:${READER_SOURCE}>)
target_compile_features(ReaderLib INTERFACE cxx_std_17)



add_executable(C-compiler Core/compiler.cpp)
target_link_libraries(C-compiler ReaderLib)

add_executable(ReaderTest Reader/test/ReaderTest.cpp)
target_link_libraries(ReaderTest testLib ReaderLib)