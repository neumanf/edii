#include "grafomst.h"

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

vector<string> GrafoListaAdj::getVertices() {
    return vertices;
}

vector<vector<pair<int, int>>> GrafoListaAdj::getArestas() {
    return arestas;
}

int GrafoListaAdj::encontrarRaiz(Grupo* grupos, int i) {
    return 0;
}

bool GrafoListaAdj::mesmoGrupo(Grupo* grupos, int a, int b) {
    return true;
}

int GrafoListaAdj::tamanhoGrupo(Grupo* grupos, int a) {
    return 0;
}

void GrafoListaAdj::unirGrupos(Grupo* grupos, int a, int b) {
    //IMPLEMENTAR
}

GrafoListaAdj* GrafoListaAdj::KruskalMST() {
    //IMPLEMENTAR

    //instanciamos um novo grafo, que armazenara
    //apenas as arestas da MST
    GrafoListaAdj* mst = new GrafoListaAdj();
    
    //adicionar vertices
    //inicializar estrutura do union-find (array de grupos)
    
    
    //inicializar priority_queue
    priority_queue<Aresta> arestasMenorPeso;
    //adicionar arestas na fila    
    
    //iterar na fila de arestas
        //se os vertices da arestas nao pertencem ao mesmo grupo
        //una-os, e adicione a aresta no MST

    return mst;
}