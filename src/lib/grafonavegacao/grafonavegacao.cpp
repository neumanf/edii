#include "grafonavegacao.h"

#include <iostream>
#include <list>

int GrafoListaAdj::obterIndiceVertice(string rotuloVertice){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i] == rotuloVertice){
            return i;
        }
    }

    return -1;
}

void GrafoListaAdj::dfs(string rotuloVOrigem, bool* indicesVerticesVisitados) {
    int vIndex = obterIndiceVertice(rotuloVOrigem);

    // cout << "[";
    // for(int i = 0; i < vertices.size(); i++) cout << indicesVerticesVisitados[i] << ", ";
    // cout << "]\n";

    if(indicesVerticesVisitados[vIndex]) return;

    indicesVerticesVisitados[vIndex] = true;

    vector<pair<int,int>> vizinhos = arestas[vIndex];

    for(int i = 0; i < vizinhos.size(); i++){
        dfs(vertices.at(vizinhos[i].first), indicesVerticesVisitados);
    }
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

    cout << "rotuloVOrigem: " << rotuloVOrigem << ", index: " << v1Index << endl;
    cout << "rotuloVDestino: " << rotuloVDestino << ", index: " << v2Index << endl;

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

bool GrafoListaAdj::haCaminho(string rotuloVOrigem, string rotuloVDestino) {
    int v1Index = obterIndiceVertice(rotuloVOrigem);
    int v2Index = obterIndiceVertice(rotuloVDestino);

    // int* distancias = bfs(rotuloVOrigem);

    // cout << "[";
    // for(int i = 0; i < vertices.size(); i++){
    //     cout << distancias[i] << " ";
    // }
    // cout << "]\n";


    // if(distancias[v2Index] > 0) return true;

    // free(distancias);

    // return false; 

    int vTamanho = vertices.size();

    for(int i = 0; i < vTamanho; i++){
        bool* visitado = new bool[vTamanho]; 
        
        for(int i = 0; i < vTamanho; i++){
            visitado[i] = false; 
        }

        dfs(rotuloVOrigem, visitado);

        cout << "[";
        for(int i = 0; i < vTamanho; i++){
            cout << visitado[i] << (i == vTamanho - 1 ? "" : ", ");
        }
        cout << "]\n";

        if(visitado[v2Index]){
            return true;
        }

        delete visitado;
    }

    return false;
}

int GrafoListaAdj::colorir(){
    int cor = 0;
    int vTamanho = vertices.size();
    bool* visitado = new bool[vTamanho]; 
    
    for(int i = 0; i < vTamanho; i++){
        visitado[i] = false; 
    }

    for(int i = 0; i < vTamanho; i++){
        if(!visitado[i]){
            dfs(vertices[i], visitado);

            cor++;
        }

        for(int j = 0; j < vTamanho; j++) {
            cout << "vertices[i]: " << vertices[i] << ", vertices[j]: " << vertices[j] << ", saoConectados: " << saoConectados(vertices[i], vertices[j]) << endl;

            if(saoConectados(vertices[i], vertices[j])){
                // cout << vertices[i][0]<< ", " << vertices[j][0] << 

                vertices[j] = to_string(cor);
            }

            if(vertices[i][0] == 'v'){
                vertices[i] = to_string(cor);
            }
        }
    }

    // for(auto i : vertices){
    //     cout << i << ", ";
    // }
    // cout << endl;
    delete visitado;

    return cor;
}

int* GrafoListaAdj::bfs(string rotuloVOrigem) {
    int vIndex = obterIndiceVertice(rotuloVOrigem);
    int vTamanho = vertices.size();

    bool* visitado = new bool[vTamanho]; 
    int* distancia = new int[vTamanho];
    list<int> q;

    for(int i = 0; i < vTamanho; i++){
        visitado[i] = false; 
        distancia[i] = 0;
    }
    
    visitado[vIndex] = true; 
    q.push_back(vIndex); 
   
    while(!q.empty()) { 
        vIndex = q.front(); 
        q.pop_front(); 
   
        for (vector<pair<int, int>>::iterator i = arestas[vIndex].begin(); i != arestas[vIndex].end(); i++) { 
            if (!visitado[(*i).first]) { 
                visitado[(*i).first] = true;
                distancia[(*i).first] = distancia[vIndex] + 1;
                q.push_back((*i).first); 
            } 
        } 
    } 

    return distancia;
}

vector<string> GrafoListaAdj::getVertices() {
    return vertices;
}

vector<vector<pair<int, int>>> GrafoListaAdj::getArestas() {
    return arestas;
}
