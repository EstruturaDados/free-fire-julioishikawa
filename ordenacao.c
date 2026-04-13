/* ============================================================================
 * ARQUIVO: ordenacao.c
 * DESCRICAO: Implementacao do modulo de ordenacao. Contem tres algoritmos
 *            classicos de ordenacao (Bubble, Insertion, Selection), cada um
 *            aplicado a um campo diferente da struct Componente, alem de
 *            funcoes de medicao de desempenho e interface de menu.
 * DEPENDENCIAS: ordenacao.h, componente.h, utils.h
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <time.h>    /* clock(), clock_t, CLOCKS_PER_SEC — para medir tempo */
#include <stdarg.h>  /* va_list, va_start, va_arg, va_end — para args variadicos */
#include "ordenacao.h"
#include "componente.h"
#include "utils.h"

/* --- Contadores de comparacoes (variaveis static = escopo restrito ao arquivo) ---
 * Cada algoritmo registra o numero de comparacoes realizadas durante a
 * ultima execucao. Sao resetados no inicio de cada chamada ao algoritmo.
 */
static long comparacoesBubble = 0;
static long comparacoesInsertion = 0;
static long comparacoesSelection = 0;

/* ============================================================================
 * FUNCAO: bubbleSortNome
 * DESCRICAO: Implementacao do Bubble Sort para ordenar componentes por nome
 *            em ordem CRESCENTE (alfabetica). O algoritmo percorre o vetor
 *            repetidamente, comparando pares adjacentes e trocando-os se
 *            estiverem fora de ordem. A cada passagem, o maior elemento
 *            "borbulha" para o final do trecho nao ordenado.
 * CRITERIO DE ORDENACAO: campo 'nome' (string), usando strcmp()
 * COMPLEXIDADE:
 *   - Pior caso:  O(n^2) comparacoes e O(n^2) trocas
 *   - Melhor caso: O(n^2) comparacoes (sem flag de otimizacao)
 * ============================================================================
 */
void bubbleSortNome(Componente componentes[], int total) {
    comparacoesBubble = 0;  /* Reseta o contador de comparacoes */

    /* Loop externo: controla o numero de passagens pelo vetor */
    for (int i = 0; i < total - 1; i++) {
        /* Loop interno: compara pares adjacentes no trecho nao ordenado
         * (total - i - 1) porque os ultimos 'i' elementos ja estao em ordem */
        for (int j = 0; j < total - i - 1; j++) {
            comparacoesBubble++;  /* Contabiliza a comparacao */

            /* Se o nome atual eh maior que o proximo (ordem lexicografica), troca */
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                Componente temp = componentes[j];      /* Salva o atual */
                componentes[j] = componentes[j + 1];    /* Move o proximo para ca */
                componentes[j + 1] = temp;              /* Coloca o salvo no proximo */
            }
        }
    }
}

/* ============================================================================
 * FUNCAO: insertionSortTipo
 * DESCRICAO: Implementacao do Insertion Sort para ordenar componentes por tipo
 *            em ordem CRESCENTE (alfabetica). O algoritmo constroi o vetor
 *            ordenado progressivamente: para cada elemento, encontra a posicao
 *            correta no trecho ja ordenado e desloca os maiores para a direita.
 * CRITERIO DE ORDENACAO: campo 'tipo' (string), usando strcmp()
 * COMPLEXIDADE:
 *   - Pior caso:  O(n^2) — vetor em ordem inversa
 *   - Melhor caso: O(n) — vetor ja ordenado (while nao executa)
 * ============================================================================
 */
void insertionSortTipo(Componente componentes[], int total) {
    comparacoesInsertion = 0;  /* Reseta o contador de comparacoes */

    /* Começa do segundo elemento (i=1); o primeiro ja esta "ordenado" */
    for (int i = 1; i < total; i++) {
        Componente chave = componentes[i];  /* Salva o elemento a ser inserido */
        int j = i - 1;  /* Indice do ultimo elemento do trecho ja ordenado */

        /* Desloca elementos maiores que a chave para a direita */
        while (j >= 0) {
            comparacoesInsertion++;  /* Contabiliza a comparacao */

            /* Se o tipo da chave eh menor, desloca o elemento atual para a direita */
            if (strcmp(chave.tipo, componentes[j].tipo) < 0) {
                componentes[j + 1] = componentes[j];  /* Desloca para a direita */
                j--;  /* Continua verificando o anterior */
            } else {
                break;  /* Posicao correta encontrada — para o deslocamento */
            }
        }
        componentes[j + 1] = chave;  /* Insere a chave na posicao correta */
    }
}

/* ============================================================================
 * FUNCAO: selectionSortPrioridade
 * DESCRICAO: Implementacao do Selection Sort para ordenar componentes por
 *            prioridade em ordem DECRESCENTE (maior primeiro). O algoritmo
 *            encontra o maior elemento no trecho nao ordenado e o coloca
 *            no inicio do trecho, repetindo para cada posicao.
 * CRITERIO DE ORDENACAO: campo 'prioridade' (int), decrescente
 * COMPLEXIDADE:
 *   - Todos os casos: O(n^2) comparacoes, O(n) trocas
 * ============================================================================
 */
void selectionSortPrioridade(Componente componentes[], int total) {
    comparacoesSelection = 0;  /* Reseta o contador de comparacoes */

    /* Loop externo: para cada posicao 'i', encontra o maior no trecho restante */
    for (int i = 0; i < total - 1; i++) {
        int indiceMaior = i;  /* Assume que o maior esta na posicao atual */

        /* Loop interno: busca o maior elemento no trecho [i+1, total-1] */
        for (int j = i + 1; j < total; j++) {
            comparacoesSelection++;  /* Contabiliza a comparacao */

            /* Se encontrou prioridade maior, atualiza o indice do maior */
            if (componentes[j].prioridade > componentes[indiceMaior].prioridade) {
                indiceMaior = j;
            }
        }

        /* Troca apenas se o maior nao esta na posicao correta (evita troca desnecessaria) */
        if (indiceMaior != i) {
            Componente temp = componentes[i];
            componentes[i] = componentes[indiceMaior];
            componentes[indiceMaior] = temp;
        }
    }
}

/* ============================================================================
 * FUNCAO: medirTempo
 * DESCRICAO: Funcao generica que mede o tempo de execucao de um algoritmo
 *            de ordenacao. Usa argumentos variadicos (stdarg.h) para receber
 *            o ponteiro de funcao do algoritmo junto com seus parametros.
 *            Registra o clock antes e depois da execucao e calcula a diferenca.
 * PARAMETROS:
 *   - algoritmo: ponteiro para funcao void(Componente[], int)
 *   - ...:       Componente* (vetor) e int (total)
 * RETORNO: tempo em segundos (double) com precisao de microsegundos
 * NOTA: Usa cast para ponteiro de funcao com assinatura correta na chamada.
 * ============================================================================
 */
double medirTempo(void (*algoritmo)(), ...) {
    /* Extrai os argumentos variadicos */
    va_list args;
    va_start(args, algoritmo);
    Componente *componentes = va_arg(args, Componente *);  /* Primeiro arg: vetor */
    int total = va_arg(args, int);                          /* Segundo arg: total */
    va_end(args);

    /* Mede o tempo de execucao usando clock() */
    clock_t inicio = clock();                                       /* Marca inicio */
    ((void (*)(Componente[], int))algoritmo)(componentes, total);   /* Executa o algoritmo */
    clock_t fim = clock();                                          /* Marca fim */

    /* Retorna a diferenca convertida para segundos */
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

/* --- Funcoes de acesso aos contadores de comparacoes ---
 * Como os contadores sao 'static' (escopo de arquivo), estas funcoes
 * permitem que outros modulos consultem os valores apos a ordenacao.
 */

long obterComparacoesBubble(void) {
    return comparacoesBubble;
}

long obterComparacoesInsertion(void) {
    return comparacoesInsertion;
}

long obterComparacoesSelection(void) {
    return comparacoesSelection;
}

/* ============================================================================
 * FUNCAO: executarOrdenacao
 * DESCRICAO: Interface do submenu de ordenacao. Apresenta ao usuario as tres
 *            estrategias disponiveis, executa a escolhida com medicao de
 *            desempenho (tempo + comparacoes) e exibe o resultado.
 *            Gerencia o flag 'ordenadoPorNome' conforme o algoritmo usado:
 *              - Bubble Sort por Nome: ativa o flag (habilita busca binaria)
 *              - Demais: desativa o flag (busca binaria nao eh segura)
 * ============================================================================
 */
void executarOrdenacao(void) {
    /* Verifica quantidade minima para ordenar */
    if (total < 2) {
        printf("Precisa de pelo menos 2 componentes para ordenar.\n");
        pausarTela();
        return;
    }

    /* Exibe submenu de opcoes de ordenacao */
    printf("\n--- ORGANIZAR MOCHILA ---\n");
    printf("1. Bubble Sort (por Nome)\n");
    printf("2. Insertion Sort (por Tipo)\n");
    printf("3. Selection Sort (por Prioridade)\n");
    printf("Escolha uma estrategia: ");

    /* Leitura da opcao do usuario */
    int opcao;
    if (scanf("%d", &opcao) != 1) {
        printf("Opcao invalida.\n");
        limparBufferEntrada();
        return;
    }
    limparBufferEntrada();

    double tempo;  /* Variavel para armazenar o tempo de execucao */

    switch (opcao) {
        case 1:
            /* Bubble Sort por Nome — ordena alfabeticamente */
            tempo = medirTempo((void (*)())bubbleSortNome, mochila, total);
            printf("\nBubble Sort concluido!\n");
            printf("Comparacoes: %ld\n", obterComparacoesBubble());
            printf("Tempo: %.6f segundos\n", tempo);
            mostrarComponentes(mochila, total);
            ordenadoPorNome = 1;  /* Ativa flag: busca binaria agora eh possivel */
            pausarTela();
            break;

        case 2:
            /* Insertion Sort por Tipo — agrupa por categoria */
            tempo = medirTempo((void (*)())insertionSortTipo, mochila, total);
            printf("\nInsertion Sort concluido!\n");
            printf("Comparacoes: %ld\n", obterComparacoesInsertion());
            printf("Tempo: %.6f segundos\n", tempo);
            mostrarComponentes(mochila, total);
            ordenadoPorNome = 0;  /* Desativa flag: nao esta mais ordenado por nome */
            pausarTela();
            break;

        case 3:
            /* Selection Sort por Prioridade — maior prioridade primeiro */
            tempo = medirTempo((void (*)())selectionSortPrioridade, mochila, total);
            printf("\nSelection Sort concluido!\n");
            printf("Comparacoes: %ld\n", obterComparacoesSelection());
            printf("Tempo: %.6f segundos\n", tempo);
            mostrarComponentes(mochila, total);
            ordenadoPorNome = 0;  /* Desativa flag: nao esta mais ordenado por nome */
            pausarTela();
            break;

        default:
            printf("Opcao invalida.\n");
            pausarTela();
    }
}
