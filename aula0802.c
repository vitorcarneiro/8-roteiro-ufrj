/* 
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2021/2
Prof. Marcelo Luiz Drumond Lanza
Autor: Vitor Carneiro Silva de Oliveira
Descricao: programa de testes da função CodificarBase16

$Author$
$Date$
$Log$
*/

#ifdef __linux__
#define _XOPEN_SOURCE 600
#endif

#if defined (__FreeBSD__) && defined (__STRICT_ANSI__)
#define __ISO_C_VISIBLE         1999
#define __LONG_LONG_SUPPORTED
#endif

#include "aula0801.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <errno.h>

#define OK						                0
#define ARGUMENTO_INVALIDO				        1
#define NUMERO_ARGUMENTOS_INVALIDO			    2
#define VALOR_MAXIMO_EXCEDIDO				    3
#define MEMORIA_INSUFICIENTE                    4

#define EOS					                    '\0'

int main (int argc, char *argv [])
{
	char *validacao;
	
	unsigned long long numeroBytes;
	char *saida;

	unsigned short indice;
	unsigned long int variavelLonga;
	byte *vetorBytes;
	

	if (argc < 2) 
	{
		printf ("Uso: <numero-inteiro-nao-negativo> <numero-inteiro-nao-negativo> ... <numero-inteiro-nao-negativo> \n");
		exit (NUMERO_ARGUMENTOS_INVALIDO);		
	}

	if(argv[1][0] == '-')
	{	
		printf ("Argumento contem caractere invalido: '-'.\n");
		exit (ARGUMENTO_INVALIDO);
	}

	variavelLonga = strtoul(argv [1], &validacao, 10);  
	numeroBytes = variavelLonga;
	
	if (*validacao != EOS)
	{
		printf ("Argumento caractere invalido.\n");
		exit (ARGUMENTO_INVALIDO);
	}

/*------------------------  Alocando memoria   ------------------------------*/
	
	saida = (char *) malloc(sizeof(char[numeroBytes * 2 + 1]));

	if(saida == NULL)
	{
		printf ("Memoria insuficiente\n");
		exit (MEMORIA_INSUFICIENTE);
	}

	vetorBytes = (byte *) malloc(sizeof(byte[numeroBytes]));
	
	if(vetorBytes == NULL)
	{
		free(saida);
		printf ("Memoria insuficiente\n");
		exit (MEMORIA_INSUFICIENTE);
	}
/*------------------------------------------------------------------------*/
	for(indice = 2; indice < argc; indice++)
	{
		if(argv[indice][0] == '-')
		{	
			printf ("Argumento %hu contem caractere invalido: '-'.\n", indice);
			exit (ARGUMENTO_INVALIDO);
		}
		if (*validacao != EOS)
		{
			printf ("Argumento contem caractere invalido.\n");
			exit (ARGUMENTO_INVALIDO);
		}
		if (*argv[indice] > 255)
		{
			printf("Valor maximo por caractere: 255");
			exit(VALOR_MAXIMO_EXCEDIDO);
		}

		variavelLonga = strtoul (argv [indice], &validacao, 10);  
		vetorBytes[indice-2] = variavelLonga;
	}

	CodificarBase16(vetorBytes, numeroBytes, saida);

	printf("Codificacao:\n");
	printf("%s\n", saida);
	
	free(vetorBytes);
	free(saida);

return OK;
}

/* RCSfile$ */
