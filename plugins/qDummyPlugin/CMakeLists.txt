cmake_minimum_required(VERSION 2.8)

#REPLACE ALL 'DUMMY' OCCURENCES BY YOUR PLUGIN NAME
#AND ADAPT THE CODE BELOW TO YOUR OWN NEEDS!

option( INSTALL_QDUMMY_PLUGIN "Check to install qDUMMY plugin" OFF )

if (INSTALL_QDUMMY_PLUGIN)

#CloudCompare 'DUMMY' plugin
project( QDUMMY_PLUGIN )

#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -Bsymbolic" )

find_package(SPC 0.1.0 REQUIRED)
include_directories(${SPC_INCLUDE_DIRS})
message(${SPC_INCLUDE_DIRS})
link_directories(${SPC_LIBRARY_DIRS})
add_definitions(${SPC_DEFINITIONS})

#load necessary libraries (see qPCV for an example)
#add_subdirectory (LIB1)

#if the plugin is an 'OpenGL filter', uncomment the line below
#set( CC_OPENGL_FILTER ON BOOL)
include( ../CMakePluginTpl.cmake )

#set dependencies to necessary libraries (see qPCV for an example)
#target_link_libraries( ${PROJECT_NAME} ${SPC_LIBRARIES} )
#target_link_libraries( ${PROJECT_NAME} )
#target_link_libraries( ${PROJECT_NAME} QPCL_PLUGIN_UTILS_LIB )

#include_directories( ${LIB1_INCLUDE_DIR} )

endif()
