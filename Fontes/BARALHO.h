#if ! defined( BARALHO_ )
#define BARALHO_
/***************************************************************************
*  $MCD Módulo de definição: BAR  Baralho
*
*  Arquivo gerado:              BARALHO.h
*  Letras identificadoras:      BAR
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Handel, Miguel e Lucas
***************************************************************************/
#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif

/***** Constantes do módulo *****/
#define COPAS 0
#define OUROS 1
#define PAUS 2
#define ESPADAS 3

#define AS 1
#define VALETE 11
#define DAMA 12
#define REI 13

/***** Declarações exportadas pelo módulo *****/

#include "LISTA.H"


/* Tipo referência para uma carta */

	typedef struct BAR_tagCarta * BAR_tppCarta;


/***********************************************************************
*
*  $FC Função: BAR  &Criar carta
*
*  $ED Descrição da função
*     Cria uma carta
*
*  $EP Parâmetros
*     naipe - inteiro que corresponde ao naipe da carta
*     num - inteiro que corresponde ao número da carta
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a carta correspondente.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

	BAR_tppCarta BAR_CriarCarta(int naipe, int num);


/***********************************************************************
*  $FC Função: BAR  &Embaralhar
*
*  $ED Descrição da função
*     Embaralha de forma aleátoria as cartas de uma lista baralho
*
*  $EP Parâmetros
*     baralho - ponteiro para a lista que armazena as cartas ordenadas
*
*  $FV Valor retornado
*     LIS_CondRetOK 
*     LIS_CondRetFimLista
*     LIS_CondRetListaVazia
***********************************************************************/

	LIS_tpCondRet BAR_Embaralhar(LIS_tppLista baralho);


/***********************************************************************
*  $FC Função: BAR  &Obter Número
*
*  $ED Descrição da função
*     Obtém o número da carta requerida
*
*  $EP Parâmetros
*     carta - ponteiro para a carta
*
*  $FV Valor retornado
*     Retorna um inteiro indicando o número da carta
***********************************************************************/

	int BAR_ObterNumero(BAR_tppCarta carta);


/***********************************************************************
*  $FC Função: BAR  &Obter Número
*
*  $ED Descrição da função
*     Obtém o naipe da carta requerida
*
*  $EP Parâmetros
*     carta - ponteiro para a carta
*
*  $FV Valor retornado
*     Retorna um inteiro indicando o naipe da carta
***********************************************************************/

	int BAR_ObterNaipe(BAR_tppCarta carta);


/***********************************************************************
*  $FC Função: BAR  &Imprimir Carta
*
*  $ED Descrição da função
*     Imprime o número e o naipe de uma carta na tela
*
*  $EP Parâmetros
*     carta - ponteiro para a carta
***********************************************************************/

	void BAR_ImprimirCarta(BAR_tppCarta carta);

/***********************************************************************
*  $FC Função: BAR  &Liberar Carta
*
*  $ED Descrição da função
*     Libera uma carta
*
*  $EP Parâmetros
*     carta - ponteiro para a carta
***********************************************************************/

	void BAR_LiberarCarta(void* carta);

/***********************************************************************
*  $FC Função: BAR  &Criar Baralho
*
*  $ED Descrição da função
*     Cria o baralho de 52 cartas ordenado. A ordem utilizada é a
*     seguinte: primeiro as 13 cartas ordenadas crescentemente
*     segundo o requisito 3 do naipe copas, depois o naipe ouros,
*     em seguida paus e por final espadas.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista correspondente
*     ao baralho ordenado.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*     
***********************************************************************/

	LIS_tppLista BAR_CriarBaralho(void);

#undef BARALHO_EXT

/********** Fim do módulo de definição: BAR  Baralho **********/

#else
#endif
