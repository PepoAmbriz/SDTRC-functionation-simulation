cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all) #Este es para visulizar

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc) 
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh) 

add_executable(sim sim.cc ${sources} ${headers}) #Creacion del ejecutable
target_link_libraries(sim ${Geant4_LIBRARIES}) #Para que encuentre las librerias

add_custom_target(Simulation DEPENDS sim)
