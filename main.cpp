#include <iostream> //ficheiro de texto que contem as instruções e as declarações de funções referentes a ações de entrada e saída de dados - biblioteca standard input/output
#include <stdlib.h>
#include <time.h> // para o seed do rand
#include "plantel.h"
#include "jogador.h"
#include "jogo.h"
#include "equipa.h"
//#include <windows.h> // para conseguirmos mostrar os acentos e isso na consola

using namespace std;

int main() {
	srand(time(NULL));
	//SetConsoleOutputCP(CP_UTF8);
	ListaJogadores plantel; //declaração dos diferentes arrays
	ListaJogadores lesionados;
	ListaJogadores castigados;
	ListaJogadores transferencias;
	ListaJogadores titulares;
	ListaJogadores suplentes;
	bool usados[100] = {false}; // todos começam como não usados; é até 100 porque iremos como índices (usados[numero]) ignoramos o 0
	//int capacidade = 20 + rand() % 11; // 20 a 30 jogadores
	//int capacidadeMax = 30;
	inicializarLista(plantel, 30); //inicialização dos arrays
	inicializarLista(lesionados, 30);
	inicializarLista(castigados, 30);
	inicializarLista(transferencias, 30);
	inicializarLista (titulares, 11);
	inicializarLista (suplentes, 6);

	gerarPlantel(plantel, usados); // aqui p = plantel

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

	string ultimoAdversario = "";
	int ultimoEDA = 0;
	int ultimoADV = 0;
	string ultSubs = "";

	ListaJogadores ultTitulares;
	ListaJogadores ultSuplentes;
	ListaJogadores ultLesionados;
	ListaJogadores ultCastigados;

	inicializarLista(ultTitulares, 11);
	inicializarLista(ultSuplentes, 6);
	inicializarLista(ultLesionados, 30);
	inicializarLista(ultCastigados, 30);

	do {
		cout << "***********************************\n";
		cout << "* EDA FC - " << jornada+1 << "a Jornada - " << pontos << " pontos.\n";
		cout << "***********************************\n";

		//jornadasLesao e jogosCastigo
		for (int i = 0; i < lesionados.tamanho; i++) {
			if (lesionados.jogadores[i].jornadasLesao == 0) {
				recuperarLesionado(plantel, lesionados, i);
				i--;
			} else {
				lesionados.jogadores[i].jornadasLesao--;
			}
		}
		for (int i = 0; i <castigados.tamanho; i++) {
			if (castigados.jogadores[i].jogosCastigo == 0) {
				recuperarCastigado(plantel, castigados, i);
				i--;
			} else {
				castigados.jogadores[i].jogosCastigo--;
			}
		}

		//selecionarEquipa(plantel, titulares, suplentes);

		// ListaJogadores titularesIniciais;
		// ListaJogadores suplentesIniciais;
		//
		// inicializarLista(titularesIniciais, 11);
		// inicializarLista(suplentesIniciais, 6);

		// listas de castigados e lesionados de cada jornada apenas
		// ListaJogadores lesionadosJornada;
		// ListaJogadores castigadosJornada;
		// inicializarLista(lesionadosJornada, 30);
		// inicializarLista(castigadosJornada, 30);
		//
		// simularJornada(plantel, titulares, suplentes, lesionados, castigados, lesionadosJornada, castigadosJornada, transferencias, usados, adversario, pontos);

		if (jornada > 0) {
			cout << "Resultado Anterior:\n";
			cout << "Resultado : EDA FC:" << ultimoEDA << " - " << ultimoAdversario << ":" << ultimoADV << endl;
			cout << "\nTitulares:\n";
			mostrarLista(ultTitulares);

			cout << "\nSuplentes:\n";
			mostrarLista(ultSuplentes);

			cout << "\nCastigados:\n";
			mostrarLista(ultCastigados);

			cout << "\nLesionados:\n";
			mostrarLista(ultLesionados);

			cout << "\nSubstituicoes:\n" << ultSubs << endl;
		}
		selecionarEquipa(plantel, titulares, suplentes);

		ultTitulares.tamanho = 0;
		ultSuplentes.tamanho = 0;
		ultLesionados.tamanho = 0;
		ultCastigados.tamanho = 0;
		ultSubs = "";

		// guardar os titulares iniciais
		for (int i = 0; i < titulares.tamanho; i++)
			inserirJogador(ultTitulares, titulares.jogadores[i]);

		// copiar os suplentes
		for (int i = 0; i < suplentes.tamanho; i++)
			inserirJogador(ultSuplentes, suplentes.jogadores[i]);

		string adversario;
		if (jornada < 17)
			adversario = equipas[jornada];
		else
			adversario = equipas[jornada - 17];

		simularJornada(plantel, titulares, suplentes, lesionados, castigados, ultLesionados, ultCastigados, transferencias, usados, adversario, pontos);

		ultimoAdversario = adversario;

		//estado atual do plantel e outras listas
		cout << "\n***********************************" << " Plantel Disponivel: " << "***********************************\n";
		mostrarLista(plantel);

		cout << "\nCastigados:\n";
		mostrarLista(castigados);

		cout << "\nLesionados:\n";
		mostrarLista(lesionados);

		jornada++;

		cout << "\n(s) seguinte    (o) sair\n";
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