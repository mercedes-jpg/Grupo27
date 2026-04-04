//
// Created by gnps0 on 03/04/2026.
//
#include "equipa.h"

// função para escolher os titulares
void escolherTitulares(ListaJogadores &plantel, ListaJogadores &titulares)
{
    titulares.tamanho = 0;
    // começamos com 0 titulares (lista vazia) - numero de titulares e 0

    int gr = 0, def = 0, med = 0, ava = 0;
    // inicialização das variaveis das várias posiçoes a 0

    // percorremos TODOS os jogadores do plantel
    for (int i = 0; i < plantel.tamanho; i++)
    {
        Jogador j = plantel.jogadores[i];
        // vamos buscar o jogador j na posição i do plantel

        // ignorar jogadores lesionados ou castigados
        if (j.jornadasLesao > 0 || j.jogosCastigo > 0)
        {
            continue;
            // caso if seja verdadeiro passa a proxima linha de codigo
        }

        // escolher 1 GR
        if (j.posicao == "GR" && gr < 1) //j.posição pode ser GR, DEF, MED e AVA, caso seja GR e se ainda não tivermos nenhum guarda-redes, pois ele começa a 0 e se for menor que çlogo zero entao ainda não escolhemos nenhum guarda-redes -> se a pos for GR e ainda não tivermos escolhido nenhum GR então...
        {
            titulares.jogadores[titulares.tamanho++] = j;
            // adiciona o jogador j na posição tamanho e dps incrementa , isto é atualiza o tamanho para mais um à lista titulares

            gr++; // atualiza os GR para mais um
        }

        // escolher 4 DEF
        else if (j.posicao == "DEF" && def < 4)
        {
            titulares.jogadores[titulares.tamanho++] = j;
            def++;
        }

        // escolher 4 MED
        else if (j.posicao == "MED" && med < 4)
        {
            titulares.jogadores[titulares.tamanho++] = j;
            med++;
        }

        // escolher 2 AVA
        else if (j.posicao == "AVA" && ava < 2)
        {
            titulares.jogadores[titulares.tamanho++] = j;
            ava++;
        }

        // se já tivermos todos os titulares, parar
        if (gr == 1 && def == 4 && med == 4 && ava == 2)
        {
            break; //quebra o ciclo
        }
    }
}
void escolherSuplentes(ListaJogadores &plantel, ListaJogadores &suplentes)
{
    suplentes.tamanho = 0;
    // lista começa vazia

    // percorre o plantel todo
    for (int i = 0; i < plantel.tamanho; i++)
    {
        Jogador j = plantel.jogadores[i];// vamos buscar o jogador j na posição i do plantel

        // ignorar lesionados/castigados hummmmm
        if (j.jornadasLesao > 0 || j.jogosCastigo > 0)
        {
            continue;
        }

        // adiciona TODOS (simplificado)
        suplentes.jogadores[suplentes.tamanho++] = j;
        // adiciona o jogador j a lista dos suplentes na posição tamanho e dps incrementa 1
    }
}

