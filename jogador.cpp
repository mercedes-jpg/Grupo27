//
// Created by clara on 29/03/2026.
//
//.cpp implementa
#include "jogador.h"
#include <stdlib.h> // dá acesso a rand()
#include <fstream> // biblioteca (classe) para escrita e leitrua de ficheiros

Jogador criarJogador(string nome, int numero, string posicao) {
    Jogador j;
    j.nome = nome;
    j.numero = numero;
    j.posicao = posicao;

    j.idade = rand() % 25 + 16; // entre 16 e 40
    j.probLesao = rand() % 16; // entre 0 e 15
    j.probCastigo = rand() % 21; // entre 0 e 20
    j.qualidade = rand() % 101; // entre 0 e 100

    j.diasTreino = 0;
    j.jornadasLesao = 0;
    j.jogosCastigo = 0;


    return j;
}

string obterNomeAleatorio() {
    string nomes [150]; // porque tem 114 nomes na lista de nomes
    int total = 0;
    string linha;
    fstream fs;
    fs.open("nomes.txt", ios::in); // abre o ficheiro para leitura
    if (fs.is_open()) { // faz o que esta a baixo enquanto o ficheiro esta aberto
        while (getline(fs,linha)) { // enquanto o getline le linhas retorna true - o getline le uma linha inteira do ficheiros aberto em fs e guarda  na var linha
            nomes[total++] = linha; // o array nomes de 150 capacidade guarda o conteudo var linha na posição total e dps icrementa 1 para guardar a proxima var
        }
        fs.close();// fecha o ficheiro
    }
    return nomes[rand() % total]; // o rand vai dar um indice aleatorio do vetor nomes; logo vai retornar um nome aleatório
}