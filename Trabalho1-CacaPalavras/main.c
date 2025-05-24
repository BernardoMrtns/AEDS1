#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "coordenada.h"
#include "matriz.h"
#include "tipos.h"
#include "palavra.h"
#include "ocorrencias.h"


/* Função que procura as palavras na matriz do caça-palavras.
   Recebe a matriz principal, a matriz pra marcar as ocorrências,
   o vetor com as palavras e a quantidade de palavras.
   Retorna 1 se encontrar tudo certo, 0 se der algum problema. */

int matriz_solucionar(TMatriz* matriz, TOcorrencias* ocorr, TPalavra* palavras, int num_palavras) {
    if (matriz == NULL || ocorr == NULL || palavras == NULL || num_palavras <= 0) {
        return 0;
    }
    
    // Busca cada palavra na matriz
    for (int i = 0; i < num_palavras; i++) {
        palavra_buscar(&palavras[i], matriz, ocorr);
    }
    
    return 1;
}

void aguardar_saida() {
    printf("\n============================================\n");
    printf("Programa concluido. Digite 'sair' para encerrar: ");
    
    char entrada[10];
    while (1) {
        scanf("%s", entrada);
        if (strcmp(entrada, "sair") == 0) {
            break;
        }
        printf("Para sair, digite 'sair': ");
    }
}

int main() {
    int n, m, k;
    
    // Lê as dimensões da matriz com mensagens informativas
    printf("Digite o numero de linhas e colunas da matriz (ex: 5 6): ");
    scanf("%d %d", &n, &m);
    
    // Cria a matriz
    TMatriz* matriz = matriz_criar(n, m);
    if (matriz == NULL) {
        printf("Erro ao criar a matriz\n");
        aguardar_saida();
        return 1;
    }
    
    // Mensagem informativa antes de preencher a matriz
    printf("Digite as %d linhas da matriz (cada linha com %d letras):\n", n, m);
    
    // Preenche a matriz
    if (!matriz_preencher(matriz, n, m)) {
        printf("Erro ao preencher a matriz\n");
        matriz_apagar(matriz);
        aguardar_saida();
        return 1;
    }
    
    // Lê o número de palavras com mensagem informativa
    printf("Digite o numero de palavras a serem buscadas: ");
    scanf("%d", &k);
    
    // Aloca memória para as palavras
    TPalavra* palavras = (TPalavra*)malloc(k * sizeof(TPalavra));
    if (palavras == NULL) {
        printf("Erro ao alocar memoria para as palavras\n");
        matriz_apagar(matriz);
        aguardar_saida();
        return 1;
    }
    
    // Mensagem informativa antes de preencher as palavras
    printf("Digite as %d palavras a serem buscadas (uma por linha):\n", k);
    
    // Preenche as palavras
    if (!palavras_preencher(palavras, k)) {
        printf("Erro ao preencher as palavras\n");
        matriz_apagar(matriz);
        free(palavras);
        aguardar_saida();
        return 1;
    }
    
    // Cria a matriz de ocorrências
    TOcorrencias ocorrencias = ocorrencias_criar();
    
    // Calcula as ocorrências
    if (!ocorrencias_calcular(&ocorrencias, matriz)) {
        printf("Erro ao calcular as ocorrencias\n");
        matriz_apagar(matriz);
        palavras_apagar(palavras, k);
        ocorrencias_apagar(&ocorrencias);
        aguardar_saida();
        return 1;
    }
    
    // Mensagem informativa antes de resolver o caça-palavras
    printf("\nResolvendo o caca-palavras...\n\n");
    
    // Resolve o caça-palavras
    if (!matriz_solucionar(matriz, &ocorrencias, palavras, k)) {
        printf("Erro ao solucionar o caca-palavras\n");
        matriz_apagar(matriz);
        palavras_apagar(palavras, k);
        ocorrencias_apagar(&ocorrencias);
        aguardar_saida();
        return 1;
    }
    
    // Mensagem informativa antes de imprimir a solução
    printf("Resultado:\n");
    
    // Imprime a solução
    palavras_imprimir_solucao(palavras, k);
    
    // Libera a memória
    matriz_apagar(matriz);
    palavras_apagar(palavras, k);
    ocorrencias_apagar(&ocorrencias);
    aguardar_saida();
    
    return 0;
}