cmake_minimum_required(VERSION 3.23)
project(Ex1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Ex1 main.c pattern_matching.h slist.h pattern_matching.c slist.c)
