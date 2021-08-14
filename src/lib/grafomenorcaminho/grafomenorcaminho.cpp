#include "grafomenorcaminho.h"

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

    cout << "[";
    for(int i = 0; i < vertices.size(); i++) cout << indicesVerticesVisitados[i] << ", ";
    cout << "]\n";

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
    return true;
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

            vertices[i] = to_string(cor);

            cor++;
        }
    }

    // for(auto i : vertices){
    //     cout << i << ", ";
    // }
    // cout << endl;

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

// int* GrafoListaAdj::bellmanFord(string rotuloVOrigem){
//     vector<pair<int, int>>::iterator traverse;
//     int i, j, k;
    
//     int startVertex = obterIndiceVertice(rotuloVOrigem);
//     int n = vertices.size();
//     int* shortestDistances = new int[n];

//     for (i = 0; i <= vertices.size(); ++i) {
//         shortestDistances[i] = POS_INF;
//     }

//     shortestDistances[startVertex] = 0;

//     for (i = 1; i <= vertices.size() - 1; ++i) {
//         for (j = 1; j <= vertices.size(); ++j) {
//             traverse = arestas[j].begin();
            
//             while (traverse != arestas[j].end()) {
//                 if (shortestDistances[j] == POS_INF) {
//                     ++traverse;
//                     continue;
//                 }
                 
//                 if ((*traverse).second + shortestDistances[j] < shortestDistances[(*traverse).first]) {
//                     shortestDistances[(*traverse).first] = (*traverse).second + shortestDistances[j];
//                 }
                 
//                 ++traverse;
//             }
//         }
//     }
     
//     for (j = 1; j <= vertices.size(); ++j) {
//         traverse = arestas[j].begin();
         
//         while (traverse != arestas[j].end()) {
//             cout << "(*traverse).first: " << (*traverse).first << ", (*traverse).second: " << (*traverse).second << endl;
            
//             if ((*traverse).second + shortestDistances[j] < shortestDistances[(*traverse).first]) {
//                 cout << "NEG_INF" << endl;
//                 shortestDistances[(*traverse).first] = NEG_INF;
//             }
            
//             ++traverse;
//         }
//     }
    
//     return shortestDistances;
// }

// int* GrafoListaAdj::bellmanFord(string rotuloVOrigem){
//         // Initialize the distance / cost from the source node to all other nodes to some max value.
//         int src = obterIndiceVertice(rotuloVOrigem);
//         int node_count = vertices.size();
//         int* distance = new int[node_count];

//         for(int i = 1; i <= node_count; i++){
//             distance[i] = POS_INF;
//         }
        
//         // Distance/cost from the source node to itself is 0.
//         distance[src] = 0;

//         cout << "[";
//         for(int i = 0; i < vertices.size(); i++){
//             cout << vertices.at(i) << (i == vertices.size() - 1 ? "" : ", ");
//         }
//         cout << "]\n";

//         for(int i = 0; i < arestas.size(); i++){
//             cout << i <<": [";
//             for(int j = 0; j < arestas.at(i).size(); j++){
//                 cout << "{" << arestas.at(i).at(j).first << ", " << arestas.at(i).at(j).second << (j == arestas.at(i).size() - 1 ? "}" : "}, "); 
//             }
//             cout << "]\n";
//         }

//         // cout << "src: " << src << ", arestas[src]:" << arestas[src][0].first << endl;

//         for (int i = 0; i < node_count; i++) {
//             for (auto& it : arestas[src]) {
//                 cout << "distance[it.first]: " << distance[it.first] << ", distance[src]: " << distance[src] << ", it.second:" << it.second << endl;
//                 if (distance[it.first] > distance[src] + it.second) {
//                     distance[it.first] = distance[src] + it.second;
//                 }
//             }
//         }

//         for (auto& it : arestas[src]) {
//             if (distance[it.first] > distance[src] + it.second) {
//                 distance[it.first] = NEG_INF;
//             }
//         }

//         return distance;
// }

int* GrafoListaAdj::bellmanFord(string rotuloVOrigem){
    int vIndex = obterIndiceVertice(rotuloVOrigem);
    int vTamanho = vertices.size();

    int* distancia = new int[vTamanho];
    list<int> q;

    for(int i = 0; i < vTamanho; i++){
        distancia[i] = POS_INF;
    }

    distancia[vIndex] = 0;

    cout << "[";
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices.at(i) << (i == vertices.size() - 1 ? "" : ", ");
    }
    cout << "]\n";

    for(int i = 0; i < arestas.size(); i++){
        cout << i <<": [";
        for(int j = 0; j < arestas.at(i).size(); j++){
            cout << "{" << arestas.at(i).at(j).first << ", " << arestas.at(i).at(j).second << (j == arestas.at(i).size() - 1 ? "}" : "}, "); 
        }
        cout << "]\n";
    }

    for(int i = 0; i < vTamanho - 1; i++){
        int j = 0;
        cout << i << endl;
        for(auto aresta : arestas){
            for(auto ares : aresta){
                int origem = j;
                int destino = ares.first;
                int peso = ares.second;

                cout << "origem: " << origem << ", destino: " << destino << ", peso: " << peso << endl;
                cout << "distancia[a]: " << distancia[origem] << ", distancia[destino]: " << distancia[destino] << endl;

                if(distancia[origem] + peso < distancia[destino]){
                    distancia[destino] = distancia[origem] + peso;
                }
            }
            j++;
        }
    }

    int j = 0;
    for(auto aresta : arestas){
        for(auto ares : aresta){
            int origem = j;
            int destino = ares.first;
            int peso = ares.second;

            if(distancia[origem] + peso < distancia[destino]){
                distancia[destino] = NEG_INF;
            }
        }
        j++;
    }

    return distancia;
}

// int* GrafoListaAdj::bellmanFord(string rotuloVOrigem){
//     int vIndex = obterIndiceVertice(rotuloVOrigem);
//     int vTamanho = vertices.size();

//     int* distancia = new int[vTamanho];
//     list<int> q;

//     for(int i = 1; i <= vTamanho; i++){
//         distancia[i] = POS_INF;
//     }

//     distancia[vIndex] = 0;

//     for(int i = 1; i <= vTamanho; i++){
//         for(int j = 0; j < arestas[vIndex].size() - 1; j++) {
//             int a = arestas[vIndex][j].first;
//             int b = j;
//             int w = arestas[vIndex][j].second;

//             cout << "j: " << j << endl;
//             cout << "a: " << a << ", b: " << b << ", w: " << w << endl;
//             cout << "distancia[a]: " << distancia[a] << ", distancia[b]: " << distancia[b] << endl;

//             distancia[b] = min(distancia[b], distancia[a] + w);
//         }
//     }

//     for(int j = 0; j < arestas[vIndex].size() - 1; j++) {
//         int a = arestas[vIndex][j].first;
//         int b = j;
//         int w = arestas[vIndex][j].second;

//         if(distancia[a] + w < distancia[b]){
//             distancia[b] = NEG_INF;
//         }
//     }

//     return distancia;
// }

int findMin(int n, int distancia[], bool visitado[]){
    int min = POS_INF;
    int vertice = 0;

    for(int i = 0; i < n; i++){
        if(visitado[i] == false && min > distancia[i]){
            min = distancia[i];
            vertice = i;
        }
    }

    return vertice;
}

int* GrafoListaAdj::dijkstra(string rotuloVOrigem){
    int vIndex = obterIndiceVertice(rotuloVOrigem);
    int n = vertices.size();
    bool* visitado = new bool[n]; 
    int* distancia = new int[n];
    
    for(int i = 0; i < n; i++){
        distancia[i] = POS_INF;                                          
        visitado[i] = false;                                                 
    }
    
    distancia[vIndex] = 0;                          
    int count = 0;
    
    while(count < n){
        int vertice = findMin(n, distancia, visitado);
        visitado[vertice] = true;

        for(auto &i : arestas[vertice]){
            if(visitado[i.first] == false){
                distancia[i.first] = min(distancia[i.first], distancia[vertice] + (i.second));
            }
        }

        count++;
    }
    
    return distancia;
}

vector<string> GrafoListaAdj::getVertices() {
    return vertices;
}

vector<vector<pair<int, int>>> GrafoListaAdj::getArestas() {
    return arestas;
}
