include(${CMAKE_SOURCE_DIR}/component.cmake)

set(PLACE_COMPONENT ${CMAKE_CURRENT_SOURCE_DIR})

component_registration(
    SOURCE_FILES
        ${PLACE_COMPONENT}/sources/main.c
    INCLUDE_DIRECTORIES
        ${PLACE_COMPONENT}/static_libs/lib_a/include
        ${PLACE_COMPONENT}/static_libs/lib_b/include
    EMBED_FILES
        ${PLACE_COMPONENT}/embed_files/embed_file_a.hex
        ${PLACE_COMPONENT}/embed_files/embed_file_b.hex
    STATIC_LIBS
        ${PLACE_COMPONENT}/static_libs/lib_a/library/lib_a.a
        ${PLACE_COMPONENT}/static_libs/lib_b/library/lib_b.a
)