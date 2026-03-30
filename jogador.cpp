//
// Created by clara on 29/03/2026.
//
//.cpp implementa
#include "jogador.h"
#include <stdlib.h> // dá acesso a rand()
#include <fstream> // biblioteca (classe) para escrita e leitrua de ficheiros

Jogador criarJogador(string nome, int numero, string posicao) {
    Jogador j;
    j.nome = obterNomeAleatorio();
    j.numero = numero;
    j.posicao = posicao;

    j.idade = rand() % 25 + 16; // entre 16 e 40
    j.probLesao = rand() % 16; // entre 0 e 15
    j.probCastigo = rand() % 21; // entre 0 e 20
    j.qualidade = rand() % 101; // entre 0 e 100

    j.diasTreino = 0;
    j.jornadasLesao = 0;
    j.jornadasCastigo = 0;

    return j;
}

string obterNomeAleatorio() {
    string nomes [150];
    int total = 0;
    string linha;
    fstream fs;
    fs.open(nomeFicheiro, ios::in);
    if (fs.is_open()) {
        while (getline(file,linha)) {
            nomes[total++] = linha;
        }
        fs.close();
    }
    return nomes[rand() % total];
}