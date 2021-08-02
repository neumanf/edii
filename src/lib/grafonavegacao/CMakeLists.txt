add_library(grafonavegacao SHARED "")

target_sources(
    grafonavegacao
    PRIVATE
        grafonavegacao.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/grafonavegacao.h
    )

target_include_directories(
    grafonavegacao
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
