//
// Created by clara on 29/03/2026.
//
#include "plantel.h"
#include <stdlib.h>

void inicializarPlantel(ListaJogadores &p, int capacidade) {
    p.jogadores = new Jogador[capacidade];
    p.tamanho = 0;
    p.capacidade = capacidade;
}

void inserirJogador(ListaJogadores &p, Jogador j) {
    if (p.tamanho < p.capacidade) { //se o nº de jogadores atual for menor que a capacidade do plantel
        p.jogadores[p.tamanho] = j; //então vamos inserir o jogador no fim da lista
        p.tamanho++; // e o nº atual de jogadores será incrementado num valor
    }
}

void removerJogador(ListaJogadores &p, int index) {
    for (int i = index; i < p.tamanho -1; i++) { //i começa no que vamos remover
        p.jogadores[i] = p.jogadores[i+1]; //para nao deixar espaços em branco os jogadores que vêm depois dele vao recuar uma casa isto é esse lugar vai ser do jogador que vem logo de seguida
    }
    p.tamanho--;
}