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
	bool usados[100] = {false}; // todos começam como não usados; é até 100 porque iremos como índices (usados[numero]) ignoramos o 0
    //int capacidade = 20 + rand() % 11; // 20 a 30 jogadores
	//int capacidadeMax = 30;
    inicializarPlantel(plantel, 30); //inicialização dos arrays
	inicializarPlantel(lesionados, 30);
	inicializarPlantel(castigados, 30);
	inicializarPlantel(transferencias, 30);

    gerarPlantel(plantel, usados); // aqui p = plantel

	char escolha;
	int jornada = 1;

	do {
		cout << "\n===== JORNADA " << jornada++ << " =====\n";
		simularJornada(plantel, lesionados, castigados, transferencias, usados);
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

