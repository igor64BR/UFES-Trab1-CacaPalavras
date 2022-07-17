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

void upperCase(char palavra[TAM]);

// Inicializacao das funcoes
int main()
{

	char matriz[TAM][TAM], palavra[TAM], palavrasEncontradas[TAM][TAM];

	gerarMatriz(matriz);

	printf("\nE inicia-se o jogo\n\n");

	for (EVER)
	{
		exibirMatriz(matriz);
		printf("Insira uma palavra a ser encontrada ou '.' para sair do programa: ");

		scanf("%s", palavra);
		upperCase(palavra);

		if (palavra[0] == '.' && strlen(palavra) == 1)
		{
			printf("Muito obrigado por jogar. Ate a proxima! ;-)\n\n");
			return 0;
		}

		buscarHorizontal(palavra, matriz);
		buscarVertical(palavra, matriz);
		buscarDiagonal(palavra, matriz);
	}
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
	for (int linha = 0; linha < TAM; linha++)
	{
		for (int coluna = 0; coluna < TAM; coluna++)
		{
			char possivelPalavra[TAM] = emptyString;
			int indicePalavra = 0;
			int letrasEncontradas = 0;

			// valida a sequencia na diagonal
			for (
				int tempLinha = linha, tempColuna = coluna;
				tempLinha < TAM && tempColuna < TAM;
				tempLinha++, tempColuna++)
			{
				char letraMatriz = matriz[tempLinha][tempColuna];
				char letraPalavra = palavra[indicePalavra];
				bool mesmaLetra = letraPalavra == letraMatriz;

				if (!mesmaLetra)
				{
					resetBusca(possivelPalavra, &letrasEncontradas, &indicePalavra);
					break;
				}

				strncat(possivelPalavra, &letraPalavra, 1);
				letrasEncontradas++;
				indicePalavra++;

				bool isPalavra = palavraFoiEncontrada(letrasEncontradas, strlen(palavra), palavra);

				if (isPalavra)
				{
					printf("'%s' foi encontrada na coordenada (%d, %d), na diagonal\n", palavra, coluna + 1, linha + 1);
					return;
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

void upperCase(char palavra[TAM])
{
	for (int i = 0; i < strlen(palavra); i++)
		palavra[i] = toupper(palavra[i]);
}
