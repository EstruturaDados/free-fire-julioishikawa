/* ============================================================================
 * ARQUIVO: utils.c
 * DESCRICAO: Implementacao do modulo de utilidades. Contem funcoes auxiliares
 *            genericas que nao possuem logica de negocio, apenas suporte
 *            tecnico para operacoes de I/O e validacao.
 * DEPENDENCIAS: utils.h
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

/* ============================================================================
 * FUNCAO: removerNovaLinha
 * DESCRICAO: Verifica se o ultimo caractere da string eh '\n' e, se for,
 *            substitui por '\0'. Isso corrige o comportamento do fgets(),
 *            que inclui o newline na string lida.
 * EXEMPLO:
 *   Entrada: "chip central\n" -> Saida: "chip central"
 * COMPLEXIDADE: O(n) para o strlen + O(1) para a substituicao
 * ============================================================================
 */
void removerNovaLinha(char *texto) {
    size_t tamanho = strlen(texto);  /* Calcula o comprimento da string */
    if (tamanho > 0 && texto[tamanho - 1] == '\n') {
        texto[tamanho - 1] = '\0';   /* Substitui '\n' por terminador nulo */
    }
}

/* ============================================================================
 * FUNCAO: limparBufferEntrada
 * DESCRICAO: Le e descarta todos os caracteres pendentes no buffer de entrada
 *            (stdin) ate encontrar '\n' ou EOF. Importante usar apos scanf()
 *            para evitar que o '\n' residual seja lido por fgets() na sequencia.
 * NOTA: O loop vazio (corpo com ";") eh intencional — apenas consome caracteres.
 * COMPLEXIDADE: O(k), onde k = numero de caracteres residuais no buffer
 * ============================================================================
 */
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        ;  /* Descarta cada caractere lido ate encontrar fim de linha ou fim de arquivo */
    }
}

/* ============================================================================
 * FUNCAO: pausarTela
 * DESCRICAO: Exibe uma mensagem solicitando que o usuario pressione Enter
 *            e aguarda a tecla. Utilizada entre telas do menu para que
 *            o usuario tenha tempo de ler as informacoes exibidas.
 * COMPLEXIDADE: O(1)
 * ============================================================================
 */
void pausarTela(void) {
    printf("\nPressione Enter para continuar...");
    getchar();  /* Aguarda o usuario pressionar Enter */
}

/* ============================================================================
 * FUNCAO: tipoValido
 * DESCRICAO: Valida se a string informada corresponde a um dos tres tipos
 *            aceitos de componente. A comparacao eh case-sensitive.
 *            Tipos validos: "controle", "suporte", "propulsao".
 * PARAMETROS:
 *   - tipo: string a ser validada
 * RETORNO: 1 (verdadeiro) se o tipo esta na lista, 0 (falso) caso contrario
 * COMPLEXIDADE: O(1) — compara contra lista fixa de 3 elementos
 * ============================================================================
 */
int tipoValido(const char *tipo) {
    /* Vetor com os tipos aceitos pelo sistema */
    const char *tiposValidos[] = {"controle", "suporte", "propulsao"};

    /* Percorre os 3 tipos validos e compara com o tipo informado */
    for (int i = 0; i < 3; i++) {
        if (strcmp(tipo, tiposValidos[i]) == 0) {
            return 1;  /* Tipo encontrado — valido */
        }
    }
    return 0;  /* Tipo nao encontrado — invalido */
}
