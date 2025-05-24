#include "ocorrencias.h"
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_INICIAL 10

TOcorrencias ocorrencias_criar() {
    TOcorrencias ocorr;
    
    ocorr.ocorrencias = (TOcorrenciaLetra*)malloc(CAPACIDADE_INICIAL * sizeof(TOcorrenciaLetra));
    ocorr.num_letras = 0;
    ocorr.capacidade = CAPACIDADE_INICIAL;
    
    return ocorr;
}

int ocorrencias_adicionar(TOcorrencias* ocorr, char letra, TCoordenada coor) {
    if (ocorr == NULL) {
        return 0;
    }
    
    // Procura se a letra já existe no vetor de ocorrências
    for (int i = 0; i < ocorr->num_letras; i++) {
        if (ocorr->ocorrencias[i].letra == letra) {
            // Verifica se precisa redimensionar o vetor de coordenadas
            if (ocorr->ocorrencias[i].num_ocorrencias >= ocorr->ocorrencias[i].capacidade) {
                int nova_capacidade = ocorr->ocorrencias[i].capacidade * 2;
                TCoordenada* novo_vetor = (TCoordenada*)realloc(
                    ocorr->ocorrencias[i].coordenadas,
                    nova_capacidade * sizeof(TCoordenada)
                );
                
                if (novo_vetor == NULL) {
                    return 0;
                }
                
                ocorr->ocorrencias[i].coordenadas = novo_vetor;
                ocorr->ocorrencias[i].capacidade = nova_capacidade;
            }
            
            // Adiciona a nova coordenada
            ocorr->ocorrencias[i].coordenadas[ocorr->ocorrencias[i].num_ocorrencias] = coor;
            ocorr->ocorrencias[i].num_ocorrencias++;
            
            return 1;
        }
    }
    
    // A letra não existe, verifica se precisa redimensionar o vetor de ocorrências
    if (ocorr->num_letras >= ocorr->capacidade) {
        int nova_capacidade = ocorr->capacidade * 2;
        TOcorrenciaLetra* novo_vetor = (TOcorrenciaLetra*)realloc(
            ocorr->ocorrencias,
            nova_capacidade * sizeof(TOcorrenciaLetra)
        );
        
        if (novo_vetor == NULL) {
            return 0;
        }
        
        ocorr->ocorrencias = novo_vetor;
        ocorr->capacidade = nova_capacidade;
    }
    
    // Cria uma nova ocorrência para a letra
    ocorr->ocorrencias[ocorr->num_letras].letra = letra;
    ocorr->ocorrencias[ocorr->num_letras].coordenadas = (TCoordenada*)malloc(CAPACIDADE_INICIAL * sizeof(TCoordenada));
    
    if (ocorr->ocorrencias[ocorr->num_letras].coordenadas == NULL) {
        return 0;
    }
    
    ocorr->ocorrencias[ocorr->num_letras].coordenadas[0] = coor;
    ocorr->ocorrencias[ocorr->num_letras].num_ocorrencias = 1;
    ocorr->ocorrencias[ocorr->num_letras].capacidade = CAPACIDADE_INICIAL;
    
    ocorr->num_letras++;
    
    return 1;
}

TCoordenada* ocorrencias_buscar_letra(TOcorrencias* ocorr, char primeira_letra, int* num_ocorrencias) {
    if (ocorr == NULL || num_ocorrencias == NULL) {
        *num_ocorrencias = 0;
        return NULL;
    }
    
    // Procura a primeira letra da palavra no vetor de ocorrências
    for (int i = 0; i < ocorr->num_letras; i++) {
        if (ocorr->ocorrencias[i].letra == primeira_letra) {
            *num_ocorrencias = ocorr->ocorrencias[i].num_ocorrencias;
            return ocorr->ocorrencias[i].coordenadas;
        }
    }
    
    *num_ocorrencias = 0;
    return NULL;
}

int ocorrencias_calcular(TOcorrencias* ocorr, TMatriz* matriz) {
    if (ocorr == NULL || matriz == NULL) {
        return 0;
    }
    
    // Percorre a matriz e adiciona cada letra as ocorrências
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            char letra = matriz->dados[i][j];
            TCoordenada coor = coordenada_criar(i, j);
            
            if (!ocorrencias_adicionar(ocorr, letra, coor)) {
                return 0;
            }
        }
    }
    
    return 1;
}

int ocorrencias_apagar(TOcorrencias* ocorr) {
    if (ocorr == NULL) {
        return 0;
    }
    
    for (int i = 0; i < ocorr->num_letras; i++) {
        if (ocorr->ocorrencias[i].coordenadas != NULL) {
            free(ocorr->ocorrencias[i].coordenadas);
        }
    }
    
    if (ocorr->ocorrencias != NULL) {
        free(ocorr->ocorrencias);
    }
    
    ocorr->num_letras = 0;
    ocorr->capacidade = 0;
    
    return 1;
}
