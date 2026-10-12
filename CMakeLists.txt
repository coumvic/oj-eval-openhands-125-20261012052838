cmake_minimum_required(VERSION 3.10)
project(Debugger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(code solution.cpp)

# Set optimization flags
set_target_properties(code PROPERTIES
    CXX_FLAGS_RELEASE "-O3 -DNDEBUG"
    CXX_FLAGS_DEBUG "-g -O0"
)

# Use release build by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()