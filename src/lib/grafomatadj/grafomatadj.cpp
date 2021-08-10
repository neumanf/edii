#include "grafomatadj.h"

#include <iostream>

struct GrafoMatrizAdj* inicializar(int numVertices, bool ponderado) {
    int valorPadrao = ponderado ? INT_MAX : 0;

    struct GrafoMatrizAdj* grafo;

    // Inicializa as linhas
    grafo->arestas = new int*[numVertices];
    grafo->rotuloVertices = new char*[numVertices];

    for(int i = 0; i < numVertices; i++){
        // Inicializa as colunas
        grafo->arestas[i] = new int[numVertices];

        // Atribui os valores iniciais
        for(int j = 0; j < numVertices; j++){
            grafo->arestas[i][j] = valorPadrao;
        }
    }

    grafo->verticesInseridos = 0;
    grafo->maxNumVertices = numVertices;

    return grafo;
}

    // for(int i = 0; i < numVertices; i++){
    //     std::cout << i <<": [";
    //     for(int j = 0; j < numVertices; j++){
    //         std::cout << grafo->arestas[i][j] << (j == numVertices - 1 ? "" : ", "); 
    //     }
    //     std::cout << "]\n";
    // }

int obterIndiceVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice) {
    for(int i = 0; i < grafo->maxNumVertices; i++){
        if(grafo->rotuloVertices[i] = rotuloVertice){
            return i;
        }
    }

    return -1;
}

void inserirAresta(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino, int peso) {
    


}

void inserirVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice) {
    grafo->rotuloVertices[grafo->verticesInseridos] = rotuloVertice;
}

bool saoConectados(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino) {
    return true;
}