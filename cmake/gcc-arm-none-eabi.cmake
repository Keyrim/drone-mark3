set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

# Let's assume the ARM toolchain is available in the PATH and comment out the following lines...
# if (NOT DEFINED ENV{ARM_TOOLCHAIN_DIR})
#     message(FATAL_ERROR "Please set the ARM_TOOLCHAIN_DIR environment variable to the path of your ARM toolchain.")
# else()
#     message(STATUS "ARM_TOOLCHAIN_DIR: " $ENV{ARM_TOOLCHAIN_DIR})
#     set(ARM_TOOLCHAIN_DIR             $ENV{ARM_TOOLCHAIN_DIR})
# endif()

# Some default GCC settings
set(TOOLCHAIN_PREFIX                arm-none-eabi-)
set(FLAGS                           "-fdata-sections -ffunction-sections --specs=nano.specs -Wl,--gc-sections")
set(CPP_FLAGS                       "-fno-rtti -fno-exceptions -fno-threadsafe-statics")

# Define compiler settings
set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc ${FLAGS})
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++ ${FLAGS} ${CPP_FLAGS})
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
