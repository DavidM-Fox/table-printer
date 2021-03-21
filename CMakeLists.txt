cmake_minimum_required(VERSION 3.0.0)

project(table-printer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt CONFIG REQUIRED)

include_directories(include)
set(SRC_DIR src)
set(INC_DIR include)

set(PROJECT_SOURCES
		"src/main.cpp"
		"include/TablePrinter.hpp")

add_executable(table-printer ${PROJECT_SOURCES})
target_link_libraries(table-printer PRIVATE fmt::fmt)
