include(${CMAKE_SOURCE_DIR}/component.cmake)

component_registration(
    SOURCE_FILES
        components/application/sources/main.c
    INCLUDE_DIRECTORIES
        components/application/static_libs/lib_a/include
        components/application/static_libs/lib_b/include
    EMBED_FILES
        components/application/embed_files/embed_file_a.hex
        components/application/embed_files/embed_file_b.hex
    STATIC_LIBS
        components/application/static_libs/lib_a/library/lib_a.a
        components/application/static_libs/lib_b/library/lib_b.a
)