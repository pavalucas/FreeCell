/***************************************************************************
*  $MCI Módulo de implementação: BAR  Baralho
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
#include <string.h>

#define BARALHO_OWN
#include "BARALHO.h"
#undef BARALHO_OWN

#define BARALHO_MAX 52
/* Máximo de cartas que um baralho possui (13*4) */

/***** Protótipos das funções encapuladas no módulo *****/

static void RecebeValores(BAR_tppCarta cartaDestino, BAR_tppCarta cartaRemetente);

/*****  Código das funções exportadas pelo módulo  *****/

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
*  Função: BAR &Embaralhar
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
		/* Obtendo carta atual da iteração */

		condRet = LIS_AvancarElementoCorrente( baralho , numAvancos);
		if( condRet != LIS_CondRetOK)
		{
			return condRet;
		}
		cartaAleatoria = (BAR_tpCarta*) LIS_ObterValor(baralho);
		/* Obtendo carta aleatoria */

		RecebeValores(cartaAux, cartaAleatoria);
		/* Passando valores da carta aleatória para uma carta auxiliar */

		RecebeValores(cartaAleatoria, cartaCorrente);
		/* Passando valores da carta corrente para carta aleatória*/

		RecebeValores(cartaCorrente, cartaAux);
		/* Passando valores da carta aleatória (aux) para carta corrente */

		condRet = LIS_AvancarElementoCorrente( baralho , 1 - numAvancos) ;
		if( condRet != LIS_CondRetOK)
		{
			return condRet;
		}
		/* Indo para o elemento seguinte da iteração (voltando para o corrente e somando 1) */
    }

    BAR_LiberarCarta( cartaAux );
    BAR_LiberarCarta( cartaAleatoria );
    BAR_LiberarCarta( cartaCorrente );

	return condRet;
}


/***********************************************************************
*  Função: BAR &Obter Número
***********************************************************************/
int BAR_ObterNumero(BAR_tppCarta carta)
{
	return carta->num;
}


/***********************************************************************
*  Função: BAR &Obter Naipe
***********************************************************************/
int BAR_ObterNaipe(BAR_tppCarta carta)
{
	return carta->naipe;
}


/***********************************************************************
*  Função: BAR &Imprimir Carta
***********************************************************************/

BAR_tpCondRet BAR_ImprimirCarta(BAR_tppCarta carta)
{
	char naipe[4], numeroDaCarta;

	if(carta == NULL)
	{
		return BAR_CondRetNull;
	}


	if(carta->naipe == 0)
		strcpy(naipe, "COPA");
	else if(carta->naipe == 1)
		strcpy(naipe, "OURO");
	else if(carta->naipe == 2)
		strcpy(naipe, "PAUS");
	else if(carta->naipe == 3)
		strcpy(naipe, "ESPA");

	numeroDaCarta = (char) carta->num;

	if(carta->num == 10)
	{
		printf("%d %s ", carta->num, naipe); 
		return BAR_CondRetOK;
	}
	
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

	printf("%c %s ", numeroDaCarta, naipe); 

	return BAR_CondRetOK;
}

/***********************************************************************
*  Função: BAR &Liberar Carta
***********************************************************************/

void BAR_LiberarCarta(void* carta)
{
	free(carta);
}

/***********************************************************************
*  Função: BAR &Criar Baralho
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

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: BAR  -Recebe Valores
*
*  $ED Descrição da função
*     Passa os valores de uma carta para outra
*
*  $EP Parâmetros
*     cartaDestino - carta que irá receber valores
*     cartaRemetente - carta que passará valores
***********************************************************************/

void RecebeValores( BAR_tppCarta cartaDestino, BAR_tppCarta cartaRemetente )
{
	cartaDestino->num = cartaRemetente->num;
	cartaDestino->naipe = cartaRemetente->naipe;
}

/********** Fim do módulo de implementação: BAR Baralho **********/