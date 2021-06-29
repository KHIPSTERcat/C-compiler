cmake_minimum_required(VERSION 3.15)
project(C-compiler)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(--coverage)
link_libraries(gcov)

include_directories("Reader/" "Reader/test" "Core/")

set(READER_SOURCE Reader/code_reader.h)
set(CORE_SOURCE Core/compiler.cpp)

add_library(CatchLib Catch/catch.h Catch/catch.cpp)
add_library(ReaderLib Reader/code_reader.cpp Reader/code_reader.h)
add_library(TokenLib Lexer/Token/lexer_token.cpp Lexer/Token/lexer_token.h)

add_executable(C-compiler Core/compiler.cpp)

add_executable(ReaderTest Reader/test/reader_test.cpp)
target_link_libraries(ReaderTest ReaderLib CatchLib)

add_executable(TokenTest Lexer/Token/Test/token_test.cpp)
target_link_libraries(TokenTest TokenLib CatchLib)


