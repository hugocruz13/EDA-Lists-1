/**
 * @file main.c
 * @author Hugo Cruz a23010
 * @brief
 * @date 2023-03-16
 * @copyright Copyright (c) 2023
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Lib/header.h" 

#pragma comment (lib,"Lib\\Funções.lib")

/**
 * @brief Função principal que utilizamos as funções criadas
 *
 * Cria uma matriz a partir de dados carregados de um arquivo,
 * modifica valores, insere e remove linhas e colunas, e exibe o estado final
 * da matriz.
 *
 */
int main() {

	setlocale(LC_ALL, "portuguese"); // Formatação correta de caracteres.

	int opcao;
	//Definir tamanho da matriz
	int Tamlinha, Tamcoluna;
	//Define o local a modificar e qual o valor.
	int linhaMudar, colunaMudar, valor;
	//Onde vamos acrescentar as linhas ou colunas.
	int linha, coluna;
	int soma;
	//Arrays para preencher linhas e colunas adicionadas
	int valores[15] = { 344, 32, 23, 61, 83, 324, 12, 43,65,  29, 87, 21, 45, 134, 56 };

	// Cria a matriz e define o tamanho
	printf("Define o tamanho da matriz (l,c)\nOpção: ");
	scanf_s("%d,%d", &Tamlinha, &Tamcoluna);
	Matriz* matriz = DistribuirDados(Tamlinha, Tamcoluna);
	printf("\n");
	MostrarMatriz(matriz);


	do {
		printf("\nMenu:\n");
		printf("1. Mudar valor de uma célula\n");
		printf("2. Inserir linha\n");
		printf("3. Inserir coluna\n");
		printf("4. Remover linha\n");
		printf("5. Remover coluna\n");
		printf("6. Mostrar matriz\n");
		printf("7. Soma\n");
		printf("8. Sair\n");
		printf("Escolha uma opção: ");
		scanf_s("%d", &opcao);

		switch (opcao) {
		case 1:
			//Mudar um valor
			printf("\nDefine a posição a mudar e o valor a inserir (l,c,v)\nOpção: ");
			scanf_s("%d,%d,%d", &linhaMudar, &colunaMudar, &valor);
			MudarValor(matriz, linhaMudar, colunaMudar, valor);
			printf("\n");
			MostrarMatriz(matriz);
			break;
		case 2:
			// Adicione aqui a lógica para ler linha_abaixo, Tamcoluna, valores
			printf("\nDefine a seguir de que linha pretende acrescentar a linha (l)\nOpção: ");
			scanf_s("%d", &linha);
			matriz = InserirLinha(matriz, linha, Tamcoluna, valores);
			printf("\n");
			MostrarMatriz(matriz);
			break;
		case 3:
			// Adicione aqui a lógica para ler coluna_direia, valores
			printf("\nDefine a seguir de que coluna pretende acrescentar a coluna (c)\nOpção: ");
			scanf_s("%d", &coluna);
			matriz = InserirColuna(matriz, coluna, valores);
			printf("\n");
			MostrarMatriz(matriz);
			break;
		case 4:
			// Remove linha
			printf("\nDefine a linha que pretende remover (l)\nOpção: ");
			scanf_s("%d", &linha);
			matriz = RemoverLinha(matriz, linha);
			printf("\n");
			MostrarMatriz(matriz);
			break;
		case 5:
			// Remove coluna
			printf("\nDefine a coluna que pretende remover (c)\nOpção: ");
			scanf_s("%d", &coluna);
			matriz = RemoverColuna(matriz, coluna);
			printf("\n");
			MostrarMatriz(matriz);
			break;
		case 6:
			//Apresenta a matriz
			printf("\n");
			MostrarMatriz(matriz);
			break;
		case 7:
			// Soma dos maiores valores das linhas
			soma = somaMaiores(matriz, Tamlinha, Tamcoluna);
			printf("\nSoma dos maiores valores das linhas: %d\n", soma);
			break;
		case 8:
			//Sair
			printf("Sair...\n\n");
			break;
		default:
			printf("Opção inválida!\n");
		}
	} while (opcao != 8);

	free(matriz);
	return 0; // Termina a execução do programa com sucesso.

}