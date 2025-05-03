# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(U1-05-teste_un_temp C CXX ASM)

pico_sdk_init()

add_executable(main_executable
        app/main.c
        drivers/rp2040_temp_sensor.c
        hal/hal_rp2040_temp.c
        )

        target_link_libraries(main_executable
        pico_stdlib 
        pico_cyw43_arch_none 
        hardware_adc
        )

target_include_directories(main_executable PRIVATE include)

# configure serial communication
pico_enable_stdio_uart(main_executable 0)
pico_enable_stdio_usb(main_executable 1) 

# generate map/bin/hex files
pico_add_extra_outputs(main_executable)

# unit test executable for temperature measurement
add_executable(unit_test_executable
        test/test_rp2040_temp.c
        drivers/rp2040_temp_sensor.c
        hal/hal_rp2040_temp.c
        include/Unity/unity.c
        )

target_link_libraries(unit_test_executable
        pico_stdlib 
        pico_cyw43_arch_none  
        hardware_adc
        )

# add include directories
target_include_directories(unit_test_executable PRIVATE include)

# configure serial communication
pico_enable_stdio_uart(unit_test_executable 0) 
pico_enable_stdio_usb(unit_test_executable 1) 

# generate map/bin/hex files
pico_add_extra_outputs(unit_test_executable)