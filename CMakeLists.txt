# The name of the system under which the assembly is carried out and its version
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

# The minimum version of CMake required to compile the project
cmake_minimum_required(VERSION 3.16)

# Include this file for work with functions components_search, 
# get_all_source_files_of_components etc.
include(${CMAKE_SOURCE_DIR}/component.cmake)

# Include this file for work with functions kconfig_update_configuration, 
# import_kconfig etc.
include(${CMAKE_SOURCE_DIR}/configuration/kconfig.cmake)

# This function run configuration/scripts/kconfig.py for create autoconf.h file
kconfig_update_configuration()

# This function parse the lines prefixed with CONFIG_ in the .config 
# file from Kconfig and makes them available in cmake files
import_kconfig(CONFIG_ ${CMAKE_SOURCE_DIR}/.config)

# Below are the names of compilers and toolchain utilities
# CXX - C++ compiler
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_LD arm-none-eabi-ld)
set(SIZE arm-none-eabi-size)

# Due to the fact that we are building a project for a microcontroller, and not for a host
# need to report this to cmake
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Project name and version, seted via the project configuration menu
project(${CONFIG_PROJECT_NAME} VERSION ${CONFIG_PROJECT_VERSION})

# Languages used
enable_language(ASM)
enable_language(C)

# We use C++ only if support is enabled in the project configuration menu
if(CONFIG_CXX_ON)
    enable_language(CXX)
endif()

# Compiled file extension
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# Configuring the file version.h
configure_file(version.h.in ${CMAKE_SOURCE_DIR}/version.h)

# Get mcu flags, seted via the project configuration menu
kconfig_get_mcu_flags(MCU_FLAGS)

# Get float enable flags, seted via the project configuration menu
kconfig_get_mcu_flags_of_float_for_printf_scanf_enable(MCU_FLOAT_ENABLE_FLAGS)

# Get ASM flags, seted via the project configuration menu
kconfig_get_gcc_assembler_flags(GCC_ASSEMBLER_FLAGS)

# Get C flags, seted via the project configuration menu
kconfig_get_gcc_compiler_flags(GCC_COMPILER_FLAGS)

# Get C++ compiler and linker flags, seted via the project configuration menu,
# only if support is enabled in the project configuration menu
if(CONFIG_CXX_ON)
    kconfig_get_gxx_compiler_flags(GXX_COMPILER_FLAGS)
    kconfig_get_gxx_linker_flags(GXX_LINKER_FLAGS)
else ()
    kconfig_get_gcc_linker_flags(GCC_LINKER_FLAGS)
endif()

# Set ASM flags
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} ${GCC_ASSEMBLER_FLAGS}")

# Set C flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU_FLAGS} ${GCC_COMPILER_FLAGS}")

# Set C++ flags only if support is enabled in the project configuration menu
if(CONFIG_CXX_ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MCU_FLAGS} ${GXX_COMPILER_FLAGS}")
endif()

# Use C++ linker flags only if support is enabled in the project configuration menu
# else use C flags
if(CONFIG_CXX_ON)
    set(LINKER_FLAGS ${GXX_LINKER_FLAGS})
else()
    set(LINKER_FLAGS ${GCC_LINKER_FLAGS})
endif()

# Set executeble linker flags
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} ${LINKER_FLAGS} ${MCU_FLOAT_ENABLE_FLAGS} -Wl,-Map=${PROJECT_NAME}.map -Wl,--print-memory-usage")

# We say to use such and such a compiler with such and such a linker, etc.
if(CONFIG_CXX_ON)
    set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
else ()
    set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
endif()

# Run search and registration of components
components_search()

# Getting source files after registering components
get_all_source_files_of_components(SOURCE_FILES)

# Getting include files after registering components
get_all_include_files_of_components(INCLUDE_FILES)

# Getting include directories after registering components
get_all_include_files_directories_of_components(INCLUDE_DIRECTORIES)

# Getting definitions after registering components
get_all_definitions_of_components(DEFINITIONS)

# Getting embed files after registering components
get_all_embed_files_of_components(EMBED_FILES)

# Getting static libraries after registering components
get_all_static_libs_of_components(STATIC_LIBS)

# Paths along which includes, '.' means project root
include_directories(.)
include_directories(${INCLUDE_DIRECTORIES})
include_directories(${CMAKE_SOURCE_DIR}/configuration)

# Add global define
add_definitions(${DEFINITIONS})

# Creating object files from embedded binaries
# Use arm-none-eabi-objdump -x file_name.obj in build directory
# for get information about object file
foreach(EMBED_FILE ${EMBED_FILES})
    get_filename_component(EMBED_FILE_DIRECTORY ${EMBED_FILE} DIRECTORY)
    get_filename_component(EMBED_FILE_NAME ${EMBED_FILE} NAME)
    get_filename_component(EMBED_FILE_NAME_WE ${EMBED_FILE} NAME_WE)
    add_custom_command(OUTPUT ${EMBED_FILE_NAME_WE}.obj
        COMMAND cd ${EMBED_FILE_DIRECTORY} && ${CMAKE_LD} -r -b binary -o ${CMAKE_BINARY_DIR}/${EMBED_FILE_NAME_WE}.obj ${EMBED_FILE_NAME}
        COMMAND ${CMAKE_OBJCOPY} --rename-section .data=.rodata,alloc,load,readonly,data,contents ${CMAKE_BINARY_DIR}/${EMBED_FILE_NAME_WE}.obj ${CMAKE_BINARY_DIR}/${EMBED_FILE_NAME_WE}.obj
    )
    list(APPEND OBJECTS_OF_EMBED_FILES ${CMAKE_BINARY_DIR}/${EMBED_FILE_NAME_WE}.obj)
endforeach()

# At this point, the project is compiled and linked to .elf
add_executable(${PROJECT_NAME} ${INCLUDE_FILES} ${SOURCE_FILES} ${OBJECTS_OF_EMBED_FILES})

# Linking static libraries with a target
foreach(STATIC_LIB ${STATIC_LIBS})
    get_filename_component(STATIC_LIB_NAME_WE ${STATIC_LIB} NAME_WE)
    add_library(${STATIC_LIB_NAME_WE} STATIC IMPORTED)
    set_target_properties(${STATIC_LIB_NAME_WE} PROPERTIES IMPORTED_LOCATION ${STATIC_LIB})
    target_link_libraries(${PROJECT_NAME} ${STATIC_LIB_NAME_WE})
endforeach()

# Convert .elf to .hex
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -Oihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex)

# Convert .elf to .bin
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)

# Output to the console data about the size of sections .bss, .data, etc., as well as the entire project
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${SIZE} ARGS --format=berkeley ${PROJECT_NAME}.elf)