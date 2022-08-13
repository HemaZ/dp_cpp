project(DesignPatterns_CPP)

option(CREATIONAL "Build CREATIONAL Design patterns." ON)
option(BEHAVIORAL "Build BEHAVIORAL Design patterns." ON)
option(STRUCTURAL "Build STRUCTURAL Design patterns." ON)

if(CREATIONAL)
    add_subdirectory(Creational)
endif(CREATIONAL)

if(BEHAVIORAL)
    add_subdirectory(Behavioral)
endif(BEHAVIORAL)

if(STRUCTURAL)
    add_subdirectory(Structural)
endif(STRUCTURAL)