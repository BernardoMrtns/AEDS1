#ifndef COORDENADA_H
#define COORDENADA_H

/**
 * Estrutura para representar uma coordenada na matriz
 */
typedef struct {
    int linha;
    int coluna;
} TCoordenada;

/* Cria uma coordenada nova com os valores passados.
   Recebe a linha (i) e a coluna (j), e retorna a coordenada montada. */

TCoordenada coordenada_criar(int i, int j);

#endif
