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
    int capacidade = 20 + rand() % 11; // 20 a 30 jogadores
	int capacidadeMax = 30;
    inicializarPlantel(plantel, capacidadeMax); //inicialização dos arrays
	inicializarPlantel(lesionados, capacidadeMax);
	inicializarPlantel(castigados, capacidadeMax);
	inicializarPlantel(transferencias, capacidadeMax);
    gerarPlantel(plantel); // aqui p = plantel
	simularJornada(plantel, lesionados, castigados, transferencias);

    cout << "Capacidade: " << capacidade << endl;

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

