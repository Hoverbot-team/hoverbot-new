cmake_minimum_required(VERSION 3.10)

project(Hoverbot)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/sensors/gyro.cpp
    src/uart.cpp
)

add_executable(Hoverbot ${SOURCES})
target_link_libraries(Hoverbot wiringPi)
