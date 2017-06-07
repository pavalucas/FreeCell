#if ! defined( COLUNAVISIVEL_ )
#define COLUNAVISIVEL_

/***************************************************************************
*  $MCD Módulo de definição: CV  Coluna Visível
*
*  Arquivo gerado:              COLUNAVISIVEL.h
*  Letras identificadoras:      Cv
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Lucas Pavanelli
***************************************************************************/

#if defined( COLUNAVISIVEL_OWN )
   #define COLUNAVISIVEL_EXT
#else
   #define COLUNAVISIVEL_EXT extern
#endif

/***** Declara?es exportadas pelo m?ulo *****/

#include "BARALHO.h"

/***********************************************************************
*
*  $TC Tipo de dados: CV Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da coluna visível
*
***********************************************************************/

typedef enum {

	CV_CondRetOK,
	/* Concluiu corretamente */

	CV_CondRetListaVazia,
	/* A lista não contém elementos */

	CV_CondRetFimLista,
	/* Foi atingido o fim de lista */

	CV_CondRetNaoAchou,
	/* Não encontrou o valor procurado */

	CV_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento de lista */

	CV_CondRetInsercaoInvalida
	/* Inserção inválida */

} CV_tpCondRet;

/***********************************************************************
*
*  $FC Função: CV &Criar coluna visível
*
*  $ED Descrição da função
*     Cria uma coluna visível.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista correspondente
*     à coluna visível.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

LIS_tppLista CV_CriarColunaVisivel( void ) ;

/***********************************************************************
*
*  $FC Função: CV  &Inicializar  Coluna Visivel
*
*  $ED Descrição da função
*     Copia as cartas da lista 'cartas' para a lista 'coluna visível',
*     dessa forma inicializando a coluna visível.
*
*  $EP Parâmetros
*     cartas - ponteiro para a lista de cartas a serem copiadas
*     colunaVisivel - ponteiro para a lista de uma coluna visível
*
*  $FV Valor retornado
*     CV_CondRetOK
*     CV_CondRetListaVazia
*     CV_CondRetFaltouMemoria
*
***********************************************************************/

CV_tpCondRet CV_InicializarColunaVisivel(LIS_tppLista cartas, LIS_tppLista colunaVisivel);

/***********************************************************************
*
*  $FC Função: CV  &Remover Carta
*
*  $ED Descrição da função
*     Remove o elemento do topo da coluna visível.
*
*  $EP Parâmetros
*     colunaVisivel - ponteiro para a lista de uma coluna visível
*
*  $FV Valor retornado
*     CV_CondRetOK
*     CV_CondRetListaVazia
*
***********************************************************************/

CV_tpCondRet CV_RemoverCarta( LIS_tppLista colunaVisivel ) ;

/***********************************************************************
*
*  $FC Função: CV  &Inserir Carta
*
*  $ED Descrição da função
*     Insere o elemento no topo da coluna visível.
*
*  $EP Parâmetros
*     colunaVisivel - ponteiro para a lista de uma coluna visível
*     carta - ponteiro para a carta a ser inserida
*
*  $FV Valor retornado
*     CV_CondRetOK
*     CV_CondRetFaltouMemoria
*     CV_CondRetInsercaoInvalida
*
***********************************************************************/

CV_tpCondRet CV_InserirCarta( LIS_tppLista colunaVisivel, BAR_tppCarta carta) ;

/***********************************************************************
*
*  $FC Função: CV  &Exibir Coluna Visivel
*
*  $ED Descrição da função
*     Exibe os elementos da coluna visível.
*
*  $EP Parâmetros
*     colunaVisivel - ponteiro para a lista de uma coluna visível
*
*  $FV Valor retornado
*     CV_CondRetFimLista   - se foram imprimidos todos os elementos até
*                         o final da lista
*     CV_CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

CV_tpCondRet CV_ExibirColunaVisivel( LIS_tppLista colunaVisivel ) ;

/***********************************************************************
*
*  $FC Função: CV  &Destruir Coluna Visivel
*
*  $ED Descrição da função
*     Destrói uma coluna vis?el
*
*  $EP Parâmetros
*     colunaVisivel - ponteiro para a lista de uma coluna visível
*
*  $FV Valor retornado
*     CV_CondRetOK
*
***********************************************************************/

CV_tpCondRet CV_DestruirColunaVisivel( LIS_tppLista colunaVisivel ) ;


#undef COLUNAVISIVEL_EXT

#else
#endif
