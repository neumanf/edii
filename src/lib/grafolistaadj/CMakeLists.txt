add_library(grafolistaadj SHARED "")

target_sources(
    grafolistaadj
    PRIVATE
        grafolistaadj.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/grafolistaadj.h
    )

target_include_directories(
    grafolistaadj
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
