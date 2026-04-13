/* ============================================================================
 * ARQUIVO: busca.h
 * DESCRICAO: Header do modulo de busca. Declara o algoritmo de busca binaria
 *            por nome de componente e a interface de usuario para executar
 *            a busca com medicao de desempenho.
 * DEPENDENCIAS: componente.h (para o tipo Componente e constantes)
 * PRE-REQUISITO: O vetor deve estar ORDENADO POR NOME para busca binaria.
 * ============================================================================
 */

#ifndef BUSCA_H
#define BUSCA_H

#include "componente.h"

/* ============================================================================
 * FUNCAO: buscaBinariaPorNome
 * DESCRICAO: Realiza busca binaria em um vetor de componentes ordenado por nome.
 *            Divide o intervalo de busca pela metade a cada iteracao, comparando
 *            a chave com o elemento do meio.
 * PRE-CONDICAO: O vetor DEVE estar ordenado por nome em ordem crescente.
 * PARAMETROS:
 *   - componentes[]: vetor ORDENADO por nome (const — nao sera modificado)
 *   - total:         numero de elementos no vetor
 *   - chave[]:       nome do componente a ser buscado
 * RETORNO: indice do componente se encontrado, -1 caso contrario
 * COMPLEXIDADE: O(log n)
 * ============================================================================
 */
int buscaBinariaPorNome(const Componente componentes[], int total, const char chave[]);

/* ============================================================================
 * FUNCAO: obterComparacoesBusca
 * DESCRICAO: Retorna o numero de comparacoes realizadas na ultima busca binaria.
 * RETORNO: numero de comparacoes (long)
 * ============================================================================
 */
long obterComparacoesBusca(void);

/* ============================================================================
 * FUNCAO: executarBuscaBinaria
 * DESCRICAO: Interface de usuario para a busca binaria. Verifica se o vetor
 *            esta ordenado por nome, solicita a chave de busca ao usuario,
 *            executa a busca com medicao de tempo e exibe os resultados.
 * PARAMETROS: nenhum (opera sobre as variaveis globais mochila/total)
 * RETORNO: void
 * ============================================================================
 */
void executarBuscaBinaria(void);

#endif
