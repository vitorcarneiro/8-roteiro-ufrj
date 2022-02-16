/* 
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2021/2
Prof. Marcelo Luiz Drumond Lanza
Autor: Vitor Carneiro Silva de Oliveira
Descricao: codigo fonte da função CodificarBase16

$Author$
$Date$
$Log$
*/

#include "aula0801.h"

#include <unistd.h>
#include <stdlib.h>              
#include <stdio.h>              
#include <string.h>  

#define EOS  '\0'

tipoErros
CodificarBase16 (byte *vetorBytes , unsigned long long numerosBytes, char * saida)
{
	unsigned indice;
	char stringAuxiliar[3];
	byte resto, numeroAuxiliar;
	
	char alfabeto[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	saida[0] = EOS;
	
	for (indice = 0; indice < numerosBytes; indice++)
	{
		numeroAuxiliar = vetorBytes[indice];
		resto = numeroAuxiliar % 16;
		numeroAuxiliar = (numeroAuxiliar - resto) / 16;
		
		stringAuxiliar[0] = alfabeto[numeroAuxiliar];
		stringAuxiliar[1] = alfabeto[resto];
		stringAuxiliar[2] = EOS;

		strcat(saida, stringAuxiliar);
	}

    return ok;
}

tipoErros
DecodificarBase16 (char *entrada, byte *vetorBytes, unsigned long long *numeroBytes)
{
	unsigned indiceBase, indiceBase0, indiceBase1, conta, indice = 0;
	unsigned validar = 0;
	unsigned long long cont;

	char alfabeto[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	
	numeroBytes[0] = strlen(entrada) / 2;

	for (cont = 0; cont < numeroBytes[0] * 2; cont = cont + 2)
	{
		for (indiceBase = 0; indiceBase < 16; indiceBase++)
		{
			if(entrada[cont] == alfabeto[indiceBase])
			{
				indiceBase0 = indiceBase;
				validar++;
			}
			if(entrada[cont + 1] == alfabeto[indiceBase])
			{
				indiceBase1 = indiceBase;
				validar++;
			}
		}
			if(validar % 2 != 0)
				return valorInvalido;
			
			validar = 0;
			
			conta = (indiceBase0 * 16) + (indiceBase1 );

			vetorBytes[indice] = conta;
			indice++;	
	}
    return ok;
}

tipoErros
CodificarBase32 (byte * vetorBytes, unsigned long long numeroBytes, tipoAlfabetoBase32 alfabeto , char * saida)
{
	char alfabetoNormalBase32[32] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','2','3','4','5','6','7'};
	char alfabetoEstendidoBase32[32] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V'};
	
	char *bin;
	int indice;
	byte numero = 0, resto;
	char string[5];
/*------------------------ Alocando memoria -----------------------*/
	bin = malloc(sizeof(char[numeroBytes * 8 + 1]));

	if(bin == NULL)
	{
		printf (" memoria insuficiente");
		return memoriaInsuficiente;
	}
/*-----------------------------------------------------------------*/		
	if(strlen(bin) % 5 != 0)
    {
		resto = strlen(bin) % 5;	
		
		for (indice=0; indice < 5 - resto; indice++)
        {
			string[indice] = '0';	
		}
		string[indice] = '\0';
		strcat(bin,string);
	}
	
	if(alfabeto == alfabetoNormal)
	{ 
		for(indice=0; indice < strlen(bin); indice += 5){
			numero =  (bin[indice] - '0') * 16;
			numero += (bin[indice + 1] - '0') * 8;
			numero += (bin[indice + 2] - '0') * 4;
			numero += (bin[indice + 3] - '0') * 2;
			numero += (bin[indice + 4] - '0') * 1;
			
			saida[indice / 5] = alfabetoNormalBase32[numero]; 
		}
		saida[indice / 5] = '\0';
	}

	if(alfabeto == alfabetoEstendido)
	{ 
		for(indice = 0; indice < strlen(bin); indice += 5){
			numero =  (bin[indice] - '0') * 16;
			numero += (bin[indice + 1] - '0') * 8;
			numero += (bin[indice + 2] - '0') * 4;
			numero += (bin[indice + 3] - '0') * 2;
			numero += (bin[indice + 4] - '0') * 1;
		    saida[indice / 5] = alfabetoEstendidoBase32[numero]; 
		}
		saida[indice / 5] = '\0';
	}
	
	if(strlen(saida) % 8 != 0){
		resto = strlen(saida) % 8;	
		
		for(indice=0; indice < 8-resto; indice++){
			string[indice] = '=';	
		}
		string[indice] = '\0';
		strcat(saida,string);
	}

	
    return ok;
}

/*$RCSfile$*/
