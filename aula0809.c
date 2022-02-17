/* 
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2021/2
Prof. Marcelo Luiz Drumond Lanza
Autor: Vitor Carneiro Silva de Oliveira
Descricao: programa de testes da função arquivo DecodificarBase64

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
#define MEMORIA_INSUFICIENTE              		2
#define ERRO_ABRINDO_ARQUIVO 					3
#define ERRO_LENDO_ARQUIVO 						4

int main (int argc, char *argv[])
{
	unsigned long long numeroBytes[1],indice;
	char *saida, buffer[COMPRIMENTO_BUFFER];
	byte *vetorBytes;
	tipoFinalLinha finalLinha = habilitado;
	tipoErros errosCodificacao64;
	FILE *codificado,*decodificado;
	size_t lidos;

	if (argc != 3) 
	{
		printf ("\nUso: %s <arquivo_codificado> <arquivo_decodificado>  \n\n", argv[0]);
		exit (NUMERO_ARGUMENTOS_INVALIDO) ;	
	}
	
	codificado = fopen (argv[1],"r");
	if (codificado == NULL) 
	{
		printf ("\nNao foi possivel abrir o arquivo \"%s\" para leitura.\n",argv[1]); 
		printf ("Erro (#%i) : %s\n",errno, strerror (errno));
		exit (ERRO_ABRINDO_ARQUIVO);
	}

	decodificado = fopen (argv[2],"w");
	if (decodificado == NULL) 
	{
		printf ("\nNao foi possivel abrir o arquivo \"%s\" para escrita.\n",argv[2]); 
		printf ("Erro (#%i) : %s\n",errno, strerror (errno));
		fclose (codificado);
		exit (ERRO_ABRINDO_ARQUIVO);
	}

	memset (buffer,0x00, COMPRIMENTO_BUFFER+2);
	indice = 1;
	while ((lidos = fread (buffer, COMPRIMENTO_BUFFER, 1, codificado)) > 0)
		indice++; 
	
	saida = (char *) malloc (sizeof (char [ (COMPRIMENTO_BUFFER)* indice]));
	if (saida == NULL)
	{
		fclose (codificado);
		fclose (decodificado);
		remove (argv[2]);
		printf ("\nMemoria insuficiente.\n\n");
		exit (MEMORIA_INSUFICIENTE);
	}
	
	fseek (codificado, 0, SEEK_SET);

	fread (saida,(COMPRIMENTO_BUFFER*indice),1, codificado); 
								 						
	if(ferror (codificado))
	{
		printf ("Erro ao ler arquivo.\n");
		fclose (codificado);
		fclose (decodificado);
		free (saida);
		remove (argv[2]);
		exit (ERRO_LENDO_ARQUIVO);
	}

	numeroBytes[0] = strlen(saida);
	
	vetorBytes = (byte *) malloc (sizeof (byte[numeroBytes[0]])) ;
	
	if (vetorBytes == NULL)
	{
		fclose (codificado);
		fclose (decodificado);
		free (saida);
		remove (argv[2]);
		printf ("\nMemoria insuficiente.\n\n");
		exit (MEMORIA_INSUFICIENTE);
	}

	errosCodificacao64 = DecodificarBase64 (saida,finalLinha,vetorBytes,numeroBytes);

	if (errosCodificacao64 == memoriaInsuficiente)
	{
		free (saida);
		fclose (codificado);
		fclose (decodificado);
		remove (argv[2]);
		free (vetorBytes);
		printf ("\nMemoria insuficiente.\n\n");
		exit (MEMORIA_INSUFICIENTE);
	}
	
	free (saida);

	fwrite (vetorBytes, 1, strlen((char *)vetorBytes), decodificado); 
	if(ferror (decodificado))
	{
		printf ("Erro escrevendo o arquivo.\n");
		fclose (codificado);
		fclose (decodificado);
		free (vetorBytes);
		remove (argv[2]);
		exit (ERRO_LENDO_ARQUIVO);
	}
		
	free (vetorBytes);
	fclose (codificado);
	fclose (decodificado);
	printf("\nArquivo \"%s\" decodificado para o arquivo \"%s\" da base 64 com sucesso.\n\n",argv[1],argv[2]);

	return ok;
}

/* $RCSfile$ */
