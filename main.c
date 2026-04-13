/* ============================================================================
 * ARQUIVO: main.c
 * DESCRICAO: Modulo principal do sistema "Torre de Resgate". Responsavel pela
 *            orquestracao do programa: exibe o cabecalho com status do sistema,
 *            apresenta o menu interativo e despacha as acoes para os modulos
 *            especializados (componente, ordenacao, busca).
 * DEPENDENCIAS: componente.h, ordenacao.h, busca.h, utils.h
 *
 * CONTEXTO DO JOGO:
 *   O jogador esta preso em uma ilha e precisa montar uma torre de resgate
 *   coletando componentes na mochila. Cada componente tem nome, tipo,
 *   quantidade e prioridade de montagem. O jogador pode organizar a mochila
 *   usando diferentes algoritmos de ordenacao e buscar componentes-chave
 *   usando busca binaria.
 *
 * COMPILACAO:
 *   gcc -g main.c componente.c ordenacao.c busca.c utils.c -o torre_resgate.exe
 * ============================================================================
 */

#include <stdio.h>
#include "componente.h"  /* Estrutura Componente, CRUD, variaveis globais */
#include "ordenacao.h"   /* Algoritmos de ordenacao e medicao de desempenho */
#include "busca.h"       /* Busca binaria por nome */
#include "utils.h"       /* Funcoes utilitarias (I/O, validacao) */

/* ============================================================================
 * FUNCAO: exibirCabecalho
 * DESCRICAO: Exibe o cabecalho do sistema com informacoes de status:
 *            - Titulo do jogo
 *            - Quantidade de itens na mochila vs. capacidade maxima
 *            - Status da ordenacao por nome (necessario para busca binaria)
 * PARAMETROS: nenhum (le as variaveis globais total e ordenadoPorNome)
 * RETORNO: void
 * ============================================================================
 */
void exibirCabecalho(void) {
    printf("\n==============================================================\n");
    printf("   PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("==============================================================\n");
    printf("Itens na Mochila: %d/%d\n", total, MAX_COMPONENTES);
    printf("Status da Ordenacao por Nome: %s\n",
           ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
}

/* ============================================================================
 * FUNCAO: main
 * DESCRICAO: Ponto de entrada do programa. Implementa o loop principal do
 *            menu interativo usando do-while (executa pelo menos uma vez).
 *            O menu apresenta 6 opcoes:
 *              1 - Adicionar Componente  (cadastrarComponente)
 *              2 - Descartar Componente  (removerComponente)
 *              3 - Listar Componentes    (mostrarComponentes)
 *              4 - Ordenar Componentes   (executarOrdenacao)
 *              5 - Busca Binaria         (executarBuscaBinaria)
 *              0 - Sair do programa
 *            Trata entrada invalida (nao-numerica) limpando o buffer.
 * RETORNO: 0 (EXIT_SUCCESS)
 * ============================================================================
 */
int main(void) {
    int opcao;  /* Armazena a opcao escolhida pelo usuario */

    printf("PREPARANDO PLANO DE FUGA...\n\n");

    do {
        /* Exibe cabecalho com status atualizado a cada iteracao */
        exibirCabecalho();

        /* Exibe as opcoes do menu principal */
        printf("\n1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("--------------------------------------------------------------\n");
        printf("Escolha uma opcao: ");

        /* Leitura da opcao com tratamento de entrada invalida */
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            limparBufferEntrada();  /* Descarta entrada nao-numerica */
            continue;               /* Volta ao inicio do loop */
        }
        limparBufferEntrada();  /* Consome o '\n' residual do scanf */

        /* Despacha a acao para o modulo correspondente */
        switch (opcao) {
            case 1:
                cadastrarComponente();        /* Modulo: componente */
                break;
            case 2:
                removerComponente();          /* Modulo: componente */
                break;
            case 3:
                mostrarComponentes(mochila, total);  /* Modulo: componente */
                pausarTela();
                break;
            case 4:
                executarOrdenacao();           /* Modulo: ordenacao */
                break;
            case 5:
                executarBuscaBinaria();        /* Modulo: busca */
                break;
            case 0:
                printf("\nTorre ativada. Boa fuga!\n");  /* Mensagem de saida */
                break;
            default:
                printf("Opcao invalida.\n");  /* Opcao fora do intervalo [0-5] */
        }
    } while (opcao != 0);  /* Repete ate o usuario escolher sair (opcao 0) */

    return 0;  /* Encerra o programa com sucesso */
}
