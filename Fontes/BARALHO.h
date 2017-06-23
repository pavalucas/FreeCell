#if ! defined( BARALHO_ )
#define BARALHO_
/***************************************************************************
*  $MCD M�dulo de defini��o: BAR  Baralho
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

/***** Constantes do m�dulo *****/
#define COPAS 0
#define OUROS 1
#define PAUS 2
#define ESPADAS 3

#define AS 1
#define VALETE 11
#define DAMA 12
#define REI 13

/***** Declara��es exportadas pelo m�dulo *****/

#include "LISTA.H"


/* Tipo refer�ncia para uma carta */

	typedef struct BAR_tagCarta * BAR_tppCarta;


/***********************************************************************
*
*  $FC Fun��o: BAR  &Criar carta
*
*  $ED Descri��o da fun��o
*     Cria uma carta
*
*  $EP Par�metros
*     naipe - inteiro que corresponde ao naipe da carta
*     num - inteiro que corresponde ao n�mero da carta
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a carta correspondente.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

	BAR_tppCarta BAR_CriarCarta(int naipe, int num);


/***********************************************************************
*  $FC Fun��o: BAR  &Embaralhar
*
*  $ED Descri��o da fun��o
*     Embaralha de forma ale�toria as cartas de uma lista baralho
*
*  $EP Par�metros
*     baralho - ponteiro para a lista que armazena as cartas ordenadas
*
*  $FV Valor retornado
*     LIS_CondRetOK 
*     LIS_CondRetFimLista
*     LIS_CondRetListaVazia
***********************************************************************/

	LIS_tpCondRet BAR_Embaralhar(LIS_tppLista baralho);


/***********************************************************************
*  $FC Fun��o: BAR  &Obter N�mero
*
*  $ED Descri��o da fun��o
*     Obt�m o n�mero da carta requerida
*
*  $EP Par�metros
*     carta - ponteiro para a carta
*
*  $FV Valor retornado
*     Retorna um inteiro indicando o n�mero da carta
***********************************************************************/

	int BAR_ObterNumero(BAR_tppCarta carta);


/***********************************************************************
*  $FC Fun��o: BAR  &Obter N�mero
*
*  $ED Descri��o da fun��o
*     Obt�m o naipe da carta requerida
*
*  $EP Par�metros
*     carta - ponteiro para a carta
*
*  $FV Valor retornado
*     Retorna um inteiro indicando o naipe da carta
***********************************************************************/

	int BAR_ObterNaipe(BAR_tppCarta carta);


/***********************************************************************
*  $FC Fun��o: BAR  &Imprimir Carta
*
*  $ED Descri��o da fun��o
*     Imprime o n�mero e o naipe de uma carta na tela
*
*  $EP Par�metros
*     carta - ponteiro para a carta
***********************************************************************/

	void BAR_ImprimirCarta(BAR_tppCarta carta);

/***********************************************************************
*  $FC Fun��o: BAR  &Liberar Carta
*
*  $ED Descri��o da fun��o
*     Libera uma carta
*
*  $EP Par�metros
*     carta - ponteiro para a carta
***********************************************************************/

	void BAR_LiberarCarta(void* carta);

/***********************************************************************
*  $FC Fun��o: BAR  &Criar Baralho
*
*  $ED Descri��o da fun��o
*     Cria o baralho de 52 cartas ordenado. A ordem utilizada � a
*     seguinte: primeiro as 13 cartas ordenadas crescentemente
*     segundo o requisito 3 do naipe copas, depois o naipe ouros,
*     em seguida paus e por final espadas.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista correspondente
*     ao baralho ordenado.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*     
***********************************************************************/

	LIS_tppLista BAR_CriarBaralho(void);

#undef BARALHO_EXT

/********** Fim do m�dulo de defini��o: BAR  Baralho **********/

#else
#endif
