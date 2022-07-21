/*
  Autores:Igor Baiocco e Pedro Henrique Oliosi
  Turma: Eng. Elet. 1o P.
  Descricao: Trabalho 1 - Caca palavras
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define maxSize 10
#define emptyString ""
#define EVER ;;
#define BREAKLINE printf("\n")
#define buscaFalha 0
#define buscaSucesso 1
#define continuarBusca 2

void gerarMatriz(char matriz[maxSize][maxSize]);
void exibirMatriz(char matriz[maxSize][maxSize]);
void buscarHorizontal(char palavra[maxSize], char matriz[maxSize][maxSize]);
void buscarVertical(char palavra[maxSize], char matriz[maxSize][maxSize]);
void buscarDiagonal(char palavra[maxSize], char matriz[maxSize][maxSize]);

// Funcoes Auxiliares
int encontrarPalavra(char palavra[maxSize], char possivelPalavra[maxSize], char matriz[maxSize][maxSize], int lRef, int cRef, int linha, int coluna, int *indicePalavra, char direcao[maxSize]);
void resetBusca(char possivelPalavra[maxSize], int *indicePalavra);
void upperCase(char palavra[maxSize]);

// Inicializacao das funcoes
int main()
{
	const char comandoSaida = '.';
	char matriz[maxSize][maxSize], palavra[maxSize], palavrasEncontradas[maxSize][maxSize];

	gerarMatriz(matriz);

	printf("\nE inicia-se o jogo\n\n");

	for (EVER)
	{
		exibirMatriz(matriz);
		printf("Insira uma palavra a ser encontrada ou '.' para sair do programa: ");

		scanf("%s", palavra);
		upperCase(palavra);

		if (palavra[0] == comandoSaida && strlen(palavra) == 1)
		{
			printf("Muito obrigado por jogar. Ate a proxima! ;-)\n\n");
			return 0;
		}

		buscarHorizontal(palavra, matriz);
		buscarVertical(palavra, matriz);
		buscarDiagonal(palavra, matriz);
	}
}

void gerarMatriz(char matriz[maxSize][maxSize])
{
	int line, column, seed;

	printf("Digite uma seed: ");
	scanf("%d", &seed);

	srand(seed);

	for (line = 0; line < maxSize; line++)
		for (column = 0; column < maxSize; column++)
			matriz[line][column] = 'A' + (char)(rand() % 26);
}

void exibirMatriz(char matriz[maxSize][maxSize])
{
	int linha, coluna;

	BREAKLINE;

	for (linha = 0; linha < maxSize; linha++)
	{
		for (coluna = 0; coluna < maxSize; coluna++)
			printf(" %c", matriz[linha][coluna]);

		BREAKLINE;
	}

	BREAKLINE;
}

void buscarHorizontal(char palavra[maxSize], char matriz[maxSize][maxSize])
{
	char direcao[maxSize] = "horizontal";
	int indicePalavra = 0;
	char possivelPalavra[maxSize] = emptyString;

	for (int linha = 0; linha < maxSize; linha++)
	{
		for (int coluna = 0; coluna < maxSize; coluna++)
		{
			char possivelPalavra[maxSize] = emptyString;
			int indicePalavra = 0;

			for (int tempLinha = linha, tempColuna = coluna; tempColuna < maxSize; tempColuna++)
			{
				int result = encontrarPalavra(palavra, possivelPalavra, matriz, linha, coluna, tempLinha, tempColuna, &indicePalavra, direcao);

				if (result == buscaFalha) break;
				if (result == buscaSucesso) return;
			}
		}
	}
}

void buscarVertical(char palavra[maxSize], char matriz[maxSize][maxSize])
{
	char direcao[maxSize] = "vertical";
	int indicePalavra = 0;
	char possivelPalavra[maxSize] = emptyString;

	for (int coluna = 0; coluna < maxSize; coluna++)
	{
		for (int linha = 0; linha < maxSize; linha++)
		{
			char possivelPalavra[maxSize] = emptyString;
			int indicePalavra = 0;

			for (int tempLinha = linha, tempColuna = coluna; tempLinha < maxSize; tempLinha++)
			{
				int result = encontrarPalavra(palavra, possivelPalavra, matriz, linha, coluna, tempLinha, tempColuna, &indicePalavra, direcao);

				if (result == buscaFalha) break;
				if (result == buscaSucesso) return;
			}
		}
	}
}

void buscarDiagonal(char palavra[maxSize], char matriz[maxSize][maxSize])
{
	char direcao[maxSize] = "diagonal";

	for (int linha = 0; linha < maxSize; linha++)
	{
		for (int coluna = 0; coluna < maxSize; coluna++)
		{
			char possivelPalavra[maxSize] = emptyString;
			int indicePalavra = 0;

			for (
				int tempLinha = linha, tempColuna = coluna;
				tempLinha < maxSize && tempColuna < maxSize;
				tempLinha++, tempColuna++)
			{
				int result = encontrarPalavra(palavra, possivelPalavra, matriz, linha, coluna, tempLinha, tempColuna, &indicePalavra, direcao);

				if (result == buscaFalha) break;
				if (result == buscaSucesso) return;
			}
		}
	}
}

// Funcoes Auxiliares
int encontrarPalavra(char palavra[maxSize], char possivelPalavra[maxSize], char matriz[maxSize][maxSize], int lRef, int cRef, int linha, int coluna, int *indicePalavra, char direcao[maxSize])
{
	char letraMatriz = matriz[linha][coluna];
	bool mesmaLetra = letraMatriz == palavra[*indicePalavra];

	if (!mesmaLetra)
	{
		resetBusca(possivelPalavra, indicePalavra);
		return buscaFalha;
	}

	strncat(possivelPalavra, &letraMatriz, 1);
	(*indicePalavra)++;

	bool saoMesmaPalavra = strcmp(possivelPalavra, palavra) == 0;

	if (saoMesmaPalavra)
	{
		printf("A palavra '%s' foi encontrada na coordenada (%d, %d), na %s\n", palavra, cRef + 1, lRef + 1, direcao);
		return buscaSucesso;
	}

	return continuarBusca;
}

void resetBusca(char possivelPalavra[maxSize], int *indicePalavra)
{
	strcpy(possivelPalavra, emptyString);
	*indicePalavra = 0;
}

void upperCase(char palavra[maxSize])
{
	for (int i = 0; i < strlen(palavra); i++)
		palavra[i] = toupper(palavra[i]);
}
