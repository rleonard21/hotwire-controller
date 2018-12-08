cmake_minimum_required(VERSION 3.12)

project(hotwire_controller)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

set(AVR_MCU "atmega328p")
set(AVR_SPEED "16000000")
set(AVR_OPT "s")

add_definitions("-fno-exceptions")

add_definitions("-mmcu=${AVR_MCU}")
add_definitions("-DF_CPU=${AVR_SPEED}")
add_definitions("-O${AVR_OPT}")

message("")
message("AVR-GCC OPTIONS ENABLED:")
message("    Target MCU: ${AVR_MCU}")
message("    MCU Speed: ${AVR_SPEED}Hz")
message("    Optimization: -O${AVR_OPT}")
message("")

include_directories(.)
include_directories(feedback)
include_directories(gpio)
include_directories(i2c)
include_directories(lcd)
include_directories(pwm)
include_directories(sensors)

add_executable(hotwire_controller
        main.c
        gpio/gpio.c
        )
