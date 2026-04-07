#include <iostream> //ficheiro de texto que contem as instruções e as declarações de funções referentes a ações de entrada e saída de dados - biblioteca standard input/output
#include <stdlib.h>
#include <time.h> // Para o seed do rand
#include <windows.h>
#include "plantel.h"
#include "jogador.h"
#include "jogo.h"
#include "equipa.h"

using namespace std;

int main() {
    srand(time(NULL));
	SetConsoleOutputCP(CP_UTF8);

    ListaJogadores plantel; //declaração dos diferentes arrays
	ListaJogadores lesionados;
	ListaJogadores castigados;
	ListaJogadores transferencias;
	ListaJogadores titulares;
	ListaJogadores suplentes;

	bool usados[100] = {false}; // todos começam como não usados; é até 100 porque iremos como índices (usados[numero]) ignoramos o 0

    inicializarLista(plantel, 30); //inicialização dos arrays
	inicializarLista(lesionados, 30);
	inicializarLista(castigados, 30);
	inicializarLista(transferencias, 30);

    gerarPlantel(plantel, usados); // aqui p = plantel

	//gerar 17 equipas sem repetir
	string equipas[17];
	int i = 0;
	while (i < 17) {
		string e = obterEquipaAdvAleatoria();
		bool repetida = false;
		for (int j= 0; j < i; j++) {
			if (equipas[j] == e) repetida = true;
		}
		if (!repetida) {
			equipas[i] = e;
			i++;
		}
	}

	//JORNADAS
	int jornada = 0;
	int pontos = 0;
	char escolha;
	string resumoAnterior = "";

	do {
		cout << "***********************************\n";
		cout << "* EDA FC - " << jornada+1 << "ª Jornada - " << pontos << " pontos.\n";
		cout << "***********************************\n";

		//mostrar resultado anterior
		if (jornada > 0) {
			cout << "\nResultado Anterior:\n";
			cout << resumoAnterior << endl;
		}
		cout << "***********************************" << " Plantel Disponível: " << "***********************************\n";
		mostrarLista(plantel);

		//jornadasLesao e jogosCastigo
		for (int i = 0; i < lesionados.tamanho; i++) {
			lesionados.jogadores[i].jornadasLesao--;
			if (lesionados.jogadores[i].jornadasLesao == 0) {
				recuperarLesionado(plantel, lesionados, i);
				i--;
			}
		}
		if (jornada > 0) {
			for (int i = 0; i <castigados.tamanho; i++) {
				castigados.jogadores[i].jogosCastigo--;
				if (castigados.jogadores[i].jogosCastigo == 0) {
					recuperarCastigado(plantel, castigados, i);
					i--;
				}
			}
		}
		string adversario;
		if (jornada < 17)
			adversario = equipas[jornada];
		else
			adversario = equipas[jornada - 17];

		selecionarEquipa(plantel, titulares, suplentes);

		cout << "\nTitulares:\n";
		mostrarLista(titulares);

		cout << "\nSuplentes:\n";
		mostrarLista(suplentes);

		if (plantel.tamanho < 7) {
			cout << "\nO jogo não pode começares, o EDA FC não tem jogadores suficientes para jogar.\n";
		}
		else {
			simularJornada(plantel, titulares, suplentes, lesionados, castigados, transferencias, usados, adversario, pontos);
			resumoAnterior = "Jogo contra " + adversario + " terminado.";
		}
		jornada++;
		cout << "\n(s) seguinte    (o) sair ";
		cin >> escolha;

	} while (escolha == 's' && jornada < 34);

	return 0;
}

// struct equipa {
//     jogador* plantel;
//     jogador* convocados;
//     int nGr;
//     int nDef;
//     int nMed;
//     int nAva;
//};

// int main() {
//     srand(time(NULL));
//     string* nomes = new nome[118]; //Cria um apontador de nome "nomes" do tipo string e cria se 118 lugares do tipo "nomes" que recebera o nome dos jogadores
// }
