cmake_minimum_required(VERSION 3.5)
project(test)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_SOURCES
            test_ast.cpp
            main.cpp)
            
set(PROJECT_HEADERS 
            catch.hpp)

add_executable(${PROJECT_NAME}
               ${PROJECT_SOURCES}
               ${PROJECT_HEADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ast)
