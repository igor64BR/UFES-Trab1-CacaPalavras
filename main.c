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

void gerarMatriz(char matriz[maxSize][maxSize]);
void exibirMatriz(char matriz[maxSize][maxSize]);
void buscarHorizontal(char palavra[maxSize], char matriz[maxSize][maxSize]);
void buscarVertical(char palavra[maxSize], char matriz[maxSize][maxSize]);
void buscarDiagonal(char palavra[maxSize], char matriz[maxSize][maxSize]);

// Funcoes Auxiliares
void resetBusca(char possivelPalavra[maxSize], int* indicePalavra);
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
	int indicePalavra = 0;
	char possivelPalavra[maxSize] = emptyString;

	for (int linha = 0; linha < maxSize; linha++)
	{
		for (int coluna = 0; coluna < maxSize; coluna++)
		{
			char letraMatriz = matriz[linha][coluna];
			bool saoMesmaLetra = letraMatriz == palavra[indicePalavra];

			if (!saoMesmaLetra)
			{
				resetBusca(possivelPalavra, &indicePalavra);
				continue;
			}

			strncat(possivelPalavra, &letraMatriz, 1);
			indicePalavra++;
			bool saoMesmaPalavra = strcmp(possivelPalavra, palavra) == 0;
			
			if (saoMesmaPalavra)
			{
				// Constantes para suprir as diferencas dos valores das coordenadas expressas e das coordenadas reais
				const int diffColunaIndex = 2;
				const int diffLinhaIndex = 1;

				// Os valores exibidos são coordenadas, não indices
				int colunaPrimeiraLetra = coluna - strlen(palavra) + diffColunaIndex;
				int linhaPrimeiraLetra = linha + diffLinhaIndex;

				printf("'%s' foi encontrada na coordenada (%d, %d), na horizontal\n", palavra, colunaPrimeiraLetra, linhaPrimeiraLetra);

				return;
			}
		}
	}
}

void buscarVertical(char palavra[maxSize], char matriz[maxSize][maxSize])
{
	int indicePalavra = 0;
	char possivelPalavra[maxSize] = emptyString;

	for (int coluna = 0; coluna < maxSize; coluna++)
	{
		for (int linha = 0; linha < maxSize; linha++)
		{
			char letraMatriz = matriz[linha][coluna];
			bool saoMesmaLetra = letraMatriz == palavra[indicePalavra];

			if (!saoMesmaLetra)
			{
				resetBusca(possivelPalavra, &indicePalavra);
				continue;
			}

			strncat(possivelPalavra, &letraMatriz, 1);
			indicePalavra++;

			bool saoMesmaPalavra = strcmp(possivelPalavra, palavra) == 0;

			if (saoMesmaPalavra)
			{
				// Constantes para suprir as diferencas dos valores das coordenadas expressas e das coordenadas reais
				const int diffColunaIndex = 1;
				const int diffLinhaIndex = 2;

				// Os valores exibidos são coordenadas, não indices
				int colunaPrimeiraLetra = coluna + diffColunaIndex;
				int linhaPrimeiraLetra = linha - strlen(palavra) + diffLinhaIndex;

				printf("'%s' foi encontrada na coordenada (%d, %d), na vertical\n", palavra, colunaPrimeiraLetra, linhaPrimeiraLetra);

				return;
			}
		}
	}
}

void buscarDiagonal(char palavra[maxSize], char matriz[maxSize][maxSize])
{
	for (int linha = 0; linha < maxSize; linha++)
	{
		for (int coluna = 0; coluna < maxSize; coluna++)
		{
			char possivelPalavra[maxSize] = emptyString;
			int indicePalavra = 0;

			// Valida a sequencia na diagonal
			// Usam-se as linhas e colunas temporarias para encontrar a palavra e nao perder a coordenada inicial da busca
			for (
				int tempLinha = linha, tempColuna = coluna;
				tempLinha < maxSize && tempColuna < maxSize;
				tempLinha++, tempColuna++)
			{
				char letraMatriz = matriz[tempLinha][tempColuna];
				bool mesmaLetra = letraMatriz == palavra[indicePalavra];

				if (!mesmaLetra)
				{
					resetBusca(possivelPalavra, &indicePalavra);
					break;
				}

				strncat(possivelPalavra, &letraMatriz, 1);
				indicePalavra++;

				bool saoMesmaPalavra = strcmp(possivelPalavra, palavra) == 0;

				if (saoMesmaPalavra)
				{
					printf("A palavra '%s' foi encontrada na coordenada (%d, %d), na diagonal\n", palavra, coluna + 1, linha + 1);
					return;
				}
			}
		}
	}
}

// Funcoes Auxiliares
void resetBusca(char possivelPalavra[maxSize], int* indicePalavra)
{
	strcpy(possivelPalavra, emptyString);
	*indicePalavra = 0;
}

void upperCase(char palavra[maxSize])
{
	for (int i = 0; i < strlen(palavra); i++)
		palavra[i] = toupper(palavra[i]);
}
