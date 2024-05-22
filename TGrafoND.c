/*
Alix D'Avelar Pretto Sanches     » 10395951
Amanda Gois Smanioto             » 10395773
Luigi Uematsu                    » 10396148 
*/

#include <stdio.h>
#include <stdlib.h>
#include "TGrafoND.h"

void inicializa_TGrafoND(struct TGrafoND *grafo, int n) {
    grafo->n = n;
    grafo->m = 0;
    grafo->adj = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
        grafo->adj[i] = (int *)calloc(n, sizeof(int)); // Inicializa a matriz com zeros
}
void libera_TGrafoND(struct TGrafoND *grafo) {
    for (int i = 0; i < grafo->n; i++)
        free(grafo->adj[i]);

    free(grafo->adj);
    grafo->n = 0;
    grafo->m = 0;
}
void insereA_TGrafoND(struct TGrafoND *grafo, int v, int w, int peso) {
    if (grafo->adj[v][w] == 0) {
        grafo->adj[v][w] = peso;
        grafo->adj[w][v] = peso;
        grafo->m++;
    }
}
void removeA_TGrafoND(struct TGrafoND *grafo, int v, int w) {
    if (grafo->adj[v][w] == 0) {
        printf("Aresta não existe\n");
        return;
    }

    grafo->adj[v][w] = 0;
    grafo->adj[w][v] = 0;
    grafo->m--;
}
void insereVertice_TGrafoND(struct TGrafoND *grafo) {
    
    int novoN = grafo->n + 1;
    grafo->adj = realloc(grafo->adj, novoN * sizeof(int *));
    grafo->adj[novoN - 1] = (int *)calloc(novoN, sizeof(int)); 

    for (int i = 0; i < novoN; i++)
        grafo->adj[i] = realloc(grafo->adj[i], novoN * sizeof(int));
    for (int i = 0; i < novoN; i++) {
        grafo->adj[i][novoN - 1] = 0;
        grafo->adj[novoN - 1][i] = 0;
    }

    grafo->n = novoN;
}
void removeVertice_TGrafoND(struct TGrafoND *grafo, int v) {
    if (v < 0 || v >= grafo->n) {
        printf("Vértice inválido\n");
        return;
    }

   
    for (int i = 0; i < grafo->n; i++) {
        if (grafo->adj[v][i] != 0)
            removeA_TGrafoND(grafo, v, i);
    }

  
    free(grafo->adj[v]);
    for (int i = v; i < grafo->n - 1; i++)
        grafo->adj[i] = grafo->adj[i + 1];
    grafo->adj = realloc(grafo->adj, (grafo->n - 1) * sizeof(int *));
    grafo->n--;
}
void removeAresta_TGrafoND(struct TGrafoND *grafo, int v, int w) {
    if (v < 0 || v >= grafo->n || w < 0 || w >= grafo->n || grafo->adj[v][w] == 0) {
        printf("Aresta não existe\n");
        return;
    }

    removeA_TGrafoND(grafo, v, w);
}
void insereAresta_TGrafoND(struct TGrafoND *grafo, int v, int w, int peso) {
    if (v < 0 || v >= grafo->n || w < 0 || w >= grafo->n) {
        printf("Vértices inválidos\n");
        return;
    }

    insereA_TGrafoND(grafo, v, w, peso);
}
void show_TGrafoND(struct TGrafoND grafo) {
    printf("n: %d\n", grafo.n);
    printf("m: %d\n", grafo.m);

    for (int i = 0; i < grafo.n; i++) {
        printf("\n");

        for (int w = 0; w < grafo.n; w++)
            printf("%d ", grafo.adj[i][w]);
    }
}
void mostrarConteudoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int caractere;
    while ((caractere = fgetc(arquivo)) != EOF) {
        printf("%c", caractere);
    }

    fclose(arquivo);
}
void lerGrafoArquivo(const char *nomeArquivo, struct TGrafoND *grafo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Lê o número de vértices
    fscanf(arquivo, "%d", &(grafo->n));
    inicializa_TGrafoND(grafo, grafo->n);

    for (int i = 0; i < grafo->n; i++) {
        int numero;
        fscanf(arquivo, "%d", &numero);
    }

    // Lê o número de arestas
    fscanf(arquivo, "%d", &(grafo->m));

    // Lê as arestas e insere no grafo
    for (int i = 0; i < grafo->m; i++) {
        int v, w, peso;
        fscanf(arquivo, "%d %d %d", &v, &w, &peso);
        insereA_TGrafoND(grafo, v - 1, w -1, peso);
    }

    
}
void gravarDadosArquivo(const char *nomeArquivo, struct TGrafoND *grafo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    
    fprintf(arquivo, "%d\n", grafo->n);

    
    for (int i = 0; i < grafo->n; i++) {
        fprintf(arquivo, "%d\n", i + 1); 
    }

    
    fprintf(arquivo, "%d\n", grafo->m);

    
    for (int i = 0; i < grafo->n; i++) {
        for (int j = i + 1; j < grafo->n; j++) {
            if (grafo->adj[i][j] != 0) {
                fprintf(arquivo, "%d %d %d\n", i + 1, j + 1, grafo->adj[i][j]); 
            }
        }
    }

    fclose(arquivo);
}
int verificaConexidade_TGrafoND(struct TGrafoND grafo) {
    
    int *visitado = (int *)malloc(grafo.n * sizeof(int));
    for (int i = 0; i < grafo.n; i++)
        visitado[i] = 0;

    int fila[grafo.n];
    int frente = 0, tras = 0;

    
    fila[tras++] = 0;
    visitado[0] = 1;

    while (frente != tras) {
        int atual = fila[frente++];
        for (int i = 0; i < grafo.n; i++) {
            if (grafo.adj[atual][i] == 1 && !visitado[i]) {
                fila[tras++] = i;
                visitado[i] = 1;
            }
        }
    }

    
    for (int i = 0; i < grafo.n; i++) {
        if (!visitado[i]) {
            free(visitado);
            return 1; 
        }
    }

    free(visitado);
    return 0; 
}
void apresentarConexidadeEGrafoReduzido(struct TGrafoND *grafo) {
    
    int conectividade = verificaConexidade_TGrafoND(*grafo);

    if (conectividade) {
        printf("O grafo não é conexo.\n");
        return;
    } else {
        printf("O grafo é conexo.\n");
    }

    
    struct TGrafoND grafoReduzido;
    int numVerticesReduzidos = 0;

    
    for (int i = 0; i < grafo->n; i++) {
        if (!grafoReduzido.adj) {
            inicializa_TGrafoND(&grafoReduzido, grafo->n);
        }

        if (grafoReduzido.adj) {
            for (int j = 0; j < grafo->n; j++) {
                if (grafo->adj[i][j] != 0) {
                    insereA_TGrafoND(&grafoReduzido, i, j, grafo->adj[i][j]);
                }
            }
            numVerticesReduzidos++;
        }
    }

    printf("Número de vértices do grafo reduzido: %d\n", numVerticesReduzidos);

    
    show_TGrafoND(grafoReduzido);

    
    libera_TGrafoND(&grafoReduzido);
}
int podeColorir(struct TGrafoND grafo, int v, int cores[], int cor, int num_cores) {
    for (int i = 0; i < grafo.n; i++) {
        if (grafo.adj[v][i] && cores[i] == cor)
            return 0;
    }
    return 1;
}

// Função para colorir o grafo
void colorirGrafo(struct TGrafoND grafo) {
    int num_cores = 0;
    int cores[grafo.n];
    for (int i = 0; i < grafo.n; i++)
        cores[i] = -1;
    for (int v = 0; v < grafo.n; v++) {
        int cor_disponivel = 0;
        while (1) {
            int cor_usada = 0;
            for (int i = 0; i < grafo.n; i++) {
                if (grafo.adj[v][i] && cores[i] == cor_disponivel) {
                    cor_usada = 1;
                    break;
                }
            }
            if (!cor_usada) {
                cores[v] = cor_disponivel;
                break;
            }
            cor_disponivel++;
        }
        if (cor_disponivel > num_cores)
            num_cores = cor_disponivel;
    }
    printf("Quantidade de partições: %d\n", num_cores + 1);
    printf("Cores atribuídas aos vértices:\n");
    for (int i = 0; i < grafo.n; i++)
        printf("Vértice %d: Cor %d\n", i + 1, cores[i]);
}
int verificarGrafoEuleriano(struct TGrafoND grafo) {
    for (int v = 0; v < grafo.n; v++) {
        int grau = 0;
        for (int i = 0; i < grafo.n; i++) {
            if (grafo.adj[v][i] != 0) {
                grau++;
            }
        }
        if (grau % 2 != 0) {
            return 0; 
        }
    }
    return 1; 
}
int verificarPercursoEuleriano(struct TGrafoND grafo) {
    int componente_conectado = verificaConexidade_TGrafoND(grafo);
    if (!componente_conectado) {
        printf("O grafo não é conectado, portanto não possui um percurso euleriano.\n");
        return 0;
    }
    int num_vertices_impares = 0;
    for (int v = 0; v < grafo.n; v++) {
        int grau = 0;
        for (int i = 0; i < grafo.n; i++) {
            if (grafo.adj[v][i] != 0) {
                grau++;
            }
        }
        if (grau % 2 != 0) {
            num_vertices_impares++;
        }
    }
    if (num_vertices_impares == 0 || num_vertices_impares == 2) {
        printf("O grafo possui um percurso euleriano.\n");
        return 1;
    } else {
        printf("O grafo não possui um percurso euleriano.\n");
        return 0;
    }
}
int proximo_vertice(int ciclo[], int n, struct TGrafoND grafo) {
    for (int i = 0; i < grafo.n; i++) {
        if (!ciclo[i])
            return i;
    }
    return -1;
}

int verifica_ciclo_hamiltoniano(int ciclo[], int n, struct TGrafoND grafo) {
    if (n == grafo.n) {
        if (grafo.adj[ciclo[n - 1]][ciclo[0]] != 0) {
            return 1; 
        } else {
            return 0; 
        }
    }

    int ultimo_vertice = ciclo[n - 1];
    for (int i = 0; i < grafo.n; i++) {
        if (!ciclo[i] && grafo.adj[ultimo_vertice][i] != 0) {
            ciclo[n] = i;
            if (verifica_ciclo_hamiltoniano(ciclo, n + 1, grafo))
                return 1;
            ciclo[n] = -1;
        }
    }
    return 0; 
}

int verificarGrafoHamiltoniano(struct TGrafoND grafo) {
    if (grafo.n <= 2) {
        return 0;
    }

    int ciclo[grafo.n];
    for (int i = 0; i < grafo.n; i++) {
        ciclo[i] = -1;
    }

    ciclo[0] = 0;
    if (verifica_ciclo_hamiltoniano(ciclo, 1, grafo)) {
        return 1; 
    }

    return 0;
}