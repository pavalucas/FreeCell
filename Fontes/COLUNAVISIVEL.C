/***************************************************************************
*  $MCI Módulo de implementação: CV  Coluna Visível
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

/*****  Dados encapsulados no módulo  *****/

static BAR_tppCarta cartaTopo ;
         /* Ponteiro para o topo da coluna visível */

/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInsercao(BAR_tppCarta carta);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: CV  &Criar coluna visível
*  ****/

LIS_tppLista CV_CriarColunaVisivel(void)
{
	LIS_tppLista pLista = LIS_CriarLista(BAR_LiberarCarta);
	cartaTopo = NULL;
	return pLista;
} /* Fim função: CV  &Criar coluna visível */

/***************************************************************************
*
*  Função: CV  &Inicializar
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
} /* Fim função: CV  &Inicializar */

/***************************************************************************
*
*  Função: CV  &Remover
*  ****/

CV_tpCondRet CV_RemoverCarta(LIS_tppLista colunaVisivel)
{
	CV_tpCondRet retorno;
	LIS_IrFinalLista(colunaVisivel);
	retorno = (CV_tpCondRet)LIS_ExcluirElemento(colunaVisivel);
	return retorno;
} /* Fim função: CV  &Remover */

/***************************************************************************
*
*  Função: CV  &Inserir
*  ****/

CV_tpCondRet CV_InserirCarta(LIS_tppLista colunaVisivel, BAR_tppCarta carta)
{
	CV_tpCondRet retorno;
	LIS_IrFinalLista(colunaVisivel);
	cartaTopo = (BAR_tppCarta)LIS_ObterValor(colunaVisivel);
	if (ValidarInsercao(carta))
	{
		printf("entrei inserir\n");
		retorno = (CV_tpCondRet)LIS_InserirElementoApos(colunaVisivel, carta);
	}
	else
	{
		retorno = CV_CondRetInsercaoInvalida;
	}
	return retorno;
} /* Fim função: CV  &Inserir */

/***************************************************************************
*
*  Função: CV  &Exibir
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
	} while (condRet != LIS_CondRetFimLista); // Avançar para o próximo elemento até chegar ao final da lista

	return condRet;
} /* Fim função: CV  &Exibir */

/***************************************************************************
*
*  Função: CV  &Destruir
*  ****/

CV_tpCondRet CV_DestruirColunaVisivel(LIS_tppLista colunaVisivel)
{
	LIS_DestruirLista(colunaVisivel);

	return CV_CondRetOK;
} /* Fim função: CV  &Destruir */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: CV  -Validar inserção
*
*  $ED Descrição da função
*     Checa se a carta ser inserida é válida
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
} /* Fim função: CV  -Validar inserção */

  /********** Fim do módulo de implementação: CV  Coluna visível **********/
