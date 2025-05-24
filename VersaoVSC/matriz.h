#ifndef MATRIZ_H
#define MATRIZ_H

#include "coordenada.h"

/* Estrutura que representa a matriz do caça-palavras */
typedef struct {
    char** dados;  // matriz de caracteres
    int linhas;    // número de linhas
    int colunas;   // número de colunas
} TMatriz;

/* Cria uma matriz nova, vazia, com o tamanho passado.
   Retorna o ponteiro pra matriz ou NULL se der erro. */
TMatriz* matriz_criar(int linhas, int colunas);

/* Preenche a matriz com dados lidos da entrada.
   Recebe a matriz, o número de linhas e colunas.
   Retorna 1 se preencher certinho, 0 se falhar. */
int matriz_preencher(TMatriz* matriz, int linhas, int colunas);

/* Imprime a matriz na tela */
void matriz_imprimir(TMatriz* matriz);

/* Confere se uma coordenada tá dentro dos limites da matriz.
   Retorna 1 se sim, 0 se não. */
int coordenada_verificar(TCoordenada coordenada, TMatriz* matriz);

/* Libera a memória usada pela matriz.
   Retorna 1 se conseguiu liberar, 0 se falhou. */
int matriz_apagar(TMatriz* matriz);

#endif
