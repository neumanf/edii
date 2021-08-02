add_library(grafomatadj SHARED "")

target_sources(
    grafomatadj
    PRIVATE
        grafomatadj.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/grafomatadj.h
    )

target_include_directories(
    grafomatadj
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
