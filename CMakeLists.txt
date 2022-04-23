cmake_minimum_required(VERSION 3.5)

project(basicVisual VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -O0 -g -Wno-reorder -Wno-unused-parameter -Wno-comment")
    message("-- Debug build.")
elseif(CMAKE_BUILD_TYPE MATCHES Test)
    set(CMAKE_CXX_FLAGS_RELEASE "-O0 -g -Wno-reorder -Wno-unused-parameter -Wno-comment")
    message("-- Test build.")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wno-reorder -Wno-unused-parameter -Wno-comment")
    message("-- Release build.")
else()
    message("-- Some unknown build type.")
endif()


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

find_package(LLVM 12 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_subdirectory(ast)

if(NOT CMAKE_BUILD_TYPE MATCHES Test)
    add_subdirectory(basicVisual)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES Test)
    add_subdirectory(tests)
endif()
