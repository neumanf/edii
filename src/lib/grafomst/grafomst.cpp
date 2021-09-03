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
    if(grupos[i].pai == i){
        return i;
    } else {
        return encontrarRaiz(grupos, grupos[i].pai);
    }
}

bool GrafoListaAdj::mesmoGrupo(Grupo* grupos, int a, int b) {
    return encontrarRaiz(grupos, a) == encontrarRaiz(grupos, b);
}

int GrafoListaAdj::tamanhoGrupo(Grupo* grupos, int a) {
    return grupos[a].tamanho;
}

void GrafoListaAdj::unirGrupos(Grupo* grupos, int a, int b) {
    int x = encontrarRaiz(grupos, a);
    int y = encontrarRaiz(grupos, b);

    if(x == y) return;

    if(grupos[x].tamanho < grupos[y].tamanho){
        grupos[x].pai = y;
        grupos[y].tamanho += grupos[x].tamanho;
    } else {
        grupos[y].pai = x;
        grupos[x].tamanho += grupos[y].tamanho;
    }
}

GrafoListaAdj* GrafoListaAdj::KruskalMST() {
    //instanciamos um novo grafo, que armazenara
    //apenas as arestas da MST
    GrafoListaAdj* mst = new GrafoListaAdj();

    int tamanho = vertices.size();

    //adicionar vertices
    for(int i = 0; i < tamanho; i++){
        mst->inserirVertice(vertices[i]);
    }

    //inicializar estrutura do union-find (array de grupos)
    Grupo* grupos = new Grupo[tamanho * sizeof(Grupo)];

    for(int i = 0; i < tamanho; i++){
        grupos[i].pai = i;
        grupos[i].tamanho = 0;
    }
    
    //inicializar priority_queue
    priority_queue<Aresta> arestasMenorPeso;
    
    //adicionar arestas na fila
    for(int i = 0; i < arestas.size(); i++){
        for(int j = 0; j < arestas.at(i).size(); j++){
            int origem = obterIndiceVertice(vertices.at(i));
            int destino = arestas.at(i).at(j).first;
            int peso = arestas.at(i).at(j).second;

            Aresta aresta = Aresta(origem, destino, peso);

            arestasMenorPeso.push(aresta);
        }
    }

    //iterar na fila de arestas
    while(!arestasMenorPeso.empty()){
        Aresta topo = arestasMenorPeso.top();

        //se os vertices da arestas nao pertencem ao mesmo grupo
        if(!mesmoGrupo(grupos, topo.origem, topo.destino)){
            //una-os, e adicione a aresta no MST
            unirGrupos(grupos, topo.origem, topo.destino);
            mst->inserirArestaDirecionada(vertices[topo.origem], vertices[topo.destino], topo.peso * 2);
        }

        arestasMenorPeso.pop();
    }

    return mst;
}