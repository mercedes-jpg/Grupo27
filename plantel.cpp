//
// Created by clara on 29/03/2026.
//
//.cpp implementa
#include "plantel.h"
#include "jogador.h"
#include <stdlib.h>

void inicializarPlantel(ListaJogadores &p, int capacidade) {
    p.jogadores = new Jogador[capacidade]; //hummmmm
    p.tamanho = 0;
    p.capacidade = capacidade;
}
void lesionarJogador(ListaJogadores &plantel, ListaJogadores &lesionados, int index) {
    Jogador j =plantel.jogadores[index]; //vai buscar o jogador ao plantel
    j.jornadasLesao = 1 + rand() % 10; // jornadas a ficar lesionado 1 a 10 aleatoriamente
    lesionados.jogadores[lesionados.tamanho++] = j; // mete o jogador j na lista lesionados dos jogadores acedida atraves dos mesmos na posição tamanho e dps encrementa 1
    removerJogador(plantel, index); //remove jogador j do plantel atraves da funcao remover jogador ja defenida
}

void castigarJogador(ListaJogadores &plantel, ListaJogadores &castigados, int index) {
    Jogador j =plantel.jogadores[index]; //vai buscar o jogador ao plantel
    j.jogosCastigo = 1 + rand() % 10; // jogos a ficar castigado 1 a 10 aleatoriamente
    castigados.jogadores[castigados.tamanho++] = j; // mete o jogador j na lista lesionados dos jogadores acedida atraves dos mesmos na posição tamanho mais 1
    removerJogador(plantel, index); //remove jogador j do plantel atraves da funcao remover jogador ja defenida
}
void adicionarTransferencia(ListaJogadores &transferencias, Jogador j) {
    transferencias.jogadores[transferencias.tamanho++] = j;
}
void inserirJogador(ListaJogadores &p, Jogador j) {
    if (p.tamanho < p.capacidade) { //se o nº de jogadores atual for menor que a capacidade do plantel
        p.jogadores[p.tamanho] = j; //então vamos inserir o jogador no fim da lista   hummmmm
        p.tamanho++; // e o nº atual de jogadores será incrementado num valor
    }
}

void removerJogador(ListaJogadores &p, int index) {
    for (int i = index; i < p.tamanho -1; i++) { //i começa no que vamos remover
        p.jogadores[i] = p.jogadores[i+1]; //para nao deixar espaços em branco os jogadores que vêm depois dele vao recuar uma casa isto é esse lugar vai ser do jogador que vem logo de seguida
    }
    p.tamanho--; //hummmmm o último não fica duplicado por causa disto
}

void gerarPlantel(ListaJogadores &p) { //ListaJogadores é o tipo, p(plantel) é a variável
    int numero = 1;

   int gr = 2 + rand() % 2; //mínimo 2 GR, máximo 3 GR
    for (int i = 0; i < gr; i++) { // o i é nos GR
        string nome = obterNomeAleatorio();
        p.jogadores[p.tamanho++] = criarJogador(nome, numero++, "GR"); //p.jogadores -> aceder ao array; p.tamanho++ -> usa o tamanho atual e depois incrementa-o
    }
    int def = 7 + rand() % 4; // mínimo 7 DEF, máximo 10 DEF
    for (int i = 0; i < def; i++) {
        string nome = obterNomeAleatorio();
        p.jogadores[p.tamanho++] = criarJogador(nome, numero++, "DEF");
    }
    int med = 7 + rand() % 4; // mínimo 7 MED, máximo 10 MED
    for (int i = 0; i < med; i++) {
        string nome = obterNomeAleatorio();
        p.jogadores[p.tamanho++] = criarJogador(nome, numero++, "MED");
    }
    int ava = 4 + rand() % 4; // minimo 4 AVA, máximo 7 AVA
    for (int i = 0; i < ava; i++) {
        string nome = obterNomeAleatorio();
        p.jogadores[p.tamanho++] = criarJogador(nome, numero++, "AVA");
    }
}