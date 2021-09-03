#include <iostream>
#include <sstream>

using namespace std;

#include "./lib/grafomst/grafomst.h"

void inserirVertices(GrafoListaAdj* grafo, int ini, int fim) {
	for (int i = ini; i <= fim; i++) {
		string rotulo;
		stringstream sstm;
		sstm << "v" << i;
		rotulo = sstm.str();
		grafo->inserirVertice(rotulo);
	}
}

int somaArestasMST(GrafoListaAdj* grafoMST) {
	int pesoArestas = 0;
	cout << "Tamanho: " << to_string(grafoMST->getArestas().size()) << endl;
	for (int vOrigem = 0; vOrigem < grafoMST->getArestas().size(); vOrigem++) {
		cout << "Qtdade de Arestas com origem em " << to_string(vOrigem) <<": " << to_string(grafoMST->getArestas().at(vOrigem).size()) << endl;
		if (!grafoMST->getArestas().at(vOrigem).empty()) {
			//for (pair<int, int> arestaSaindoDeVOrigem : grafoMST->getArestas().at(vOrigem)) {
			for (int i = 0; i < grafoMST->getArestas().at(vOrigem).size(); i++) {
				cout << "Par: (" << to_string(grafoMST->getArestas().at(vOrigem).at(i).first) << "," << to_string(grafoMST->getArestas().at(vOrigem).at(i).second) << ")" << endl;
				//first é o indice do vertice, second é o peso (caso o grafo seja ponderado)
				pesoArestas += grafoMST->getArestas().at(vOrigem).at(i).second;
			}
		}
	}
	return pesoArestas;
}

void printVertices(vector<string> vertices){
    cout << "[";
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices.at(i) << (i == vertices.size() - 1 ? "" : ", ");
    }
    cout << "]\n";
}

void printArestas(vector<vector<pair<int, int>>> arestas){
    for(int i = 0; i < arestas.size(); i++){
        cout << i <<": [";
        for(int j = 0; j < arestas.at(i).size(); j++){
            cout << "{" << arestas.at(i).at(j).first << ", " << arestas.at(i).at(j).second << (j == arestas.at(i).size() - 1 ? "}" : "}, "); 
        }
        cout << "]\n";
    }
}

int main() {
    GrafoListaAdj* grafo = new GrafoListaAdj();

	inserirVertices(grafo, 1, 10);
	
	//Grafo: https://www.youtube.com/watch?v=JZBQLXgSGfs&t
	grafo->inserirArestaNaoDirecionada("v1", "v2", 5);
	grafo->inserirArestaNaoDirecionada("v1", "v4", 4);
	grafo->inserirArestaNaoDirecionada("v1", "v5", 1);
	grafo->inserirArestaNaoDirecionada("v2", "v3", 4);
	grafo->inserirArestaNaoDirecionada("v2", "v4", 2);
	grafo->inserirArestaNaoDirecionada("v3", "v8", 4);
	grafo->inserirArestaNaoDirecionada("v3", "v9", 1);
	grafo->inserirArestaNaoDirecionada("v3", "v10", 2);
	grafo->inserirArestaNaoDirecionada("v4", "v5", 2);
	grafo->inserirArestaNaoDirecionada("v4", "v6", 5);
	grafo->inserirArestaNaoDirecionada("v4", "v7", 11);
	grafo->inserirArestaNaoDirecionada("v4", "v8", 2);
	grafo->inserirArestaNaoDirecionada("v5", "v6", 1);
	grafo->inserirArestaNaoDirecionada("v6", "v7", 7);
	grafo->inserirArestaNaoDirecionada("v7", "v8", 1);
	grafo->inserirArestaNaoDirecionada("v7", "v9", 4);
	grafo->inserirArestaNaoDirecionada("v8", "v9", 6);
	grafo->inserirArestaNaoDirecionada("v9", "v10", 0);

	// v1 = a
	// v2 = b
	// v3 = c
	// v4 = d
	// v5 = e
	// v6 = f
	// v7 = g
	// v8 = h
	// v9 = i
	// v10 = j

	printVertices(grafo->getVertices());
	printArestas(grafo->getArestas());

	GrafoListaAdj* grafoMST = grafo->KruskalMST();

	int pesoArestas = somaArestasMST(grafoMST);

	cout << "pesoArestas: " << pesoArestas << endl;

	delete(grafo);

    return 0;
}