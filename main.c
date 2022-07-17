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
#define EVER ;;

void gerarMatriz(char matriz[TAM][TAM]);

void exibirMatriz(char matriz[TAM][TAM]);

void buscarHorizontal(char palavra[TAM], char matriz[TAM][TAM]);

void buscarVertical(char palavra[TAM], char matriz[TAM][TAM]);

void buscarDiagonal(char palavra[TAM], char matriz[TAM][TAM]);

// Funcoes Auxiliares
bool palavraFoiEncontrada(int letrasEncontradas, int tamPalavra, char palavra[]);

void resetBusca(char possivelPalavra[TAM], int* letrasEncontradas, int* indicePalavra);

// Inicializacao das funcoes
int main()
{
	// test constants
	const char testeHorizontal[] = "MOXAID";
	const char testeVertical[] = "PYQX";
	const char testeDiagonal[] = "WUAX";

	char matriz[TAM][TAM], palavra[TAM], palavrasEncontradas[TAM][TAM];

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
			printf(" %c", matriz[linha][coluna]);

		printf("\n");
	}

	printf("\n");
}

void buscarHorizontal(char palavra[TAM], char matriz[TAM][TAM])
{
	int letrasEncontradas = 0;
	int indicePalavra = 0;
	char possivelPalavra[TAM] = emptyString;

	for (int linha = 0; linha < TAM; linha++)
	{
		for (int coluna = 0; coluna < TAM; coluna++)
		{
			char letraMatriz = matriz[linha][coluna];
			bool saoMesmaLetra = letraMatriz == palavra[indicePalavra];

			if (!saoMesmaLetra)
			{
				resetBusca(possivelPalavra, &letrasEncontradas, &indicePalavra);
				continue;
			}

			strncat(possivelPalavra, &letraMatriz, 1); // concatena um char
			letrasEncontradas++;
			indicePalavra++;

			int tamPalavra = strlen(palavra);
			bool isPalavra = palavraFoiEncontrada(letrasEncontradas, tamPalavra, possivelPalavra);

			if (isPalavra)
			{
				// Constantes para suprir os erros das coordenadas expressas e das coordenadas reais
				// Os valores exibidos não são os indices
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
	int letrasEncontradas = 0;
	int indicePalavra = 0;
	char possivelPalavra[TAM] = emptyString;

	for (int coluna = 0; coluna < TAM; coluna++)
	{
		for (int linha = 0; linha < TAM; linha++)
		{
			char letraMatriz = matriz[linha][coluna];
			bool saoMesmaLetra = letraMatriz == palavra[indicePalavra];

			if (!saoMesmaLetra)
			{
				resetBusca(possivelPalavra, &letrasEncontradas, &indicePalavra);
				continue;
			}

			strncat(possivelPalavra, &letraMatriz, 1);
			letrasEncontradas++;
			indicePalavra++;

			int tamPalavra = strlen(palavra);
			bool isPalavra = palavraFoiEncontrada(letrasEncontradas, tamPalavra, possivelPalavra);

			if (isPalavra)
			{
				// Constantes para suprir os erros das coordenadas expressas e das coordenadas reais
				// Os valores exibidos não são os indices
				const int diffColunaIndex = 1;
				const int diffLinhaIndex = 2;

				int colunaPrimeiraLetra = coluna + diffColunaIndex;
				int linhaPrimeiraLetra = linha - tamPalavra + diffLinhaIndex;

				printf("'%s' foi encontrada na coordenada (%d, %d), na vertical\n", palavra, colunaPrimeiraLetra, linhaPrimeiraLetra);

				return;
			}
		}
	}
}

void buscarDiagonal(char palavra[TAM], char matriz[TAM][TAM])
{
	int letrasEncontradas = 0, indicePalavra = 0;
	char possivelPalavra[TAM] = emptyString;

	for (int linha = 0; linha < TAM; linha++)
	{
		for (int coluna = 0; coluna < TAM; coluna++)
		{
			char letraMatriz = matriz[linha][coluna];
			bool saoMesmaLetra = letraMatriz == palavra[indicePalavra];

			if (!saoMesmaLetra)
			{
				resetBusca(possivelPalavra, letrasEncontradas, indicePalavra);
				continue;
			}

			// variaveis utilizadas para nao perder as posicoes de busca linha, coluna
			int tempLinha = linha;
			int tempColuna = coluna;

			for (EVER)
			{
				letraMatriz = matriz[tempLinha][tempColuna];

				strncat(possivelPalavra, &letraMatriz, 1);
				letrasEncontradas++;
				indicePalavra++;

				int tamPalavra = strlen(palavra);
				bool isPalavra = palavraFoiEncontrada(letrasEncontradas, tamPalavra, palavra);

				if (isPalavra)
				{
					// indexes comecam no valor 0, enquanto coordenadas no 1
					const int diffLinhaIndex = 1;
					const int diffColunaIndex = 1;

					int colunaPrimeiraLetra = coluna + diffColunaIndex;
					int linhaPrimeiraLetra = linha + diffLinhaIndex;

					printf("'%s' foi encontrada na coordenada (%d, %d), na diagonal\n", palavra, colunaPrimeiraLetra, linhaPrimeiraLetra);

					return;
				}

				tempColuna++;
				tempLinha++;

				bool impossivelSerPalavra = tempLinha >= TAM || tempColuna >= TAM;

				if (impossivelSerPalavra)
				{
					resetBusca(possivelPalavra, &letrasEncontradas, &indicePalavra);
					break;
				}
			}
		}
	}
}

// Funcoes Auxiliares
bool palavraFoiEncontrada(int letrasEncontradas, int tamPalavra, char palavra[])
{
	bool temMesmoTamanho = letrasEncontradas == tamPalavra;

	if (!temMesmoTamanho)
		return false;

	printf("PALAVRA ENCONTRADA: %s\n", palavra); // TODO: Remove: O metodo não deve exibir nenhuma informação
	return true;
}

void resetBusca(char possivelPalavra[TAM], int* letrasEncontradas, int* indicePalavra)
{
	strcpy(possivelPalavra, emptyString);
	*letrasEncontradas = 0;
	*indicePalavra = 0;
}
