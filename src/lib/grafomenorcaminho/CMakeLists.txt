add_library(grafomenorcaminho SHARED "")

target_sources(
    grafomenorcaminho
    PRIVATE
        grafomenorcaminho.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/grafomenorcaminho.h
    )

target_include_directories(
    grafomenorcaminho
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
