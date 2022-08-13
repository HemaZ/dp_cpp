project(DesignPatterns_CPP)
cmake_minimum_required(VERSION 3.16)

option(CREATIONAL "Build CREATIONAL Design patterns." ON)
option(BEHAVIORAL "Build BEHAVIORAL Design patterns." ON)
option(STRUCTURAL "Build STRUCTURAL Design patterns." ON)

if(CREATIONAL)
    message(STATUS "Building Creational Patterns")
    add_subdirectory(Creational)
endif(CREATIONAL)

if(BEHAVIORAL)
    message(STATUS "Building Behavioral Patterns")
    add_subdirectory(Behavioral)
endif(BEHAVIORAL)

if(STRUCTURAL)
    message(STATUS "Building Structural Patterns")
    add_subdirectory(Structural)
endif(STRUCTURAL)