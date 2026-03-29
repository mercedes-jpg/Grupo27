//
// Created by clara on 29/03/2026.
//

#ifndef GRUPO27_PLANTEL_H
#define GRUPO27_PLANTEL_H

#include "jogador.h" // como usamos jogador o compilador precisa saber o que é um jogador; quando usamos uma struct temos de incluir o ficheiro onde ela está definida

struct ListaJogadores {
    Jogador* jogadores; //array dinâmico
    int tamanho; // nº atual de jogadores
    int capacidade; //capacidade do plantel, ou seja, o nº máximo de jogadores
};

#endif //GRUPO27_PLANTEL_H