#include "palavra.h"
#include "ocorrencias.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TPalavra palavra_criar(char* palavra) {
    TPalavra nova_palavra;
    
    // Aloca memória para o texto da palavra
    nova_palavra.texto = strdup(palavra);
    
    // Inicializa as coordenadas com valores inválidos
    nova_palavra.inicio = coordenada_criar(-1, -1);
    nova_palavra.fim = coordenada_criar(-1, -1);
    
    // Inicializa o flag de encontrada como falso
    nova_palavra.encontrada = 0;
    
    return nova_palavra;
}

// Direções possíveis para busca (8 direções)
 int direcoes[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},  // Diagonal superior esquerda, acima, diagonal superior direita
    {0, -1},            {0, 1},   // Esquerda, direita
    {1, -1},  {1, 0},  {1, 1}     // Diagonal inferior esquerda, abaixo, diagonal inferior direita
};

TCoordenada palavra_buscar_pos(TPalavra palavra, TMatriz* matriz, TCoordenada pos) {
    if (matriz == NULL || palavra.texto == NULL || !coordenada_verificar(pos, matriz)) {
        return coordenada_criar(-1, -1);
    }
    
    int len = strlen(palavra.texto);
    
    // Verifica se a primeira letra da palavra corresponde à posição inicial
    if (matriz->dados[pos.linha][pos.coluna] != palavra.texto[0]) {
        return coordenada_criar(-1, -1);
    }
    
    // Tenta todas as 8 direções possíveis
    for (int dir = 0; dir < 8; dir++) {
        int encontrada = 1;
        TCoordenada fim = pos;
        
        // Verifica se a palavra completa pode ser encontrada nesta direção
        for (int i = 1; i < len; i++) {
            int nova_linha = pos.linha + i * direcoes[dir][0];
            int nova_coluna = pos.coluna + i * direcoes[dir][1];
            TCoordenada nova_pos = coordenada_criar(nova_linha, nova_coluna);
            
            if (!coordenada_verificar(nova_pos, matriz) || 
                matriz->dados[nova_linha][nova_coluna] != palavra.texto[i]) {
                encontrada = 0;
                break;
            }
            
            fim = nova_pos;
        }
        
        if (encontrada) {
            return fim;
        }
    }
    
    return coordenada_criar(-1, -1);
}

int palavra_buscar(TPalavra* palavra, TMatriz* matriz, TOcorrencias* ocorr) {
    if (matriz == NULL || palavra == NULL || palavra->texto == NULL || ocorr == NULL) {
        return 0;
    }
    
    int num_ocorrencias;
    TCoordenada* ocorrencias = ocorrencias_buscar_letra(ocorr, palavra->texto[0], &num_ocorrencias);
    
    if (ocorrencias == NULL) {
        return 0;
    }
    
    // Tenta encontrar a palavra a partir de cada ocorrência da primeira letra
    for (int i = 0; i < num_ocorrencias; i++) {
        TCoordenada fim = palavra_buscar_pos(*palavra, matriz, ocorrencias[i]);
        
        if (fim.linha != -1 && fim.coluna != -1) {
            palavra->inicio = ocorrencias[i];
            palavra->fim = fim;
            palavra->encontrada = 1;
            return 1;
        }
    }
    
    // Palavra não encontrada
    palavra->inicio = coordenada_criar(0, 0);
    palavra->fim = coordenada_criar(0, 0);
    palavra->encontrada = 0;
    
    return 0;
}

int palavras_preencher(TPalavra* palavras, int num_palavras) {
    if (palavras == NULL || num_palavras <= 0) {
        return 0;
    }
    
    char buffer[100];  // Buffer para ler as palavras
    
    for (int i = 0; i < num_palavras; i++) {
        scanf("%s", buffer);
        palavras[i] = palavra_criar(buffer);
    }
    
    return 1;
}

// Modifique a função palavras_imprimir_solucao para incluir o nome da palavra
void palavras_imprimir_solucao(TPalavra* palavras, int num_palavras) {
    if (palavras == NULL) {
        return;
    }
    
    for (int i = 0; i < num_palavras; i++) {
        printf("%d %d %d %d %s\n", 
               palavras[i].inicio.linha, palavras[i].inicio.coluna,
               palavras[i].fim.linha, palavras[i].fim.coluna,
               palavras[i].texto);
    }
}

int palavras_apagar(TPalavra* palavras, int num_palavras) {
    if (palavras == NULL) {
        return 0;
    }
    
    for (int i = 0; i < num_palavras; i++) {
        if (palavras[i].texto != NULL) {
            free(palavras[i].texto);
        }
    }
    
    return 1;
}
