cmake_minimum_required(VERSION 3.25)
project(Yadro2___)

set(CMAKE_CXX_STANDARD 20)

add_executable(Yadro2___ main.cpp tape.cpp tape.h config.hpp config.cpp yadroException.hpp sort.cpp sort.h reader_writer.cpp reader_writer.h)
