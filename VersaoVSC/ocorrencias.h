#ifndef OCORRENCIAS_H
#define OCORRENCIAS_H

#include "coordenada.h"
#include "matriz.h"
#include "tipos.h"

/*
 * Cria uma nova estrutura de ocorrências
 * Retorna a estrutura criada
 */

TOcorrencias ocorrencias_criar();

/*
 * Adiciona uma coordenada para uma letra no vetor de ocorrências
 * Recebe o ponteiro pra ocorrências, a letra e a coordenada
 * Retorna 1 se der certo, 0 se falhar
 */
int ocorrencias_adicionar(TOcorrencias* ocorr, char letra, TCoordenada coor);

/*
 * Busca as coordenadas da primeira letra da palavra
 * Recebe o ponteiro pra ocorrências, a letra e ponteiro pra número de ocorrências
 * Retorna o vetor de coordenadas ou NULL se não achar
 */

TCoordenada* ocorrencias_buscar_letra(TOcorrencias* ocorr, char primeira_letra, int* num_ocorrencias);

/*
 * Calcula todas as ocorrências das letras na matriz do caça-palavras
 * Recebe o ponteiro pra ocorrências e a matriz
 * Retorna 1 se funcionar, 0 se falhar
 */
int ocorrencias_calcular(TOcorrencias* ocorr, TMatriz* matriz);

/*
 * Libera toda a memória da estrutura de ocorrências
 * Recebe o ponteiro pra ocorrências
 * Retorna 1 se liberar certo, 0 se falhar
 */
int ocorrencias_apagar(TOcorrencias* ocorr);

#endif
