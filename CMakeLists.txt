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

find_package(LLVM 12 QUIET CONFIG)

if(LLVM_FOUND)
    message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
    message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

    include_directories(${LLVM_INCLUDE_DIRS})
    add_definitions(${LLVM_DEFINITIONS})
else()
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
    include_directories(llvm-core_INCLUDE_DIRS)
endif()

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

target_include_directories(${PROJECT_NAME} PUBLIC ast/inc basicVisual/inc)