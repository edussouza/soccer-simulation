#ifndef jogo
#define jogo
 
typedef struct {
    Time casa;
    Time visitante;
    int placar[2];
} Jogo;

// posição 0 do vetor placar[] representa os gols do time de casa
// posição 1 do vetor placar[] representa os gols do time visitante
// posição 2 do vetor placar[] representa o total de gols do jogo

#endif