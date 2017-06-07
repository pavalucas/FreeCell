#if ! defined( CELULABASE_ ) 
#define CELULABASE_
/***************************************************************************
*  $MCD Módulo de definição: CB  Célula Base
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


/***** Declarações exportadas pelo módulo *****/

#include "BARALHO.h"


/***********************************************************************
*
*  $TC Tipo de dados: CB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da celula base
*
***********************************************************************/

typedef enum {

	CB_CondRetOK,
	/* Concluiu corretamente */

	CB_CondRetListaVazia,
	/* A lista não contém elementos */

	CB_CondRetFimLista,
	/* Foi atingido o fim de lista */

	CB_CondRetNaoAchou,
	/* Não encontrou o valor procurado */

	CB_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento de lista */

	CB_CondRetInsercaoInvalida
	/* Inserção inválida */

} CB_tpCondRet;


/***********************************************************************
*  $FC Função: CB &Criar Celula Base
*
*  $ED Descrição da função
*     Cria uma lista para as células bases
*
*  $FV Valor retornado
*     Retorna a própria lista criada
***********************************************************************/

	LIS_tppLista CB_CriarCelulaBase();


/***********************************************************************
*  $FC Função: CB &Destruir
*
*  $ED Descrição da função
*     Destroi uma célula base
*
*  $FV Valor retornado
*     CondRetOK
***********************************************************************/

	CB_tpCondRet CB_DestruirCelulaBase(LIS_tppLista celulaBase);


/***********************************************************************
*  $FC Função: CB  &Inserir
*
*  $ED Descrição da função
*     Tenta inserir um elemento no final da célula base
*
*  $EP Parâmetros
*     celulaBase - ponteiro para a lista de uma célula base
*     carta - a carta a ser inserida
*
*  $FV Valor retornado
*     CB_CondRetOK
*     CB_CondRetFaltouMemoria
*     CB_CondRetInsercaoInvalida
***********************************************************************/

	CB_tpCondRet CB_InserirCarta(LIS_tppLista celulaBase, BAR_tppCarta carta);


/***********************************************************************
*  $FC Função: CB  &Exibir
*
*  $ED Descrição da função
*     Exibe as cartas da célula base em ordem
*
*  $EP Parâmetros
*     celulaBase - ponteiro para a lista de uma célula base
*
*  $FV Valor retornado
*	  CB_CondRetListaVazia - se não há elementos na lista
*     CB_CondRetFimLista - se todos os elementos foram lidos
***********************************************************************/

	CB_tpCondRet CB_ExibirCelulaBase(LIS_tppLista celulaBase);


#undef CELULABASE_EXT

/********** Fim do módulo de definição: CB  Célula Base **********/

#else
#endif