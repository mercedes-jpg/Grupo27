//
// Created by clara on 29/03/2026.
//
//.h declara
#ifndef GRUPO27_PLANTEL_H
#define GRUPO27_PLANTEL_H

#include "jogador.h" // como usamos jogador o compilador precisa saber o que é um jogador; quando usamos uma struct temos de incluir o ficheiro onde ela está definida

struct ListaJogadores {
    Jogador* jogadores; //array dinâmico  hummmmmm jogadores porque é um array de vários jogadores
    int tamanho; // nº atual de jogadores
    int capacidade; //capacidade do plantel, ou seja, o nº máximo de jogadores
};

void inicializarPlantel(ListaJogadores &p, int capacidade);
void lesionarJogador(ListaJogadores &plantel, ListaJogadores &lesionados, int index);
void castigarJogador(ListaJogadores &plantel, ListaJogadores &castigados, int index);
void adicionarTransferencia(ListaJogadores &transferencias, Jogador j);
void recuperarLesionado(ListaJogadores &plantel, ListaJogadores &lesionados, int index);

void inserirJogador(ListaJogadores &p, Jogador j);
void removerJogador(ListaJogadores &p, int index);
void gerarPlantel(ListaJogadores &p); // o & serve para obter o endereço de uma variável na memória (passagem por referência), assim mudamos o plantel verdadeiro; sem & as alteraçaões não ficariam guardadas

#endif //GRUPO27_PLANTEL_H