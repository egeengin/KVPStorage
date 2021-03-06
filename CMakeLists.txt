cmake_minimum_required(VERSION 3.14)
include(FetchContent)

project(KVPStorage)

# C++17 so can work with C++20
set(CMAKE_CXX_STANDARD 17)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
        SOURCE_DIR "../lib/googletest/"
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(src lib/nlohmann )
include_directories(lib/googletest/googletest/include/ lib/googletest/googletest/)

# set(DCMAKE_BUILD_TYPE,Debug)

add_subdirectory(src)
add_subdirectory(tst)
#add_subdirectory(lib/googletest)

set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING "Build options: Debug Release Coverage." FORCE)

# Use generator expression to enable flags for the Coverage profile
# target_compile_options(KVPStorage PUBLIC "--coverage")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")