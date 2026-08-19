cmake_minimum_required(VERSION 3.20)

project(PlutoniumRecursion
    VERSION 0.1.0
    DESCRIPTION "A browser engine written in C++ and designed to run through WebAssembly"
    LANGUAGES CXX
)

# ---------------------------------------------------------
# C++ Configuration
# ---------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------
# Recursion Engine
# ---------------------------------------------------------

add_library(recursion_engine STATIC

    # HTML
    src/html/node.cpp
    src/html/parser.cpp

    # CSS Core
    src/css/parser.cpp
    src/css/core/declaration.cpp
    src/css/core/selector.cpp
    src/css/core/rule.cpp
    src/css/core/stylesheet.cpp

    # CSS Layout
    src/css/layout/computed_style.cpp
    src/css/layout/box.cpp
)

# ---------------------------------------------------------
# Include Directories
# ---------------------------------------------------------

target_include_directories(recursion_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/html
        ${CMAKE_CURRENT_SOURCE_DIR}/src/css
        ${CMAKE_CURRENT_SOURCE_DIR}/src/css/core
        ${CMAKE_CURRENT_SOURCE_DIR}/src/css/layout
)

# ---------------------------------------------------------
# Compiler Warnings
# ---------------------------------------------------------

if(MSVC)

    target_compile_options(
        recursion_engine
        PRIVATE
            /W4
    )

else()

    target_compile_options(
        recursion_engine
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )

endif()