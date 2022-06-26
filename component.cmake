# Define global list of source files
define_property(
    GLOBAL PROPERTY SOURCE_FILES_GLOBAL_LIST
    BRIEF_DOCS "Global list of source files"
    FULL_DOCS "Used for get access to global source file list"
)

# Define global list of include files
define_property(
    GLOBAL PROPERTY INCLUDE_FILES_GLOBAL_LIST
    BRIEF_DOCS "Global list of include files"
    FULL_DOCS "Used for get access to global include file list"
)

# Define global list of include directories
define_property(
    GLOBAL PROPERTY INCLUDE_DIRECTORIES_GLOBAL_LIST
    BRIEF_DOCS "Global list of include directories"
    FULL_DOCS "Used for get access to global include directory list"
)

# Define global list of definitions
define_property(
    GLOBAL PROPERTY DEFINITIONS_GLOBAL_LIST
    BRIEF_DOCS "Global list of definitions"
    FULL_DOCS "Used for get access to global define list"
)

# Define global list of embed files
define_property(
    GLOBAL PROPERTY EMBED_FILES_GLOBAL_LIST
    BRIEF_DOCS "Global list of embed files"
    FULL_DOCS "Used for get access to global embed file list"
)

# Define global list of static libs
define_property(
    GLOBAL PROPERTY STATIC_LIBS_GLOBAL_LIST
    BRIEF_DOCS "Global list of static libs"
    FULL_DOCS "Used for get access to global static libs list"
)

# Set path to directory with components
set(PLACE_COMPONENTS ${CMAKE_SOURCE_DIR}/components)

#[[
The function of scanning directory and get subdirectories.

DIRECTORY input argument, directory for scanning

SUB_DIRECTORIES output argument, multivalue list of sub directories
]]
function(get_sub_directories DIRECTORY SUB_DIRECTORIES)
    file(GLOB CHILDREN RELATIVE ${DIRECTORY} ${DIRECTORY}/*)
    set(DIRECTORIES)
    foreach(CHILD ${CHILDREN})
        if(IS_DIRECTORY ${DIRECTORY}/${CHILD})
            list(APPEND DIRECTORIES ${CHILD})
        endif()
    endforeach()
  set(${SUB_DIRECTORIES} ${DIRECTORIES} PARENT_SCOPE)
endfunction()

#[[
Register a component to the build.

SOURCE_FILES input optional argument, multivalue list of source files for the component  
mast be .c for С, .cpp for CPP and .s for ASM

INCLUDE_DIRECTORIES input optional argument, multivalue list of include directories 
for the component, files in director mast be .h for C or .hpp for CPP files 
with other extension will be ignored

DEFINITIONS input optional argument, multivalue list of definition for the component

EMBED_FILES input optional argument, multivalue list of binary files to embed with the
project

STATIC_LIBS input optional argument, multivalue list of static libs to link with project
]]
function(component_registration)
    set(flags)
    set(args)
    set(list_args SOURCE_FILES INCLUDE_DIRECTORIES DEFINITIONS EMBED_FILES STATIC_LIBS)
    cmake_parse_arguments(arg "${flags}" "${args}" "${list_args}" ${ARGN})
    if(arg_SOURCE_FILES)
        foreach(SOURCE_FILE ${arg_SOURCE_FILES})
            get_filename_component(SOURCE_FILE_NAME ${SOURCE_FILE} NAME)
            get_filename_component(SOURCE_FILE_DIRECTORY ${SOURCE_FILE} DIRECTORY)
            set(FOUND_SOURCE_FILE "FOUND_SOURCE_FILE-NOTFOUND")
            find_file(FOUND_SOURCE_FILE NAMES ${SOURCE_FILE_NAME} PATHS ${CMAKE_SOURCE_DIR}/${SOURCE_FILE_DIRECTORY})
            if(NOT EXISTS ${FOUND_SOURCE_FILE})
                message(FATAL_ERROR "Not found source file: ${CMAKE_SOURCE_DIR}/${SOURCE_FILE}")
            endif()
            set_property(GLOBAL APPEND PROPERTY SOURCE_FILES_GLOBAL_LIST ${FOUND_SOURCE_FILE})
        endforeach()
    endif()
    if(arg_INCLUDE_DIRECTORIES)
        foreach(INCLUDE_DIRECTORY ${arg_INCLUDE_DIRECTORIES})
            if(NOT EXISTS ${CMAKE_SOURCE_DIR}/${INCLUDE_DIRECTORY})
                message(FATAL_ERROR "Not found include directory: ${CMAKE_SOURCE_DIR}/${INCLUDE_DIRECTORY}")
            endif()
            file(GLOB INCLUDE_FILES
                ${CMAKE_SOURCE_DIR}/${INCLUDE_DIRECTORY}/*.h
                if(CONFIG_CXX_ON)
                    ${CMAKE_SOURCE_DIR}/${INCLUDE_DIRECTORY}/*.hpp
                endif()
            )
            if(INCLUDE_FILES)
                foreach(INCLUDE_FILE ${INCLUDE_FILES})
                    file(RELATIVE_PATH CONTENT ${CMAKE_SOURCE_DIR} ${INCLUDE_FILE})
                    set_property(GLOBAL APPEND PROPERTY INCLUDE_FILES_GLOBAL_LIST ${CMAKE_SOURCE_DIR}/${CONTENT})
                endforeach()
            endif()
            set_property(GLOBAL APPEND PROPERTY INCLUDE_DIRECTORIES_GLOBAL_LIST ${CMAKE_SOURCE_DIR}/${INCLUDE_DIRECTORY})
        endforeach()
    endif()
    foreach(DEFINE ${arg_DEFINITIONS})
        set_property(GLOBAL APPEND PROPERTY DEFINITIONS_GLOBAL_LIST -D${DEFINE})
    endforeach()
    if(arg_EMBED_FILES)
        foreach(EMBED_FILE ${arg_EMBED_FILES})
            get_filename_component(EMBED_FILE_NAME ${EMBED_FILE} NAME)
            get_filename_component(EMBED_FILE_DIRECTORY ${EMBED_FILE} DIRECTORY)
            get_filename_component(EMBED_FILE_EXTENSION ${EMBED_FILE} EXT)
            set(FOUND_EMBED_FILE "FOUND_EMBED_FILE-NOTFOUND")
            find_file(FOUND_EMBED_FILE NAMES ${EMBED_FILE_NAME} PATHS ${CMAKE_SOURCE_DIR}/${EMBED_FILE_DIRECTORY})
            if(NOT EXISTS ${FOUND_EMBED_FILE})
                message(FATAL_ERROR "Not found embed file: ${CMAKE_SOURCE_DIR}/${EMBED_FILE}")
            endif()
            if(NOT ${EMBED_FILE_EXTENSION} STREQUAL .bin AND NOT ${EMBED_FILE_EXTENSION} STREQUAL .hex)
                message(FATAL_ERROR "Invalid extension for embedded file: ${FOUND_EMBED_FILE}, extension most be .bin or .hex")
            endif()
            set_property(GLOBAL APPEND PROPERTY EMBED_FILES_GLOBAL_LIST ${FOUND_EMBED_FILE})
        endforeach()
    endif()
    if(arg_STATIC_LIBS)
        foreach(STATIC_LIB ${arg_STATIC_LIBS})
            get_filename_component(STATIC_LIB_NAME ${STATIC_LIB} NAME)
            get_filename_component(STATIC_LIB_DIRECTORY ${STATIC_LIB} DIRECTORY)
            set(FOUND_STATIC_LIB "FOUND_STATIC_LIB-NOTFOUND")
            find_library(FOUND_STATIC_LIB NAMES ${STATIC_LIB_NAME} PATHS ${CMAKE_SOURCE_DIR}/${STATIC_LIB_DIRECTORY})
            if(NOT EXISTS ${FOUND_STATIC_LIB})
                message(FATAL_ERROR "Not found static library: ${CMAKE_SOURCE_DIR}/${STATIC_LIB}")
            endif()
            set_property(GLOBAL APPEND PROPERTY STATIC_LIBS_GLOBAL_LIST ${FOUND_STATIC_LIB})
        endforeach()
    endif()
endfunction()

#[[
Get global list of source files.

SOURCE_FILES output argument, in argument will be set global list of source files
]]
function(get_all_source_files_of_components SOURCE_FILES)
    get_property(content GLOBAL PROPERTY SOURCE_FILES_GLOBAL_LIST)
    set(${SOURCE_FILES} ${content} PARENT_SCOPE)
endfunction()

#[[
Get global list of include files.

INCLUDE_FILES output argument, in argument will be set global list of include files
]]
function(get_all_include_files_of_components INCLUDE_FILES)
    get_property(content GLOBAL PROPERTY INCLUDE_FILES_GLOBAL_LIST)
    set(${INCLUDE_FILES} ${content} PARENT_SCOPE)
endfunction()

#[[
Get global list of include directories.

INCLUDE_DIRECTORIES output argument, in argument will be set global list of include directories
]]
function(get_all_include_files_directories_of_components INCLUDE_DIRECTORIES)
    get_property(content GLOBAL PROPERTY INCLUDE_DIRECTORIES_GLOBAL_LIST)
    set(${INCLUDE_DIRECTORIES} ${content} PARENT_SCOPE)
endfunction()

#[[
Get global list of defines.

DEFINITIONS output argument, in argument will be set global list of defines
]]
function(get_all_definitions_of_components DEFINITIONS)
    get_property(content GLOBAL PROPERTY DEFINITIONS_GLOBAL_LIST)
    set(${DEFINITIONS} ${content} PARENT_SCOPE)
endfunction()

#[[
Get global list of embed files.

EMBED_FILES output argument, in argument will be set global list of embed files
]]
function(get_all_embed_files_of_components EMBED_FILES)
    get_property(content GLOBAL PROPERTY EMBED_FILES_GLOBAL_LIST)
    set(${EMBED_FILES} ${content} PARENT_SCOPE)
endfunction()

#[[
Get global list of static library.

STATIC_LIBS output argument, in argument will be set global list of static library
]]
function(get_all_static_libs_of_components STATIC_LIBS)
    get_property(content GLOBAL PROPERTY STATIC_LIBS_GLOBAL_LIST)
    set(${STATIC_LIBS} ${content} PARENT_SCOPE)
endfunction()

#[[
The function of checking all directories from the PLACE_COMPONENTS list and searching 
in each directory for the CMakeLists.txt file, if the directory contains this file, 
it will be added as a sub directory and the component will be registered.
]]
function(components_search)
    message(STATUS "Begin search components ...")
    get_sub_directories(${PLACE_COMPONENTS} COMPONENTS)
    foreach(COMPONENT ${COMPONENTS})
        set(MY_BUILD_${COMPONENT} TRUE
            CACHE BOOL "Build the ${COMPONENT} component")
        if(MY_BUILD_${COMPONENT} AND EXISTS
            ${PLACE_COMPONENTS}/${COMPONENT}/CMakeLists.txt)
            message(STATUS "Component \"${COMPONENT}\" will be included")
            add_subdirectory(${PLACE_COMPONENTS}/${COMPONENT})
        else()
            message(STATUS "Component \"${COMPONENT}\" will NOT be included")
            list(REMOVE_ITEM COMPONENTS ${COMPONENT})
        endif()
    endforeach()
    message(STATUS "End search components")
endfunction()