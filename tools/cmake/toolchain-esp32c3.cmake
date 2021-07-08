set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER ${ZEPHYR_CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${ZEPHYR_CMAKE_CXX_COMPILER})
set(CMAKE_ASM_COMPILER ${ZEPHYR_CMAKE_ASM_COMPILER})

set(CMAKE_C_FLAGS "-march=rv32imc" CACHE STRING "C Compiler Base Flags")
set(CMAKE_CXX_FLAGS "-march=rv32imc" CACHE STRING "C++ Compiler Base Flags")
set(CMAKE_EXE_LINKER_FLAGS "-nostartfiles -march=rv32imc --specs=nosys.specs" CACHE STRING "Linker Base Flags")