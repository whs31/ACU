cmake_minimum_required(VERSION 3.15)

project(Cogwheel LANGUAGES CXX)

if(TARGET ${PROJECT_NAME})
    return()
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

include_directories(src/c++ include)
file(GLOB_RECURSE COGWHEEL_CORE src/c++/*)
file(GLOB_RECURSE COGWHEEL_CORE_INCLUDE include/*)
set(SRC ${COGWHEEL_CORE} ${COGWHEEL_CORE_INCLUDE})

add_library(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_include_directories(${PROJECT_NAME} PUBLIC include src)