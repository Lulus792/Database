cmake_minimum_required(VERSION 3.20)

project(Database VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "~/Qt/6.6.3/gcc_64/lib/cmake/")

if (CMAKE_CXX_COMPILER)
  add_compile_options(
    -Wall 
    -Wextra 
    -Werror 
    -Wpedantic 
    -pedantic 
    -pedantic-errors)
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
qt_standard_project_setup()

set(SOURCES
 code/main.cpp
 code/window/window.cpp
 code/menu/menu.cpp
 code/file/file_handling.cpp
 code/handleSql/handleSql.cpp
 code/handleSql/lexer/lexer.cpp
 code/handleSql/parser/parser.cpp
 code/error/error.cpp
 ../si_language/code/stringFunction.cc
)

set (HEADERS
  code/window/window.h
  code/menu/menu.h
  code/file/file_handling.h
  code/header.h
  code/handleSql/handleSql.h
  code/handleSql/lexer/lexer.h
  code/handleSql/parser/parser.h
  code/handleSql/sql.h
  code/error/error.h
  ../si_language/code/stringFunction.h
)

qt_add_executable(Database ${SOURCES} ${HEADERS})

target_link_libraries(Database PRIVATE Qt6::Widgets Qt6::Core)
