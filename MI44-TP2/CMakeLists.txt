cmake_minimum_required(VERSION 2.8.8)

project(MI44-RSA)

set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDES})

add_definitions(${Qt5Widgets_INCLUDES})

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

file(GLOB_RECURSE src src/*)
add_executable(MI44-RSA ${src})

QT5_USE_MODULES(MI44-RSA Widgets)