add_library(startup OBJECT
    startup.s
)

target_include_directories(startup PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)