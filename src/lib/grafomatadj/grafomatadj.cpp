#include "grafomatadj.h"

#include <iostream>

struct GrafoMatrizAdj* inicializar(int numVertices, bool ponderado) {
    int valorPadrao = ponderado ? INT_MAX : 0;

    GrafoMatrizAdj* grafo = (GrafoMatrizAdj *) malloc(sizeof(GrafoMatrizAdj));

    grafo->arestas = (int **) calloc(numVertices, sizeof(int*));
    grafo->rotuloVertices = (char**) calloc(numVertices, sizeof(char*));

    for(int i = 0; i < numVertices; i++){
        grafo->arestas[i] = (int *) calloc(numVertices, sizeof(int));

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
        if(grafo->rotuloVertices[i] == rotuloVertice){
            return i;
        }
    }

    return -1;
}

void inserirAresta(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino, int peso) {
    int v1Index = obterIndiceVertice(grafo, rotuloVOrigem);
    int v2Index = obterIndiceVertice(grafo, rotuloVDestino);

    grafo->arestas[v1Index][v2Index] = peso;
}

void inserirVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice) {
    grafo->rotuloVertices[grafo->verticesInseridos] = rotuloVertice;
    grafo->verticesInseridos++;
}

bool saoConectados(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino) {
    int v1Index = obterIndiceVertice(grafo, rotuloVOrigem);
    int v2Index = obterIndiceVertice(grafo, rotuloVDestino);

    if((v1Index != -1 && v2Index != -1) && grafo->arestas[v1Index][v2Index] > 0){ 
        return true;
    }
    
    return false;
}