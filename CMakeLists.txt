cmake_minimum_required(VERSION 3.10)

project(Hoverbot)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for your custom SSD1306 implementation
include_directories(include)

set(SOURCES
    src/main.cpp
    src/sensors/gyro.cpp
    src/uart.cpp
    # Add other source files here
)

# Link the bcm2835 library
add_executable(Hoverbot ${SOURCES})
target_link_libraries(Hoverbot wiringPi)
