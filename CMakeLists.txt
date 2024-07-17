cmake_minimum_required(VERSION 3.10)

project(CppMySQLApp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the path to SQLite3 include and library directories
set(SQLITE3_INCLUDE_DIR "C:/Program Files/sqlite")
set(SQLITE3_LIBRARY "C:/Program Files/sqlite/sqlite3.lib")

# Include directories
include_directories(${SQLITE3_INCLUDE_DIR})

# Add the source files
add_executable(CppMySQLApp src/main.cpp)

# Link the SQLite3 library
target_link_libraries(CppMySQLApp ${SQLITE3_LIBRARY})
