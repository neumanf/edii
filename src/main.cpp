#include <iostream>
#include <sstream>

// #include "./lib/grafomatadj/grafomatadj.h"

using namespace std;

// void freeGrafo(struct GrafoMatrizAdj* grafo) {
//     for (int i = 0; i < grafo->maxNumVertices; i++) {
//         free(grafo->arestas[i]);
//     }
//     free(grafo->arestas);
//     free(grafo->rotuloVertices);
//     free(grafo);
// }

// int main(){
//     GrafoMatrizAdj* grafo = inicializar(10, false);

// 	cout << grafo->maxNumVertices << endl;

//     freeGrafo(grafo);

//     return 0;
// }

#include "./lib/grafonavegacao/grafonavegacao.h"

void construirGrafoCom5Componentes(GrafoListaAdj* grafo) {
	//comp1
	grafo->inserirArestaNaoDirecionada("v0", "v4");
	grafo->inserirArestaNaoDirecionada("v0", "v8");
	grafo->inserirArestaNaoDirecionada("v0", "v13");
	grafo->inserirArestaNaoDirecionada("v0", "v14");

	//comp2
	grafo->inserirArestaNaoDirecionada("v1", "v5");
	grafo->inserirArestaNaoDirecionada("v5", "v16");
	grafo->inserirArestaNaoDirecionada("v5", "v17");

	//comp3
	grafo->inserirArestaNaoDirecionada("v3", "v9");
	grafo->inserirArestaNaoDirecionada("v9", "v2");
	grafo->inserirArestaNaoDirecionada("v15", "v9");
	grafo->inserirArestaNaoDirecionada("v15", "v2");
	grafo->inserirArestaNaoDirecionada("v15", "v10");

	//comp4
	grafo->inserirArestaNaoDirecionada("v6", "v7");
	grafo->inserirArestaNaoDirecionada("v6", "v11");
	grafo->inserirArestaNaoDirecionada("v7", "v11");

	//comp5: v�rtice "v12" (sem arestas)
}

void construirGrafoNaoPonderado(GrafoListaAdj* grafo) {
	grafo->inserirArestaNaoDirecionada("v1", "v2");
	grafo->inserirArestaNaoDirecionada("v1", "v3");
	grafo->inserirArestaNaoDirecionada("v2", "v4");
	grafo->inserirArestaNaoDirecionada("v3", "v4");
	grafo->inserirArestaNaoDirecionada("v3", "v5");
	grafo->inserirArestaNaoDirecionada("v4", "v6");
	grafo->inserirArestaNaoDirecionada("v4", "v7");
	grafo->inserirArestaNaoDirecionada("v5", "v9");
	grafo->inserirArestaNaoDirecionada("v6", "v8");
	grafo->inserirArestaNaoDirecionada("v8", "v9");
	grafo->inserirArestaNaoDirecionada("v9", "v9");
}

void inserirVertices2(GrafoListaAdj* grafo, int ini, int fim) {
	for (int i = ini; i <= fim; i++) {
		string rotulo;
		std::stringstream sstm;
		sstm << "v" << i;
		rotulo = sstm.str();
		grafo->inserirVertice(rotulo);
	}
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

	inserirVertices2(grafo, 0, 17);
    // inserirVertices2(grafo,1,10);
	construirGrafoCom5Componentes(grafo);
	// construirGrafoNaoPonderado(grafo);
	
    vector<string> vertices = grafo->getVertices();
    vector<vector<pair<int, int>>> arestas = grafo->getArestas();

    cout << "==Antes==\n";
    printVertices(vertices);
    printArestas(arestas);

    int colorido = grafo->colorir(); // 1

    vertices = grafo->getVertices();
    arestas = grafo->getArestas();
    
    cout << "==Depois==\n";
    printVertices(vertices);
    printArestas(arestas);
    cout << "colorido: " << colorido << endl;

	delete(grafo);

    return 0;
}