/***************************************************************************
*  $MCI M�dulo de implementa��o: BAR  Baralho
*
*  Arquivo gerado:              BARALHO.c
*  Letras identificadoras:      BAR
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Handel, Miguel e Lucas
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BARALHO_OWN
#include "BARALHO.h"
#undef BARALHO_OWN

#define BARALHO_MAX 52
/* M�ximo de cartas que um baralho possui (13*4) */

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void RecebeValores(BAR_tppCarta cartaDestino, BAR_tppCarta cartaRemetente);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*  $TC Tipo de dados: BAR Descritor da carta
***********************************************************************/
typedef struct BAR_tagCarta
{
	int num;
	int naipe;
}BAR_tpCarta;


/***********************************************************************
*  $TC Tipo de dados: BAR Descritor da carta
***********************************************************************/

BAR_tppCarta BAR_CriarCarta(int naipe, int num)
{
	BAR_tpCarta* pCarta = (BAR_tpCarta*)malloc(sizeof(BAR_tpCarta));
	if (pCarta == NULL)
	{
		return NULL;
	}
	pCarta->naipe = naipe;
	pCarta->num = num;
	return pCarta;
}


/***********************************************************************
*  Fun��o: BAR &Embaralhar
***********************************************************************/
LIS_tpCondRet BAR_Embaralhar(LIS_tppLista baralho)
{
	int i;
	BAR_tpCarta* cartaAux = BAR_CriarCarta(0,0);
	BAR_tpCarta* cartaAleatoria = BAR_CriarCarta(0,0);
	BAR_tpCarta* cartaCorrente = BAR_CriarCarta(0,0);
	/* Declarando ponteiros para as cartas corrente e aletaoria */

	LIS_tpCondRet condRet = LIS_CondRetOK;
	LIS_IrInicioLista( baralho ) ;

    for (i = 0; i < BARALHO_MAX - 1; i++) 
    {
        int indiceAleatorio = i + rand() / (RAND_MAX / (BARALHO_MAX - i) + 1);
		int numAvancos = indiceAleatorio - i;
		/* Acha um indice aleatorio e calcula a distancia de tal para o elemento corrente*/

		cartaCorrente = (BAR_tpCarta*) LIS_ObterValor(baralho);
		/* Obtendo carta atual da itera��o */

		condRet = LIS_AvancarElementoCorrente( baralho , numAvancos);
		if( condRet != LIS_CondRetOK)
		{
			return condRet;
		}
		cartaAleatoria = (BAR_tpCarta*) LIS_ObterValor(baralho);
		/* Obtendo carta aleatoria */

		RecebeValores(cartaAux, cartaAleatoria);
		/* Passando valores da carta aleat�ria para uma carta auxiliar */

		RecebeValores(cartaAleatoria, cartaCorrente);
		/* Passando valores da carta corrente para carta aleat�ria*/

		RecebeValores(cartaCorrente, cartaAux);
		/* Passando valores da carta aleat�ria (aux) para carta corrente */

		condRet = LIS_AvancarElementoCorrente( baralho , 1 - numAvancos) ;
		if( condRet != LIS_CondRetOK)
		{
			return condRet;
		}
		/* Indo para o elemento seguinte da itera��o (voltando para o corrente e somando 1) */
    }

    BAR_LiberarCarta( cartaAux );
    BAR_LiberarCarta( cartaAleatoria );
    BAR_LiberarCarta( cartaCorrente );

	return condRet;
}


/***********************************************************************
*  Fun��o: BAR &Obter N�mero
***********************************************************************/
int BAR_ObterNumero(BAR_tppCarta carta)
{
	return carta->num;
}


/***********************************************************************
*  Fun��o: BAR &Obter Naipe
***********************************************************************/
int BAR_ObterNaipe(BAR_tppCarta carta)
{
	return carta->naipe;
}


/***********************************************************************
*  Fun��o: BAR &Imprimir Carta
***********************************************************************/

void BAR_ImprimirCarta(BAR_tppCarta carta)
{
	/* Naipe tem o n�mero que � o c�digo ASCII do naipe, 3 � COPAS e nossos valores de naipes foram escolhidos
	 para que esteja na ordem ASCII*/
	char naipe = (char) carta->naipe + 3;

	char numeroDaCarta = (char) carta->num;

	if(numeroDaCarta == AS)
		numeroDaCarta = 'A';
	else if(numeroDaCarta == VALETE)
		numeroDaCarta = 'J';
	else if(numeroDaCarta == DAMA)
		numeroDaCarta = 'Q';
	else if(numeroDaCarta == REI)
		numeroDaCarta = 'K';
	else
		numeroDaCarta += '0'; // ASCII

	printf("%c%c ", numeroDaCarta, naipe); 
}

/***********************************************************************
*  Fun��o: BAR &Liberar Carta
***********************************************************************/

void BAR_LiberarCarta(void* carta)
{
	free(carta);
}

/***********************************************************************
*  Fun��o: BAR &Criar Baralho
***********************************************************************/

LIS_tppLista BAR_CriarBaralho(void)
{
	int naipe, num;
	LIS_tppLista baralho = LIS_CriarLista(BAR_LiberarCarta);
	if (baralho == NULL)
	{
		return NULL;
	}

	for (naipe = COPAS; naipe <= ESPADAS; naipe++)
	{
		for (num = AS; num <= REI; num++)
		{
			BAR_tpCarta* pCarta = BAR_CriarCarta(naipe, num);
			if (pCarta == NULL)
			{
				return NULL;
			}

			if (LIS_InserirElementoApos(baralho, pCarta) == LIS_CondRetFaltouMemoria)
			{
				return NULL;
			}
		}
	}
	return baralho;
}

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: BAR  -Recebe Valores
*
*  $ED Descri��o da fun��o
*     Passa os valores de uma carta para outra
*
*  $EP Par�metros
*     cartaDestino - carta que ir� receber valores
*     cartaRemetente - carta que passar� valores
***********************************************************************/

void RecebeValores( BAR_tppCarta cartaDestino, BAR_tppCarta cartaRemetente )
{
	cartaDestino->num = cartaRemetente->num;
	cartaDestino->naipe = cartaRemetente->naipe;
}

/********** Fim do m�dulo de implementa��o: BAR Baralho **********/