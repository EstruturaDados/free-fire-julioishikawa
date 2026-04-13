/* ============================================================================
 * ARQUIVO: ordenacao.h
 * DESCRICAO: Header do modulo de ordenacao. Declara tres algoritmos de
 *            ordenacao classicos (Bubble Sort, Insertion Sort, Selection Sort),
 *            funcoes para medicao de desempenho (tempo e contagem de comparacoes)
 *            e a interface do menu de ordenacao.
 * DEPENDENCIAS: componente.h (para o tipo Componente)
 * ============================================================================
 */

#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "componente.h"

/* ============================================================================
 * FUNCAO: bubbleSortNome
 * DESCRICAO: Ordena o vetor de componentes em ordem CRESCENTE pelo campo 'nome'
 *            usando o algoritmo Bubble Sort (comparacao e troca de adjacentes).
 * PARAMETROS:
 *   - componentes[]: vetor a ser ordenado
 *   - total:         numero de elementos no vetor
 * COMPLEXIDADE: O(n^2) no pior/medio caso, O(n) no melhor caso (ja ordenado, sem flag)
 * ============================================================================
 */
void bubbleSortNome(Componente componentes[], int total);

/* ============================================================================
 * FUNCAO: insertionSortTipo
 * DESCRICAO: Ordena o vetor de componentes em ordem CRESCENTE pelo campo 'tipo'
 *            usando o algoritmo Insertion Sort (insercao na posicao correta).
 * PARAMETROS:
 *   - componentes[]: vetor a ser ordenado
 *   - total:         numero de elementos no vetor
 * COMPLEXIDADE: O(n^2) no pior caso, O(n) no melhor caso (ja ordenado)
 * ============================================================================
 */
void insertionSortTipo(Componente componentes[], int total);

/* ============================================================================
 * FUNCAO: selectionSortPrioridade
 * DESCRICAO: Ordena o vetor de componentes em ordem DECRESCENTE pelo campo
 *            'prioridade' usando o algoritmo Selection Sort (selecao do maior).
 * PARAMETROS:
 *   - componentes[]: vetor a ser ordenado
 *   - total:         numero de elementos no vetor
 * COMPLEXIDADE: O(n^2) para todos os casos
 * ============================================================================
 */
void selectionSortPrioridade(Componente componentes[], int total);

/* ============================================================================
 * FUNCAO: medirTempo
 * DESCRICAO: Funcao generica que executa um algoritmo de ordenacao e mede
 *            o tempo de execucao em segundos. Usa argumentos variadicos (va_list)
 *            para receber o vetor e o total como parametros.
 * PARAMETROS:
 *   - algoritmo: ponteiro para funcao de ordenacao (Componente[], int)
 *   - ...:       argumentos variadicos (Componente*, int)
 * RETORNO: tempo de execucao em segundos (double)
 * ============================================================================
 */
double medirTempo(void (*algoritmo)(), ...);

/* --- Funcoes de acesso aos contadores de comparacoes ---
 * Cada algoritmo de ordenacao conta suas comparacoes em variaveis static.
 * Essas funcoes permitem acesso externo aos valores apos a ordenacao.
 */
long obterComparacoesBubble(void);
long obterComparacoesInsertion(void);
long obterComparacoesSelection(void);

/* ============================================================================
 * FUNCAO: executarOrdenacao
 * DESCRICAO: Interface do menu de ordenacao. Apresenta as opcoes ao usuario,
 *            executa o algoritmo escolhido com medicao de tempo e exibe
 *            os resultados (comparacoes, tempo, inventario ordenado).
 * PARAMETROS: nenhum (opera sobre as variaveis globais mochila/total)
 * RETORNO: void
 * ============================================================================
 */
void executarOrdenacao(void);

#endif
