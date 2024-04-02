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
	int* aux = (int*)malloc(sizeof(int) * 50); // Aloca memória para 50 inteiros.

	FILE* ficheiro = fopen("matriz.csv", "r"); // Abrir o arquivo.

	if (ficheiro == NULL) return NULL; // Retorna NULL caso o ficheiro não seja aberto.

	// Lê os dados separados por ponto e virgula enquanto houver dados.
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
 * @brief Cria memória para alocar a estrutura lista.
 *
 * @param n numero que é colocado na lista
 * @return Lista* Ponteiro para o novo elemento da lista.
 */
Lista* CriarNumero(int n) {

	Lista* aux = (Lista*)malloc(sizeof(Lista) * 1); // Aloca memória para um novo elemento na lista.

	if (aux != NULL)
	{
		aux->num = n;     // Define o valor do número.
		aux->prox = NULL; // Define o proximo elemento como NULL.
	}

	return aux; // Retorna uma apontador para o novo elemento da lista.
	free(aux);
}

/**
 * @brief Insere um número no final da lista.
 *
 * @param inicio Apontador para o primeiro elemento da lista.
 * @param n O número a ser inserido na lista.
 */
Lista* ColocarNaLista(Lista* inicio, int n) {
	Lista* nova = CriarNumero(n); // Cria um novo elemento.
	if (nova == NULL)
		return inicio; // Retorna o início.

	if (inicio == NULL)
	{
		inicio = nova; // Se a lista está vazia, o novo elemento é colocado no início.
	}

	else
	{
		Lista* aux2 = inicio;
		// Percorre a lista até o final.
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
 * @param lista Apontador para a lista que é uma linha da matriz.
 */
Matriz* CriarMatriz(Lista* lista) {

	Matriz* aux = (Matriz*)malloc(sizeof(Matriz) * 1); // Aloca memória para uma nova linha da matriz.

	if (aux != NULL)
	{
		aux->linha = lista;    // Define a lista como linha da matriz.
		aux->ProxLinha = NULL; // Define a próxima linha vazia
	}

	return aux; // Retorna um apontador para a nova linha da matriz.
	free(aux);
}

/**
 * @brief Insere uma nova linha na matriz.
 *
 * @param inicio Apontador para a primeira linha da matriz.
 * @param linha Apontador para a lista que será inserida como nova linha.
 */
Matriz* ColocarNaMatriz(Matriz* inicio, Lista* linha) {

	Matriz* nova = CriarMatriz(linha); // Cria uma nova linha com a lista fornecida.

	if (nova == NULL) return inicio; // Retorna o início se falha ao criar a nova linha.

	if (inicio == NULL)
	{
		inicio = nova; // Se a matriz está vazia, a nova linha é o início.
	}
	else
	{
		Matriz* aux2 = inicio;

		// Percorre a matriz até a última linha.
		while (aux2->ProxLinha != NULL)
		{
			aux2 = aux2->ProxLinha;
		}
		aux2->ProxLinha = nova; // Insere a nova linha no final da matriz.
	}
	return inicio; // Retorna um apontador para a primeira linha da matriz.
}

/**
 * @brief Distribui os dados lidos de um arquivo em uma matriz dinâmica.
 *
 * @param linhas Número de linhas da matriz a ser criada.
 * @param colunas Número de colunas por linha na matriz.
 */
Matriz* DistribuirDados(int linhas, int colunas) {
	int i = 0;
	int quantosNum = 0;
	int* valores = CarregaDados(&quantosNum); // Carrega os dados do arquivo.

	Matriz* matriz = NULL;

	// Cria a matriz linha por linha.
	for (int l = 0; l < linhas; l++) {
		Lista* linha = NULL;

		// Adiciona os valores à linha atual.
		for (int c = 0; c < colunas; c++) {
			linha = ColocarNaLista(linha, valores[i++]);
		}

		// Adiciona a linha à matriz.
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

		printf("\n"); // Nova linha após terminar de imprimir uma linha da matriz.
		linhaAtual = linhaAtual->ProxLinha;
	}
}

/**
 * @brief Modifica o valor de um elemento específico na matriz.
 *
 * @param matriz Apontador para a matriz a ser modificada.
 * @param linha Número da linha do elemento a ser modificado.
 * @param coluna Número da coluna do elemento a ser modificado.
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
	return false; // Retorna falso se não modificar o valor.
}
/**
 * @brief Insere uma nova linha após uma linha específica na matriz.
 *
 * Esta função insere uma nova linha preenchida com os valores fornecidos após a
 * linha especificada. Se a linha especificada for a última, a nova linha será
 * adicionada ao final da matriz.
 *
 * @param matriz Aponta para a matriz onde a linha será inserida.
 * @param linha Posição após a qual a nova linha será inserida.
 * @param tamanhoC Numero de colunas na nova linha.
 * @param valores Apontador para um arrays que prenche a nova linha.
 */
Matriz* InserirLinha(Matriz* matriz, int linha, int tamanhoC, int* valores) {

	Matriz* LinhaM = matriz; // Inicializa o apontador para percorrer a matriz.
	int contadorLinha = 2; // Contador para encontrar a posição correta da linha.

	// Percorre a matriz até encontrar a posição para inserir a nova linha.
	while (LinhaM != NULL && contadorLinha < linha)
	{
		LinhaM = LinhaM->ProxLinha; // Avança para a próxima linha.
		contadorLinha++;            // Incrementa o contador de linhas.
	}
	// Verifica se a posição foi encontrada.
	if (LinhaM != NULL)
	{
		Lista* novaLinha = NULL; // Inicializa a nova linha a ser inserida.

		// Preenche a nova linha com os valores fornecidos.
		for (int i = 0; i < tamanhoC; i++)
		{
			novaLinha = ColocarNaLista(novaLinha, valores[i]);
		}


		Matriz* novaMatriz = CriarMatriz(novaLinha); // Cria um novo elemento de matriz para a nova linha.
		novaMatriz->ProxLinha = LinhaM->ProxLinha; // Insere a nova linha na posição correta.
		LinhaM->ProxLinha = novaMatriz; // Conecta a nova linha à matriz.
	}

	return matriz; // Retorna o apontador para a matriz atualizada.
}
/**
 * @brief Insere uma nova coluna em uma posição específica em todas as linhas da matriz.
 *
 * A função percorre cada linha da matriz, inserindo um novo valor da matriz de
 * valores fornecida na posição especificada.
 *
 * @param matriz Apontador para a matriz onde a coluna será inserida.
 * @param posicao Posição  onde a nova coluna será inserida.
 * @param valores Apontador para um arrays que prenche a nova coluna.
 */
Matriz* InserirColuna(Matriz* matriz, int posicao, int* valores) {

	int contadorLinha = 0; // Contador para acessar o valor correspondente na matriz.
	int i = 0; // Indice para percorrer os valores a serem inseridos.

	Matriz* auxMatriz = matriz; // Apontador para percorrer a matriz.


	while (auxMatriz != NULL) // Percorre todas as linhas da matriz.
	{
		Lista* novaLinha = NULL; // Inicializa a nova configuração da linha.
		Lista* linhaAtual = auxMatriz->linha; // Apontador para percorrer os elementos da linha atual.
		int contadorColuna = 1; // Contador para encontrar a posição correta da coluna.


		while (linhaAtual != NULL && contadorColuna < posicao) // Copia os elementos da linha até a posição de inserção da nova coluna.
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


		auxMatriz = auxMatriz->ProxLinha; // Avança para a próxima linha da matriz.
		contadorLinha++;
	}

	return matriz; // Retorna o apontador para a matriz atualizada.
}

/**
 * @brief Remove uma linha específica da matriz.
 *
 * Localiza a linha a ser removida. Se encontrada, a linha á
 * removida.
 *
 * @param matriz Apontador para a matriz da qual a linha será removida.
 * @param linha Número da linha a ser removida.
 */
Matriz* RemoverLinha(Matriz* matriz, int linha) {

	Matriz* LinhaAtual = matriz; // Apontador para percorrer a matriz.
	Matriz* LinhaAnterior = NULL; // Apontador para manter a linha anterior.
	int contadorLinha = 1; // Contador para encontrar a linha especificada.

	// Percorre a matriz até encontrar a linha a ser removida.
	while (LinhaAtual != NULL && contadorLinha < linha)
	{
		LinhaAnterior = LinhaAtual;         // Atualiza a linha anterior.
		LinhaAtual = LinhaAtual->ProxLinha; // Avança para a próxima linha.
		contadorLinha++;                    // Incrementa o contador de linhas.
	}

	if (LinhaAtual != NULL)  // Verifica se a linha a ser removida foi encontrada.
	{
		if (LinhaAnterior == NULL)  // Se for a primeira linha da matriz.
		{
			matriz = LinhaAtual->ProxLinha; // Atualiza o início da matriz.
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
 * @brief Remove uma coluna específica de todas as linhas da matriz.
 *
 * Percorre todas as linhas da matriz, remove o elemento que corresponde à
 * coluna especificada em cada linha.
 *
 * @param matriz Apontador para a matriz da qual a coluna será removida.
 * @param coluna Número da coluna a ser removida
 */
Matriz* RemoverColuna(Matriz* matriz, int coluna) {

	Matriz* LinhaAtual = matriz; // Apontador para percorrer a matriz.

	// Percorre todas as linhas da matriz.
	while (LinhaAtual != NULL)
	{
		Lista* ElementoAtual = LinhaAtual->linha; // Apontador para percorrer os elementos da linha.
		Lista* ElementoAnterior = NULL; // Mantém a referência ao elemento anterior na lista.
		int contadorColuna = 1; // Contador para encontrar a coluna especificada.

		// Percorre os elementos da linha até encontrar a coluna a ser removida.
		while (ElementoAtual != NULL)
		{
			if (contadorColuna == coluna)  // Verifica a coluna a ser removida.
			{
				if (ElementoAnterior == NULL)  // Se for o primeiro elemento da linha.
				{
					LinhaAtual->linha = ElementoAtual->prox; // Atualiza o início da linha.
				}
				else
				{
					ElementoAnterior->prox = ElementoAtual->prox; // Remove o elemento da linha.
				}
				free(ElementoAtual); // Limpa a memória usada pelo elemento removido.
				break;               // Sai do loop após remover o elemento.
			}

			ElementoAnterior = ElementoAtual;    // Atualiza o elemento anterior.
			ElementoAtual = ElementoAtual->prox; // Avança para o próximo elemento.
			contadorColuna++;                    // Incrementa o contador de colunas.
		}

		LinhaAtual = LinhaAtual->ProxLinha; // Avança para a proxima linha da matriz.
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
	int contadorColunas = 0; // Declara uma variável para contar as colunas
	int maior = 0;

	// Enquanto houver linhas na matriz são percorridas.
	while (Linhas != NULL)
	{
		// Inicializa um apontador 'colunas' para percorrer os elementos (valores) de cada linha.
		Lista* colunas = Linhas->linha;
		contadorColunas = 0; // Reinicia o contador de colunas
		maior = 0; // Inicializa a 0 o maior no inicio de cada linha

		// Enquanto houver elementos percorre
		while (colunas != NULL)
		{
			// Condição que derfine o maior da linha
			if (colunas->num > maior)
			{
				maior = colunas->num; // Determina o maior das linhas
				contadorColunas++; // Conta as colunas
			}
			colunas = colunas->prox; // Avança de coluna
		}

		total += maior;// Adiciona o maior valor encontrado na linha

		Linhas = Linhas->ProxLinha; // Avança para a proxima linha
	}


	return total; // Retorna o total acumulado dos maiores valores encontrados em cada linha.
}