add_library(tabelahash SHARED "")

target_sources(
    tabelahash
    PRIVATE
        tabelahash.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/tabelahash.h
    )

target_include_directories(
    tabelahash
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
