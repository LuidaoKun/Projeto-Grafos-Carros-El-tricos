/*
Alix D'Avelar Pretto Sanches     » 10395951
Amanda Gois Smanioto             » 10395773
Luigi Uematsu                    » 10396148 
*/

#ifndef TGRAFOND_H
#define TGRAFOND_H
struct TGrafoND {
    int n; // Número de vértices
    int m; // Número de arestas
    int **adj; // Matriz de adjacência
};

void inicializa_TGrafoND(struct TGrafoND *grafo, int n);
void libera_TGrafoND(struct TGrafoND *grafo);
void insereA_TGrafoND(struct TGrafoND *grafo, int v, int w, int peso);
void insereVertice_TGrafoND(struct TGrafoND *grafo);
void insereAresta_TGrafoND(struct TGrafoND *grafo, int v, int w, int peso);
void removeAresta_TGrafoND(struct TGrafoND *grafo, int v, int w);
void removeVertice_TGrafoND(struct TGrafoND *grafo, int v);
void removeA_TGrafoND(struct TGrafoND *grafo, int v, int w);
void mostrarConteudoArquivo(const char *nomeArquivo);
void lerGrafoArquivo(const char *nomeArquivo, struct TGrafoND *grafo);
void gravarDadosArquivo(const char *nomeArquivo, struct TGrafoND *grafo);
int verificaConexidade_TGrafoND(struct TGrafoND grafo);
void apresentarConexidadeEGrafoReduzido(struct TGrafoND *grafo);
void show_TGrafoND(struct TGrafoND grafo);
int podeColorir(struct TGrafoND grafo, int v, int cores[], int cor, int num_cores);
void colorirGrafo(struct TGrafoND grafo);
int verificarGrafoEuleriano(struct TGrafoND grafo);
int verificarPercursoEuleriano(struct TGrafoND grafo);
int verifica_ciclo_hamiltoniano(int ciclo[], int n, struct TGrafoND grafo);
int proximo_vertice(int ciclo[], int n, struct TGrafoND grafo);
int verificarGrafoHamiltoniano(struct TGrafoND grafo);
#endif 