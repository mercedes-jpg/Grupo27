#ifndef GRUPO27_JOGADOR_H
#define GRUPO27_JOGADOR_H

#include <string> // string não é básica como int, ela pertence à biblioteca <string>
using namespace std;

struct Jogador {
    string nome;
    int numero;
    string posicao;
    int idade;
    int probLesao;
    int probCastigo;
    int qualidade;
    int semanasTreino;
    int jornadasLesao;
    int jogosCastigo;

};

Jogador criarJogador(string nome, int numero, string posicao);
string obterNomeAleatorio(); // existe uma função com este nome e retorna string
int gerarNumeroUnico(bool usados[]);

#endif //GRUPO27_JOGADOR_H
