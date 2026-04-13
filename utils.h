/* ============================================================================
 * ARQUIVO: utils.h
 * DESCRICAO: Header do modulo de utilidades. Declara funcoes auxiliares
 *            genericas usadas por diversos modulos do projeto, como
 *            manipulacao de strings, controle de buffer de entrada e
 *            validacao de tipos de componente.
 * DEPENDENCIAS: Nenhuma.
 * ============================================================================
 */

#ifndef UTILS_H
#define UTILS_H

/* ============================================================================
 * FUNCAO: removerNovaLinha
 * DESCRICAO: Remove o caractere '\n' do final de uma string, caso exista.
 *            Essencial apos uso de fgets(), que inclui o '\n' na leitura.
 * PARAMETROS:
 *   - texto: ponteiro para a string a ser tratada
 * RETORNO: void (modifica a string in-place)
 * ============================================================================
 */
void removerNovaLinha(char *texto);

/* ============================================================================
 * FUNCAO: limparBufferEntrada
 * DESCRICAO: Consome todos os caracteres restantes no buffer de entrada (stdin)
 *            ate encontrar '\n' ou EOF. Necessario apos uso de scanf() para
 *            evitar que caracteres residuais afetem leituras subsequentes.
 * PARAMETROS: nenhum
 * RETORNO: void
 * ============================================================================
 */
void limparBufferEntrada(void);

/* ============================================================================
 * FUNCAO: pausarTela
 * DESCRICAO: Pausa a execucao do programa ate o usuario pressionar Enter.
 *            Utilizada para dar tempo de leitura das mensagens no terminal.
 * PARAMETROS: nenhum
 * RETORNO: void
 * ============================================================================
 */
void pausarTela(void);

/* ============================================================================
 * FUNCAO: tipoValido
 * DESCRICAO: Verifica se um tipo de componente eh valido, comparando com a
 *            lista de tipos aceitos: "controle", "suporte" e "propulsao".
 * PARAMETROS:
 *   - tipo: string com o tipo a ser validado
 * RETORNO: 1 se valido, 0 se invalido
 * ============================================================================
 */
int tipoValido(const char *tipo);

#endif
