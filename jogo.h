//
// Created by clara on 31/03/2026.
//

#ifndef GRUPO27_JOGO_H
#define GRUPO27_JOGO_H
#include "plantel.h"

string obterEquipaAdvAleatoria();

void simularJornada(ListaJogadores &plantel, ListaJogadores &titulares, ListaJogadores &suplentes, ListaJogadores &lesionados, ListaJogadores &castigados, ListaJogadores &lesionadosJornada, ListaJogadores &castigadosJornada, ListaJogadores &transferencias, bool usados[], string adversario, int &pontos, int &golosEDA, int &golosADV, string &subs);
int encontrarSubstituto(ListaJogadores &s, string pos, int grS, int defS, int medS, int avaS);

#endif //GRUPO27_JOGO_H