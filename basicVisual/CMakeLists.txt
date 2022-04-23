cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
       src/main.cpp
       src/mainwindow.cpp
       src/maingraphicsscene.cpp
       src/pseudoterminal.cpp
       src/mainwindow.ui
       src/pseudoterminal.ui
)

set(PROJECT_HEADERS
       inc/mainwindow.hpp
       inc/maingraphicsscene.hpp
       inc/pseudoterminal.hpp
)

add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ast)

