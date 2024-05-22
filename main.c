/*
Alix D'Avelar Pretto Sanches     » 10395951
Amanda Gois Smanioto             » 10395773
Luigi Uematsu                    » 10396148 
*/

#include <stdio.h>
#include <stdlib.h>
#include "TGrafoND.h"

int main() {
    struct TGrafoND grafo;
    inicializa_TGrafoND(&grafo, 0); 
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Ler dados do arquivo grafo.txt\n");
        printf("2. Gravar dados no arquivo grafo.txt\n");
        printf("3. Inserir vértice\n");
        printf("4. Inserir aresta\n");
        printf("5. Remove vértice\n");
        printf("6. Remove aresta\n");
        printf("7. Mostrar conteúdo do arquivo\n");
        printf("8. Mostrar grafo\n");
        printf("9. Apresentar a conexidade do grafo e o reduzido;\n");
        printf("10. Colorir o grafo\n"); 
        printf("11. Verificar se o grafo é euleriano\n");
        printf("12. Verificar percurso euleriano\n");
        printf("13. Verificar se o grafo é Hamiltoniano\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                lerGrafoArquivo("grafo.txt", &grafo);
                break;
            }
            case 2: {
                gravarDadosArquivo("grafo.txt", &grafo);
                break;
            }
            case 3: {
                insereVertice_TGrafoND(&grafo);
                printf("Vértice inserido com sucesso.\n");
                break;
            }
            case 4: {
                int v, w, peso;
                printf("Digite os números dos vértices (v w) e o peso da aresta: ");
                scanf("%d %d %d", &v, &w, &peso);
                insereA_TGrafoND(&grafo, v - 1, w - 1, peso); 
                printf("Aresta inserida com sucesso.\n");
                break;
            }
            case 5: {
                int vertice;
                printf("Digite o número do vértice a ser removido: ");
                scanf("%d", &vertice);
                removeVertice_TGrafoND(&grafo, vertice - 1); 
                printf("Vértice removido com sucesso.\n");
                break;
            }
            case 6: {
                int v, w;
                printf("Digite os números dos vértices (v w) da aresta a ser removida: ");
                scanf("%d %d", &v, &w);
                removeAresta_TGrafoND(&grafo, v - 1, w - 1);
                printf("Aresta removida com sucesso.\n");
                break;
            }
            case 7: {
                printf("Conteúdo do arquivo grafo.txt: \n");
                mostrarConteudoArquivo("grafo.txt");
                break;
            }
            case 8: {
                printf("Grafo: \n");
                show_TGrafoND(grafo);
                break;
            }
            case 9: {
                apresentarConexidadeEGrafoReduzido(&grafo);
                break;
            }
            case 10: { 
                colorirGrafo(grafo);
                break;
            }
            case 11: {
                if (verificarGrafoEuleriano(grafo))
                  printf("O grafo é euleriano.\n");
                else
                  printf("O grafo não é euleriano.\n");
                break;
            }
            case 12: {
                verificarPercursoEuleriano(grafo);
                break;
            }
            case 13: {
                if (verificarGrafoHamiltoniano(grafo))
                    printf("O grafo é hamiltoniano.\n");
                else
                    printf("O grafo não é hamiltoniano.\n");
            }
            case 0: {
                printf("FIM\n");
                break;
            }
            default: {
                printf("Opção inválida. Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 0);

    libera_TGrafoND(&grafo);

    return 0;
}