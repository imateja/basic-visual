cmake_minimum_required(VERSION 3.5)

project(ast) 

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

find_package(LLVM 12 REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(PROJECT_SOURCES
       src/ast.cpp
       src/state.cpp
       src/interpret.cpp
       src/compile.cpp
       src/exprtree.cpp
       src/serializer.cpp
)

set(PROJECT_HEADERS
       inc/ast.hpp
       inc/state.hpp
       inc/interpret.hpp
       inc/compile.hpp
       inc/exprtree.hpp
       inc/serializable.hpp
       inc/serializer.hpp
)


add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS})


set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${PROJECT_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC inc)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Widgets LLVM)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION lib/${PROJECT_NAME})
