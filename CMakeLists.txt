cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Minimal_SAI)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
        Core/Src/audio.c
#        Core/Src/console.c
#        Core/Src/consoleCommands.c
#        Core/Src/consoleIo.c
#        Core/Src/usart.c
        Core/Src/oscillators.c
        Core/Src/help_func.c
        Core/Src/lcd.c
        Core/Src/usart.c


        #        Utilities/Fonts/font8.c
#        Utilities/Fonts/font12.c
#        Utilities/Fonts/font16.c
#        Utilities/Fonts/font20.c
#        Utilities/Fonts/font24.c
        #        Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.c
#        Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.c
#        Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.c

)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.c
    Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.c
    Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_sdram.c
    Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_lcd.c
    Drivers/BSP/Components/wm8994/wm8994.c
    Drivers/BSP/Components/otm8009a/otm8009a.c
    Drivers/BSP/Components/adv7533/adv7533.c
    Drivers/BSP/Components/nt35510/nt35510.c
    # Utilities/Fonts
    #Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dfsdm.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    Drivers/BSP/STM32F769I-Discovery
    Drivers/BSP/Components/wm8994
    Drivers/BSP/Components/adv7533
    Drivers/BSP/Components/otm8009a
    Drivers/BSP/Components/nt35510
    Drivers/CMSIS/Include
    Drivers/CMSIS/Core/Include
    Drivers/CMSIS/DSP/Include Drivers/CMSIS/Device/ST/STM32F7xx/Include
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
