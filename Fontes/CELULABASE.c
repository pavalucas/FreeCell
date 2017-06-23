/***************************************************************************
*  $MCI M�dulo de implementa��o: CB  C�lula Base
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


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*  Fun��o: CB &Criar
***********************************************************************/
LIS_tppLista CB_CriarCelulaBase()
{
	LIS_tppLista pLista = LIS_CriarLista(BAR_LiberarCarta);
    return pLista;
} /* Fim fun��o: CB  &Criar */


/***********************************************************************
*  Fun��o: CB &Destruir
***********************************************************************/

CB_tpCondRet CB_DestruirCelulaBase(LIS_tppLista celulaBase)
{
	LIS_DestruirLista(celulaBase);

	return CB_CondRetOK;
} /* Fim fun��o: CB  &Destruir */

/***********************************************************************
*  Fun��o: CB &Inserir
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
	} /* Checa se n�o h� cartas na celula base e se a carta a ser inserida � o AS */
	else if( BAR_ObterNumero(ultimaCarta) + 1 == cartaNum )
	{
		return (CB_tpCondRet) LIS_InserirElementoApos(celulaBase, carta);
	} /* Checa se carta a ser inserida � consecutiva do topo da c�lula base */

	return CB_CondRetInsercaoInvalida;
} /* Fim fun��o: CB  &Inserir */


/***********************************************************************
*  Fun��o: CB &Exibir
***********************************************************************/
CB_tpCondRet CB_ExibirCelulaBase( LIS_tppLista celulaBase )
{
	CB_tpCondRet condRet = CB_CondRetListaVazia;

	LIS_IrInicioLista( celulaBase );
	if ( LIS_ObterValor( celulaBase ) == NULL) return condRet; // Lista vazia

	while ( condRet != CB_CondRetFimLista )
	{
		condRet = ( CB_tpCondRet ) LIS_AvancarElementoCorrente( celulaBase, 1 ); 
	}; // Avan�ar para o pr�ximo elemento at� chegar ao final da lista

	BAR_ImprimirCarta( (BAR_tppCarta) LIS_ObterValor(celulaBase) );

	return condRet;
} /* Fim fun��o: CB  &Exibir */