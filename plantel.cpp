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

void inserirJogador(ListaJogadores &p, Jogador j) {
    if (p.tamanho < p.capacidade) { //se o nº de jogadores atual for menor que a capacidade do plantel
        p.jogadores[p.tamanho] = j; //então vamos inserir o jogador no fim da lista
        p.tamanho++; // e o número atual de jogadores será incrementado num valor
    }
}

void removerJogador(ListaJogadores &p, int a) {
    for (int i = a; i < p.tamanho - 1; i++) { //i começa no que vamos remover
        p.jogadores[i] = p.jogadores[i+1]; //para não deixar espaços em branco os jogadores que vêm depois dele vão recuar uma casa isto é esse lugar vai ser do jogador que vem logo de seguida
    }
    p.tamanho--; //o último não fica duplicado por causa disto
}

void gerarPlantel(ListaJogadores &p) { //ListaJogadores é o tipo, p(plantel) é a variável
    bool usados[100] = {false}; // todos começam como não usados; até 100 porque usados[numero] ignoramos o 0

    int total = 20 + rand() % 11; // 20 a 30
    p.tamanho = 0;

    int gr = 2, def = 7, med = 7, ava = 4; // numero minimo de cada posição
    int restantes = total - 20; // tirando do número aleatório 20 que são os jogadores mínimos

    while (restantes > 0) { //enquanto restar jogadores para criar
        int r = rand() % 4; //vamos escolher aleatoriamente uma posição para cada um deles

        if (r == 0 && gr < 3) { gr++; restantes--;} // se já tiver no máximo da posição então não entra em nenhum if e gera outro r
        else if (r == 1 && def < 10) { def++; restantes--;}
        else if (r == 2 && med < 10) { med++; restantes--;}
        else if (r == 3 && ava < 7) { ava++; restantes--;}
    }
    //criar jogadores por ordem
    for (int i= 0; i < gr; i++) // o for percorre o plantel atraves dos indices: sendo i = 0 e i<gr que é o numero de gr no plantel insere o jogador j no plantel p incrementando 1 em i
        inserirJogador(p, criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), "GR")); //a função inserir jogador recebe o plantel p e um jogador j criado pela função criarJogador, do tipo jogador - struct ja criada que cebe um nome, numero e posição, funcao esta que recebe 3 coisas
    for (int i = 0; i < def; i++)
        inserirJogador(p, criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), "DEF"));
    for (int i = 0; i < med; i++)
        inserirJogador(p, criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), "MED"));
    for (int i = 0; i < ava; i++)
        inserirJogador(p, criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), "AVA"));
}

void lesionarJogador(ListaJogadores &plantel, ListaJogadores &lesionados, int a) {
    Jogador j =plantel.jogadores[a]; //vai buscar o jogador ao plantel
    j.jornadasLesao = 1 + rand() % 10; // jornadas a ficar lesionado 1 a 10 aleatoriamente
    //lesionados.jogadores[lesionados.tamanho++] = j; // mete o jogador j na lista lesionados dos jogadores acedida através dos mesmos na posição tamanho e dps encrementa 1
    inserirJogador(lesionados, j); //adiciona o jogador j no fim da lista dos lesionados onde o jogador j é o jogador lesionado
	removerJogador(plantel, a); //remove jogador j do plantel através da função remover jogador já definida
}

void castigarJogador(ListaJogadores &plantel, ListaJogadores &castigados, int a) {
    Jogador j =plantel.jogadores[a]; //vai buscar o jogador ao plantel
    j.jogosCastigo = 1 + rand() % 10; // jogos a ficar castigado 1 a 10 aleatoriamente
    //castigados.jogadores[castigados.tamanho++] = j; // mete o jogador j na lista lesionados dos jogadores acedida através dos mesmos na posição de índice tamanho
    inserirJogador(castigados, j);
	removerJogador(plantel, a); //remove jogador j do plantel através da funcao remover jogador já definida
}

void recuperarLesionado(ListaJogadores &plantel, ListaJogadores &lesionados, int a) {
    Jogador j =lesionados.jogadores[a]; //vai buscar o jogador j à lista de lesionados, que contém jogadores, na posição index
    j.jornadasLesao = 0; // não fica lesionado nenhuma jornada neste momento, porque já recuperou da lesão
    inserirJogador(plantel, j); //adiciona o jogador j no fim da lista do plantel onde o jogador j é o jogador que recuperou da lesão
    removerJogador(lesionados, a); //remove jogador j dos lesionados atraves da funcao remover jogador ja definida
}

void recuperarCastigado(ListaJogadores &plantel, ListaJogadores &castigados, int a) {
    Jogador j =castigados.jogadores[a]; // vai buscar o jogador à lista de castigados
    j.jogosCastigo = 0; // não fica castigado em nenhum jogo, pois tirado do castigo
    inserirJogador(plantel, j);
    removerJogador(castigados, a); //remove jogador j da lista de castigados através da função remover jogador já definida
}

void adicionarTransferencia(ListaJogadores &transferencias, Jogador j) {
    inserirJogador(transferencias, j);
}