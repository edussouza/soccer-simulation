#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define getName(var)

// média de gols do Campeonato Brasileiro 2022
// 905 gols / 380 jogos = 2,38 gols

#define PROB 0.027
// probabilidade de um gol acontecer em um dos 90 minutos -> 2,38/90 = 0,027


typedef struct {
    int pontuacao;
    int posicao = 0;
    int vitorias = 0;
    int empates = 0;
    int derrotas = 0;
    int golsMarcados = 0;
    int golsSofridos = 0;
} Time;

typedef struct {
    Time casa;
    Time visitante;
    int placar[2];
    int minutos[90];
} Jogo;
// posição 0 do vetor placar[] representa os gols do time de casa
// posição 1 do vetor placar[] representa os gols do time visitante
// posição 2 do vetor placar[] representa o total de gols do jogo

typedef struct {
    Jogo vet[380];    
} Campeonato;
// para cada uma das posições do vetor vet[], ocorrerá uma chamada da função simulaPartida

//interface
void simulaPartida(Time, Time, Jogo);
void mostraInfoTime(Time);

//-------------------------------------------------------------------------------------------//

// IMPLEMENTAÇÃO FUNÇÕES

void simulaPartida(Time A, Time B, Jogo x){
// inicializa o placar com 0x0
    x.placar[0] = 0;
    x.placar[1] = 0;
    x.placar[2] = 0;

// define os times casa/visitante
    x.casa = A;
    x.visitante = B;

    srand(time(NULL));

    int minuto = 1;

    for(minuto; minuto <= 90; minuto++){

        float probA = (float)rand() / RAND_MAX; // calcula um número de 0 a 1 para o time A
        float probB = (float)rand() / RAND_MAX; // calcula um número de 0 a 1 para o time B

        if(probA <= PROB){  // time A marcou gol
            x.placar[0]++;
        }

        if(probB <= PROB){ // time B marcou gol
            x.placar[1]++;
        }
    }

    x.placar[2] = x.placar[0] + x.placar[1]; // atualiza total de gols na partida
    
    // atualiza gols dos times
    A.golsMarcados = A.golsMarcados + x.placar[0];
    A.golsSofridos = A.golsSofridos + x.placar[1];
    B.golsMarcados = B.golsMarcados + x.placar[1];
    B.golsSofridos = B.golsSofridos + x.placar[0];

    if(x.placar[0] > x.placar[1]){  // atualiza dados do time A caso ganhe
        A.vitorias++;
        A.pontuacao = A.pontuacao + 3;
        B.derrotas++;
    } else if (x.placar[1] > x.placar[0]){ // atualiza dados do time B caso ganhe
        B.vitorias++;
        B.pontuacao = B.pontuacao + 3;
        A.derrotas++;
    } else {    // caso ocorra empate
        A.empates++;
        A.pontuacao++;
        B.empates++;
        B.pontuacao++;
    }

}

void mostraInfoTimes(Time A){

    printf("\n\n");
    printf("TIME: %s\n", getName(A));
    printf("Pontuacao: %d\n", A.pontuacao);
    printf("Vitorias: %d\n", A.vitorias);
    printf("Derrotas: %d\n", A.derrotas);
    printf("Empates: %d\n", A.empates);
    printf("Gols Marcados: %d", A.golsMarcados);
    printf("Gols Sofridos: %d", A.golsSofridos);
    printf("\n\n");
}

int main(){

    Jogo primeiro;

    Time um;
    Time dois;
    // Time tres;
    // Time quatro;
    // Time cinco;
    // Time seis;
    // Time sete;
    // Time oito;
    // Time nove;
    // Time dez;
    // Time onze;
    // Time doze;
    // Time treze;
    // Time quatorze;
    // Time quinze;
    // Time dezesseis;
    // Time dezessete;
    // Time dezoito;
    // Time dezenove;
    // Time vinte;

    simulaPartida(um, dois, primeiro);
    mostraInfoTime(um);
    mostraInfoTime(dois);    

}