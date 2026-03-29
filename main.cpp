#include <iostream> //ficheiro de texto que contem as instruções e as declarações de funções referentes a ações de entrada e saída de dados - biblioteca standard input/output

using namespace std;

struct jogador {
    string nome;
    int numero;
    string posicao;
    int idade;
    int probLesao;
    int probCastigo;
    int qualidade;
    bool lesionado;
};


struct equipa {
    jogador* plantel;
    jogador* convocados;
    int nGr;
    int nDef;
    int nMed;
    int nAva;
};
int main() {
    srand(time(NULL));
    string* nomes = new nome[118]; //Cria um apontador de nome "nomes" do tipo string e cria se 118 lugares do tipo "nomes" que recebera o nome dos jogadores
}

