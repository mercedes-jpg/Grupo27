#include <iostream> //ficheiro de texto que contem as instruções e as declarações de funções referentes a ações de entrada e saída de dados - biblioteca standard input/output
#include <stdlib.h>
#include <time.h> // para o seed do rand
#include "plantel.h"
#include "jogador.h"
#include "jogo.h"
#include "equipa.h"
//#include <windows.h> // para conseguirmos mostrar os acentos e isso na consola

using namespace std;

/**
 * Função principal do programa
 * @return registo das jornadas e informações
 */
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

	inicializarLista(plantel, 30); //inicialização dos arrays
	inicializarLista(lesionados, 30);
	inicializarLista(castigados, 30);
	inicializarLista(transferencias, 68);
	inicializarLista (titulares, 11);
	inicializarLista (suplentes, 6);

	gerarPlantel(plantel, usados); // aqui p = plantel

	ListaJogadores plantelInicial;
	inicializarLista(plantelInicial, 30);

	// copiar o plantel
	for (int i = 0; i < plantel.tamanho; i++) {
		inserirJogador(plantelInicial, plantel.jogadores[i]);
	}

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

	ListaJogadores lesionadosJornada;
	ListaJogadores castigadosJornada;

	inicializarLista(lesionadosJornada, 30);
	inicializarLista(castigadosJornada, 30);

	ListaJogadores transferenciasUltimas;
	inicializarLista(transferenciasUltimas, 68);

	ListaJogadores castigadosAteAgora;
	ListaJogadores lesionadosAteAgora;

	inicializarLista(castigadosAteAgora, 30);
	inicializarLista(lesionadosAteAgora, 30);

	do {
		castigadosAteAgora.tamanho = 0;
		lesionadosAteAgora.tamanho = 0;

		for (int i = 0; i < castigados.tamanho; i++)
			inserirJogador(castigadosAteAgora, castigados.jogadores[i]);

		for (int i = 0; i < lesionados.tamanho; i++)
			inserirJogador(lesionadosAteAgora, lesionados.jogadores[i]);

		//jornadasLesao e jogosCastigo
		for (int i = 0; i < lesionados.tamanho; i++) {
			lesionados.jogadores[i].jogosLesao--;
			if (lesionados.jogadores[i].jogosLesao < 0) {
				// vamos voltar a colocá-lo no plantel na jornada seguinte a ficar a zeros
				recuperarLesionado(plantel, lesionados, i);
				i--;
			}
		}
		for (int i = 0; i <castigados.tamanho; i++) {
			castigados.jogadores[i].jogosCastigo--;
			if (castigados.jogadores[i].jogosCastigo < 0) { // vamos voltar a colocá-lo no plantel na jornada seguinte a ficar a zeros
				recuperarCastigado(plantel, castigados, i);
				i--;
			}
		}

		cout << "***********************************\n";
		cout << "* EDA FC - " << jornada+1 << "a Jornada - " << pontos << " pontos.\n";
		cout << "***********************************\n";

		if (jornada > 0) {

			cout << "Resultado Anterior:\n";
			cout << "Resultado : EDA FC:" << ultimoEDA << " - " << ultimoAdversario << ":" << ultimoADV << endl;

			cout << "\nTitulares:\n";
			mostrarPlantelEtc(ultTitulares);

			cout << "\nSuplentes:\n";
			mostrarPlantelEtc(ultSuplentes);

			cout << "\nCastigados:\n";
			mostrarCastigados(ultCastigados);

			cout << "\nLesionados:\n";
			mostrarLesionados(ultLesionados);

			cout << "\nSubstituicoes:\n" << ultSubs << endl;

			lesionadosJornada.tamanho = 0;
			castigadosJornada.tamanho = 0;
			ultLesionados.tamanho = 0;
			ultCastigados.tamanho = 0;
			ultSubs = "";
		}

		selecionarEquipa(plantel, titulares, suplentes);

		ultTitulares.tamanho = 0;
		ultSuplentes.tamanho = 0;
		ultSubs = "";
		transferenciasUltimas.tamanho = 0;

		// guardar os titulares iniciais
		for (int i = 0; i < titulares.tamanho; i++)
			inserirJogador(ultTitulares, titulares.jogadores[i]);

		// copiar os suplentes
		for (int i = 0; i < suplentes.tamanho; i++)
			inserirJogador(ultSuplentes, suplentes.jogadores[i]);

		//copiar as transferencias
		for (int i = 0; i < transferencias.tamanho; i++)
			inserirJogador(transferenciasUltimas, transferencias.jogadores[i]);

		string adversario;
		if (jornada < 17)
			adversario = equipas[jornada];
		else
			adversario = equipas[jornada - 17];

		simularJornada(plantel, titulares, suplentes, lesionados, castigados, lesionadosJornada, castigadosJornada, usados, adversario, pontos, ultimoEDA, ultimoADV, ultSubs);

		ultimoAdversario = adversario;

		// copiar os do jogo que está a ocorrer
		for (int i = 0; i < lesionadosJornada.tamanho; i++)
			inserirJogador(ultLesionados, lesionadosJornada.jogadores[i]);

		for (int i = 0; i < castigadosJornada.tamanho; i++)
			inserirJogador(ultCastigados, castigadosJornada.jogadores[i]);

		//transferencias
		for (int i = 0; i < 2; i++) {
			string posicoes[] = {"GR","DEF","MED","AVA"};

			Jogador j = criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), posicoes[rand() % 4]);
			inserirJogador(transferencias, j);
		}
		//estado atual do plantel e outras listas
		cout << "\n***********************************" << " Plantel Disponivel: " << "***********************************\n";

		if (jornada == 0)
			mostrarPlantelEtc(plantelInicial);
		else
			mostrarPlantelEtc(plantel);

		if (jornada > 0) {
			cout << "\nCastigados:\n";
			mostrarCastigados(castigadosAteAgora);

			cout << "\nLesionados:\n";
			mostrarLesionados(lesionadosAteAgora);

			cout << "\n**************************************************************************************\n";
			cout << "Transferencias:\n";
			mostrarTransferencias(transferenciasUltimas);
		}

		int opcao;
		// variável onde vamos guardar a escolha do utilizador (1, 2 ou 0)

		cout << "\n--- TREINO ---\n";
		// imprime um título para a parte do treino

		cout << "1 - Mudar posicao\n";
		// opção 1: alterar a posição de um jogador

		cout << "2 - Melhorar qualidade\n";
		// opção 2: treinar jogador para aumentar qualidade

		cout << "3 - Gravar Jogo\n";
		//opção 3: gravar o jogo num ficheiro

		cout << "4 - Carregar Jogo\n";
		//opção 4: carregar o jodo do ficheiro

		cout << "0 - Ignorar\n";
		// opção 0: não fazer nada (seguir o jogo normalmente)

		cout << "Escolha: ";
		// pede ao utilizador que escolha uma opção

		cin >> opcao;
		// lê o valor que o utilizador escreveu e guarda em "opcao"


		// se quiser fazer treino (ou seja, escolheu 1 ou 2)
		mostrarPlantelEtc(plantel);
		if (opcao == 1 || opcao == 2){
    		int i;
    		// variável para guardar o índice do jogador no array

    		cout << "Indice do jogador: ";
    		// pede ao utilizador qual jogador quer alterar

    		cin >> i;
    		// lê o índice escolhido
			if (i < 0 || i >= plantel.tamanho){
    			cout << "Indice invalido!\n";
			}
			else {


    			// se escolheu mudar posição
    			if (opcao == 1){
    				string novaPos;
    				// variável para guardar a nova posição

    				cout << "Nova posicao (GR DEF MED AVA): ";
    				cin >> novaPos;
    				// lê a posição


    				if (novaPos != "GR" && novaPos != "DEF" && novaPos != "MED" && novaPos != "AVA") {
       					cout << "Posicao invalida!\n";
        				// se for inválida, avisa e não faz nada
    				}
    				else {
        				mudarPosicao(plantel, i, novaPos);
        				// só muda se for válida
    				}
				}



    			// se escolheu melhorar qualidade
   				else if (opcao == 2){
        			int semanas;
        			// variável para guardar o número de semanas de treino

        			cout << "Numero de semanas (max 5): ";
        			// pede ao utilizador quantas semanas quer treinar

        			cin >> semanas;
        			// lê o número introduzido

        			treinarJogador(plantel, i, semanas);
        			// chama a função que aumenta a qualidade do jogador
        			// de acordo com o número de semanas
    			}

				//se escolheu gravar equipa
   				else if (opcao == 3) {
   					cout << "A gravar os dados do jogo..." << endl;
   					gravarEquipa(plantel, "plantel.txt");
   					gravarEquipa(lesionados, "lesionados.txt");
   					gravarEquipa(castigados, "castigados.txt");
   					gravarEquipa(transferencias, "transferencias.txt");
   					gravarProgresso(jornada, pontos, "estado.txt");
   					cout << "Jogo guardado\n";
   				}

				//se escolheu carregar equipa
   				else if (opcao == 4) {
   					cout << "A carregar os dados do jogo..." << endl;
   					carregarEquipa(plantel, "plantel.txt");
   					carregarEquipa(lesionados, "lesionados.txt");
   					carregarEquipa(castigados, "castigados.txt");
   					carregarEquipa(transferencias, "transferencias.txt");
   					carregarProgresso(jornada, pontos, "estado.txt");
   					cout << "Jogo carregado\n";
   				}
			}
		}

		// //jornadasLesao e jogosCastigo
		// for (int i = 0; i < lesionados.tamanho; i++) {
		// 	lesionados.jogadores[i].jornadasLesao--;
		// 	if (lesionados.jogadores[i].jornadasLesao < 0) {
		// 		// vamos voltar a colocá-lo no plantel na jornada seguinte a ficar a zeros
		// 		recuperarLesionado(plantel, lesionados, i);
		// 		i--;
		// 	}
		// }
		// for (int i = 0; i <castigados.tamanho; i++) {
		// 	castigados.jogadores[i].jogosCastigo--;
		// 	if (castigados.jogadores[i].jogosCastigo < 0) { // vamos voltar a colocá-lo no plantel na jornada seguinte a ficar a zeros
		// 		recuperarCastigado(plantel, castigados, i);
		// 		i--;
		// 	}
		// }

		jornada++;

		cout << "\n(s) seguinte    (o) sair\n";
		cin >> escolha;
	}
		while (escolha == 's' && jornada < 34);

	int opTransferencia;
	cout << "\n--- Tranferências ---\n";
	cout << "1 - Contratar jogador\n0 - Ignorar\nEscolha: ";
	cin >> opTransferencia;
	if (opTransferencia == 1) {
		fazerTransferencia(plantel, transferencias);
	}
	return 0;
}