/**
 * @file source.c
 * @author Hugo Cruz a23010
 * @brief
 * @date 2023-03-16
 * @copyright Copyright (c) 2023
 *
 */


#include "header.h"
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


 /**
  * @brief Carrega dados de um ficheiro CSV
  *
  * @param tamanho Guarda quantos dados foram lidos
  * @return int* Apontador que retorna os dados lidos.
  */
int* CarregaDados(int* tamanho) {
	int i = 0;
	int* aux = (int*)malloc(sizeof(int) * 50); // Aloca mem�ria para 50 inteiros.

	FILE* ficheiro = fopen("matriz.csv", "r"); // Abrir o arquivo.

	if (ficheiro == NULL) return NULL; // Retorna NULL caso o ficheiro n�o seja aberto.

	// L� os dados separados por ponto e virgula enquanto houver dados.
	while (fscanf_s(ficheiro, "%d;", &aux[i]) == 1)
	{
		i++;
	}

	*tamanho = i;     // Armazena a quantidade de numeros lidos.
	fclose(ficheiro); // Fecha o arquivo.

	return aux; // Retorna um apontador para os inteiros armazenados.
	free(aux);
}

/**
 * @brief Cria mem�ria para alocar a estrutura lista.
 *
 * @param n numero que � colocado na lista
 * @return Lista* Ponteiro para o novo elemento da lista.
 */
Lista* CriarNumero(int n) {

	Lista* aux = (Lista*)malloc(sizeof(Lista) * 1); // Aloca mem�ria para um novo elemento na lista.

	if (aux != NULL)
	{
		aux->num = n;     // Define o valor do n�mero.
		aux->prox = NULL; // Define o proximo elemento como NULL.
	}

	return aux; // Retorna uma apontador para o novo elemento da lista.
	free(aux);
}

/**
 * @brief Insere um n�mero no final da lista.
 *
 * @param inicio Apontador para o primeiro elemento da lista.
 * @param n O n�mero a ser inserido na lista.
 */
Lista* ColocarNaLista(Lista* inicio, int n) {
	Lista* nova = CriarNumero(n); // Cria um novo elemento.
	if (nova == NULL)
		return inicio; // Retorna o in�cio.

	if (inicio == NULL)
	{
		inicio = nova; // Se a lista est� vazia, o novo elemento � colocado no in�cio.
	}

	else
	{
		Lista* aux2 = inicio;
		// Percorre a lista at� o final.
		while (aux2->prox != NULL)
		{
			aux2 = aux2->prox;
		}
		aux2->prox = nova; // Insere o novo elemento no final da lista.
	}

	return inicio; // Retorna um apontador para o primeiro elemento da lista.
}

/**
 * @brief Cria uma Matriz.
 *
 * @param lista Apontador para a lista que � uma linha da matriz.
 */
Matriz* CriarMatriz(Lista* lista) {

	Matriz* aux = (Matriz*)malloc(sizeof(Matriz) * 1); // Aloca mem�ria para uma nova linha da matriz.

	if (aux != NULL)
	{
		aux->linha = lista;    // Define a lista como linha da matriz.
		aux->ProxLinha = NULL; // Define a pr�xima linha vazia
	}

	return aux; // Retorna um apontador para a nova linha da matriz.
	free(aux);
}

/**
 * @brief Insere uma nova linha na matriz.
 *
 * @param inicio Apontador para a primeira linha da matriz.
 * @param linha Apontador para a lista que ser� inserida como nova linha.
 */
Matriz* ColocarNaMatriz(Matriz* inicio, Lista* linha) {

	Matriz* nova = CriarMatriz(linha); // Cria uma nova linha com a lista fornecida.

	if (nova == NULL) return inicio; // Retorna o in�cio se falha ao criar a nova linha.

	if (inicio == NULL)
	{
		inicio = nova; // Se a matriz est� vazia, a nova linha � o in�cio.
	}
	else
	{
		Matriz* aux2 = inicio;

		// Percorre a matriz at� a �ltima linha.
		while (aux2->ProxLinha != NULL)
		{
			aux2 = aux2->ProxLinha;
		}
		aux2->ProxLinha = nova; // Insere a nova linha no final da matriz.
	}
	return inicio; // Retorna um apontador para a primeira linha da matriz.
}

/**
 * @brief Distribui os dados lidos de um arquivo em uma matriz din�mica.
 *
 * @param linhas N�mero de linhas da matriz a ser criada.
 * @param colunas N�mero de colunas por linha na matriz.
 */
Matriz* DistribuirDados(int linhas, int colunas) {
	int i = 0;
	int quantosNum = 0;
	int* valores = CarregaDados(&quantosNum); // Carrega os dados do arquivo.

	Matriz* matriz = NULL;

	// Cria a matriz linha por linha.
	for (int l = 0; l < linhas; l++) {
		Lista* linha = NULL;

		// Adiciona os valores � linha atual.
		for (int c = 0; c < colunas; c++) {
			linha = ColocarNaLista(linha, valores[i++]);
		}

		// Adiciona a linha � matriz.
		matriz = ColocarNaMatriz(matriz, linha);
	}

	return matriz; // Retorna a matriz criada.
}

/**
 * @brief Mostra os elementos de uma matriz no console.
 *
 * @param m Apontador para a primeira linha da matriz.
 */
void MostrarMatriz(Matriz* m) {
	Matriz* linhaAtual = m;

	// Corre cada linha da matriz.
	while (linhaAtual != NULL)
	{
		Lista* elementoAtual = linhaAtual->linha;

		// Corre cada coluna da linha atual.
		while (elementoAtual != NULL)
		{
			printf("%d ", elementoAtual->num); // Imprime o valor do elemento.
			elementoAtual = elementoAtual->prox; // Passa para a proxima linha
		}

		printf("\n"); // Nova linha ap�s terminar de imprimir uma linha da matriz.
		linhaAtual = linhaAtual->ProxLinha;
	}
}

/**
 * @brief Modifica o valor de um elemento espec�fico na matriz.
 *
 * @param matriz Apontador para a matriz a ser modificada.
 * @param linha N�mero da linha do elemento a ser modificado.
 * @param coluna N�mero da coluna do elemento a ser modificado.
 * @param ValorMudar Novo valor para o elemento especificado.
 */
bool MudarValor(Matriz* matriz, int linha, int coluna, int ValorMudar) {
	Matriz* auxLinha = matriz;
	int contadorLinha = 1;

	// Encontra a linha especificada.
	while (auxLinha != NULL && contadorLinha < linha) {
		auxLinha = auxLinha->ProxLinha;
		contadorLinha++;
	}

	if (auxLinha != NULL)
	{
		Lista* auxColuna = auxLinha->linha;
		int contadorColuna = 1;

		// Encontra a coluna especificada.
		while (auxColuna != NULL && contadorColuna < coluna)
		{
			auxColuna = auxColuna->prox;
			contadorColuna++;
		}

		if (auxColuna != NULL)
		{
			auxColuna->num = ValorMudar; // Modifica o valor.
			return true;                 // Retorna verdadeiro se mudar o valor.
		}
	}
	return false; // Retorna falso se n�o modificar o valor.
}
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
Matriz* InserirLinha(Matriz* matriz, int linha, int tamanhoC, int* valores) {

	Matriz* LinhaM = matriz; // Inicializa o apontador para percorrer a matriz.
	int contadorLinha = 2; // Contador para encontrar a posi��o correta da linha.

	// Percorre a matriz at� encontrar a posi��o para inserir a nova linha.
	while (LinhaM != NULL && contadorLinha < linha)
	{
		LinhaM = LinhaM->ProxLinha; // Avan�a para a pr�xima linha.
		contadorLinha++;            // Incrementa o contador de linhas.
	}
	// Verifica se a posi��o foi encontrada.
	if (LinhaM != NULL)
	{
		Lista* novaLinha = NULL; // Inicializa a nova linha a ser inserida.

		// Preenche a nova linha com os valores fornecidos.
		for (int i = 0; i < tamanhoC; i++)
		{
			novaLinha = ColocarNaLista(novaLinha, valores[i]);
		}


		Matriz* novaMatriz = CriarMatriz(novaLinha); // Cria um novo elemento de matriz para a nova linha.
		novaMatriz->ProxLinha = LinhaM->ProxLinha; // Insere a nova linha na posi��o correta.
		LinhaM->ProxLinha = novaMatriz; // Conecta a nova linha � matriz.
	}

	return matriz; // Retorna o apontador para a matriz atualizada.
}
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
Matriz* InserirColuna(Matriz* matriz, int posicao, int* valores) {

	int contadorLinha = 0; // Contador para acessar o valor correspondente na matriz.
	int i = 0; // Indice para percorrer os valores a serem inseridos.

	Matriz* auxMatriz = matriz; // Apontador para percorrer a matriz.


	while (auxMatriz != NULL) // Percorre todas as linhas da matriz.
	{
		Lista* novaLinha = NULL; // Inicializa a nova configura��o da linha.
		Lista* linhaAtual = auxMatriz->linha; // Apontador para percorrer os elementos da linha atual.
		int contadorColuna = 1; // Contador para encontrar a posi��o correta da coluna.


		while (linhaAtual != NULL && contadorColuna < posicao) // Copia os elementos da linha at� a posi��o de inser��o da nova coluna.
		{
			novaLinha = ColocarNaLista(novaLinha, linhaAtual->num);
			linhaAtual = linhaAtual->prox;
			contadorColuna++;
		}


		novaLinha = ColocarNaLista(novaLinha, valores[i++]); // Insere o novo valor na coluna especificada.


		while (linhaAtual != NULL) // Continua a copiar o restante dos elementos da linha.
		{
			novaLinha = ColocarNaLista(novaLinha, linhaAtual->num);
			linhaAtual = linhaAtual->prox;
		}


		auxMatriz->linha = novaLinha; // Atualiza a linha na matriz.


		auxMatriz = auxMatriz->ProxLinha; // Avan�a para a pr�xima linha da matriz.
		contadorLinha++;
	}

	return matriz; // Retorna o apontador para a matriz atualizada.
}

/**
 * @brief Remove uma linha espec�fica da matriz.
 *
 * Localiza a linha a ser removida. Se encontrada, a linha �
 * removida.
 *
 * @param matriz Apontador para a matriz da qual a linha ser� removida.
 * @param linha N�mero da linha a ser removida.
 */
Matriz* RemoverLinha(Matriz* matriz, int linha) {

	Matriz* LinhaAtual = matriz; // Apontador para percorrer a matriz.
	Matriz* LinhaAnterior = NULL; // Apontador para manter a linha anterior.
	int contadorLinha = 1; // Contador para encontrar a linha especificada.

	// Percorre a matriz at� encontrar a linha a ser removida.
	while (LinhaAtual != NULL && contadorLinha < linha)
	{
		LinhaAnterior = LinhaAtual;         // Atualiza a linha anterior.
		LinhaAtual = LinhaAtual->ProxLinha; // Avan�a para a pr�xima linha.
		contadorLinha++;                    // Incrementa o contador de linhas.
	}

	if (LinhaAtual != NULL)  // Verifica se a linha a ser removida foi encontrada.
	{
		if (LinhaAnterior == NULL)  // Se for a primeira linha da matriz.
		{
			matriz = LinhaAtual->ProxLinha; // Atualiza o in�cio da matriz.
		}
		else
		{
			LinhaAnterior->ProxLinha = LinhaAtual->ProxLinha; // Remove a linha da matriz.
		}


		Lista* elementoAtual = LinhaAtual->linha;
		Lista* tempElemento;

	}

	return matriz; // Retorna o apontador para a matriz atualizada.
}

/**
 * @brief Remove uma coluna espec�fica de todas as linhas da matriz.
 *
 * Percorre todas as linhas da matriz, remove o elemento que corresponde �
 * coluna especificada em cada linha.
 *
 * @param matriz Apontador para a matriz da qual a coluna ser� removida.
 * @param coluna N�mero da coluna a ser removida
 */
Matriz* RemoverColuna(Matriz* matriz, int coluna) {

	Matriz* LinhaAtual = matriz; // Apontador para percorrer a matriz.

	// Percorre todas as linhas da matriz.
	while (LinhaAtual != NULL)
	{
		Lista* ElementoAtual = LinhaAtual->linha; // Apontador para percorrer os elementos da linha.
		Lista* ElementoAnterior = NULL; // Mant�m a refer�ncia ao elemento anterior na lista.
		int contadorColuna = 1; // Contador para encontrar a coluna especificada.

		// Percorre os elementos da linha at� encontrar a coluna a ser removida.
		while (ElementoAtual != NULL)
		{
			if (contadorColuna == coluna)  // Verifica a coluna a ser removida.
			{
				if (ElementoAnterior == NULL)  // Se for o primeiro elemento da linha.
				{
					LinhaAtual->linha = ElementoAtual->prox; // Atualiza o in�cio da linha.
				}
				else
				{
					ElementoAnterior->prox = ElementoAtual->prox; // Remove o elemento da linha.
				}
				free(ElementoAtual); // Limpa a mem�ria usada pelo elemento removido.
				break;               // Sai do loop ap�s remover o elemento.
			}

			ElementoAnterior = ElementoAtual;    // Atualiza o elemento anterior.
			ElementoAtual = ElementoAtual->prox; // Avan�a para o pr�ximo elemento.
			contadorColuna++;                    // Incrementa o contador de colunas.
		}

		LinhaAtual = LinhaAtual->ProxLinha; // Avan�a para a proxima linha da matriz.
	}

	return matriz; // Retorna o ponteiro para a matriz atualizada.
}
/**
 * @brief Soma os valores maiores da linha
 *
 * Percorre todas as linhas da matriz, e identifica o maior de todas as linhas.
 *
 * @param matriz Apontador para a matriz de qual iremos somar as linhas.
 */
int somaMaiores(Matriz* m) {


	Matriz* Linhas = m; // Um apontador para percorrer as linhas da matriz.
	int total = 0; // Acumular a soma dos maiores valores encontrados.
	int contadorColunas = 0; // Declara uma vari�vel para contar as colunas
	int maior = 0;

	// Enquanto houver linhas na matriz s�o percorridas.
	while (Linhas != NULL)
	{
		// Inicializa um apontador 'colunas' para percorrer os elementos (valores) de cada linha.
		Lista* colunas = Linhas->linha;
		contadorColunas = 0; // Reinicia o contador de colunas
		maior = 0; // Inicializa a 0 o maior no inicio de cada linha

		// Enquanto houver elementos percorre
		while (colunas != NULL)
		{
			// Condi��o que derfine o maior da linha
			if (colunas->num > maior)
			{
				maior = colunas->num; // Determina o maior das linhas
				contadorColunas++; // Conta as colunas
			}
			colunas = colunas->prox; // Avan�a de coluna
		}

		total += maior;// Adiciona o maior valor encontrado na linha

		Linhas = Linhas->ProxLinha; // Avan�a para a proxima linha
	}


	return total; // Retorna o total acumulado dos maiores valores encontrados em cada linha.
}