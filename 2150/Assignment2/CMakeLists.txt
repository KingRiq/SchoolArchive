cmake_minimum_required(VERSION 3.16)
project(Assignment2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Assignment2 A2main.cpp EndAssembly.h EndAssembly.cpp Event.h Event.cpp ListItem.cpp ListItem.h Node.cpp Node.h OrderedItem.cpp OrderedItem.h ProductArrival.cpp ProductArrival.h PartArrival.cpp PartArrival.h PriorityQueue.cpp PriorityQueue.h Queue.cpp Simulation.cpp Simulation.h StartAssembly.cpp)
file(GLOB SOURCES
        *.h
        *.cpp
        )