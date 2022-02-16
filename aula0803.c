
/* Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao 
EEL270 - Computacao II - Turma 2021/1 
Prof. Marcelo Luiz Drumond Lanza
Autor: Mikaela Rikberg Alves
Descricao: Implementa a funcao decodificar base 16. 

Author:$
$Date: 2021/10/02 19:04:37 $ 
$Log: aula0803.c,v $
Revision 1.1  2021/10/02 19:04:37  mikaela.alves
Initial revision


 
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


int main (int argc, char *argv [])
{
	unsigned long long numeroBytes[1];
	char *entrada;
	unsigned short indice;
	byte *vetorBytes;

	if (argc != 2) 
	{
		printf ("Uso: <string>  \n");
		exit (NUMERO_ARGUMENTOS_INVALIDO);		
	}

	if(argv[1][0] == '-')
	{	
		printf ("Argumento caractere invalido.\n");
		exit (ARGUMENTO_INVALIDO);
	}

/*------------------------  Alocando memoria   ------------------------------*/
	
	entrada = (char *) malloc (sizeof(char[strlen(argv[1])+1]));
	
	if( entrada == NULL)
	{
		printf (" memoria insuficiente");
		exit (MEMORIA_INSUFICIENTE);
	}

	strcpy(entrada,argv[1]);
	
	vetorBytes = (byte *) malloc (sizeof(byte[strlen(entrada)]));
	
	if(vetorBytes == NULL)
	{
		free(entrada);
		printf ("\n memoria insuficiente");
		exit (MEMORIA_INSUFICIENTE);
	}
/*------------------------------------------------------------------------*/
	for(indice=2; indice<argc; indice++)
	{
		if(argv[indice][0] == '-')
		{	
			free(entrada);
			free(vetorBytes);
			printf ("Argumento caractere invalido.\n");
			exit (ARGUMENTO_INVALIDO);
		}
		
		if (*argv[indice] > 255)
		{
			free(entrada);
			free(vetorBytes);
			printf("valor maximo por caractere eh 255");
			exit (VALOR_MAXIMO_EXCEDIDO);
		}
	}
	
	DecodificarBase16 (entrada, vetorBytes, numeroBytes);

	printf("Decodificacao:\n");
	for (indice = 0; indice < numeroBytes[0]; indice++)
	{
		printf("%d ", vetorBytes[indice]);
	}
	printf("\n");

	free(entrada);
	free(vetorBytes);
	
    return OK;
}

/* RCSfile$ */
