//
// Created by gnps0 on 03/04/2026.
//

#ifndef GRUPO27_EQUIPA_H
#define GRUPO27_EQUIPA_H
#include "plantel.h"
// função que escolhe os titulares a partir do plantel
void escolherTitulares(ListaJogadores &plantel, ListaJogadores &titulares);

// função que escolhe suplentes
void escolherSuplentes(ListaJogadores &plantel, ListaJogadores &suplentes);
void selecionarEquipa(ListaJogadores &plantel, ListaJogadores &titulares, ListaJogadores &suplentes);

#endif //GRUPO27_EQUIPA_H

