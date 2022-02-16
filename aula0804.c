/* 
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2021/2
Prof. Marcelo Luiz Drumond Lanza
Autor: Vitor Carneiro Silva de Oliveira
Descricao: programa de testes da função CodificarBase32

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
#include <limits.h>
#include <errno.h>

#define OK						                    0
#define ARGUMENTO_INVALIDO				            1
#define NUMERO_ARGUMENTOS_INVALIDO			        2
#define MEMORIA_INSUFICIENTE                        3
#define ALFABETO_INVALIDO                           4

int main (int argc, char *argv [])
{
	char *validacao;
	char *saida;
	unsigned long long numeroBytes[1];
	char  *entrada;
	tipoAlfabetoBase32 alfabeto;

	unsigned short indice;

	byte *vetorBytes;

	if (argc < 4) 
	{
		printf ("Uso: <numero-inteiro-nao-negativo> <numero-inteiro-nao-negativo> <numero-inteiro-nao-negativo> \n");
		exit (NUMERO_ARGUMENTOS_INVALIDO);		
	}
	
	if(argv[1][0] == '-')
	{	
		printf ("Argumento caractere invalido.\n");
		exit (ARGUMENTO_INVALIDO);
	}
	  
	if(argv[1][0] == '0')
		alfabeto = alfabetoNormal;

	if(argv[1][0] == '1')
		alfabeto =  alfabetoEstendido;

	if(argv[1][0] != '0' && argv[1][0] != '1')
	{
		printf ("Argumento invalido.\n");
		exit (ALFABETO_INVALIDO);
	}

	numeroBytes[0] = strtoull(argv [2], &validacao, 10);
		
/*----------------Alocando memoria---------------------*/
	entrada = malloc(sizeof(char[(argc - 3) * 2 + 1]));

	if( entrada == NULL)
	{
		printf (" memoria insuficiente");
		exit (MEMORIA_INSUFICIENTE);
	}

	saida = malloc(sizeof(char[numeroBytes[0] * 2 + 1]));

	if( entrada == NULL)
	{
		printf (" memoria insuficiente");
		exit (MEMORIA_INSUFICIENTE);
	}

	vetorBytes = malloc(sizeof(byte[numeroBytes[0] * 2]));

	if( entrada == NULL)
	{
		printf (" memoria insuficiente");
		exit (MEMORIA_INSUFICIENTE);
	}

/*-------------------------------------------------------*/
	
	for(indice = 3; indice < argc; indice++)
		strcat(entrada,argv[indice]);
	
	DecodificarBase16 (entrada, vetorBytes, numeroBytes);
	
	CodificarBase32 (vetorBytes, numeroBytes[0], alfabeto, saida);

	printf ("\n %s \n", saida);


return OK;
}

/* RCSfile$ */
