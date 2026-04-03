
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
    string equipas[100];
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

void simularJornada(ListaJogadores &plantel, ListaJogadores &lesionados, ListaJogadores &castigados, ListaJogadores &transferencias) {
    int jogadoresEmJogo;
    string adversario = obterEquipaAdvAleatoria();
    int totalGolos = rand() % 9; // mínimo 0 golos, máximo 8 golos, no total
    int golosEDA = rand() % (totalGolos + 1); // escolher um número aleatório entre 0 e o total de golos que deu, para ver quantos golos o EDA FC marcou
    int golosADV = totalGolos - golosEDA; // depois o que restar fica para a equipa adversária

    cout << "\n=== JORNADA ===\n";
    cout << "EDA FC vs" << adversario << endl;
    cout << "Resultado : EDA FC:" << golosEDA << " - " << adversario << ":"<< golosADV << endl;

    if (plantel.tamanho >= 11)
        jogadoresEmJogo = 11;
    else
        jogadoresEmJogo = plantel.tamanho;

    //simular lesões um a um
    for (int i = 0; i < jogadoresEmJogo; i++) {
        int r = rand() % 101;
        if (r < plantel.jogadores[i].probLesao) {
            lesionarJogador(plantel, lesionados, i);
            jogadoresEmJogo--;
            i--; // como o lesionarJogador remove um jogador e os outros que estavam à sua frente andam uma casa para trás temos de decrementar o i para não saltarmos um jogador
        }
    }
    //simular castigos um a um
    for (int i = 0; i < jogadoresEmJogo; i++) {
        int r = rand() % 101;
        if (r < plantel.jogadores[i].probCastigo) {
            castigarJogador(plantel, castigados, i);
            jogadoresEmJogo--;
            i--; // como o castigarJogador remove um jogador e os outros andam uma casa para trás temos de decrementar o i para não saltarmos um jogador
        }
    }
    if (plantel.tamanho < 7) {
        cout << "Não há jogadores suficientes. Ora bolas!";
    }
    if (jogadoresEmJogo < 7) {
        cout << "O jogo foi terminado por falta de jogadores.";
    }
    //transferências
    for (int i = 0; i < 2; i++) {
        string posicoes[] = {"GR","DEF","MED","AVA"};
        Jogador j = criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), posicoes[rand() % 4]);
        inserirJogador(transferencias, j);
    }
}