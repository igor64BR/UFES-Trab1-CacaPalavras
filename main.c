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

#define TAM 10
#define emptyString ""

int main();

void gerarMatriz(char matriz[TAM][TAM]);

void exibirMatriz(char matriz[TAM][TAM]);

void buscarHorizontal(char palavra[TAM], char matriz[TAM][TAM]);

void buscarVertical(char palavra[TAM], char matriz[TAM][TAM]);

void buscarDiagonal(char palavra[TAM], char matriz[TAM][TAM]);

// Funcoes Auxiliares
bool palavraFoiEncontrada(int letrasEncontradas, int tamPalavra, char palavra[]);

// Inicializacao das funcoes
int main()
{
	// test constants
	const char testeHorizontal[] = "QIRT";
	const char testeVertical[] = "PYQX";
	const char testeDiagonal[] = "IXYB";

	char matriz[TAM][TAM] = NULL, palavra[TAM] = NULL, palavrasEncontradas[TAM][TAM] = NULL;

	gerarMatriz(matriz);

	printf("\nE inicia-se o jogo\n\n");
	exibirMatriz(matriz);

	strcpy(palavra, testeHorizontal); // test only (2a linha)
	// printf("\n\nDigite a palavra a ser pesquisada: ");
	// scanf("%s", palavra);
	buscarHorizontal(palavra, matriz);

	strcpy(palavra, testeVertical);
	buscarVertical(palavra, matriz);

	strcpy(palavra, testeDiagonal);
	buscarDiagonal(palavra, matriz);

	return 0;
}

void gerarMatriz(char matriz[TAM][TAM])
{
	int line, column, seed;

	// printf("Digite uma seed: ");
	// scanf("%d", &seed);

	seed = 2; // test only

	srand(seed);

	for (line = 0; line < TAM; line++)
		for (column = 0; column < TAM; column++)
			matriz[line][column] = 'A' + (char)(rand() % 26);
}

void exibirMatriz(char matriz[TAM][TAM])
{
	int linha, coluna;

	for (linha = 0; linha < TAM; linha++)
	{
		for (coluna = 0; coluna < TAM; coluna++)
		{
			printf(" %c", matriz[linha][coluna]);
		}

		printf("\n");
	}

	printf("\n");
}

void buscarHorizontal(char palavra[TAM], char matriz[TAM][TAM])
{
	int coluna, linha, letrasEncontradas = 0, indicePalavra = 0;
	int tamPalavra = strlen(palavra);
	char possivelPalavra[TAM] = emptyString;
	bool isPalavra = false;

	for (linha = 0; linha < TAM; linha++)
	{
		for (coluna = 0; coluna < TAM; coluna++)
		{
			// Logica para verificar se as letras sao as mesmas e analizar se a palavera foi encontrada

			char letraMatriz = matriz[linha][coluna];
			bool saoMesmaLetra = letraMatriz == palavra[indicePalavra];

			if (saoMesmaLetra)
			{
				strncat(possivelPalavra, &letraMatriz, 1); // concatena um char
				letrasEncontradas++;
				indicePalavra++;

				isPalavra = palavraFoiEncontrada(letrasEncontradas, tamPalavra, possivelPalavra);
			}
			else
			{
				strcpy(possivelPalavra, emptyString);
				letrasEncontradas = 0;
				indicePalavra = 0;
			}

			if (isPalavra)
			{
				// indexes comecam no valor 0, enquanto coordenadas no 1
				const int diffColunaIndex = 2;
				const int diffLinhaIndex = 1;

				int colunaPrimeiraLetra = coluna - tamPalavra + diffColunaIndex;

				int linhaPrimeiraLetra = linha + diffLinhaIndex;
				printf("'%s' foi encontrada na coordenada (%d, %d), na horizontal\n", palavra, colunaPrimeiraLetra, linhaPrimeiraLetra);

				return;
			}
		}
	}
}

void buscarVertical(char palavra[TAM], char matriz[TAM][TAM])
{
	int coluna, linha, letrasEncontradas = 0, indicePalavra = 0;
	int tamPalavra = strlen(palavra);
	char possivelPalavra[TAM] = emptyString;
	bool isPalavra = false;

	for (coluna = 0; coluna < TAM; coluna++)
	{
		for (linha = 0; linha < TAM; linha++)
		{
			// Logica para verificar se as letras sao as mesmas e analizar se a palavera foi encontrada

			char letraMatriz = matriz[linha][coluna];
			bool saoMesmaLetra = letraMatriz == palavra[indicePalavra];

			if (saoMesmaLetra)
			{
				strncat(possivelPalavra, &letraMatriz, 1); // concatena um char
				letrasEncontradas++;
				indicePalavra++;

				isPalavra = palavraFoiEncontrada(letrasEncontradas, tamPalavra, possivelPalavra);
			}
			else
			{
				strcpy(possivelPalavra, emptyString);
				letrasEncontradas = 0;
				indicePalavra = 0;
			}

			if (isPalavra)
			{
				// indexes comecam no valor 0, enquanto coordenadas no 1
				const int diffLinhaIndex = 2;
				const int diffColunaIndex = 1;

				int colunaPrimeiraLetra = coluna + diffColunaIndex;

				int linhaPrimeiraLetra = linha - tamPalavra + diffLinhaIndex;
				printf("'%s' foi encontrada na coordenada (%d, %d), na vertical\n", palavra, colunaPrimeiraLetra, linhaPrimeiraLetra);

				return;
			}
		}
	}
}

void buscarDiagonal(char palavra[TAM], char matriz[TAM][TAM]) // TODO: Ajustar a lógica da funcao para realizar buscas na diagonal
{
	int coluna, linha, letrasEncontradas = 0, indicePalavra = 0;
	int tamPalavra = strlen(palavra);
	char possivelPalavra[TAM] = emptyString;
	bool isPalavra = false;

	for (coluna = 0; coluna < TAM; coluna++)
	{
		for (linha = 0; linha < TAM; linha++)
		{
			// Logica para verificar se as letras sao as mesmas e analizar se a palavera foi encontrada

			char letraMatriz = matriz[linha][coluna];
			bool saoMesmaLetra = letraMatriz == palavra[indicePalavra];

			if (saoMesmaLetra)
			{
				strncat(possivelPalavra, &letraMatriz, 1); // concatena um char
				letrasEncontradas++;
				indicePalavra++;

				isPalavra = palavraFoiEncontrada(letrasEncontradas, tamPalavra, possivelPalavra);
			}
			else
			{
				strcpy(possivelPalavra, emptyString);
				letrasEncontradas = 0;
				indicePalavra = 0;
			}

			if (isPalavra)
			{
				// indexes comecam no valor 0, enquanto coordenadas no 1
				const int diffLinhaIndex = 2;
				const int diffColunaIndex = 1;

				int colunaPrimeiraLetra = coluna + diffColunaIndex;

				int linhaPrimeiraLetra = linha - tamPalavra + diffLinhaIndex;
				printf("'%s' foi encontrada na coordenada (%d, %d), na vertical\n", palavra, colunaPrimeiraLetra, linhaPrimeiraLetra);

				return;
			}
		}
	}
}

// Auxiliares
bool palavraFoiEncontrada(int letrasEncontradas, int tamPalavra, char palavra[])
{
	bool temMesmoTamanho = letrasEncontradas == tamPalavra;

	if (!temMesmoTamanho)
		return false;

	printf("PALAVRA ENCONTRADA: %s\n", palavra);
	return true;
}
