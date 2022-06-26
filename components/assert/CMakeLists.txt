include(${CMAKE_SOURCE_DIR}/component.cmake)

component_registration(
    SOURCE_FILES
        components/assert/sources/assert.c
    INCLUDE_DIRECTORIES
        components/assert/include
)