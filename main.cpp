#include <iostream> //ficheiro de texto que contem as instruções e as declarações de funções referentes a ações de entrada e saída de dados - biblioteca standard input/output
#include <stdlib.h>
#include <time.h> // Para o seed do rand

#include "plantel.h"
#include "jogador.h"
#include "jogo.h"
#include "equipa.h"

using namespace std;

int main() {
    srand(time(NULL));

    ListaJogadores plantel; //declaração dos diferentes arrays
	ListaJogadores lesionados;
	ListaJogadores castigados;
	ListaJogadores transferencias;
	ListaJogadores titulares;
	ListaJogadores suplentes;
	bool usados[100] = {false}; // todos começam como não usados; é até 100 porque iremos como índices (usados[numero]) ignoramos o 0
    //int capacidade = 20 + rand() % 11; // 20 a 30 jogadores
	//int capacidadeMax = 30;
    inicializarLista(plantel, 30); //inicialização dos arrays
	inicializarLista(lesionados, 30);
	inicializarLista(castigados, 30);
	inicializarLista(transferencias, 30);

    gerarPlantel(plantel, usados); // aqui p = plantel

	string equipas[17];

	int i = 0;
	while (i < 17) {
		string e = obterEquipaAdvAleatoria();
		bool repetida = false;
		for (int j= 0; j < i; j++) {
			if (equipas[j] == e) repetida = true;
		}
		if (!repetida) {
			equipas[i] = e;
			i++;
		}
	}

	//JORNADAS
	for (int j = 0; j < 34; j++) {
		cout << "\n====== JORNADA " << j + 1 << " =====\n";
		string adversario = equipas[j/2];
		selecionarEquipa(plantel, titulares, suplentes);
		simularJornada(plantel, titulares, suplentes, lesionados, castigados, transferencias, usados, adversario);
	}

	do {
		cout << "\n===== JORNADA " << jornada++ << " =====\n";
		selecionarEquipa(plantel, titulares, suplentes);
		simularJornada(plantel, titulares, suplentes, lesionados, castigados, transferencias, usados, adversario);
		cout << "\n(s) seguinte    (o) sair ";
		cin >> escolha;
	} while (escolha == 's');

	return 0;
}

// struct equipa {
//     jogador* plantel;
//     jogador* convocados;
//     int nGr;
//     int nDef;
//     int nMed;
//     int nAva;
//};

// int main() {
//     srand(time(NULL));
//     string* nomes = new nome[118]; //Cria um apontador de nome "nomes" do tipo string e cria se 118 lugares do tipo "nomes" que recebera o nome dos jogadores
// }

