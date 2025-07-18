add_library(startup OBJECT
    startup.s
)

set_source_files_properties(startup.s PROPERTIES LANGUAGE C)

target_include_directories(startup PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linkerScript.ld CACHE INTERNAL "Linker script")