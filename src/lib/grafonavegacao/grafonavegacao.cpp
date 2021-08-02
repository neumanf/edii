#include "grafonavegacao.h"

#include <iostream>

int GrafoListaAdj::obterIndiceVertice(string rotuloVertice){
    return 0;
}

void GrafoListaAdj::dfs(string rotuloVOrigem, bool* indicesVerticesVisitados) {
}

void GrafoListaAdj::inserirVertice(string rotuloVertice) {

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

}

bool GrafoListaAdj::saoConectados(string rotuloVOrigem, string rotuloVDestino) {
    return true;
}

bool GrafoListaAdj::haCaminho(string rotuloVOrigem, string rotuloVDestino) {
    return true;
}

int GrafoListaAdj::colorir(){
    return 0;
}

int* GrafoListaAdj::bfs(string rotuloVOrigem) {
    
}

vector<string> GrafoListaAdj::getVertices() {
    return vertices;
}

vector<vector<pair<int, int>>> GrafoListaAdj::getArestas() {
    return arestas;
}
