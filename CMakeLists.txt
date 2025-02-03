# Generated CMake Pico project file

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
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(U4C4O12T_Tarefa_WLS C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable
add_executable(U4C4O12T_Tarefa_WLS U4C4O12T_Tarefa_WLS.c)

pico_set_program_name(U4C4O12T_Tarefa_WLS "U4C4O12T_Tarefa_WLS")
pico_set_program_version(U4C4O12T_Tarefa_WLS "0.1")

# Criar diretório para arquivos gerados
file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/output)

# Gerar cabeçalho a partir do U4C4O12T_Tarefa_WLS.pio
pico_generate_pio_header(U4C4O12T_Tarefa_WLS ${CMAKE_CURRENT_LIST_DIR}/U4C4O12T_Tarefa_WLS.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/output)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(U4C4O12T_Tarefa_WLS 1)
pico_enable_stdio_usb(U4C4O12T_Tarefa_WLS 0)

# Add the standard library to the build
target_link_libraries(U4C4O12T_Tarefa_WLS PRIVATE
        pico_stdlib 
        hardware_pio
)

# Adicionar diretórios de inclusão
target_include_directories(U4C4O12T_Tarefa_WLS PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/output
)

# Adicionar os arquivos de código necessários
target_sources(U4C4O12T_Tarefa_WLS PRIVATE 
    U4C4O12T_Tarefa_WLS.c
)

# Adicionar saída extra (bin, uf2, hex)
pico_add_extra_outputs(U4C4O12T_Tarefa_WLS)
