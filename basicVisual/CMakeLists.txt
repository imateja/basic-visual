cmake_minimum_required(VERSION 3.5)

project(basicVisual VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES llvm-core/12.0.0
                      GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})

find_package(llvm-core)

set(PROJECT_SOURCES
        src/mainwindow.ui
        src/instructiondialog.ui
        src/main.cpp
        src/mainwindow.cpp
        src/maingraphicsscene.cpp
        src/instructioncontainer.cpp
        src/instruction.cpp
        src/instructiondialog.cpp
        src/ast.cpp
        src/state.cpp
        src/interpret.cpp
        src/exprtree.cpp
        #src/serializable.cpp
        src/serializer.cpp
        #tests/test_ast.cpp
)

set(PROJECT_HEADERS
        inc/mainwindow.h
        inc/maingraphicsscene.hpp
        inc/instructioncontainer.h
        inc/instruction.h
        inc/instructiondialog.h
        inc/ast.h
        inc/state.h
        inc/interpret.h
        inc/exprtree.h
        inc/serializable.h
        inc/serializer.h
        tests/catch.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(basicVisual
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET basicVisual APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(basicVisual SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(basicVisual
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
        )
    endif()
endif()

target_link_libraries(basicVisual PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(basicVisual PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(basicVisual)
endif()
