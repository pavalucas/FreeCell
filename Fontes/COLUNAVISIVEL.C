/***************************************************************************
*  $MCI M�dulo de implementa��o: CV  Coluna Vis�vel
*
*  Arquivo gerado:              COLUNAVISIVEL.c
*  Letras identificadoras:      CV
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Lucas Pavanelli
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <assert.h>

#define COLUNAVISIVEL_OWN
#include "COLUNAVISIVEL.H"
#undef COLUNAVISIVEL_OWN

#define TRUE 1
#define FALSE 0

/*****  Dados encapsulados no m�dulo  *****/

static BAR_tppCarta cartaTopo ;
         /* Ponteiro para o topo da coluna vis�vel */

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static int ValidarInsercao(BAR_tppCarta carta);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: CV  &Criar coluna vis�vel
*  ****/

LIS_tppLista CV_CriarColunaVisivel(void)
{
	LIS_tppLista pLista = LIS_CriarLista(BAR_LiberarCarta);
	cartaTopo = NULL;
	return pLista;
} /* Fim fun��o: CV  &Criar coluna vis�vel */

/***************************************************************************
*
*  Fun��o: CV  &Inicializar
*  ****/

CV_tpCondRet CV_InicializarColunaVisivel(LIS_tppLista cartas, LIS_tppLista colunaVisivel)
{
	CV_tpCondRet condRetAvancar = CV_CondRetOK;
	BAR_tppCarta cartaAtual;
	LIS_IrInicioLista(cartas);
	condRetAvancar = (CV_tpCondRet)LIS_AvancarElementoCorrente(cartas, 0);
	if (condRetAvancar == CV_CondRetListaVazia)
	{
		return CV_CondRetListaVazia;
	}
	while (condRetAvancar != CV_CondRetFimLista)
	{
		cartaAtual = (BAR_tppCarta)LIS_ObterValor(cartas);
		if (LIS_InserirElementoApos(colunaVisivel, cartaAtual) == LIS_CondRetFaltouMemoria)
		{
			return CV_CondRetFaltouMemoria;
		}
		condRetAvancar = (CV_tpCondRet)LIS_AvancarElementoCorrente(cartas, 1);
	}
	return CV_CondRetOK;
} /* Fim fun��o: CV  &Inicializar */

/***************************************************************************
*
*  Fun��o: CV  &Remover
*  ****/

CV_tpCondRet CV_RemoverCarta(LIS_tppLista colunaVisivel)
{
	CV_tpCondRet retorno;
	LIS_IrFinalLista(colunaVisivel);
	retorno = (CV_tpCondRet)LIS_ExcluirElemento(colunaVisivel);
	return retorno;
} /* Fim fun��o: CV  &Remover */

/***************************************************************************
*
*  Fun��o: CV  &Inserir
*  ****/

CV_tpCondRet CV_InserirCarta(LIS_tppLista colunaVisivel, BAR_tppCarta carta)
{
	CV_tpCondRet retorno;
	LIS_IrFinalLista(colunaVisivel);
	cartaTopo = (BAR_tppCarta)LIS_ObterValor(colunaVisivel);
	if (ValidarInsercao(carta))
	{
		retorno = (CV_tpCondRet)LIS_InserirElementoApos(colunaVisivel, carta);
	}
	else
	{
		retorno = CV_CondRetInsercaoInvalida;
	}
	return retorno;
} /* Fim fun��o: CV  &Inserir */

/***************************************************************************
*
*  Fun��o: CV  &Exibir
*  ****/

CV_tpCondRet CV_ExibirColunaVisivel(LIS_tppLista colunaVisivel)
{
	CV_tpCondRet condRet = CV_CondRetListaVazia;
	LIS_IrFinalLista(colunaVisivel);
	cartaTopo = (BAR_tppCarta)LIS_ObterValor(colunaVisivel);
	if (cartaTopo == NULL) return condRet; // Lista vazia

	LIS_IrInicioLista(colunaVisivel);
	do
	{
		BAR_ImprimirCarta((BAR_tppCarta)LIS_ObterValor(colunaVisivel)); // Imprimir carta atual
		condRet = (CV_tpCondRet)LIS_AvancarElementoCorrente(colunaVisivel, 1);
	} while (condRet != LIS_CondRetFimLista); // Avan�ar para o pr�ximo elemento at� chegar ao final da lista

	return condRet;
} /* Fim fun��o: CV  &Exibir */

/***************************************************************************
*
*  Fun��o: CV  &Destruir
*  ****/

CV_tpCondRet CV_DestruirColunaVisivel(LIS_tppLista colunaVisivel)
{
	LIS_DestruirLista(colunaVisivel);

	return CV_CondRetOK;
} /* Fim fun��o: CV  &Destruir */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: CV  -Validar inser��o
*
*  $ED Descri��o da fun��o
*     Checa se a carta ser inserida � v�lida
*
***********************************************************************/

int ValidarInsercao(BAR_tppCarta carta)
{
	int naipeCarta = BAR_ObterNaipe(carta);
	int numCarta = BAR_ObterNumero(carta);
	int naipeTopo;
	int numTopo;

	if (cartaTopo == NULL)
	{
		return TRUE;
	}
	else
	{
		naipeTopo = BAR_ObterNaipe(cartaTopo);
		numTopo = BAR_ObterNumero(cartaTopo);
		if (numTopo > AS)
		{
			if (numCarta == numTopo - 1)
			{
				if ((naipeCarta <= OUROS && naipeTopo >= PAUS) || (naipeCarta >= PAUS && naipeTopo <= OUROS))
				{
					return TRUE;
				}
			}
		}
	}
	
	return FALSE;
} /* Fim fun��o: CV  -Validar inser��o */

  /********** Fim do m�dulo de implementa��o: CV  Coluna vis�vel **********/
