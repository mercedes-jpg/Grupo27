#include <iostream>

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
    std::cout << "Hello World!" << std::endl;
}
// parece que sim

