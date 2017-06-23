/***************************************************************************
*  $MCI Módulo de implementação: CB  Célula Base
*
*  Arquivo gerado:              CELULABASE.c
*  Letras identificadoras:      CB
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Miguel Corti
***************************************************************************/

#include <stdio.h>
#include <assert.h>

#define CELULABASE_OWN
#include "CELULABASE.h"
#undef CELULABASE_OWN


/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*  Função: CB &Criar
***********************************************************************/
LIS_tppLista CB_CriarCelulaBase()
{
	LIS_tppLista pLista = LIS_CriarLista(BAR_LiberarCarta);
    return pLista;
} /* Fim função: CB  &Criar */


/***********************************************************************
*  Função: CB &Destruir
***********************************************************************/

CB_tpCondRet CB_DestruirCelulaBase(LIS_tppLista celulaBase)
{
	LIS_DestruirLista(celulaBase);

	return CB_CondRetOK;
} /* Fim função: CB  &Destruir */

/***********************************************************************
*  Função: CB &Inserir
***********************************************************************/
CB_tpCondRet CB_InserirCarta(LIS_tppLista celulaBase, BAR_tppCarta carta)
{
	BAR_tppCarta ultimaCarta;
	int cartaNum = BAR_ObterNumero(carta);

	LIS_IrFinalLista(celulaBase);
	ultimaCarta = (BAR_tppCarta) LIS_ObterValor(celulaBase);

	if(ultimaCarta == NULL)
	{
		if(cartaNum == AS)
		{
			return (CB_tpCondRet) LIS_InserirElementoApos(celulaBase, carta);
		}
	} /* Checa se não há cartas na celula base e se a carta a ser inserida é o AS */
	else if( BAR_ObterNumero(ultimaCarta) + 1 == cartaNum )
	{
		return (CB_tpCondRet) LIS_InserirElementoApos(celulaBase, carta);
	} /* Checa se carta a ser inserida é consecutiva do topo da célula base */

	return CB_CondRetInsercaoInvalida;
} /* Fim função: CB  &Inserir */


/***********************************************************************
*  Função: CB &Exibir
***********************************************************************/
CB_tpCondRet CB_ExibirCelulaBase( LIS_tppLista celulaBase )
{
	CB_tpCondRet condRet = CB_CondRetListaVazia;

	LIS_IrInicioLista( celulaBase );
	if ( LIS_ObterValor( celulaBase ) == NULL) return condRet; // Lista vazia

	while ( condRet != CB_CondRetFimLista )
	{
		condRet = ( CB_tpCondRet ) LIS_AvancarElementoCorrente( celulaBase, 1 ); 
	}; // Avançar para o próximo elemento até chegar ao final da lista

	BAR_ImprimirCarta( (BAR_tppCarta) LIS_ObterValor(celulaBase) );

	return condRet;
} /* Fim função: CB  &Exibir */