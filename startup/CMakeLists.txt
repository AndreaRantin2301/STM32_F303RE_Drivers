add_library(startup OBJECT
    startup.s
)

add_compile_options(-mthumb)