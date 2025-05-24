#include "coordenada.h"

TCoordenada coordenada_criar(int i, int j) {
    TCoordenada coordenada;
    coordenada.linha = i;
    coordenada.coluna = j;
    return coordenada;
}
