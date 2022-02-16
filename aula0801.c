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

tipoErros
DecodificarBase32 (char * entrada, tipoAlfabetoBase32 alfabeto, byte * vetorBytes, unsigned long long * numeroBytes)
{
	char alfabetoNormalBase32[32] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','2','3','4','5','6','7'};
	char alfabetoEstendidoBase32[32] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V'};
	int indice, cont, tamanhoVetor;
	char *decimal;

	tamanhoVetor = strlen((char*)entrada);
	
	int resto, auxiliar;
	char stringAux[tamanhoVetor][6];
	char *bin;

/*------------------------ Alocando memoria -----------------------*/
	bin = malloc(sizeof(char[tamanhoVetor * 8 + 1]));

	if(bin == NULL)
	{
		printf ("Memoria insuficiente\n");
		return memoriaInsuficiente;
	}
	
	decimal = malloc(sizeof(char[tamanhoVetor + 1]));

	if(decimal == NULL)
	{
		printf ("Memoria insuficiente\n");
		return memoriaInsuficiente;
	}
/*-----------------------------------------------------------------*/	
	bin[0] = '\0';
	
	if (alfabeto == alfabetoNormal)
	{
		for (indice = 0; indice < tamanhoVetor; indice++ )
			for (cont = 0; cont < 32; cont++)
				if(entrada[indice] == alfabetoNormalBase32[cont])
					decimal[indice] = cont;
					
		for(cont = 0; cont < tamanhoVetor; cont++)
        {
			stringAux[cont][5] = '\0';

			for(indice = 4; indice >= 0; indice--)
			{
				resto = decimal[cont] % 2;
				auxiliar = (decimal[cont] - resto) / 2;
				decimal[cont] = auxiliar; 
		
				if(resto == 0 || resto == 1 )
					stringAux[cont][indice] = resto + '0';
			}
			strcat(bin,stringAux[cont]);
		}
		
		numeroBytes[0] = (int) strlen( (char*) vetorBytes);
	}

	if(alfabeto == alfabetoEstendido)
	{
		for (indice = 0; indice < tamanhoVetor; indice++ )
			for (cont = 0; cont < 32; cont++)
				if (entrada[indice] == alfabetoEstendidoBase32[cont])
					decimal[indice] = cont;
			
		for (cont = 0; cont < tamanhoVetor; cont++)
        {
			for (indice = 5; indice >= 0; indice++)
			{
				resto = decimal[cont] % 2;
				auxiliar = (decimal[cont] - resto) / 2;
				decimal[cont] = auxiliar; 
		
				if(resto == 0 || resto == 1 )
					stringAux[cont][indice] = resto + '0';
			}
			strcat(bin,stringAux[cont]);
		}

		numeroBytes[0] = (int)strlen((char*)vetorBytes);
	}

    return ok;
}

tipoErros
CodificarBase64 (byte * vetorBytes, unsigned long long numeroBytes, tipoFinalLinha finalLinha, char * saida)
{
	char alfabeto[64] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};
	char *bin;
	int indice, indiceLinha, cont;
	byte numero = 0, resto;
	char string[6];
	int conta;

/*------------------------ Alocando memoria -----------------------*/
	bin = malloc(sizeof(char[numeroBytes * 8 + 1]));

	if(bin == NULL)
	{
		printf (" memoria insuficiente");
		return memoriaInsuficiente;
	}

/*-----------------------------------------------------------------*/

	conta = strlen(bin) % 24;
	if (conta != 0)
    {
		if(strlen(bin)%6 != 0){
			resto = strlen(bin)%6;	
			
			for(indice=0; indice < 6-resto; indice++)
				string[indice] = '0';	
	
			string[indice] = '\0';
			strcat(bin,string);
		}
	}

	for (indice=0; indice < strlen(bin); indice += 6)
    {
		numero = (bin[indice] - '0') * 32;
		numero += (bin[indice + 1] - '0') * 16;
		numero += (bin[indice + 2] - '0') * 8;
		numero += (bin[indice + 3] - '0') * 4;
		numero += (bin[indice + 4] - '0') * 2;
		numero += (bin[indice + 5] - '0') * 1;
		
		saida[indice / 6] = alfabeto[numero]; 
	}
	saida[indice / 6] = '\0';
	
	conta = strlen(saida) % 4;
	
	if(conta != 0)
    {
		resto = strlen(saida) % 4;	
		for(indice = 0; indice < 4 - resto; indice++)
			string[indice] = '=';	
		
		string[indice] = '\0';
		strcat(saida,string);
	}
    	
	if(finalLinha == habilitado)
	{
		indiceLinha = 1;
		for(indice = 0; indice < strlen(saida); indice++)
        {
			if(indiceLinha == 77)
			{
				saida[strlen(saida) + 1] = '\0';
				for(cont = strlen(saida); cont > indice; cont--)
					saida[cont] = saida[cont - 1];
				
				saida[indice] = '\n';
				indiceLinha = 0;
			}
			indiceLinha++;
		}
	}
    return ok;
}


/*$RCSfile$*/
