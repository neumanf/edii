#include <iostream>
#include <vector>
#include <list>

using namespace std;

class GrafoListaAdj {
private:
    vector<string> vertices;

    //first é o indice do vertice, second é o peso (caso o grafo seja ponderado)
    vector<vector<pair<int, int>>> arestas;

    /**
    * A principio nao temos nenhuma ordenacao usando os rotulos.
    * Portanto, usaremos busca linear.
    **/
    int obterIndiceVertice(string rotuloVertice) {
        for(int i = 0; i < vertices.size(); i++){
            if(vertices[i] == rotuloVertice){
                return i;
            }
        }

        return -1;
    }

    /**
    * O argumento indicesVerticesVisitados serve para controlar quais
    * vertices já foram visitados.
    * Lembrando que DFS é uma função recursiva.
    **/
    void dfs(string rotuloVOrigem, bool* indicesVerticesVisitados) {
        int vIndex = obterIndiceVertice(rotuloVOrigem);

        if(indicesVerticesVisitados[vIndex]) return;
        
        indicesVerticesVisitados[vIndex] = true;

        for(auto x: arestas[vIndex]){
            dfs(vertices.at(x.first), indicesVerticesVisitados);
        }
    }

public:
    /**
    * Lembrem-se:
    *       1) nao podemos inserir vertices com mesmo rotulo
    *       2) toda vez que inserirmos um novo vértice, precisaremos
    *          inserir um vetor para representar as conexões daquele
    *          vértice na lista de adjacências
    **/
    void inserirVertice(string rotuloVertice) {
        if(obterIndiceVertice(rotuloVertice) != -1) return;

        vector<pair<int, int>> vec;

        vertices.push_back(rotuloVertice);
        arestas.push_back(vec);
    }

    /**
    * Sempre que o grafo for não ponderado, adicionaremos o peso 1,
    * por conveniência.
    **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino) {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino) {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso) {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
    }

    /**
    * Inserir uma aresta entre rotuloVOrigem e rotuloVDestino com o peso
    * especificado.
    **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso) {
        int v1Index = obterIndiceVertice(rotuloVOrigem);
        int v2Index = obterIndiceVertice(rotuloVDestino);

        arestas.at(v1Index).push_back(make_pair(v2Index, peso));
    }

    /**
    * Verifica se vértice rotuloVOrigem e vértice rotuloVDestino são
    * conectados (vizinhos).
    **/
    bool saoConectados(string rotuloVOrigem, string rotuloVDestino) {
        int v1Index = obterIndiceVertice(rotuloVOrigem);
        int v2Index = obterIndiceVertice(rotuloVDestino);

        for(int i = 0; i < arestas.at(v1Index).size(); i++){
            if(arestas.at(v1Index).at(i).first == v2Index){
                return true;
            }
        }
        
        return false;
    }

    /**
    * Verifica se há algum caminho entre vértice rotuloVOrigem e 
    * vértice rotuloVDestino.
    * A melhor forma de fazer isto é reusando a função dfs.
    **/
    bool haCaminho(string rotuloVOrigem, string rotuloVDestino) {
        int v2Index = obterIndiceVertice(rotuloVDestino);

        int vTamanho = vertices.size();
        bool* visitado = new bool[vTamanho]; 

        for(int i = 0; i < vTamanho; i++){
            visitado[i] = false; 
        }

        dfs(rotuloVOrigem, visitado);

        if(visitado[v2Index]){
            return true;
        }

        delete visitado;

        return false;
    }

    /**
    * Muda os rótulos do vértices dos diferentes componentes para
    * nomes que representam cores.
    * Dica: procura componentes partindo do vértice v0 ou v1, em ordem
    * crescente (mas você pode usar outra ordem se desejar). 
    * Retorna a quantidade de componentes.
    * A melhor forma de fazer isto é reusando a função dfs.
    **/
    int colorir() {
        int cor = 0;
        int vTamanho = vertices.size();

        bool* visitado = new bool[vTamanho]; 
    
        for(int j = 0; j < vTamanho; j++){
            visitado[j] = false; 
        }

        for(int i = 0; i < vTamanho; i++){
            if(!visitado[i]){
                dfs(vertices[i], visitado);

                cor++;
            }

            for(int j = 0; j < vTamanho; j++) {
                if(saoConectados(vertices[i], vertices[j])){
                    vertices[j] = to_string(cor);
                }

                if(vertices[i][0] == 'v'){
                    vertices[i] = to_string(cor);
                }
            }
        }

        delete visitado;

        return cor;
    }

    /**
    * Usa a abordagem de navegação BFS para listar as distâncias
    * entre o vértice rotuloVOrigem e cada um dos demais vértices.
    * A função BFS consegue listar a menor distância entre um vértice
    * e os demais se o grafo for NÃO-PONDERADO.
    * Retorna um vetor de inteiros com a quantidade de arestas 
    * (distância) e o vértice rotuloVOrigem e cada um dos demais vértices.
    * Não é uma função recursiva. 
    * É necessário utilizar a ED fila.
    **/
    int* bfs(string rotuloVOrigem) {
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

    vector<string> getVertices() {
        return vertices;
    }

    vector<vector<pair<int, int>>> getArestas() {
        return arestas;
    }
};