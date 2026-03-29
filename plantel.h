//
// Created by clara on 29/03/2026.
//

#ifndef GRUPO27_PLANTEL_H
#define GRUPO27_PLANTEL_H

#include "jogador.h"

struct ListaJogadores {
    Jogador* jogadores; //array dinâmico
    int tamanho;
    int capacidade;
};

#endif //GRUPO27_PLANTEL_H