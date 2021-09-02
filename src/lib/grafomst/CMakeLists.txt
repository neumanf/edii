add_library(grafomst SHARED "")

target_sources(
    grafomst
    PRIVATE
        grafomst.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/grafomst.h
    )

target_include_directories(
    grafomst
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
