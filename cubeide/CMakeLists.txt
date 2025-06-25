set(CUBE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(CUBE_CORE_DIR ${CUBE_DIR}/Core)
set(CUBE_DRIVERS_DIR ${CUBE_DIR}/Drivers)

# Include the core and drivers directories
set(INCLUDE_PATH_DIRS
    ${INCLUDE_PATH_DIRS}
    ${CUBE_CORE_DIR}/Inc
    ${CUBE_DRIVERS_DIR}/STM32F4XX_HAL_Driver/Inc
    ${CUBE_DRIVERS_DIR}/STM32F4XX_HAL_Driver/Inc/Legacy
    ${CUBE_DRIVERS_DIR}/CMSIS/Device/ST/STM32F4XX/Include
    ${CUBE_DRIVERS_DIR}/CMSIS/Include
)

# Add the core and drivers source files
file(GLOB_RECURSE
    CUBE_CORE_FILES
    ${CUBE_CORE_DIR}/Src/*.c
)
file(GLOB_RECURSE
    CUBE_DRIVERS_FILES
    ${CUBE_DRIVERS_DIR}/STM32F4XX_HAL_Driver/Src/*.c
)
set(SRCS_FILES
    ${SRCS_FILES}
    ${CUBE_CORE_FILES}
    ${CUBE_DRIVERS_FILES}
    ${CUBE_CORE_DIR}/Startup/startup_stm32f405rgtx.s
)

# Set some CPU specific compiler and linker flags
# Core MCU flags, CPU, instruction set and FPU setup
# Needs to be set properly for your MCU
set(CPU_PARAMETERS
    -mthumb
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

LIST(APPEND SYMBOLS
    # Symbols definition needed by the HAL
    "DEBUG"
    "USE_HAL_DRIVER"
    "STM32F405xx"
    # Symbol used in the main.c and it.c files to enable use "non cube ide" code
    "USE_NON_CUBEIDE_CODE"
)

# Add the linker script and startup file
set(LINKER_SCRIPT_SRC ${CUBE_DIR}/STM32F405RGTX_FLASH.ld)
