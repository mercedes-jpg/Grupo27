
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

void simularJornada(ListaJogadores &plantel, ListaJogadores &lesionados, ListaJogadores &castigados, ListaJogadores &transferencias, bool usados[]) {
    int jogadoresEmJogo = (plantel.tamanho >= 11) ? 11 : plantel.tamanho; // se tivermos 11 ou mais jogadores no plantel, inicialmente serão 11 que irão jogar, se só tiver 10, 9, 8 ou 7 será esse o número de jogadores a jogar
    int substituicoes = 0;

    string adversario = obterEquipaAdvAleatoria();
    int totalGolos = rand() % 9; // mínimo 0 golos, máximo 8 golos, no total
    int golosEDA = rand() % (totalGolos + 1); // escolher um número aleatório entre 0 e o total de golos que deu, para ver quantos golos o EDA FC marcou
    int golosADV = totalGolos - golosEDA; // depois o que restar fica para a equipa adversária

    cout << "EDA FC vs" << adversario << endl;
    cout << "Resultado : EDA FC:" << golosEDA << " - " << adversario << ":"<< golosADV << endl;

    //simular lesões um a um
    for (int i = 0; i < jogadoresEmJogo; i++) {
        int r = rand() % 101;

        if (r < plantel.jogadores[i].probLesao) { // se esse número for menos que a probabilidade de lesão desse jogador então ele é lesionado

            if (substituicoes < 3) {
                substituicoes++;
            } else {
                jogadoresEmJogo--;
            }
            lesionarJogador(plantel, lesionados, i);
            i--; // como o lesionarJogador remove um jogador e os outros que estavam à sua frente andam uma casa para trás temos de decrementar o i para não saltarmos um jogador
        }
    }
    //simular castigos um a um
    for (int i = 0; i < jogadoresEmJogo; i++) {
        int r = rand() % 101;

        if (r < plantel.jogadores[i].probCastigo) { // se esse número for menos que a probabilidade de castigo desse jogador então ele é castigado

            if (substituicoes < 3) { // se ainda não tivermos usado as 3 substituições
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
    }
    //transferências
    for (int i = 0; i < 2; i++) {
        string posicoes[] = {"GR","DEF","MED","AVA"};

        Jogador j = criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), posicoes[rand() % 4]);
        inserirJogador(transferencias, j);
    }
}