include(${CMAKE_SOURCE_DIR}/component.cmake)

set(PLACE_COMPONENT ${CMAKE_CURRENT_SOURCE_DIR})

component_registration(
    SOURCE_FILES
        ${PLACE_COMPONENT}/sources/assert.c
    INCLUDE_DIRECTORIES
        ${PLACE_COMPONENT}/include
)