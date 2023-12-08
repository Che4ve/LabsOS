cmake_minimum_required(VERSION 3.27.5)
project(lab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

# Create the shared library
add_library(dlexp SHARED ./src/dlexp.cpp)
add_library(dlsort SHARED ./src/dlsort.cpp)

add_library(libexp ./src/dlexp.cpp)

# Create the executable
add_executable(prog1 prog1.cpp)
add_executable(prog2 prog2.cpp)

# Link the executable with the library
target_link_libraries(prog1 libexp)

install(TARGETS dlexp DESTINATION lib)
install(TARGETS dlsort DESTINATION lib)

# cmake -DCMAKE_INSTALL_PREFIX=$(PWD)/.. .