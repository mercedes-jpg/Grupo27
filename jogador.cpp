//
// Created by clara on 29/03/2026.
//
#include "jogador.h"
#include <stdlib.h> // dá acesso a rand()

Jogador criarJogador(string nome, int numero, string posicao) {
    Jogador j;
    j.nome = nome;
    j.numero = numero;
    j.posicao = posicao;

    j.idade = rand() % 25 + 16; // entre 16 e 40
    j.probLesao = rand() % 16; // entre 0 e 15
    j.probCastigo = rand() % 21; // entre 0 e 20
    j.qualidade = rand() % 101; // entre 0 e 100

    j.diasTreino = 0;
    j.jornadasLesao = 0;
    j.jornadasCastigo = 0;

    return j;
}