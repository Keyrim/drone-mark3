cmake_minimum_required(VERSION 3.25)

# Setup compiler settings
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(PROJ_PATH                       ${CMAKE_CURRENT_SOURCE_DIR})
message("Build type: "              ${CMAKE_BUILD_TYPE})

# Try to include a local configuration file
# This file can be used to override some settings for a development environment
# It should not be included in the repository
include(${PROJ_PATH}/local_config.cmake OPTIONAL)

# Core project settings
project(mark3
    # VERSION 0.1 TODO(tmagne) do this properly using ??
    LANGUAGES C CXX ASM
)

# Define some variables to be used in the project
set(EXECUTABLE mark3_app)

# Include every subdirectory
include (${PROJ_PATH}/cubeide/CMakeLists.txt)
include (${PROJ_PATH}/lib/CMakeLists.txt)
include (${PROJ_PATH}/bsp/CMakeLists.txt)
include (${PROJ_PATH}/src/CMakeLists.txt)


# Compiler flag for ou app
LIST(APPEND C_FLAGS
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    -Werror
)

# Linker flags for ou app
LIST(APPEND LD_FLAGS
    --specs=nosys.specs
    -u _printf_float
    -Wl,--start-group
    -lc
    -lm
    -Wl,--end-group
    -Wl,--print-memory-usage
)

# Create an executable target and configure it
add_executable(${EXECUTABLE} ${SRCS_FILES})
target_include_directories(${EXECUTABLE} PRIVATE
    ${INCLUDE_PATH_DIRS}
)
target_compile_definitions(${EXECUTABLE} PRIVATE
    ${SYMBOLS}
)
target_compile_options(${EXECUTABLE} PRIVATE
    ${C_FLAGS}
    ${CPU_PARAMETERS}
)
target_link_options(${EXECUTABLE} PRIVATE
    ${LD_FLAGS}
    ${CPU_PARAMETERS}
    -T${LINKER_SCRIPT_SRC}
    -Wl,-Map=${EXECUTABLE}.map
)

# Execute post-build to print size
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
)

# Convert output to hex and binary
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
)

# Convert to bin file -> add conditional check?
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin
)
