include(${CMAKE_SOURCE_DIR}/component.cmake)

component_registration(
    SOURCE_FILES
        components/logger/sources/logger.c
    INCLUDE_DIRECTORIES
        components/logger/include
)