cmake_minimum_required(VERSION 3.10)
project(HoverbotMods)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Modify this path to point to your main project's include/ folder
include_directories(../include)

# Find all .cpp files in this directory and build each as a .so
file(GLOB MOD_SOURCES "*.cpp")

foreach(mod_src ${MOD_SOURCES})
    # Get the filename without path and extension
    get_filename_component(mod_name ${mod_src} NAME_WE)

    # Create shared library
    add_library(${mod_name} SHARED ${mod_src})

    # Optionally set output file name to lib<mod_name>.so
    set_target_properties(${mod_name} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/mods
        PREFIX "lib"
    )
endforeach()
