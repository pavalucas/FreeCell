#if ! defined( CELULAEXTRA_ )
#define CELULAEXTRA_ 
/***************************************************************************
*  $MCD M�dulo de defini��o: CE  Celula extra 
*
*  Arquivo gerado:              CELULAEXTRA.h
*  Letras identificadoras:      CE
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Handel Scholze Marques
*
***************************************************************************/

#if defined( CELULAEXTRA_OWN )
   #define CELULAEXTRA_EXT
#else
   #define CELULAEXTRA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

#include "BARALHO.h"


/***********************************************************************
*
*  $TC Tipo de dados: CE Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es de C�lula Extra
*
***********************************************************************/
	typedef enum {

         CE_CondRetOK ,
               /* Concluiu corretamente */

         CE_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         CE_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         CE_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         CE_CondRetFaltouMemoria ,
               /* Faltou mem�ria ao tentar criar um elemento de lista */
		
         CE_CondRetListaCheia
               /* Quantidade m�xima de elementos j� foi atingida (4) */

   } CE_tpCondRet ;



/***********************************************************************
*  $FC Fun��o: CE  &Criar Lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista que ter�o as cartas que est�o nas c�lulas extras
*
*  $FV Valor retornado
*     CE_CondRetOK
*     CE_CondRetFaltouMemoria
***********************************************************************/

	LIS_tppLista CE_CriarCelulasExtras(void);


/***********************************************************************
*  $FC Fun��o: CE  &Inserir Carta
*
*  $ED Descri��o da fun��o
*     Insere uma carta em uma das c�lulas extras, no m�ximo teremos 4, 
*     caso j� tenhamos 4 ela n�o � inserida e retornamos que a lista est� cheia.
*
*  $EP Par�metros
*     carta - ponteiro para a carta
*
*  $FV Valor retornado
*     CE_CondRetOK
*     CE_CondRetFaltouMemoria
*     CE_CondRetListaCheia
***********************************************************************/
	CE_tpCondRet CE_InserirCarta(LIS_tppLista lista, BAR_tppCarta carta); 


/***********************************************************************
*  $FC Fun��o: CE  &Exibir
*
*  $ED Descri��o da fun��o
*     Mostra as cartas que est�o nas c�lulas extras
*
*  $EP Par�metros
*     lista - Ponteiro para as c�lulas extras
*
*  $FV Valor retornado
*     CondRetFimLista   - se foram imprimidos todos os elementos at� 
*                         o final da lista
*     CondRetListaVazia - se a lista est� vazia
***********************************************************************/

	CE_tpCondRet CE_ExibirCelulasExtras(LIS_tppLista lista);

/***********************************************************************
*  $FC Fun��o: CE  &Remover Carta
*
*  $ED Descri��o da fun��o
*     Retira a carta que est� na c�lula "posicao"
*
*  $EP Par�metros
*     lista - Ponteiro para as c�lulas extras
*     posicao - posi��o da carta que deve ser retirada
*
*  $FV Valor retornado
*     CV_CondRetOK           - Se excluiu a carta especificada
*     CV_CondRetFimLista     - Se posicao ultrapassa a quantidade de elementos na lista
*     CE_CondRetNaoAchou     - Se posicao menor que zero ou maior que a quantidade m�xima de elementos
*     CV_CondRetListaVazia   - Se a lista est� vazia
*
***********************************************************************/

	CE_tpCondRet CE_RemoverCarta(LIS_tppLista lista, int posicao);


/***********************************************************************
*
*  $FC Fun��o: CE  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista de c�lulas extras fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

	CE_tpCondRet CE_DestruirCelulasExtras(LIS_tppLista lista);

#undef CELULAEXTRA_EXT

/********** Fim do m�dulo de defini��o: CE  Celula extra **********/

#else
#endif






