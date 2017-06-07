#if ! defined( CELULABASE_ ) 
#define CELULABASE_
/***************************************************************************
*  $MCD M�dulo de defini��o: CB  C�lula Base
*
*  Arquivo gerado:              CELULABASE.h
*  Letras identificadoras:      CB
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Miguel Corti
***************************************************************************/
#if defined( CELULABASE_OWN )
   #define CELULABASE_EXT
#else
   #define CELULABASE_EXT extern
#endif


/***** Declara��es exportadas pelo m�dulo *****/

#include "BARALHO.h"


/***********************************************************************
*
*  $TC Tipo de dados: CB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da celula base
*
***********************************************************************/

typedef enum {

	CB_CondRetOK,
	/* Concluiu corretamente */

	CB_CondRetListaVazia,
	/* A lista n�o cont�m elementos */

	CB_CondRetFimLista,
	/* Foi atingido o fim de lista */

	CB_CondRetNaoAchou,
	/* N�o encontrou o valor procurado */

	CB_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar um elemento de lista */

	CB_CondRetInsercaoInvalida
	/* Inser��o inv�lida */

} CB_tpCondRet;


/***********************************************************************
*  $FC Fun��o: CB &Criar Celula Base
*
*  $ED Descri��o da fun��o
*     Cria uma lista para as c�lulas bases
*
*  $FV Valor retornado
*     Retorna a pr�pria lista criada
***********************************************************************/

	LIS_tppLista CB_CriarCelulaBase();


/***********************************************************************
*  $FC Fun��o: CB &Destruir
*
*  $ED Descri��o da fun��o
*     Destroi uma c�lula base
*
*  $FV Valor retornado
*     CondRetOK
***********************************************************************/

	CB_tpCondRet CB_DestruirCelulaBase(LIS_tppLista celulaBase);


/***********************************************************************
*  $FC Fun��o: CB  &Inserir
*
*  $ED Descri��o da fun��o
*     Tenta inserir um elemento no final da c�lula base
*
*  $EP Par�metros
*     celulaBase - ponteiro para a lista de uma c�lula base
*     carta - a carta a ser inserida
*
*  $FV Valor retornado
*     CB_CondRetOK
*     CB_CondRetFaltouMemoria
*     CB_CondRetInsercaoInvalida
***********************************************************************/

	CB_tpCondRet CB_InserirCarta(LIS_tppLista celulaBase, BAR_tppCarta carta);


/***********************************************************************
*  $FC Fun��o: CB  &Exibir
*
*  $ED Descri��o da fun��o
*     Exibe as cartas da c�lula base em ordem
*
*  $EP Par�metros
*     celulaBase - ponteiro para a lista de uma c�lula base
*
*  $FV Valor retornado
*	  CB_CondRetListaVazia - se n�o h� elementos na lista
*     CB_CondRetFimLista - se todos os elementos foram lidos
***********************************************************************/

	CB_tpCondRet CB_ExibirCelulaBase(LIS_tppLista celulaBase);


#undef CELULABASE_EXT

/********** Fim do m�dulo de defini��o: CB  C�lula Base **********/

#else
#endif