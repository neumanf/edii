#include <iostream>
#include <vector>
#include <list>

using namespace std;

#define POS_INF 1000000000
#define NEG_INF -1000000000

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

        vector<pair<int,int>> vizinhos = arestas[vIndex];

        for(int i = 0; i < vizinhos.size(); i++){
            dfs(vertices.at(vizinhos[i].first), indicesVerticesVisitados);
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
        return true;
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
        return 0;
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

    /**
    * Usamos o BellmanFord para encontrar menor caminho
    * em grafos com arestas com pesos negativos.
    * O BellmanFord consegue detectar ciclos negativos
    * e atribuir o valor NEG_INF (constante definida nesse arquivo)
    * aos vértices que pertençam ao ciclo.
    * POS_INF deve ser atribuído aos vértices inalcançáveis.
    * O aspecto negativo é sua complexidade de tempo: O(V*E).
    * Isto acontece pois, como possui arestas negativas, cada vértice 
    * do grafo precisa ser processado V vezes.   
    * Pseudo-código: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#bellman-ford
    **/
    int* bellmanFord(string rotuloVOrigem) {
        int vIndex = obterIndiceVertice(rotuloVOrigem);
        int vTamanho = vertices.size();

        int* distancia = new int[vTamanho];
        list<int> q;

        for(int i = 0; i < vTamanho; i++){
            distancia[i] = POS_INF;
        }

        distancia[vIndex] = 0;

        for(int i = 0; i < vTamanho - 1; i++){
            int j = 0;

            for(auto aresta : arestas){
                for(auto ares : aresta){
                    int origem = j;
                    int destino = ares.first;
                    int peso = ares.second;

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

    /**
    * Usamos o Dijkstra para encontrar menor caminho
    * em grafos sem arestas com pesos negativos.
    * O Dijkstra retorna respostas incorretas caso o grafo
    * possua arestas negativas, e portanto não consegue
    * detectar ciclos negativos. Este é o aspecto negativo.
    * POS_INF deve ser atribuído aos vértices inalcançáveis.
    * O aspecto positivo é sua complexidade de tempo: O(V+E).
    * Isto acontece pois, como o grafo não possui arestas negativas, 
    * cada vértice do grafo precisa ser processado apenas 1 vez.
    * Pseudo-código: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#dijkstra
    * Ilustração: https://docs.google.com/drawings/d/1NmkJPHpcg8uVcDZ24FQiYs3uHR5n-rdm1AZwD74WiMY/edit?usp=sharing
    **/
    int* dijkstra(string rotuloVOrigem) {
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

    vector<string> getVertices() {
        return vertices;
    }

    vector<vector<pair<int, int>>> getArestas() {
        return arestas;
    }
};