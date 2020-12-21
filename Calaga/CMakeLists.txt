cmake_minimum_required(VERSION 3.16.5)
project(Calaga C)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(Calaga main.c jogo.c jogo.h usuarios.c usuarios.h)
target_link_libraries(Calaga ${CURSES_LIBRARIES})