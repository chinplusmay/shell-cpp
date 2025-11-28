cmake_minimum_required(VERSION 3.13)

project(shell-starter-cpp)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

add_executable(shell ${SOURCE_FILES})

# Find and link readline library
find_library(READLINE_LIBRARY NAMES readline)
if(READLINE_LIBRARY)
    target_link_libraries(shell PRIVATE ${READLINE_LIBRARY})
else()
    message(WARNING "readline library not found, building without it")
endif()
