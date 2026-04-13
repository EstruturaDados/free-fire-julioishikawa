/* ============================================================================
 * ARQUIVO: componente.h
 * DESCRICAO: Header do modulo de componentes. Define a estrutura de dados
 *            principal (Componente), as constantes globais do sistema e
 *            declara as funcoes de CRUD (criar, listar, remover) do inventario.
 * DEPENDENCIAS: Nenhuma (modulo raiz do projeto).
 * ============================================================================
 */

#ifndef COMPONENTE_H
#define COMPONENTE_H

/* --- Constantes do sistema ---
 * MAX_COMPONENTES: capacidade maxima da mochila (vetor estatico).
 * MAX_NOME:        tamanho maximo do nome de um componente (incluindo '\0').
 * MAX_TIPO:        tamanho maximo do tipo de um componente (incluindo '\0').
 */
#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

/* ============================================================================
 * ESTRUTURA: Componente
 * DESCRICAO: Representa um componente necessario para montar a torre de resgate.
 * CAMPOS:
 *   - nome:       identificador unico do componente (ex: "chip central")
 *   - tipo:       categoria do componente ("controle", "suporte" ou "propulsao")
 *   - quantidade: numero de unidades disponiveis na mochila (minimo 1)
 *   - prioridade: nivel de importancia para montagem (1 = baixa, 10 = critica)
 * ============================================================================
 */
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade;
} Componente;

/* --- Variaveis globais (definidas em componente.c) ---
 * mochila:         vetor que armazena todos os componentes coletados.
 * total:           quantidade atual de componentes cadastrados na mochila.
 * ordenadoPorNome: flag que indica se o vetor esta ordenado por nome (1) ou nao (0).
 *                  Necessario para habilitar a busca binaria.
 */
extern Componente mochila[MAX_COMPONENTES];
extern int total;
extern int ordenadoPorNome;

/* ============================================================================
 * FUNCAO: mostrarComponentes
 * DESCRICAO: Exibe todos os componentes cadastrados em formato de tabela.
 * PARAMETROS:
 *   - componentes: vetor de componentes a exibir
 *   - total:       numero de componentes no vetor
 * RETORNO: void
 * COMPLEXIDADE: O(n), onde n = total de componentes
 * ============================================================================
 */
void mostrarComponentes(Componente componentes[], int total);

/* ============================================================================
 * FUNCAO: cadastrarComponente
 * DESCRICAO: Coleta dados do usuario e adiciona um novo componente na mochila.
 *            Realiza validacoes: nome unico, tipo valido, quantidade > 0,
 *            prioridade entre 1 e 10. Invalida o flag de ordenacao.
 * PARAMETROS: nenhum (opera sobre as variaveis globais mochila/total)
 * RETORNO: void
 * COMPLEXIDADE: O(n) para verificacao de nome duplicado
 * ============================================================================
 */
void cadastrarComponente(void);

/* ============================================================================
 * FUNCAO: removerComponente
 * DESCRICAO: Remove um componente da mochila pelo nome. Desloca os elementos
 *            subsequentes para preencher a lacuna. Invalida o flag de ordenacao.
 * PARAMETROS: nenhum (opera sobre as variaveis globais mochila/total)
 * RETORNO: void
 * COMPLEXIDADE: O(n) para busca + O(n) para deslocamento = O(n)
 * ============================================================================
 */
void removerComponente(void);

#endif
