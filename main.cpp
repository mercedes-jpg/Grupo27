#include <iostream> //ficheiro de texto que contem as instruções e as declarações de funções referentes a ações de entrada e saída de dados - biblioteca standard input/output
#include <stdlib.h>
#include <time.h>

#include "plantel.h"
#include "jogador.h"

using namespace std;

int main() {
    srand(time(NULL));

    ListaJogadores plantel;

    int capacidade = 20 + rand() % 11; // 20 a 30 jogadores
    inicializarPlantel(plantel, capacidade);

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

