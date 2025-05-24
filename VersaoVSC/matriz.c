#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cria uma matriz nova com o número de linhas e colunas dados.
   Aloca toda a memória necessária para guardar os dados.
   Retorna o ponteiro pra matriz criada, ou NULL se algo der errado. */
TMatriz* matriz_criar(int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0) {
        return NULL;
    }

    TMatriz* matriz = (TMatriz*)malloc(sizeof(TMatriz));
    if (matriz == NULL) {
        return NULL;
    }

    matriz->linhas = linhas;
    matriz->colunas = colunas;
    
    // Aloca memória para as linhas
    matriz->dados = (char**)malloc(linhas * sizeof(char*));
    if (matriz->dados == NULL) {
        free(matriz);
        return NULL;
    }

    // Aloca memória para as colunas de cada linha
    for (int i = 0; i < linhas; i++) {
        matriz->dados[i] = (char*)malloc(colunas * sizeof(char));
        if (matriz->dados[i] == NULL) {
            // Libera a memória já alocada
            for (int j = 0; j < i; j++) {
                free(matriz->dados[j]);
            }
            free(matriz->dados);
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

/* Preenche a matriz com os caracteres digitados.
   Recebe a matriz, o número de linhas e colunas.
   Lê linha por linha e copia os caracteres, se estiver tudo certo retorna 1,
   se der erro (como linha curta ou ponteiro nulo), retorna 0. */

int matriz_preencher(TMatriz* matriz, int linhas, int colunas) {
    if (matriz == NULL || matriz->dados == NULL || linhas != matriz->linhas || colunas != matriz->colunas) {
        return 0;
    }

    // Lê os caracteres da matriz linha por linha
    for (int i = 0; i < linhas; i++) {
        char linha[100];
        scanf("%s", linha);
        
        // Verifica se a linha tem o tamanho correto
        if (strlen(linha) < colunas) {
            printf("Erro: A linha %d tem menos de %d caracteres\n", i+1, colunas);
            return 0;
        }
        
        // Copia os caracteres para a matriz
        for (int j = 0; j < colunas; j++) {
            matriz->dados[i][j] = linha[j];
        }
    }

    return 1;
}

void matriz_imprimir(TMatriz* matriz) {
    if (matriz == NULL || matriz->dados == NULL) {
        return;
    }

    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            printf("%c ", matriz->dados[i][j]);
        }
        printf("\n");
    }
}

int coordenada_verificar(TCoordenada coordenada, TMatriz* matriz) {
    if (matriz == NULL) {
        return 0;
    }
    
    return (coordenada.linha >= 0 && coordenada.linha < matriz->linhas &&
            coordenada.coluna >= 0 && coordenada.coluna < matriz->colunas);
}

int matriz_apagar(TMatriz* matriz) {
    if (matriz == NULL) {
        return 0;
    }

    if (matriz->dados != NULL) {
        for (int i = 0; i < matriz->linhas; i++) {
            if (matriz->dados[i] != NULL) {
                free(matriz->dados[i]);
            }
        }
        free(matriz->dados);
    }

    free(matriz);
    return 1;
}
