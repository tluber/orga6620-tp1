cmake_minimum_required(VERSION 3.14)
project(orga6620_tp1 C)

set(CMAKE_C_STANDARD 99)

add_executable(orga6620_tp1 src/ant_engine.c includes/ant_engine.h src/artist_ant.c includes/artist_ant.h includes/ant_constants.h)

file(GLOB SOURCES
        *.h
        *.cpp
        )