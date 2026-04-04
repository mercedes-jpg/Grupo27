//
// Created by clara on 29/03/2026.
//
//.h declara
#ifndef GRUPO27_PLANTEL_H
#define GRUPO27_PLANTEL_H

#include "jogador.h" // como usamos jogador o compilador precisa saber o que é um jogador; quando usamos uma struct temos de incluir o ficheiro onde ela está definida

struct ListaJogadores {
    Jogador* jogadores; //array dinâmico  hummmmmm jogadores porque é um array de vários jogadores
    int tamanho; // número atual de jogadores
    int capacidade; // número inicial de jogadores
    const int CAPACIDADEMAX = 30; // no máximo 30 jogadores
};

void inicializarPlantel(ListaJogadores &p, int capacidade);
void inserirJogador(ListaJogadores &p, Jogador j);
void removerJogador(ListaJogadores &p, int a);

void lesionarJogador(ListaJogadores &plantel, ListaJogadores &lesionados, int a);
void castigarJogador(ListaJogadores &plantel, ListaJogadores &castigados, int a);

void recuperarLesionado(ListaJogadores &plantel, ListaJogadores &lesionados, int a);
void recuperarCastigado(ListaJogadores &plantel, ListaJogadores &castigados, int a);
void adicionarTransferencia(ListaJogadores &transferencias, Jogador j);

void gerarPlantel(ListaJogadores &p, bool usados[]); // o & serve para obter o endereço de uma variável na memória (passagem por referência), assim mudamos o plantel verdadeiro; sem & as alterações não ficariam guardadas

#endif //GRUPO27_PLANTEL_H