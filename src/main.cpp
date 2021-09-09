#include <iostream>
#include <algorithm>

using namespace std;

#include "./lib/tabelahash/tabelahashexercicio.h"

//& para forçar a passagem do objeto por referência
void criarTabela(TabelaHash<string, int>& tabela, int qtdadeRepeticoes, string itens[]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= qtdadeRepeticoes; j++) {
			tabela.inserir(itens[i] + to_string(j), 500);
		}
	}
}

int main() {	
	string itens[5] = { "cebola", "feijao", "tomate", "arroz", "macarrao" };
	TabelaHash<string, int> estoqueSupermercadoTabelaHash;

	int qtdadeRepeticoes = 2;
	criarTabela(estoqueSupermercadoTabelaHash,qtdadeRepeticoes,itens);
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= qtdadeRepeticoes; j++) {
			cout << i << " " << j << " " << itens[i] + to_string(j) << endl;
			cout << estoqueSupermercadoTabelaHash.contemChave(itens[i] + to_string(j)) << endl;
		}
	}

	// int qtdadeRepeticoes = 1000;
	// criarTabela(estoqueSupermercadoTabelaHash, qtdadeRepeticoes, itens);	
	// vector<string> chaves = estoqueSupermercadoTabelaHash.getChaves();

	// cout << chaves.size() << endl;

	// for (int i = 0; i < 5; i++) {
	// 	for (int j = 1; j <= qtdadeRepeticoes; j++) {
	// 		cout << count(chaves.begin(), chaves.end(), itens[i] + to_string(j)) << endl;
	// 	}
	// }	

	cout << estoqueSupermercadoTabelaHash.contemChave("arroz1") << endl;
	cout << estoqueSupermercadoTabelaHash.size() << endl;
	cout << estoqueSupermercadoTabelaHash.bucket_count() << endl;	

	estoqueSupermercadoTabelaHash.printTabela();

	estoqueSupermercadoTabelaHash.clear();

    return 0;
}