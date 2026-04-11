#include "jogador.h"
#include <stdlib.h> // dá acesso a rand()
#include <fstream> // biblioteca (classe) para escrita e leitrua de ficheiros

/**
 * Cria um novo jogador e inicializa os seus atributos
 * @param nome Nome do jogador
 * @param numero Número único do jogador
 * @param posicao Posição do jogador (GR, DEF, MED, AVA)
 * @return Jogador inicializado com vários atributos inicializados
 */
Jogador criarJogador(string nome, int numero, string posicao) {
    Jogador j;
    j.nome = nome;
    j.numero = numero;
    j.posicao = posicao;

    j.idade = 16 + rand() % 25; // entre 16 e 40
    j.probLesao = rand() % 16; // entre 0 e 15
    j.probCastigo = rand() % 21; // entre 0 e 20
    j.qualidade = rand() % 101; // entre 0 e 100

    j.semanasTreino = 0;
    j.jogosLesao = 0;
    j.jogosCastigo = 0;

    return j;
}

/**
 * Obtém um nome aleatório retirado do ficheiro nomes.txt
 * @return Nome aleatório (string)
 */
string obterNomeAleatorio() {

    string nomes [150]; // porque tem 114 nomes na lista de nomes, caso adicione se mais depois
    int total = 0;
    string linha;
    fstream fs;
    fs.open("nomes.txt", ios::in); // abre o ficheiro para leitura
    if (fs.is_open()) { // faz o que está a baixo enquanto o ficheiro está aberto
        while (getline(fs,linha)) { // enquanto o getline lê linhas retorna true - o getline lê uma linha inteira do ficheiro aberto em fs e guarda na var linha
            nomes[total++] = linha; // o array nomes de 150 capacidade guarda o conteúdo var linha na posição total e dps incrementa 1 para guardar a próxima var
        }
        fs.close();// fecha o ficheiro
    }
    if (total == 0) return "Jogador";

    return nomes[rand() % total]; // o rand vai dar um indice aleatório do vetor nomes; logo vai retornar um nome aleatório
}

/**
 * Gera um número único/não repetido entre 1 e 99
 * @param usados Array que indica os números que já foram utilizados
 * @return Número único/não repetido
 */
int gerarNumeroUnico(bool usados[]) {

    int n;
    do {
        n = 1 + rand() % 99; // os números no futebol vão de 1 a 99
    } while (usados[n]); // se já foi usada continua a repetir, se ainda não foi usado sai do ciclo
    usados[n] = true; // agora esse número passa a usado
    return n;
}