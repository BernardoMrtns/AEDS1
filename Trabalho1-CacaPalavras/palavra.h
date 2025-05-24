#ifndef PALAVRA_H
#define PALAVRA_H

#include "coordenada.h"
#include "matriz.h"
#include "tipos.h"

/*
 * Cria uma nova palavra a partir do texto passado
 * Retorna a palavra criada
 */
TPalavra palavra_criar(char* palavra);

/*
 * Busca a palavra começando em uma posição específica na matriz
 * Recebe a palavra, a matriz e a posição inicial
 * Retorna a coordenada final se achar, ou (-1,-1) se não achar
 */
TCoordenada palavra_buscar_pos(TPalavra palavra, TMatriz* matriz, TCoordenada pos);

/*
 * Busca a palavra usando a matriz de ocorrências para otimizar
 * Recebe a palavra, a matriz e as ocorrências
 * Retorna 1 se encontrar, 0 se não
 */
int palavra_buscar(TPalavra* palavra, TMatriz* matriz, TOcorrencias* ocorr);

/*
 * Adiciona uma palavra ao vetor de palavras
 * Retorna o tamanho atualizado do vetor ou -1 se falhar
 */
int palavras_add(TPalavra* palavras, TPalavra palavra);

/*
 * Preenche o vetor de palavras lendo da entrada padrão
 * Recebe o vetor e a quantidade de palavras
 * Retorna 1 se ler tudo certo, 0 se falhar
 */
int palavras_preencher(TPalavra* palavras, int num_palavras);

/*
 * Imprime a solução do caça-palavras (as palavras encontradas)
 * Recebe o vetor de palavras e a quantidade
 */
void palavras_imprimir_solucao(TPalavra* palavras, int num_palavras);

/*
 * Libera a memória usada pelo vetor de palavras
 * Recebe o vetor e a quantidade
 * Retorna 1 se liberar tudo, 0 se falhar
 */
int palavras_apagar(TPalavra* palavras, int num_palavras);

#endif
