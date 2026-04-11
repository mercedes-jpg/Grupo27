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

void simularJornada(ListaJogadores &plantel, ListaJogadores &titulares, ListaJogadores &suplentes, ListaJogadores &lesionados, ListaJogadores &castigados, ListaJogadores & lesionadosJornada, ListaJogadores & castigadosJornada, bool usados[], string adversario, int &pontos, int &golosEDA, int&golosADV, string &subs) {

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

    if (titulares.tamanho < 7) {
        golosEDA = 0;
        golosADV = 3 + rand() % 6;
        return; // termina a função, sai da função simularJornada
    }
    else {
        int totalGolos = rand() % 9; // mínimo 0 golos, máximo 8 golos, no total
        golosEDA = rand() % (totalGolos + 1); // escolher um número aleatório entre 0 e o total de golos que deu, para ver quantos golos o EDA FC marcou
        golosADV = totalGolos - golosEDA; // depois o que restar fica para a equipa adversária
    }

    // atualizar pontos do EDA FC
    if (golosEDA > golosADV)
        pontos = pontos + 3;
    else if (golosEDA == golosADV)
        pontos = pontos + 1;

    subs = "";
    int substituicoes = 0;

    //simular lesões um a um
    for (int i = 0; i < titulares.tamanho; i++) {
        int r = rand() % 101;

        if (r < titulares.jogadores[i].probLesao) { // se esse número for menos que a probabilidade de lesão desse jogador então ele é lesionado

            int indicePlantel = encontrarIndicePorNumero(plantel, titulares.jogadores[i].numero);

            if (indicePlantel != -1) {
                lesionarJogador(plantel, lesionados, indicePlantel);
                int k = encontrarIndicePorNumero(lesionados, titulares.jogadores[i].numero);
                Jogador j = lesionados.jogadores[k];
                inserirJogador(lesionadosJornada, j);
                Jogador sai = titulares.jogadores[i];
                removerJogador(titulares, i);

                if (substituicoes < 3 && suplentes.tamanho > 0) {

                    int s = encontrarSubstituto(suplentes, sai.posicao, grS, defS, medS, avaS);

                    Jogador entra = suplentes.jogadores[s];
                    subs += sai.nome + " -> " + entra.nome + "\n";

                    removerJogador(suplentes, s);
                    inserirJogador(titulares, entra);
                    substituicoes++;
                }
                i--;
            }
        }
    }

    //simular castigos um a um
    for (int i = 0; i < titulares.tamanho; i++) {
        int r = rand() % 101;

        if (titulares.jogadores[i].jornadasLesao > 0) continue;

        if (r < titulares.jogadores[i].probCastigo) { // se esse número for menos que a probabilidade de castigo desse jogador então ele é castigado

            int indicePlantel = encontrarIndicePorNumero(plantel, titulares.jogadores[i].numero);

            if (indicePlantel != -1) {
                castigarJogador(plantel, castigados, indicePlantel);
                int k = encontrarIndicePorNumero(castigados, titulares.jogadores[i].numero);
                Jogador j = castigados.jogadores[k];
                inserirJogador(castigadosJornada, j);
                Jogador sai = titulares.jogadores[i];
                removerJogador(titulares, i);

                if (substituicoes < 3 && suplentes.tamanho > 0) { // se ainda não tivermos usado as 3 substituições

                    int s = encontrarSubstituto(suplentes, sai.posicao, grS, defS, medS, avaS);

                    Jogador entra = suplentes.jogadores[s];
                    subs += sai.nome + " -> " + entra.nome + "\n";

                    removerJogador(suplentes, s);
                    inserirJogador(titulares, entra);
                    substituicoes++; // incrementamos o número de substituições usadas
                }
                i--;
            }
        }
    }
    //
    // if (plantel.tamanho < 7) {
    //     cout << "Nao ha jogadores suficientes. Ora bolas!";
    // }
    // if (titulares.tamanho < 7) {
    //     cout << "O jogo foi terminado por falta de jogadores.\n";
    //     if (golosADV > 3) {
    //         cout << "Resultado : EDA FC:0" << " - " << adversario << ":"<< golosADV << endl;
    //     } else {
    //         cout << "Resultado : EDA FC:0" << " - " << adversario << ":"<< "3" << endl;
    //     }
    // } else {
    //     cout << "Resultado : EDA FC:" << golosEDA << " - " << adversario << ":"<< golosADV << endl;
    // }

    //transferências
}