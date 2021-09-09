#include <iostream>
#include <vector>

using namespace std;

template <typename K, typename V>
class Tupla {
	private:
		K chave;
		V valor;
		Tupla* prox;
	public:
		Tupla(K c, V v) {
			chave = c;
			valor = v;
			prox = NULL;
		}

		K getChave() {
			return chave;
		}

		V getValor() {
			return valor;
		}

		Tupla* getProx() {
			return prox;
		}

		void setValor(V valor) {
			Tupla::valor = valor;
		}

		void setProx(Tupla* prox) {
			Tupla::prox = prox;
		}
};

template <typename Chave, typename Valor>
class TabelaHash {

	private:
		Tupla<Chave, Valor>** tabela;

		//tamanho atual do array
		int qtde_buckets;
		//qtdade de elementos já inseridos na tabela hash
		int tamanho;

		int obterPosicaoDaChave(Chave chave) {
			hash<string> hash_string;
			int hash = hash_string(chave);

			return abs(hash) % qtde_buckets;
		}

		/**
		* Função para inserir a tupla <c,v> na tabela.
		* É preciso calcular o código hash a partir da chave c.
		* Em seguida, usamos qtde_buckets para descobrir o índice
		* dessa tupla. Prestar atenção na alocação de tupla quando
		* há colisões. A função hash às vezes retorna valores
		* negativos: use abs() para evitar índices negativos.
		**/
		void inserir(Chave c, Valor v, Tupla<Chave, Valor>** tabela) {
			int posicao = obterPosicaoDaChave(c);

			Tupla<Chave, Valor>* entry = new Tupla<Chave, Valor>(c, v);

			if(tabela[posicao] == NULL){
				tabela[posicao] = entry;
			} else {
				Tupla<Chave, Valor>* entries = tabela[posicao];

				while(entries->getProx() != NULL){
					entries = entries->getProx();
				}

				entries->setProx(entry);
			}

			// Tupla<Chave, Valor>* p = NULL;
			// Tupla<Chave, Valor>* en = tabela[posicao];

			// while(en != NULL){
			// 	p = en;
			// 	en = en->getProx();
			// }

			// if(en == NULL){
			// 	en = new Tupla<Chave, Valor>(c, v);

			// 	if(p == NULL){
			// 		tabela[posicao] = en;
			// 	} else {
			// 		p->setProx(en);
			// 	}
			// } else {
			// 	en->setValor(v);
			// }
		}

		/**
		* Função para aumentar o tamanho do array quando o
		* fator de carga for >= 1. O tamanho do array
		* (qtde_buckets) deve ser multiplicado por 8 para
		* que essa operação seja feita com pouca frequência.
		* Por fim, precisamos reposicionar as tuplas, considerando
		* que a posição nesse novo array com maior tamanho
		* será diferente.
		**/
		void aumentaArray() {
			qtde_buckets *= 8;

			Tupla<Chave, Valor>** novaTabela = new Tupla<Chave, Valor>*[qtde_buckets];

			for(int i = 0; i < qtde_buckets; i++){
				novaTabela[i] = NULL;
			}

			cout << "qt buckets: " << qtde_buckets << ", " << qtde_buckets/8 << endl;

			for(int i = 0; i < qtde_buckets / 8; i++) {
				if(tabela[i] == NULL) continue;

				int posicao = obterPosicaoDaChave(tabela[i]->getChave());

				// cout << "posicao da chave " << tabela[i]->getChave() << ": " << posicao << endl;

				novaTabela[posicao] = tabela[i];
			}

			tabela = novaTabela;
		}

	public:

		/**
		* Inicializar o array de tuplas com capacidade = qtde_buckets.
		* Lembrar de setar todas as posições do array inicializado
		* para NULL.
		**/
		TabelaHash() {
			qtde_buckets = 8;
			tamanho = 0;

			tabela = new Tupla<Chave, Valor>*[qtde_buckets];

			for(int i = 0; i < qtde_buckets; i++){
				tabela[i] = NULL;
			}
		}

		/**
		* Essa é a função pública que nos permite inserir
		* uma tupla <c,v> na tabela. Nessa função nós
		* verificamos se é preciso aumentar o array de acordo
		* com o load factor. Essa função pode reusar sua versão
		* sobrecarregada para inserir a tupla na tabela.
		* Essa função também incrementa a quantidade de elementos
		* na tabela (variável tamanho).
		**/
		void inserir(Chave c, Valor v) {
			double fator_de_carga = load_factor();
			
			if(fator_de_carga >= 1) aumentaArray();

			inserir(c, v, tabela);
			tamanho++;
		}

		/**
		* Essa função retorna o fator de carga da Tabela Hash.
		**/
		double load_factor() {
			return (double) tamanho / qtde_buckets;
		}

		/**
		* Há apenas um valor associado a uma chave.
		* Essa função retorna esse valor, caso a chave exista.
		* Se a chave não existir a função retorna NULL.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		**/
		Valor getValor(Chave chave) {
			int posicao = obterPosicaoDaChave(chave);

			Tupla<Chave, Valor>* entries = tabela[posicao];

			if(entries != NULL){
				while(entries->getChave() != chave && entries->getProx() != NULL){
					entries = entries->getProx();
				}

				return entries->getValor();
			}

			return NULL;
		}

		/**
		* Essa função retorna true caso a chave exista,
		* false caso contrário.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		**/
		bool contemChave(Chave chave) {
			int posicao = obterPosicaoDaChave(chave);

			Tupla<Chave, Valor>* entries = tabela[posicao];

			if(entries != NULL){
				cout << "chave: " << entries->getChave() << endl;

				while(entries->getChave() != chave && entries->getProx() != NULL){
					entries = entries->getProx();
				}

				return true;
			}

			// cout << "posicao: " << posicao << endl;

			// Tupla<Chave, Valor>* en = tabela[posicao];

			// if(en != NULL){
			// 	while(en != NULL){
			// 		cout << "chave atual: " << en->getChave() << ", chave a ser comparada: " << chave << endl;
			// 		if(en->getChave() == chave){
			// 			cout << chave << " existe." << endl;
			// 			return true;
			// 		}

			// 		en = en->getProx();
			// 		cout << "prox: " << en->getChave() << endl;
			// 	}
			// }

			return false;
		}

		/**
		* Essa função retorna um vetor com todas as chaves
		* já inseridas na tabela.
		**/
		vector<Chave> getChaves() {
			vector<Chave> vec;

			for(int i = 0; i < qtde_buckets; i++){
				Tupla<Chave, Valor>* entries = tabela[i];

				if(entries != NULL){
					while(entries != NULL){
						vec.push_back(entries->getChave());

						entries = entries->getProx();
					}
				}
			}

			return vec;
		}

		/**
		* Essa função desaloca os nós previamente alocados, e muda
		* o tamanho do array de tuplas para 8.
		**/
		void clear() {
			//IMPLEMENTAR
		}

		/**
		* Há apenas um nó associado com uma mesma chave.
		* Essa função remove esse nó da tabela, caso a chave exista.
		* Se a chave não existir a função não faz nada.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		* Dica: olhar algoritmo de remoção em lista ligada, pois
		* após a remoção de um nó a lista precisa permanecer íntegra,
		* ou seja, navegável.
		**/
		void remover(Chave chave) {
			int posicao = obterPosicaoDaChave(chave);

			Tupla<Chave, Valor>* anterior = tabela[posicao];
			Tupla<Chave, Valor>* atual = anterior->getProx();

			while(atual != NULL){
				if(atual->getChave() == chave){
					break;
				} else {
					anterior = atual;
					atual = atual->getProx();
				}

				if(atual != NULL){
					anterior->setProx(atual->getProx());
					delete atual;
					tamanho--;
				}
			}

		}

		/**
		* Essa função retorna a quantidade de pares
		* que já foram inseridos na Tabela Hash.
		**/
		int size() {
			return tamanho;
		}

		/**
		* Essa função retorna o tamanho atual do
		* array usado para armazenar a Tabela Hash.
		**/
		int bucket_count() {
			return qtde_buckets;
		}

		void printTabela() {
			cout << "[";
			for(int i = 0; i < qtde_buckets; i++) {
				if(!tabela[i]) {
					cout << 0 << ", ";
				} else {
					Tupla<string, int>* en = tabela[i];
					
					cout << "[";
					if(en != NULL){
						while(en != NULL){
							cout << "{" << en->getChave() << ": " << en->getValor() << "}, ";

							en = en->getProx();
						}
					}
					cout << "], ";
				}
			}
			cout << "]\n";
		}
};