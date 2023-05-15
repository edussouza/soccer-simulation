#ifndef time
#define time

typedef struct {
    int pontuacao;
    int posicao;
    int vitorias;
    int empates;
    int derrotas;
    int golsMarcados;
    int golsSofridos;
    char nome[15];
} Time;

#endif