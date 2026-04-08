//
// Created by gnps0 on 03/04/2026.
//
#include "equipa.h"
#include "plantel.h"

using namespace std;

// função para escolher os titulares
// void escolherTitulares(ListaJogadores &plantel, ListaJogadores &titulares)
// {
//     titulares.tamanho = 0;
//     // começamos com 0 titulares (lista vazia) - numero de titulares e 0
//
//     int gr = 0, def = 0, med = 0, ava = 0;
//     // inicialização das variaveis das várias posiçoes a 0
//
//     // percorremos TODOS os jogadores do plantel
//     for (int i = 0; i < plantel.tamanho; i++)
//     {
//         Jogador j = plantel.jogadores[i];
//         // vamos buscar o jogador j na posição i do plantel
//
//         // ignorar jogadores lesionados ou castigados
//         if (j.jornadasLesao > 0 || j.jogosCastigo > 0)
//         {
//             continue;
//             // caso if seja verdadeiro passa a proxima linha de codigo
//         }
//
//         // escolher 1 GR
//         if (j.posicao == "GR" && gr < 1) //j.posição pode ser GR, DEF, MED e AVA, caso seja GR e se ainda não tivermos nenhum guarda-redes, pois ele começa a 0 e se for menor que çlogo zero entao ainda não escolhemos nenhum guarda-redes -> se a pos for GR e ainda não tivermos escolhido nenhum GR então...
//         {
//             titulares.jogadores[titulares.tamanho++] = j;
//             // adiciona o jogador j na posição tamanho e dps incrementa , isto é atualiza o tamanho para mais um à lista titulares
//
//             gr++; // atualiza os GR para mais um
//         }
//
//         // escolher 4 DEF
//         else if (j.posicao == "DEF" && def < 4)
//         {
//             titulares.jogadores[titulares.tamanho++] = j;
//             def++;
//         }
//
//         // escolher 4 MED
//         else if (j.posicao == "MED" && med < 4)
//         {
//             titulares.jogadores[titulares.tamanho++] = j;
//             med++;
//         }
//
//         // escolher 2 AVA
//         else if (j.posicao == "AVA" && ava < 2)
//         {
//             titulares.jogadores[titulares.tamanho++] = j;
//             ava++;
//         }
//
//         // se já tivermos todos os titulares, parar
//         if (gr == 1 && def == 4 && med == 4 && ava == 2)
//         {
//             break; //quebra o ciclo
//         }
//     }
// }
// void escolherSuplentes(ListaJogadores &plantel, ListaJogadores &suplentes)
// {
//     suplentes.tamanho = 0;
//     // lista começa vazia
//
//     // percorre o plantel
//     for (int i = 0; i < plantel.tamanho; i++)
//     {
//         Jogador j = plantel.jogadores[i];// vamos buscar o jogador j na posição i do plantel
//
//         // ignorar lesionados/castigados hummmmm
//         if (j.jornadasLesao > 0 || j.jogosCastigo > 0)
//         {
//             continue;
//         }
//
//         // adiciona TODOS (simplificado)
//         suplentes.jogadores[suplentes.tamanho++] = j;
//         // adiciona o jogador j a lista dos suplentes na posição tamanho e dps incrementa 1
//     }
// }

void selecionarEquipa(ListaJogadores &plantel, ListaJogadores &titulares, ListaJogadores &suplentes) {
    titulares.tamanho = 0;
    titulares.tamanho = 0;
    inicializarLista(titulares, 11);// inicializa a lista de titulares
    inicializarLista(suplentes, 6);// inicializa a lista dos suplentes
    ordenarPorQualidade(plantel);// ordena o plantel por qualidade

    // titulares 1-4-4-2
    int gr = 0, def = 0, med = 0, ava = 0;// inicialização das diferentes posições a zero
    for (int i = 0; i < plantel.tamanho; i++) { // percorre se o plantel usando o seu indice e o que esta abaixo acontece sempre que i<plantel.tamanho ou i<=(plantel.tamanho - 1) sendo que i começa a zero e vai incrementando sempre 1
        Jogador j = plantel.jogadores[i];// jogado j é um jogador que se foi buscar ao plantel de jogadores ou a lista de jogadores no plantel na posição i e por sua vez guarda se na variavel j do tipo jogador

        if (j.posicao == "GR" && gr < 1) { // se a posição do jogador j for gr e se ainda não tivermos nenhum guarda redes, pois so precisamos de um gr, então:
            inserirJogador(titulares, j); // insere jogador na lista dos titulares como jogador j
            gr++;//incrementa mais um gr
        }
        else if (j.posicao == "DEF" && def < 4) {
            inserirJogador(titulares, j);
            def++;
        }
        else if (j.posicao == "MED" && med < 4) {
            inserirJogador(titulares, j);
            med++;
        }
        else if (j.posicao == "AVA" && ava < 2) {
            inserirJogador(titulares, j);
            ava++;
        }
        if (titulares.tamanho == 11) break;// quebra o ciclo quando tivermos os 11 titulares pois se não entra num if entra noutro e assim sucessivamente e por fim apos verificar td, ja temos os titulares, quebra
    }
    // suplentes 1-2-2-1
    int grS = 0, defS = 0, medS = 0, avaS = 0;

    for (int i = 0; i < plantel.tamanho; i++) {
        Jogador j = plantel.jogadores[i];

        bool jaTitular = false; // para não usar os que já são titulares - cria se uma var do tipo boolenano inicializada a false
        // vamos ver se este jogador já é titular
        for (int k = 0; k < titulares.tamanho; k++) { // percorre se o array dos titulares usando k como a posição
            if (titulares.jogadores[k].numero == j.numero) { //se numero do jogador k da lista de titulares for igual ao numero do jogador j que e o jogador da posiçao i do plantel de jogadores
                jaTitular = true; // se ele é titular a var jaTitular fica true
                break; // como já o encontramos, então paramos o ciclo
            }
        }
        if (jaTitular) continue; // se ele é titular não pode ser suplente logo vamos passar ao próximo i ou seja continua
        // não é titular então pode ser suplente:
        if (j.posicao == "GR" && grS < 1) { // se a posição do jogador em i for gr e ainda não tivermos 1 então este fica suplente
            inserirJogador(suplentes, j);//insere o jogador j na lista de suplentes
            grS++;
        }
        else if (j.posicao == "DEF" && defS < 2) { // se a posição for def e tivermos menos que 2 então este fica suplente
            inserirJogador(suplentes, j);
            defS++;
        }
        else if (j.posicao == "MED" && medS < 2) {
            inserirJogador(suplentes, j);
            medS++;
        }
        else if (j.posicao == "AVA" && avaS < 1) {
            inserirJogador(suplentes, j);
            avaS++;
        }
        if (suplentes.tamanho == 6) break; // quando tiverem 6 suplentes paramos
    }
}
