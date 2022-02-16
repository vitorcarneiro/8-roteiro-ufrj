/* 
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2021/2
Prof. Marcelo Luiz Drumond Lanza
Autor: Vitor Carneiro Silva de Oliveira
Descricao: Prototipo do roteiro 8

$Author$
$Date$
$Log$
*/

#ifndef _AULA08_
#define _AULA08_  "@(#)aula08.h $Revision$"
#endif

typedef unsigned char byte;

typedef enum
{
	ok,
	valorInvalido,
	memoriaInsuficiente
} tipoErros;

tipoErros
CodificarBase16 (byte * /* (E) */, unsigned long long /* (E) */, char * /* (S) */);

tipoErros
DecodificarBase16 (char * /* (E) */, byte * /* (S) */, unsigned long long * /* (S) */);


/*$RCSfile$*/
