/* ============================================================================
 * ARQUIVO: busca.c
 * DESCRICAO: Implementacao do modulo de busca. Contem o algoritmo de busca
 *            binaria por nome e a interface de usuario para executa-la.
 *            A busca binaria so funciona se o vetor estiver ordenado por nome
 *            (flag 'ordenadoPorNome' == 1).
 * DEPENDENCIAS: busca.h, componente.h, utils.h
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <time.h>    /* clock(), clock_t, CLOCKS_PER_SEC — para medir tempo */
#include "busca.h"
#include "componente.h"
#include "utils.h"

/* Contador de comparacoes da ultima busca (static = escopo de arquivo) */
static long comparacoesBusca = 0;

/* ============================================================================
 * FUNCAO: buscaBinariaPorNome
 * DESCRICAO: Implementacao da busca binaria classica. O algoritmo funciona
 *            mantendo dois ponteiros (esquerda e direita) que delimitam
 *            o intervalo de busca. A cada iteracao:
 *              1. Calcula o indice do meio: meio = (esquerda + direita) / 2
 *              2. Compara a chave com o nome no indice do meio
 *              3. Se igual: componente encontrado — retorna o indice
 *              4. Se chave < meio: descarta a metade direita (direita = meio - 1)
 *              5. Se chave > meio: descarta a metade esquerda (esquerda = meio + 1)
 *            Repete ate encontrar ou ate o intervalo ser invalido (esquerda > direita).
 * PRE-CONDICAO: O vetor DEVE estar ordenado por nome (ordem crescente).
 * PARAMETROS:
 *   - componentes[]: vetor ordenado por nome (const — somente leitura)
 *   - total:         numero de elementos no vetor
 *   - chave[]:       nome do componente a buscar
 * RETORNO: indice (0-based) se encontrado, -1 se nao encontrado
 * COMPLEXIDADE: O(log n) — divide o intervalo pela metade a cada passo
 * ============================================================================
 */
int buscaBinariaPorNome(const Componente componentes[], int total, const char chave[]) {
    comparacoesBusca = 0;       /* Reseta o contador para esta busca */
    int esquerda = 0;           /* Limite inferior do intervalo de busca */
    int direita = total - 1;    /* Limite superior do intervalo de busca */

    /* Loop principal: continua enquanto o intervalo for valido */
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;  /* Calcula o ponto medio */
        comparacoesBusca++;                    /* Contabiliza a comparacao */

        /* Compara a chave com o nome no ponto medio */
        int resultado = strcmp(chave, componentes[meio].nome);

        if (resultado == 0) {
            return meio;              /* ENCONTRADO: retorna o indice */
        } else if (resultado < 0) {
            direita = meio - 1;       /* Chave esta na metade ESQUERDA */
        } else {
            esquerda = meio + 1;      /* Chave esta na metade DIREITA */
        }
    }
    return -1;  /* NAO ENCONTRADO: chave nao existe no vetor */
}

/* ============================================================================
 * FUNCAO: obterComparacoesBusca
 * DESCRICAO: Retorna o numero de comparacoes realizadas na ultima execucao
 *            da busca binaria. Permite acesso externo ao contador static.
 * RETORNO: numero de comparacoes (long)
 * ============================================================================
 */
long obterComparacoesBusca(void) {
    return comparacoesBusca;
}

/* ============================================================================
 * FUNCAO: executarBuscaBinaria
 * DESCRICAO: Interface de usuario para a busca binaria por nome. Realiza
 *            as seguintes etapas:
 *              1. Verifica se o vetor esta ordenado por nome (pre-condicao)
 *              2. Verifica se ha componentes cadastrados
 *              3. Solicita o nome do componente-chave ao usuario
 *              4. Executa a busca binaria com medicao de tempo (clock)
 *              5. Exibe o resultado: dados do componente ou mensagem de nao encontrado
 *              6. Exibe metricas: comparacoes realizadas e tempo gasto
 * ============================================================================
 */
void executarBuscaBinaria(void) {
    /* Pre-condicao: vetor deve estar ordenado por nome */
    if (!ordenadoPorNome) {
        printf("\nVoce PRECISA ordenar por NOME primeiro (opcao 4)!\n");
        pausarTela();
        return;
    }

    /* Verifica se ha componentes cadastrados */
    if (total == 0) {
        printf("Nenhum componente cadastrado.\n");
        pausarTela();
        return;
    }

    /* Solicita a chave de busca ao usuario */
    char chave[MAX_NOME];
    printf("\n--- BUSCA BINARIA POR COMPONENTE-CHAVE ---\n");
    printf("Nome do componente-chave: ");
    fgets(chave, MAX_NOME, stdin);
    removerNovaLinha(chave);  /* Remove '\n' residual */

    /* Validacao: chave nao pode ser vazia */
    if (chave[0] == '\0') {
        printf("Nome nao pode ser vazio.\n");
        pausarTela();
        return;
    }

    /* Executa a busca binaria com medicao de tempo */
    clock_t inicio = clock();                                   /* Marca inicio */
    int indice = buscaBinariaPorNome(mochila, total, chave);    /* Busca */
    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC; /* Calcula tempo */

    /* Exibe os resultados da busca */
    printf("\n--- RESULTADO DA BUSCA BINARIA ---\n");
    if (indice != -1) {
        /* Componente encontrado: exibe todos os seus dados */
        printf("COMPONENTE-CHAVE ENCONTRADO!\n");
        printf("Posicao: %d\n", indice + 1);                /* Posicao 1-based */
        printf("Nome: %s\n", mochila[indice].nome);
        printf("Tipo: %s\n", mochila[indice].tipo);
        printf("Quantidade: %d\n", mochila[indice].quantidade);
        printf("Prioridade: %d\n", mochila[indice].prioridade);
    } else {
        /* Componente nao encontrado */
        printf("Componente-chave '%s' NAO ENCONTRADO!\n", chave);
    }

    /* Exibe metricas de desempenho da busca */
    printf("Comparacoes realizadas: %ld\n", obterComparacoesBusca());
    printf("Tempo: %.6f segundos\n", tempo);
    printf("----------------------------------------------\n");
    pausarTela();
}
