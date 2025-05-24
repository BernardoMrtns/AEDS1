#ifndef TIPOS_H
#define TIPOS_H

#include "coordenada.h"

/*
 * Representa uma palavra no caça-palavras
 * Guarda o texto, início, fim e se foi encontrada
 */
typedef struct {
    char* texto;           // Texto da palavra
    TCoordenada inicio;    // Coordenada de início da palavra
    TCoordenada fim;       // Coordenada de fim da palavra
    int encontrada;        // Flag indicando se a palavra foi encontrada
} TPalavra;

/*
 * Guarda uma letra e todas as coordenadas onde ela aparece
 * Também armazena quantas vezes apareceu e o tamanho do vetor
 */
typedef struct {
    char letra;                // Letra
    TCoordenada* coordenadas;  // Vetor de coordenadas onde a letra ocorre
    int num_ocorrencias;       // Número de ocorrências da letra
    int capacidade;            // Capacidade atual do vetor de coordenadas
} TOcorrenciaLetra;

/*
 * Guarda todas as ocorrências de letras na matriz
 * Tem um vetor de TOcorrenciaLetra, quantidade e capacidade
 */
typedef struct {
    TOcorrenciaLetra* ocorrencias;  // Vetor de ocorrências de letras
    int num_letras;                 // Número de letras diferentes
    int capacidade;                 // Capacidade atual do vetor de ocorrências
} TOcorrencias;

#endif
