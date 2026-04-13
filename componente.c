/* ============================================================================
 * ARQUIVO: componente.c
 * DESCRICAO: Implementacao do modulo de componentes. Gerencia o inventario
 *            (mochila) com operacoes de cadastro, remocao e listagem.
 *            Contem a definicao das variaveis globais do sistema.
 * DEPENDENCIAS: componente.h, utils.h
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include "componente.h"
#include "utils.h"

/* --- Definicao das variaveis globais declaradas em componente.h ---
 * mochila:         vetor estatico que armazena os componentes coletados.
 * total:           contador de componentes atualmente na mochila (inicia em 0).
 * ordenadoPorNome: flag de controle — 1 se esta ordenado por nome, 0 caso contrario.
 */
Componente mochila[MAX_COMPONENTES];
int total = 0;
int ordenadoPorNome = 0;

/* ============================================================================
 * FUNCAO: mostrarComponentes
 * DESCRICAO: Exibe todos os componentes cadastrados em formato de tabela
 *            formatada com colunas alinhadas. Mostra o status atual do
 *            inventario (quantidade atual / capacidade maxima).
 * PARAMETROS:
 *   - componentes[]: vetor de componentes a ser exibido
 *   - total:         quantidade de elementos validos no vetor
 * COMPLEXIDADE: O(n)
 * ============================================================================
 */
void mostrarComponentes(Componente componentes[], int total) {
    /* Cabecalho com contagem atual */
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", total, MAX_COMPONENTES);
    printf("--------------------------------------------------------------------------\n");

    if (total == 0) {
        /* Caso especial: mochila vazia */
        printf("Nenhum componente cadastrado ainda.\n");
    } else {
        /* Cabecalho das colunas com formatacao alinhada */
        printf("%-3s | %-28s | %-12s | %-10s | %s\n",
               "N",
               "NOME",
               "TIPO",
               "QUANTIDADE",
               "PRIORIDADE");
        printf("--------------------------------------------------------------------------\n");

        /* Percorre e exibe cada componente */
        for (int i = 0; i < total; i++) {
            printf("%-3d | %-28s | %-12s | %-10d | %d\n",
                   i + 1,                      /* Numero sequencial (1-based) */
                   componentes[i].nome,         /* Nome do componente */
                   componentes[i].tipo,         /* Tipo (controle/suporte/propulsao) */
                   componentes[i].quantidade,   /* Unidades disponiveis */
                   componentes[i].prioridade);  /* Nivel de prioridade (1-10) */
        }
    }
    printf("--------------------------------------------------------------------------\n");
}

/* ============================================================================
 * FUNCAO: cadastrarComponente
 * DESCRICAO: Permite ao usuario cadastrar um novo componente na mochila.
 *            Realiza as seguintes validacoes antes de inserir:
 *              1. Verifica se a mochila ainda tem espaco (MAX_COMPONENTES)
 *              2. Nome nao pode ser vazio
 *              3. Nome deve ser unico (busca linear O(n))
 *              4. Tipo deve ser um dos validos (controle, suporte, propulsao)
 *              5. Quantidade deve ser >= 1
 *              6. Prioridade deve estar entre 1 e 10
 *            Ao inserir com sucesso, invalida o flag de ordenacao por nome.
 * COMPLEXIDADE: O(n) para verificacao de duplicidade
 * ============================================================================
 */
void cadastrarComponente(void) {
    /* Verifica se ha espaco na mochila */
    if (total >= MAX_COMPONENTES) {
        printf("\nLimite de %d componentes atingido!\n", MAX_COMPONENTES);
        return;
    }

    printf("\n--- COLETANDO NOVO COMPONENTE ---\n");

    /* === Leitura e validacao do NOME === */
    printf("Nome: ");
    fgets(mochila[total].nome, MAX_NOME, stdin);
    removerNovaLinha(mochila[total].nome);  /* Remove '\n' residual do fgets */

    /* Validacao: nome nao pode ser vazio */
    if (mochila[total].nome[0] == '\0') {
        printf("Nome nao pode ser vazio.\n");
        return;
    }

    /* Validacao: verifica se ja existe componente com mesmo nome (busca linear) */
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, mochila[total].nome) == 0) {
            printf("Ja existe um componente com esse nome!\n");
            return;
        }
    }

    /* === Leitura e validacao do TIPO === */
    printf("Tipo (controle, suporte, propulsao): ");
    fgets(mochila[total].tipo, MAX_TIPO, stdin);
    removerNovaLinha(mochila[total].tipo);

    /* Validacao: tipo deve ser um dos tres validos */
    if (!tipoValido(mochila[total].tipo)) {
        printf("Tipo invalido! Use: controle, suporte ou propulsao.\n");
        return;
    }

    /* === Leitura e validacao da QUANTIDADE === */
    printf("Quantidade: ");
    if (scanf("%d", &mochila[total].quantidade) != 1) {
        printf("Quantidade invalida.\n");
        limparBufferEntrada();  /* Descarta caracteres invalidos do buffer */
        return;
    }
    limparBufferEntrada();  /* Consome o '\n' residual do scanf */

    /* Validacao: quantidade minima de 1 unidade */
    if (mochila[total].quantidade < 1) {
        printf("Quantidade deve ser maior que zero.\n");
        return;
    }

    /* === Leitura e validacao da PRIORIDADE === */
    printf("Prioridade de Montagem (1-10): ");
    if (scanf("%d", &mochila[total].prioridade) != 1) {
        printf("Prioridade invalida.\n");
        limparBufferEntrada();
        return;
    }
    limparBufferEntrada();

    /* Validacao: prioridade deve estar no intervalo [1, 10] */
    if (mochila[total].prioridade < 1 || mochila[total].prioridade > 10) {
        printf("Prioridade deve estar entre 1 e 10.\n");
        return;
    }

    /* === Insercao concluida com sucesso === */
    total++;                  /* Incrementa o contador de componentes */
    ordenadoPorNome = 0;      /* Invalida a ordenacao (novo elemento nao ordenado) */
    printf("\nComponente '%s' adicionado!\n", mochila[total - 1].nome);
    mostrarComponentes(mochila, total);  /* Exibe inventario atualizado */
    pausarTela();
}

/* ============================================================================
 * FUNCAO: removerComponente
 * DESCRICAO: Remove um componente da mochila pelo nome informado pelo usuario.
 *            Realiza busca linear pelo nome e, ao encontrar, desloca todos os
 *            elementos seguintes uma posicao para a esquerda para preencher
 *            o espaco vazio (mantendo contiguidade do vetor).
 *            Invalida o flag de ordenacao apos a remocao.
 * COMPLEXIDADE: O(n) para busca + O(n) para deslocamento = O(n)
 * ============================================================================
 */
void removerComponente(void) {
    /* Verifica se ha componentes para remover */
    if (total == 0) {
        printf("Nenhum componente para remover.\n");
        return;
    }

    char nome[MAX_NOME];
    printf("\n--- DESCARTAR COMPONENTE ---\n");
    printf("Nome do componente a remover: ");
    fgets(nome, MAX_NOME, stdin);
    removerNovaLinha(nome);

    /* Busca linear pelo nome do componente */
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            /* Componente encontrado: desloca elementos para preencher o gap */
            for (int j = i; j < total - 1; j++) {
                mochila[j] = mochila[j + 1];  /* Copia elemento seguinte */
            }
            total--;              /* Decrementa o contador */
            ordenadoPorNome = 0;  /* Invalida ordenacao (posicoes mudaram) */
            printf("\nComponente '%s' descartado!\n", nome);
            mostrarComponentes(mochila, total);
            pausarTela();
            return;  /* Encerra apos remocao (nomes sao unicos) */
        }
    }

    /* Nome nao encontrado no inventario */
    printf("Componente nao encontrado.\n");
    pausarTela();
}
