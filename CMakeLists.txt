cmake_minimum_required(VERSION 3.5)

project(basicVisual VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

find_package(LLVM 12 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(PROJECT_SOURCES
        basicVisual/src/mainwindow.ui
        basicVisual/src/pseudoterminal.ui
        basicVisual/src/main.cpp
        basicVisual/src/mainwindow.cpp
        basicVisual/src/maingraphicsscene.cpp
        basicVisual/src/pseudoterminal.cpp
        ast/src/ast.cpp
        ast/src/state.cpp
        ast/src/interpret.cpp
        ast/src/compile.cpp
        ast/src/exprtree.cpp
        ast/src/serializer.cpp
        #tests/test_ast.cpp
		#tests/catch.cpp
)

set(PROJECT_HEADERS
        basicVisual/inc/mainwindow.hpp
        basicVisual/inc/maingraphicsscene.hpp
        basicVisual/inc/pseudoterminal.hpp
        ast/inc/ast.hpp
        ast/inc/state.hpp
        ast/inc/interpret.hpp
        ast/inc/compile.hpp
        ast/inc/exprtree.hpp
        ast/inc/serializable.hpp
        ast/inc/serializer.hpp
        #tests/catch.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(basicVisual
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
endif()

target_link_libraries(basicVisual PRIVATE Qt${QT_VERSION_MAJOR}::Widgets LLVM)

set_target_properties(basicVisual PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(basicVisual)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ast/inc basicVisual/inc)
