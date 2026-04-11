#include <iostream>
#include "plantel.h"
#include "jogador.h"
#include <iomanip> // para usar o setw
#include <stdlib.h>

using namespace std;

/**
 *
 * @param p
 * @param capacidade
 */
void inicializarLista(ListaJogadores &p, int capacidade) {
    p.jogadores = new Jogador[capacidade]; // hummmmm
    p.tamanho = 0;
    p.capacidade = capacidade;
}

/**
 *
 * @param p
 * @param numero
 * @return
 */
int encontrarIndicePorNumero(ListaJogadores &p, int numero) {
    for (int i = 0; i < p.tamanho; i++) {
        if (p.jogadores[i].numero == numero)
            return i;
    }
    return -1;
}

/**
 *
 * @param pos
 * @return
 */
int ordemPos(string pos) {
    if (pos == "GR") {
        return 0;
    }
    if (pos == "DEF") {
        return 1;
    }
    if (pos == "MED") {
        return 2;
    }
    if (pos == "AVA") {
        return 3;
    }
    return -1;
}

/**
 *
 * @param p
 * @param j
 */
void inserirJogador(ListaJogadores &p, Jogador j) { // & é para trabalhar na lista original
    if (p.tamanho < p.CAPACIDADEMAX) { // se o nº de jogadores atual for menor que a capacidade do plantel
        int i = 0;
        // vamos encontrar a posição certa para a lista continuar ordenada
        while (i < p.tamanho && (ordemPos(p.jogadores[i].posicao) < ordemPos(j.posicao) || (p.jogadores[i].posicao == j.posicao && p.jogadores[i].qualidade > j.qualidade))) {
        // se a posição do jogador de índice i for "menor" que o que vamos inserir, passamos ao próximo, se a posição é a mesma, mas a qualidade é maior passamos ao próximo
            i++; // vamos passar ao próximo
        }
        // quando chegarmos a um que a posição seja maior, ou que a posição seja a mesma, mas a qualidade seja menor temos de passar os jogadores uma casa para a direita para ter lugar para o que vamos inserir
        for (int k = p.tamanho; k > i; k--) {
            p.jogadores[k] = p.jogadores[k - 1]; // no índice do tamanho, isto é, no fim da lista vamos igualar esse ao anterior, depois o indice anterior ao anterior-anterior (= passar todos uma casa para a direita)
        }
        p.jogadores[i] = j;
        p.tamanho++; // e o número atual de jogadores será incrementado num valor
    }
}

void removerJogador(ListaJogadores &p, int a) {
    for (int i = a; i < p.tamanho - 1; i++) { // i começa no que vamos remover
        p.jogadores[i] = p.jogadores[i+1]; // para não deixar espaços em branco os jogadores que vêm depois dele vão recuar uma casa isto é esse lugar vai ser do jogador que vem logo de seguida
    }
    p.tamanho--; // o último não fica duplicado graças a isto
}

void gerarPlantel(ListaJogadores &p, bool usados[]) { // ListaJogadores é o tipo, p(plantel) é a variável

    int capacidade = 20 + rand() % 11; // 20 a 30 - capacidade
    p.tamanho = 0; //tamanho inicial do plantel

    int gr = 2, def = 7, med = 7, ava = 4; // numero minimo de cada posição
    int restantes = capacidade - 20; // tirando do número aleatório 20 que são os jogadores mínimos - restantes será o restante da capacidade, ou seja, tirando o min total de jogadores no plantel que é 20 logo restantes mais total da a capacidade - total no min é 20 e no max é 30 a capacidade é sempre 30

    while (restantes > 0) { // enquanto restar jogadores para criar
        int r = rand() % 4; // vamos escolher aleatoriamente uma posição para cada um deles

        if (r == 0 && gr < 3) { gr++; restantes--;} // se já tiver no máximo da posição então não entra em nenhum if e gera outro r, isto e, outra posição aleatoria
        else if (r == 1 && def < 10) { def++; restantes--;}
        else if (r == 2 && med < 10) { med++; restantes--;}
        else if (r == 3 && ava < 7) { ava++; restantes--;}
    }
    // criar jogadores por ordem
    for (int i= 0; i < gr; i++) // o for percorre o plantel através dos índices: sendo i = 0 e i<gr que é o número de gr no plantel insere o jogador j no plantel p incrementando 1 em i
        inserirJogador(p, criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), "GR")); // a função inserir jogador recebe o plantel p e um jogador j criado pela função criarJogador, do tipo jogador - struct já criada que recebe um nome, número e posição, função esta que recebe 3 coisas
    for (int i = 0; i < def; i++)
        inserirJogador(p, criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), "DEF"));
    for (int i = 0; i < med; i++)
        inserirJogador(p, criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), "MED"));
    for (int i = 0; i < ava; i++)
        inserirJogador(p, criarJogador(obterNomeAleatorio(), gerarNumeroUnico(usados), "AVA"));
}

void lesionarJogador(ListaJogadores &plantel, ListaJogadores &lesionados, int a) {
    Jogador j = plantel.jogadores[a]; // vai buscar o jogador ao plantel
    j.jornadasLesao = 1 + rand() % 10; // jornadas a ficar lesionado 1 a 10 aleatoriamente
    // lesionados.jogadores[lesionados.tamanho++] = j; // mete o jogador j na lista lesionados dos jogadores acedida através dos mesmos na posição tamanho e dps encrementa 1
    inserirJogador(lesionados, j); // adiciona o jogador j no fim da lista dos lesionados onde o jogador j é o jogador lesionado
	removerJogador(plantel, a); // remove jogador j do plantel através da função remover jogador já definida
}

void castigarJogador(ListaJogadores &plantel, ListaJogadores &castigados, int a) {
    Jogador j = plantel.jogadores[a]; // vai buscar o jogador ao plantel
    j.jogosCastigo = 1 + rand() % 10; // jogos a ficar castigado 1 a 10 aleatoriamente
    // castigados.jogadores[castigados.tamanho++] = j; // mete o jogador j na lista lesionados dos jogadores acedida através dos mesmos na posição de índice tamanho
    inserirJogador(castigados, j);
	removerJogador(plantel, a); // remove jogador j do plantel através da funcao remover jogador já definida
}

void recuperarLesionado(ListaJogadores &plantel, ListaJogadores &lesionados, int a) {
    Jogador j = lesionados.jogadores[a]; // vai buscar o jogador j à lista de lesionados, que contém jogadores, na posição index
    j.jornadasLesao = 0; // não fica lesionado nenhuma jornada neste momento, porque já recuperou da lesão
    inserirJogador(plantel, j); // adiciona o jogador j no fim da lista do plantel onde o jogador j é o jogador que recuperou da lesão
    removerJogador(lesionados, a); // remove jogador j dos lesionados através da funcao remover jogador já definida
}

void recuperarCastigado(ListaJogadores &plantel, ListaJogadores &castigados, int a) {
    Jogador j = castigados.jogadores[a]; // vai buscar o jogador à lista de castigados
    j.jogosCastigo = 0; // não fica castigado em nenhum jogo, pois tirado do castigo
    inserirJogador(plantel, j);
    removerJogador(castigados, a); // remove jogador j da lista de castigados através da função remover jogador já definida
}

void adicionarTransferencia(ListaJogadores &transferencias, Jogador j) {
    inserirJogador(transferencias, j);
}

void ordenarPorQualidade(ListaJogadores &p) { // dentro de cada posição
// bubble sort porque tem relativamente poucos dados
    bool swapped = true; // inicializamos a true para entrar no for
    for (int i = 0; i < p.tamanho - 1 && swapped; i++) { // quando swapped=false quer dizer que não fez trocas então já estão ordenados
        swapped = false;
        for (int j = p.tamanho - 1; j > i; j--) {
            if (p.jogadores[j].posicao == p.jogadores[j-1].posicao && p.jogadores[j].qualidade > p.jogadores[j-1].qualidade) {
                // swap, vamos trocar os dois entre eles
                Jogador temp = p.jogadores[j];
                p.jogadores[j]=p.jogadores[j-1];
                p.jogadores[j-1] = temp;

                swapped = true; // fizemos trocas
            }
        }
    }
} // 30 40 20 50    40 30 20 50     40 30 20 50

void mostrarPlantelEtc(ListaJogadores &p) {
    cout << left << setw(23) << "Nome" << " | " << setw(3) << "No" << " | " << setw(7) << "Posicao" << " | " << setw(5) << "Idade" << " | " << setw(9) << "ProbLesao" << " | " << setw(11) << "ProbCastigo" << " | " << setw(10) << "Qualidade" << " | " << setw(10) << "SemTreinos"<< endl;
    cout << "--------------------------------------------------------------------------------------\n";
    for (int i = 0; i < p.tamanho; i++) {
        cout << left << setw(23) << p.jogadores[i].nome << " | " << setw(3) << p.jogadores[i].numero << " | " << setw(7) << p.jogadores[i].posicao << " | " << setw(5) << p.jogadores[i].idade << " | " << setw(9) << (to_string(p.jogadores[i].probLesao) + "%") << " | " << setw(11) << (to_string(p.jogadores[i].probCastigo) + "%") << " | " << setw(10) << p.jogadores[i].qualidade << setw(10) << p.jogadores[i].semanasTreino << " | "  <<endl;
    }
}

void mostrarLesionados(ListaJogadores &p) {
    cout << left << setw(23) << "Nome" << " | " << setw(3) << "No" << " | " << setw(7) << "Posicao" << " | " << setw(5) << "Idade" << " | " << setw(9) << "ProbLesao" << " | " << setw(11) << "ProbCastigo" << " | " << setw(10) << "Qualidade" << " | " << setw(8) << "JogosLesao" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < p.tamanho; i++) {
        cout << left << setw(23) << p.jogadores[i].nome << " | " << setw(3) << p.jogadores[i].numero << " | " << setw(7) << p.jogadores[i].posicao << " | " << setw(5) << p.jogadores[i].idade << " | " << setw(9) << (to_string(p.jogadores[i].probLesao) + "%") << " | " << setw(11) << (to_string(p.jogadores[i].probCastigo) + "%") << " | " << setw(10) << p.jogadores[i].qualidade << " | " << setw(8) << p.jogadores[i].jornadasLesao << endl;
    }
}

void mostrarCastigados(ListaJogadores &p) {
    cout << left << setw(23) << "Nome" << " | " << setw(3) << "No" << " | " << setw(7) << "Posicao" << " | " << setw(5) << "Idade" << " | " << setw(9) << "ProbLesao" << " | " << setw(11) << "ProbCastigo" << " | " << setw(10) << "Qualidade" << " | " << setw(8) << "JogosCastigo" << endl;
    cout << "------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < p.tamanho; i++) {
        cout << left << setw(23) << p.jogadores[i].nome << " | " << setw(3) << p.jogadores[i].numero << " | " << setw(7) << p.jogadores[i].posicao << " | " << setw(5) << p.jogadores[i].idade << " | " << setw(9) << (to_string(p.jogadores[i].probLesao) + "%") << " | " << setw(11) << (to_string(p.jogadores[i].probCastigo) + "%") << " | " << setw(10) << p.jogadores[i].qualidade << " | " << setw(8) << p.jogadores[i].jogosCastigo << endl;
    }
}

void mostrarTransferencias(ListaJogadores &p) {
    cout << left << setw(23) << "Nome" << " | " << setw(3) << "No" << " | " << setw(7) << "Posicao" << " | " << setw(5) << "Idade" << " | " << setw(9) << "ProbLesao" << " | " << setw(11) << "ProbCastigo" << " | " << setw(10) << "Qualidade" << endl;
    cout << "--------------------------------------------------------------------------------------\n";
    for (int i = 0; i < p.tamanho; i++) {
        cout << left << setw(23) << p.jogadores[i].nome << " | " << setw(3) << p.jogadores[i].numero << " | " << setw(7) << p.jogadores[i].posicao << " | " << setw(5) << p.jogadores[i].idade << " | " << setw(9) << (to_string(p.jogadores[i].probLesao) + "%") << " | " << setw(11) << (to_string(p.jogadores[i].probCastigo) + "%") << " | " << setw(10) << p.jogadores[i].qualidade << endl;
    }
}
int contarPosicao(ListaJogadores &plantel, string posicao){ //funcão auxiliar
    int count = 0; // variável para contar jogadores dessa posição - começa a zero

    // percorre todos os jogadores do plantel
    for (int i = 0; i < plantel.tamanho; i++)
    {
        // se a posição do jogador for igual à que queremos contar - caso não seja ignora o if e passa para outra posição (outra verificação)
        if (plantel.jogadores[i].posicao == posicao)
        {
            count++; // incrementa um à variável
        }
    }

    return count; // devolve a variável - numero de jogadores numa dada posição
}
void ordenarPorPosicao(ListaJogadores &plantel)
{
    // função que recebe o plantel por referência (&)
    // ou seja, vai alterar diretamente o plantel original

    for (int i = 0; i < plantel.tamanho - 1; i++)
    {
        // ciclo exterior: percorre o plantel desde o primeiro jogador até ao penúltimo
        // usamos tamanho - 1 porque o último já fica automaticamente ordenado - O último elemento não precisa de ser percorrido porque já foi comparado com todos os anteriores, garantindo a sua posição correta

        for (int j = i + 1; j < plantel.tamanho; j++)
        {
            // ciclo interior: compara o jogador i com todos os jogadores à frente dele
            // começa em i+1 porque não faz sentido comparar com ele próprio

            // usa a função ordemPos para converter a posição em número
            // e comparar esses valores

            if (ordemPos(plantel.jogadores[i].posicao) >
                ordemPos(plantel.jogadores[j].posicao))
            {
                // se o jogador i tiver uma posição "maior" que o j
                // significa que está fora de ordem e deve trocar

                Jogador temp = plantel.jogadores[i];
                // guarda temporariamente o jogador i
                // para não perder os dados quando fizermos a troca

                plantel.jogadores[i] = plantel.jogadores[j];
                // coloca o jogador j na posição i

                plantel.jogadores[j] = temp;
                // coloca o antigo jogador i (guardado em temp) na posição j
            }
        }
    }
}
void mudarPosicao(ListaJogadores &plantel, int i, string novaPosicao)
{
    // verifica se o índice é válido (não pode ser negativo nem maior ou igual ao tamanho)
    if (i < 0 || i >= plantel.tamanho)
    {
        return; // se for inválido, sai da função sem fazer nada
    }

    // cria um endereço ao jogador na posição indicada
    Jogador &j = plantel.jogadores[i];
    // usamos & para não criar cópia → assim alteramos diretamente o jogador no plantel - poisa usamos bo seu endereço unico

    // conta quantos jogadores já existem na posição que queremos mudar
    int total = contarPosicao(plantel, novaPosicao);
    // isto é importante para respeitar os limites do enunciado

    // verificar limites máximos de cada posição

    if (novaPosicao == "GR" && total >= 3)
        return; // já existem 3 GR → não pode adicionar mais - para a função

    if (novaPosicao == "DEF" && total >= 10)
        return; // já existem 10 DEF → não pode adicionar mais

    if (novaPosicao == "MED" && total >= 10)
        return; // já existem 10 MED → não pode adicionar mais

    if (novaPosicao == "AVA" && total >= 7)
        return; // já existem 7 AVA → não pode adicionar mais

    // alterar a posição do jogador
    j.posicao = novaPosicao;
    // aqui o jogador j passa oficialmente a ter a nova posição
    // ao mudar a posição, o plantel fica desorganizado

    ordenarPorPosicao(plantel);
    // chama a função que reorganiza o plantel usando ordemPos
}
void treinarJogador(ListaJogadores &plantel, int i, int semanas)
{
    // verifica se o índice i é válido
    // i não pode ser menor que 0 nem maior ou igual ao tamanho do plantel
    if (i < 0 || i >= plantel.tamanho)
    {
        return; // se for inválido, sai da função sem fazer nada
    }

    // cria um endereço ao jogador na posição i do array
    // isto NÃO cria cópia - altera diretamente o jogador original
    Jogador &j = plantel.jogadores[i];

    // verifica se o jogador está lesionado
    // se jornadasLesao > 0 significa que ainda está lesionado
    if (j.jornadasLesao > 0)
    {
        return; // jogador lesionado não pode treinar - sai da função
    }

    // limita o número de semanas a no máximo 5
    // mesmo que o utilizador escreva 10, passa a 5
    if (semanas > 5)
    {
        semanas = 5;
    }

    // verifica se o número de semanas é inválido (0 ou negativo)
    // não faz sentido treinar nessas condições
    if (semanas <= 0)
    {
        return; // sai da função sem alterar nada
    }

    // calcula o aumento da qualidade
    // cada semana dá +5 pontos
    int aumento = semanas * 5;

    // adiciona o aumento à qualidade atual do jogador
    j.qualidade += aumento;

    // garante que a qualidade não ultrapassa o máximo (100)
    if (j.qualidade > 100)
    {
        j.qualidade = 100; // define o máximo permitido
    }
}