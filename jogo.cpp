
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

void simularJornada(ListaJogadores &plantel, ListaJogadores &titulares, ListaJogadores &suplentes, ListaJogadores &lesionados, ListaJogadores &castigados, ListaJogadores &transferencias, bool usados[], string adversario, int &pontos) {

    int substituicoes = 0;
    int grS=0, defS=0, medS=0, avaS=0;
    for (int i = 0; i < suplentes.tamanho; i++) {
        if (suplentes.jogadores[i].posicao == "GR")
            grS++;
        else if (suplentes.jogadores[i].posicao == "DEF")
            defS++;
        else if (suplentes.jogadores[i].posicao == "MED")
            medS++;
        else if (suplentes.jogadores[i].posicao == "AVA")
            avaS++;
    }

    int totalGolos = rand() % 9; // mínimo 0 golos, máximo 8 golos, no total
    int golosEDA = rand() % (totalGolos + 1); // escolher um número aleatório entre 0 e o total de golos que deu, para ver quantos golos o EDA FC marcou
    int golosADV = totalGolos - golosEDA; // depois o que restar fica para a equipa adversária

    // atualizar pontos do EDA FC

    if (golosEDA > golosADV)
        pontos = pontos + 3;
    else if (golosEDA == golosADV)
        pontos = pontos + 1;

    cout << "EDA FC vs " << adversario << endl;
    cout << "Resultado : EDA FC:" << golosEDA << " - " << adversario << ":"<< golosADV << endl;


    string subs = "";
    //simular lesões um a um
    for (int i = 0; i < titulares.tamanho; i++) {
        int r = rand() % 101;

        if (r < titulares.jogadores[i].probLesao) { // se esse número for menos que a probabilidade de lesão desse jogador então ele é lesionado

            if (substituicoes < 3 && suplentes.tamanho > 0) {
                int s = encontrarSubstituto(suplentes, titulares.jogadores[i].posicao, grS, defS, medS, avaS);
                subs = subs + titulares.jogadores[i].nome + " -> " + suplentes.jogadores[s].nome + "\n";
                inserirJogador(titulares, suplentes.jogadores[s]);
                removerJogador(suplentes, s);
                substituicoes++;
            }
            else {
                removerJogador(titulares, i);
                i--; // como remove um jogador e os outros andam uma casa para trás temos de decrementar o i para não saltarmos um jogador
            }
            lesionarJogador(plantel, lesionados, i);
        }
    }
    //simular castigos um a um
    for (int i = 0; i < titulares.tamanho; i++) {
        int r = rand() % 101;

        if (r < titulares.jogadores[i].probCastigo) { // se esse número for menos que a probabilidade de castigo desse jogador então ele é castigado

            if (substituicoes < 3) { // se ainda não tivermos usado as 3 substituições
                int s = encontrarSubstituto(suplentes, titulares.jogadores[i].posicao, grS, defS, medS, avaS);

                subs = subs + titulares.jogadores[i].nome + " -> " + suplentes.jogadores[s].nome + "\n";
                inserirJogador(titulares, suplentes.jogadores[s]);
                removerJogador(suplentes, s);
                substituicoes++; // incrementamos o número de substituições usadas
            }
            else {
                removerJogador(titulares, i); // se já tivermos usado as 3, o jogador sai à mesma, mas a equipa passa a jogar com menos um jogador
                i--; //como remove um jogador e os outros andam uma casa para trás temos de decrementar o i para não saltarmos um jogador
            }
            castigarJogador(plantel, castigados, i);
        }
    }
    if (plantel.tamanho < 7) {
        cout << "Não há jogadores suficientes. Ora bolas!";
    }
    if (titulares.tamanho < 7) {
        cout << "O jogo foi terminado por falta de jogadores.\n";
        if (golosADV > 3) {
            cout << "Resultado : EDA FC:0" << " - " << adversario << ":"<< golosADV << endl;
        } else {
            cout << "Resultado : EDA FC:0" << " - " << adversario << ":"<< "3" << endl;
        }
    } else {
        cout << "Resultado : EDA FC:" << golosEDA << " - " << adversario << ":"<< golosADV << endl;
    }

    cout << "\nSubstituições:\n" << subs << endl;

    //transferências
    for (int i = 0; i < 2; i++) {
        string posicoes[] = {"GR","DEF","MED","AVA"};

        Jogador j = criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), posicoes[rand() % 4]);
        inserirJogador(transferencias, j);
    }
}