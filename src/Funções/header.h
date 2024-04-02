/**
 * @file header.h
 * @author Hugo Cruz a23010
 * @brief
 * @date 2023-03-16
 * @copyright Copyright (c) 2023
 *
 */

#pragma once
#include <stdbool.h>

/*
@struct Lista
* @brief Esta estrutura para criar uma lista
*/
typedef struct Lista
{
	int num; /**< Variavel que armazena os numeros */
	struct Lista* prox;	/**< Apontador para o proximo n�mero  */

}Lista;

/*
@struct Matriz
* @brief Esta estrutura para criar uma Matriz
*/
typedef struct Matriz
{
	Lista* linha; /**< Apontador para listas */
	struct Matriz* ProxLinha; /**< Apontador para a proxima lista  */

}Matriz;

/**
 * @brief Carrega dados de um ficheiro CSV
 *
 * @param tamanho Guarda quantos dados foram lidos
 * @return int* Apontador que retorna os dados lidos.
 */
int* CarregaDados(int* tamanho);
/**
 * @brief Cria mem�ria para alocar a estrutura lista.
 *
 * @param n numero que � colocado na lista
 * @return Lista* Ponteiro para o novo elemento da lista.
 */
Lista* CriarNumero(int n);
/**
 * @brief Insere um n�mero no final da lista.
 *
 * @param inicio Apontador para o primeiro elemento da lista.
 * @param n O n�mero a ser inserido na lista.
 */
Lista* ColocarNaLista(Lista* inicio, int n);
/**
 * @brief Cria uma Matriz.
 *
 * @param lista Apontador para a lista que � uma linha da matriz.
 */
Matriz* CriarMatriz(Lista* lista);
/**
 * @brief Insere uma nova linha na matriz.
 *
 * @param inicio Apontador para a primeira linha da matriz.
 * @param linha Apontador para a lista que ser� inserida como nova linha.
 */
Matriz* ColocarNaMatriz(Matriz* inicio, Lista* linha);
/**
 * @brief Distribui os dados lidos de um arquivo em uma matriz din�mica.
 *
 * @param linhas N�mero de linhas da matriz a ser criada.
 * @param colunas N�mero de colunas por linha na matriz.
 */
Matriz* DistribuirDados(int linhas, int colunas);
/**
 * @brief Mostra os elementos de uma matriz no console.
 *
 * @param m Apontador para a primeira linha da matriz.
 */
void MostrarMatriz(Matriz* m);
/**
 * @brief Modifica o valor de um elemento espec�fico na matriz.
 *
 * @param matriz Apontador para a matriz a ser modificada.
 * @param linha N�mero da linha do elemento a ser modificado.
 * @param coluna N�mero da coluna do elemento a ser modificado.
 * @param ValorMudar Novo valor para o elemento especificado.
 */
bool MudarValor(Matriz* matriz, int linha, int coluna, int ValorMudar);
/**
 * @brief Insere uma nova linha ap�s uma linha espec�fica na matriz.
 *
 * Esta fun��o insere uma nova linha preenchida com os valores fornecidos ap�s a
 * linha especificada. Se a linha especificada for a �ltima, a nova linha ser�
 * adicionada ao final da matriz.
 *
 * @param matriz Aponta para a matriz onde a linha ser� inserida.
 * @param linha Posi��o ap�s a qual a nova linha ser� inserida.
 * @param tamanhoC Numero de colunas na nova linha.
 * @param valores Apontador para um arrays que prenche a nova linha.
 */
Matriz* InserirLinha(Matriz* matriz, int linha, int tamanhoC, int* valores);
/**
 * @brief Insere uma nova coluna em uma posi��o espec�fica em todas as linhas da matriz.
 *
 * A fun��o percorre cada linha da matriz, inserindo um novo valor da matriz de
 * valores fornecida na posi��o especificada.
 *
 * @param matriz Apontador para a matriz onde a coluna ser� inserida.
 * @param posicao Posi��o  onde a nova coluna ser� inserida.
 * @param valores Apontador para um arrays que prenche a nova coluna.
 */
Matriz* InserirColuna(Matriz* matriz, int posicao, int* valores);
/**
 * @brief Remove uma linha espec�fica da matriz.
 *
 * Localiza a linha a ser removida. Se encontrada, a linha �
 * removida.
 *
 * @param matriz Apontador para a matriz da qual a linha ser� removida.
 * @param linha N�mero da linha a ser removida.
 */
Matriz* RemoverLinha(Matriz* matriz, int linha);
/**
 * @brief Remove uma coluna espec�fica de todas as linhas da matriz.
 *
 * Percorre todas as linhas da matriz, remove o elemento que corresponde �
 * coluna especificada em cada linha.
 *
 * @param matriz Apontador para a matriz da qual a coluna ser� removida.
 * @param coluna N�mero da coluna a ser removida
 */
Matriz* RemoverColuna(Matriz* matriz, int coluna);
/**
 * @brief Soma os valores maiores da linha
 *
 * Percorre todas as linhas da matriz, e identifica o maior de todas as linhas.
 *
 * @param matriz Apontador para a matriz de qual iremos somar as linhas.
 */
int somaMaiores(Matriz* m);

