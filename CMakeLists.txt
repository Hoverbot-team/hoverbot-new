cmake_minimum_required(VERSION 3.10)

project(Hoverbot)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
find_package(OpenCV REQUIRED)

set(SOURCES
    src/main.cpp
    src/sensors/gyro.cpp
    src/movement/engines.cpp
    src/movement/PID.cpp
    src/modules/codePlugins/loader.cpp
    src/movement/movement.cpp
    src/misc/logs/log.cpp
    src/interfaces/OLED/SSD1306.cpp
    src/interfaces/UART/UART.cpp
)

add_executable(Hoverbot ${SOURCES})
target_link_libraries(Hoverbot wiringPi ${OpenCV_LIBS})

