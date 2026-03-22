#include <iostream>
//teste123456789

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
    int nAva;

};
int main() {
    std::cout << "Hello World!" << std::endl;
}
// parece que sim

