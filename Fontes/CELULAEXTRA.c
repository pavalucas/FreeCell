#include "CELULAEXTRA.h"

#include <stdio.h>
#define QNT_CELULAS 4

static int qntCEVazias; // Quantidade de c�lulas extras vazias

/***********************************************************************
*  Fun��o: CE &Criar Lista
***********************************************************************/

LIS_tppLista CE_CriarCelulasExtras(void)
{
	LIS_tppLista pLista = LIS_CriarLista(BAR_LiberarCarta); //Cria a lista
	qntCEVazias = QNT_CELULAS;  // Inicialmente temos 4 c�lulas extras vazias
	return pLista;
}

/***********************************************************************
*  Fun��o: CE &Inserir Carta
***********************************************************************/

CE_tpCondRet CE_InserirCarta(LIS_tppLista lista, BAR_tppCarta carta)
{
	CE_tpCondRet valorRetorno;
	
	if(qntCEVazias == 0) // Nenhuma c�lula vazia <=> lista cheia
		return CE_CondRetListaCheia;
	
	valorRetorno = (CE_tpCondRet) LIS_InserirElementoAntes(lista, carta); //Inserimos o elemento

	if(valorRetorno == LIS_CondRetOK ) // se tudo deu certo temos um espa�o vazio a menos
		qntCEVazias--;

	return valorRetorno;
}

/***********************************************************************
*  Fun��o: CE &Exibir
***********************************************************************/

CE_tpCondRet CE_ExibirCelulasExtras(LIS_tppLista lista)
{
	CE_tpCondRet condRet = CE_CondRetListaVazia;
	if(qntCEVazias == QNT_CELULAS) return condRet; //Lista vazia

	LIS_IrInicioLista(lista);
	do
	{
		BAR_ImprimirCarta( (BAR_tppCarta) LIS_ObterValor(lista) ); // Imprimir carta atual
		condRet = (CE_tpCondRet) LIS_AvancarElementoCorrente(lista, 1);
	} while( condRet != LIS_CondRetFimLista ); // Avan�ar para o pr�ximo elemento at� chegar ao final da lista

	return condRet;
}

/***********************************************************************
*  Fun��o: CE &Remover Carta
***********************************************************************/

CE_tpCondRet CE_RemoverCarta(LIS_tppLista lista, int posicao)
{
	CE_tpCondRet condRet;

	if(posicao >= QNT_CELULAS || posicao < 0) 
		return CE_CondRetNaoAchou; //Posicao com valor incorreto
	
	/* setamos o elemento corrente para o desejado */
	LIS_IrInicioLista(lista);
	condRet = LIS_AvancarElementoCorrente(lista, posicao);

	if(condRet == CE_CondRetFimLista) //Passou do n�emro de elementos
		return condRet;

	if(condRet == CE_CondRetListaVazia) //Lista vazia
		return condRet;

	condRet = LIS_ExcluirElemento(lista); // exluimos a carta
	return condRet;
}

/***********************************************************************
*  Fun��o: CE &Destruir Lista
***********************************************************************/

CE_tpCondRet CE_DestruirCelulasExtras(LIS_tppLista lista)
{
	LIS_DestruirLista(lista);
	return CE_CondRetOK;
}

