
//
// Created by clara on 31/03/2026.
//

#include "jogo.h"
#include "jogador.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

string obterEquipaAdvAleatoria() {
    string equipas[50];
    int total = 0;
    string linha;
    fstream fs;
    fs.open("equipas.txt", ios::in);
    if (fs.is_open()) {
        while (getline(fs, linha)) {
            equipas[total++] = linha;
        }
        fs.close();
    }
    return equipas[rand() % total];
}

int encontrarSubstituto(ListaJogadores &s, string pos, int grS, int defS, int medS, int avaS) {
    for (int i = 0; i < s.tamanho; i++) {
        if (s.jogadores[i].posicao == pos)
            return i;
    }
    string escolhida;

    if (grS >= defS && grS >= medS && grS >= avaS)
        escolhida = "GR";
    else if (defS >= medS && defS >= avaS)
        escolhida = "DEF"; // não precisamos de comparar com grS porque já verificamos antes se ele era o maior
    else if (medS>= avaS)
        escolhida = "MED";
    else
        escolhida = "AVA";

    for (int i = 0; i < s.tamanho; i++) {
        if (s.jogadores[i].posicao == escolhida)
            return i;
    }
    return 0;
}

void simularJornada(ListaJogadores &plantel, ListaJogadores &titulares, ListaJogadores &suplentes, ListaJogadores &lesionados, ListaJogadores &castigados, ListaJogadores &transferencias, bool usados[], string adversario) {

    int jogadoresEmJogo = titulares.tamanho;
    int substituicoes = 0;

    string adversario = obterEquipaAdvAleatoria();
    int totalGolos = rand() % 9; // mínimo 0 golos, máximo 8 golos, no total
    int golosEDA = rand() % (totalGolos + 1); // escolher um número aleatório entre 0 e o total de golos que deu, para ver quantos golos o EDA FC marcou
    int golosADV = totalGolos - golosEDA; // depois o que restar fica para a equipa adversária

    cout << "EDA FC vs" << adversario << endl;
    //cout << "Resultado : EDA FC:" << golosEDA << " - " << adversario << ":"<< golosADV << endl;

    //simular lesões um a um
    for (int i = 0; i < titulares.tamanho; i++) {
        int r = rand() % 101;

        if (r < titulares.jogadores[i].probLesao) { // se esse número for menos que a probabilidade de lesão desse jogador então ele é lesionado

            if (substituicoes < 3 && suplentes.tamanho > 0) {
                int s = encontrarSubstituto(suplentes, titulares.jogadores[i].posicao, grS, defS, medS, avaS);
                inserirJogador(titulares, suplentes.jogadores[s]);
                removerJogador(suplentes, s);
                substituicoes++;
            } else {
                jogadoresEmJogo--;
            }
            lesionarJogador(plantel, lesionados, i);
            i--; // como o lesionarJogador remove um jogador e os outros que estavam à sua frente andam uma casa para trás temos de decrementar o i para não saltarmos um jogador
        }
    }
    //simular castigos um a um
    for (int i = 0; i < titulares.tamanho; i++) {
        int r = rand() % 101;

        if (r < titulares.jogadores[i].probCastigo) { // se esse número for menos que a probabilidade de castigo desse jogador então ele é castigado

            if (substituicoes < 3) { // se ainda não tivermos usado as 3 substituições
                int s = encontrarSubstituto(suplentes, titulares.jogadores[i].posicao, grS, defS, medS, avaS);
                inserirJogador(titulares, suplentes.jogadores[s]);
                removerJogador(suplentes, s);
                substituicoes++; // incrementamos o número de substituições usadas
            } else {
                jogadoresEmJogo--; // se já tivermos usado as 3, o jogador sai à mesma, mas a equipa passa a jogar com menos um jogador
            }
            castigarJogador(plantel, castigados, i);
            i--; // como o castigarJogador remove um jogador e os outros andam uma casa para trás temos de decrementar o i para não saltarmos um jogador
        }
    }
    if (plantel.tamanho < 7) {
        cout << "Não há jogadores suficientes. Ora bolas!";
    }
    if (jogadoresEmJogo < 7) {
        cout << "O jogo foi terminado por falta de jogadores.\n";
        if (golosADV > 3) {
            cout << "Resultado : EDA FC:0" << " - " << adversario << ":"<< golosADV << endl;
        } else {
            cout << "Resultado : EDA FC:0" << " - " << adversario << ":"<< 3 << endl;
        }
    } else {
        cout << "Resultado : EDA FC:" << golosEDA << " - " << adversario << ":"<< golosADV << endl;
    }
    //transferências
    for (int i = 0; i < 2; i++) {
        string posicoes[] = {"GR","DEF","MED","AVA"};

        Jogador j = criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), posicoes[rand() % 4]);
        inserirJogador(transferencias, j);
    }
}