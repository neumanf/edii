add_executable(
    unit_tests
    # testGrafoListaAdj.cpp
    testGrafoMatrizAdj.cpp
    testGrafoNavegacao.cpp
    testMenorCaminho.cpp
    )

target_link_libraries(
    unit_tests
    gtest_main
    grafolistaadj
    grafomatadj
    grafonavegacao
    grafomenorcaminho
    )

add_test(
  NAME unit_tests
  COMMAND unit_tests
)
