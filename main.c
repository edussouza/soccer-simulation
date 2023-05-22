#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "equipe.h"
//#include "jogo.h"
//#include "campeonato.h"

#define getName(var)  #var

// média de gols do Campeonato Brasileiro 2022
// 905 gols / 380 jogos = 2,38 gols

#define PROB 0.0264444
// probabilidade de um gol acontecer em um dos 90 minutos -> 2,38/90 = 0,024

typedef enum {									// enum que define os nomes dos times
	AMERICAMINEIRO,
	ATHELTICOPR,
	ATLETICOMG,
	BAHIA,
	BOTAFOGO, 
	BRAGANTINO,
	CORINTHIANS, 
	CORITIBA,
	CRUZEIRO,
	CUIABA,
	FLAMENGO,
	FLUMINENSE,
	FORTALEZA,
	GOIAS,
	GREMIO,
	INTERNACIONAL,
	PALMEIRAS,
	SANTOS,
	SAOPAULO,
	VASCO,
} nomeTimes;

static const char *const nome_Times[] = {		// transforma os enum para String
	[AMERICAMINEIRO] = "America-MG",
	[ATHELTICOPR] = "Athletico-PR",
	[ATLETICOMG] = "Atletico-MG",
	[BAHIA] = "Bahia",
	[BOTAFOGO] = "Botafogo",
	[BRAGANTINO] = "Bragantino",
	[CORINTHIANS] = "Corinthians",
	[CORITIBA] = "Coritiba",
	[CRUZEIRO] = "Cruzeiro",
	[CUIABA] = "Cuiaba",
	[FLAMENGO] = "Flamengo",
	[FLUMINENSE] = "Fluminense",
	[FORTALEZA] = "Fortaleza",
	[GOIAS] = "Goias",
	[GREMIO] = "Gremio",
	[INTERNACIONAL] = "Internacional",
	[PALMEIRAS] = "Palmeiras",
	[SANTOS] = "Santos",
	[SAOPAULO] = "Sao Paulo",
	[VASCO] = "Vasco",
};

typedef struct {
    int pontuacao;
    int posicao;
    int vitorias;
    int empates;
    int derrotas;
    int golsMarcados;
    int golsSofridos;
    char nome[40];
} Time;

typedef struct {
    Time casa;
    Time visitante;
    int placar[2];
} Jogo;
// posição 0 do vetor placar[] representa os gols do time de casa
// posição 1 do vetor placar[] representa os gols do time visitante
// posição 2 do vetor placar[] representa o total de gols do jogo

typedef struct{
	Jogo vet[9];
} Rodada;
// para cada posição do vetor, tera um jogo, configurando os 10 jogos de cada rodada

typedef struct {
    Rodada rodadas[10];
	Time tab[20];
    Time chaves[20];    
} Campeonato;
// para cada uma das posições do vetor vet[], acontecera uma rodada

//interface
void simulaPartida(Time*, Time*, Jogo*);
void mostraInfoTime(Time, int);
Time inicializaDados(Time*, char[]);
void mostraPlacar(Jogo);
Campeonato criaCampeonato();

//-------------------------------------------------------------------------------------------//

// IMPLEMENTAÇÃO FUNÇÕES

void simulaPartida(Time* A, Time* B, Jogo* x){
// inicializa o placar com 0x0
    x->placar[0] = 0;
    x->placar[1] = 0;
    x->placar[2] = 0;

// define os times casa/visitante
    x->casa = *A;
    x->visitante = *B;

    int minuto;

    for(minuto = 1; minuto <= 90; minuto++){
    	
    	float probA = (float)rand() / RAND_MAX; // calcula um número de 0 a 1 para o time A
        //printf("PROBA : %f\n", probA);
        float probB = (float)rand() / RAND_MAX; // calcula um número de 0 a 1 para o time B
        //printf("PROBb : %f\n", probB);
        

        if(PROB >= probA){  // time A marcou gol    
    	// atualiza gols dos times
            x->placar[0]++;
            //printf("Gols A: %d\n", x->placar[0]);
            (A->golsMarcados)++;
            //printf("Gols Marcados A: %d\n", A->golsMarcados);
            (B->golsSofridos)++;
    		//printf("Gols Sofridos B: %d\n", B->golsSofridos);
        }

        if(PROB >= probB){ // time B marcou gol
            // atualiza gols dos times
            x->placar[1]++;
            //printf("Gols B: %d\n", x->placar[1]);
            A->golsSofridos = A->golsSofridos + 1;
            //printf("Gols Sofridos A: %d\n", A->golsSofridos);
    		B->golsMarcados = B->golsMarcados + 1;
    		//printf("Gols Marcados B: %d\n", B->golsMarcados);
        }
    }

    x->placar[2] = x->placar[0] + x->placar[1]; // atualiza total de gols na partida
    //printf("\nTotal: %d", x->placar[2]);
	
	   

    if(x->placar[0] > x->placar[1]){  // atualiza dados do time A caso ganhe
        A->vitorias++;
        A->pontuacao = A->pontuacao + 3;
        B->derrotas++;
    } else if (x->placar[1] > x->placar[0]){ // atualiza dados do time B caso ganhe
        B->vitorias++;
        B->pontuacao = B->pontuacao + 3;
        A->derrotas++;
    } else {    // caso ocorra empate
        A->empates++;
        A->pontuacao++;
        B->empates++;
        B->pontuacao++;
    }

}

void mostraInfoTime(Time A, int len) {
    printf("\n");
    printf("--------------------------------");
    printf("TIME: %.*s\n", len, A.nome);
    printf("Pontuacao: %d\n", A.pontuacao);
    printf("Vitorias: %d\n", A.vitorias);
    printf("Derrotas: %d\n", A.derrotas);
    printf("Empates: %d\n", A.empates);
    printf("Gols Marcados: %d\n", A.golsMarcados);
    printf("Gols Sofridos: %d\n", A.golsSofridos);
    printf("--------------------------------");
    printf("\n");
}

Time inicializaDados(Time *A, char nome[]) {
	memcpy(A->nome, nome, 15);
    A->derrotas = 0;
    A->empates = 0;
    A->golsMarcados = 0;
    A->golsSofridos = 0;
    A->pontuacao = 0;
    A->posicao = 0;
    A->vitorias = 0;
    return *A;
}

void mostraPlacar(Jogo x){
	printf("-----------------------------------");
    printf("\n%s X %s", x.casa.nome, x.visitante.nome);
	printf("\n%d X %d", x.placar[0], x.placar[1]);
	printf("\nTotal de Gols: %d\n", x.placar[0] + x.placar[1]);
	
}

Campeonato criaCampeonato(){
	
	Campeonato x;
		
	int i = 0;
	
	for(i; i< 20; i++){
		
		memset(x.tab[i].nome, 0, sizeof(x.tab[i].nome));
        strcpy(x.tab[i].nome, nome_Times[i]);
        inicializaDados(&x.tab[i], x.tab[i].nome);
		//printf("\n%s", x.vet[i - 1].nome);	
	}
	
	return x;
	
}

int main(){

    srand(time(NULL));
	
	Campeonato x = criaCampeonato();
    
    simulaPartida(&x.tab[0], &x.tab[1], &x.rodadas->vet[0]);

    mostraPlacar(x.rodadas->vet[0]);
	
    // Jogo primeiro;

	// char sp[] = "Sao Paulo";
    // Time um = inicializaDados(&um, sp);
	
	// char pal[] = "Palmeiras";   
    // Time dois = inicializaDados(&dois, pal);

    // simulaPartida(&um, &dois, &primeiro);
    
    // mostraInfoTime(um, strlen(um.nome));
    // mostraInfoTime(dois, strlen(dois.nome));
    
    // mostraPlacar(primeiro);
	
    
	return 0;
}