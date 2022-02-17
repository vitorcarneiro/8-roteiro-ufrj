/* 
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2021/2
Prof. Marcelo Luiz Drumond Lanza
Autor: Vitor Carneiro Silva de Oliveira
Descricao: programa de testes da função arquivo CodificarBase64

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

#define OK										0
#define NUMERO_ARGUMENTOS_INVALIDO				1
#define MEMORIA_INSUFICIENTE                    2
#define ERRO_ABRINDO_ARQUIVO 					3
#define ERRO_LENDO_ARQUIVO 						4

int
main (int argc, char *argv[])
{
	unsigned long long numeroBytes,indice;
	char *saida;
	byte *bytes, buffer[COMPRIMENTO_BUFFER];
	tipoFinalLinha finalLinha = habilitado;
	tipoErros errosCodificacao64;
	
	FILE *original,*codificado;
	size_t lidos;

	if (argc != 3)  
	{
		printf ("\nUso: %s <arquivo> <arquivo_codificado>  \n\n", argv[0]);
		exit (NUMERO_ARGUMENTOS_INVALIDO) ;	
	}
	
	original = fopen (argv[1],"r");
	if (original == NULL) 
	{
		printf ("\nNao foi possivel abrir o arquivo \"%s\" para leitura.\n",argv[1]); 
		printf ("Erro (#%i) : %s\n",errno, strerror (errno));
		exit (ERRO_ABRINDO_ARQUIVO);
	}

	codificado = fopen (argv[2],"w");
	if (codificado == NULL) 
	{
		printf ("\nNao foi possivel abrir o arquivo \"%s\" para escrita.\n",argv[2]); 
		printf ("Erro (#%i) : %s\n",errno, strerror (errno));
		fclose (original);
		exit (ERRO_ABRINDO_ARQUIVO);
	}

	memset (buffer,0x00, COMPRIMENTO_BUFFER+2);
	indice = 1;
	while ((lidos = fread (buffer, COMPRIMENTO_BUFFER, 1, original)) > 0)
		indice++; 
	
	bytes = (byte *) malloc (sizeof (byte [ (COMPRIMENTO_BUFFER)* indice]));
	if (bytes == NULL)
	{
		fclose (original);
		fclose (codificado);
		remove (argv[2]);
		printf ("\nMemoria insuficiente.\n\n");
		exit (MEMORIA_INSUFICIENTE);
	}
	
	fseek (original, 0, SEEK_SET);

	fread (bytes,(COMPRIMENTO_BUFFER*indice),1, original); 
											
	if(ferror (original))
	{
		printf ("Erro lendo o arquivo.\n");
		fclose (original);
		fclose (codificado);
		free (bytes);
		remove (argv[2]);
		exit (ERRO_LENDO_ARQUIVO);
	}

	numeroBytes = strlen((char*) bytes);
	
	saida = (char *) malloc (sizeof (char[numeroBytes*2+4])) ;
	
	if (saida == NULL)
	{
		fclose (original);
		fclose (codificado);
		free (bytes);
		remove (argv[2]);
		printf ("\nMemoria insuficiente.\n\n");
		exit (MEMORIA_INSUFICIENTE);
	}

	errosCodificacao64 = CodificarBase64 (bytes,numeroBytes,finalLinha,saida); 

	if (errosCodificacao64 == memoriaInsuficiente)
	{
		free (saida);
		fclose (original);
		fclose (codificado);
		remove (argv[2]);
		free (bytes);
		printf ("\nMemoria insuficiente.\n\n");
		exit (MEMORIA_INSUFICIENTE);
	}
	
	free (bytes);
	
	fwrite (saida, 1, strlen(saida) , codificado); 
	if(ferror (codificado))
	{
		printf ("Erro escrevendo o arquivo.\n");
		fclose (original);
		fclose (codificado);
		free (saida);
		remove (argv[2]);
		exit (ERRO_LENDO_ARQUIVO);
	}
		
	free (saida);
	fclose (original);
	fclose (codificado);
	printf("\nArquivo \"%s\" codificado para o arquivo \"%s\" na base 64 com sucesso.\n\n",argv[1],argv[2]);

	return ok;
}

/* $RCSfile: aula0808.c,v $ */
