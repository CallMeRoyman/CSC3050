cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_COMPILER "g++")
project(project_1 CXX)
set(MIPS main.cpp LabelTable.cpp phase1.cpp phase2.cpp)
add_executable(assembler ${MIPS})

set(tester Tester.cpp LabelTable.cpp phase1.cpp phase2.cpp)
add_executable(tester ${tester})
