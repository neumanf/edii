#include "grafolistaadj.h"

#include <iostream>

int GrafoListaAdj::obterIndiceVertice(string rotuloVertice){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i] == rotuloVertice){
            return i;
        }
    }

    return -1;
}

void GrafoListaAdj::inserirVertice(string rotuloVertice) {
    if(obterIndiceVertice(rotuloVertice) != -1) return;

    vector<pair<int, int>> vec;

    vertices.push_back(rotuloVertice);
    arestas.push_back(vec);
}

void GrafoListaAdj::inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
}

void GrafoListaAdj::inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
}

void GrafoListaAdj::inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
    inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
}

void GrafoListaAdj::inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso) {
    int v1Index = obterIndiceVertice(rotuloVOrigem);
    int v2Index = obterIndiceVertice(rotuloVDestino);

    arestas.at(v1Index).push_back(make_pair(v2Index, peso));
}

bool GrafoListaAdj::saoConectados(string rotuloVOrigem, string rotuloVDestino) {
    int v1Index = obterIndiceVertice(rotuloVOrigem);
    int v2Index = obterIndiceVertice(rotuloVDestino);

    for(int i = 0; i < arestas.at(v1Index).size(); i++){
        if(arestas.at(v1Index).at(i).first == v2Index){
            return true;
        }
    }
    
    return false;
}

vector<string> GrafoListaAdj::getVertices() {
    return vertices;
}

vector<vector<pair<int, int>>> GrafoListaAdj::getArestas() {
    return arestas;
}