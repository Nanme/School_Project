cmake_minimum_required(VERSION 2.8.8)

project(MI44_RSA)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(CMAKE_INCLUDE_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

include_directories(${Qt5Widgets_INLCUDES})

add_definitions(${Qt5Widgets_INLCUDES})

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

file(GLOB_RECURSE src src/*)

add_executable(MI44_RSA ${src})

QT5_USE_MODULES(MI44_RSA Widgets)

