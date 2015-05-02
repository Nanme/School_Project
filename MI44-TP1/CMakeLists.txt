cmake_minimum_required()

project(MI44_Feistel)

file(GLOB_RECURSE src src/*)

add_executable(MI44_Feistel ${src})

