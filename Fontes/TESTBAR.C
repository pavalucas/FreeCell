/***************************************************************************
*  $MCI M�dulo de implementa��o: TBAR Teste baralho de cartas
*
*  Arquivo gerado:              TESTBAR.c
*  Letras identificadoras:      TBAR
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Miguel e Lucas
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Baralho.h"


static const char CRIAR_CARTA_CMD         [ ] = "=criarcarta";
static const char OBTER_NAIPE_CMD         [ ] = "=obternaipe";
static const char OBTER_NUM_CMD           [ ] = "=obternum";
static const char EMBARALHAR_CMD          [ ] = "=embaralhar";
static const char RECEBE_VALORES_CMD      [ ] = "=recebevalores";
static const char CRIAR_BARALHO_CMD       [ ] = "=criarbaralho"   ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VT_CARTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[DIM_VT_LISTA];
BAR_tppCarta   vtCartas[DIM_VT_CARTA];


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static int ValidarInxLista(int inxLista, int Modo);

static int ValidarInxCarta(int inxCarta, int Modo);

static void RecebeValores( BAR_tppCarta cartaDestino, BAR_tppCarta cartaRemetente );


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*  $TC Tipo de dados: BAR Descritor da carta
***********************************************************************/
typedef struct BAR_tagCarta
{
	int num;
	int naipe;
}BAR_tpCarta;

/***********************************************************************
*
*  $FC Fun��o: TBAR &Testar baralho
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 listas e cartas, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =criarcarta                  <inxCarta>   <naipe>        <n�mero>
*     =obternaipe                  <inxCarta>   <naipeEsp>
*     =obternum                    <inxCarta>   <numeroEsp>
*	  =embaralhar                  <inxBaralho> <condRetEsp>
*     =recebevalores               <inxCarta>   <inxCarta2>
*     =criarbaralho                <inxCarta>   <numeroEsp>
*     =obtervalorelem              <inxLista>   <inxCarta>     <CondretPonteiro>
*     =irinicio                    <inxLista>
*     =irfinal                     <inxLista>
*     =avancarelem                 <inxLista>   <numElem>      <CondRetEsp>
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	int inxCarta = -1,
		inxCarta2 = -1,
		inxLista = -1,
		inxBaralho = -1,
		numLidos = -1,
		ValEsp = -1,
		CondRetEsp = -1,
		numElem = -1;

	TST_tpCondRet CondRet;

	BAR_tppCarta pCarta;

	/* Testar CriarCarta */
	
	if (strcmp(ComandoTeste, CRIAR_CARTA_CMD) == 0)
	{
		int naipe, num;

		numLidos = LER_LerParametros("iii",
			&inxCarta, &naipe, &num);

		if ((numLidos != 3)
			|| (!ValidarInxCarta(inxCarta, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		vtCartas[inxCarta] =
			BAR_CriarCarta(naipe, num);

		return TST_CompararPonteiroNulo(1, vtCartas[inxCarta],
			"Erro em ponteiro de nova lista.");

	} /* fim ativa: Testar CriarCarta */

	/* Testar Obter Naipe */

	else if(strcmp(ComandoTeste, OBTER_NAIPE_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii",
			&inxCarta, &ValEsp);

		if ((numLidos != 2)
			|| (!ValidarInxCarta(inxCarta, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt( ValEsp ,
                      BAR_ObterNaipe( vtCartas[ inxCarta ] ) ,
                     "Naipe retornado est� errado."   ) ;

	} /* fim ativa: Testar ObterNaipe */

	/* Testar Obter N�mero */

	else if(strcmp(ComandoTeste, OBTER_NUM_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii",
			&inxCarta, &ValEsp);

		if ((numLidos != 2)
			|| (!ValidarInxCarta(inxCarta, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt( ValEsp ,
                      BAR_ObterNumero( vtCartas[ inxCarta ] ) ,
                     "N�mero retornado est� errado."   ) ;

	} /* fim ativa: Testar ObterNumero */

	/* Testar Embaralhar */

	else if(strcmp(ComandoTeste, EMBARALHAR_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii",
			&inxBaralho, &CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarInxLista(inxBaralho, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = BAR_Embaralhar(vtListas[inxBaralho]);

		return TST_CompararInt( CondRetEsp , CondRet ,
                     "Cond retornado est� errado."   ) ;

	} /* fim ativa: Testar Embaralhar*/

	/* Testar Recebe Valores */

	else if(strcmp(ComandoTeste, RECEBE_VALORES_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii",
			&inxCarta, &inxCarta2);

		if ((numLidos != 2)
			|| (!ValidarInxCarta(inxCarta, NAO_VAZIO))
			|| (!ValidarInxCarta(inxCarta2, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		RecebeValores(vtCartas[inxCarta], vtCartas[inxCarta2]);

		return TST_CompararInt( BAR_ObterNumero( vtCartas[ inxCarta ] ) ,
                      BAR_ObterNumero( vtCartas[ inxCarta2 ] ) ,
                     "Valor das cartas � diferente."   ) ;

	} /* fim ativa: Testar Recebe Valores */


	/* Testar Criar Baralho */

	else if(strcmp(ComandoTeste, CRIAR_BARALHO_CMD) == 0)
	{
		numLidos = LER_LerParametros("i",
			&inxLista);

		if ((numLidos != 1)
			|| (!ValidarInxLista(inxLista, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		vtListas[ inxLista ] = BAR_CriarBaralho();

		return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
                         "Dado tipo um deveria existir." ) ;

	} /* fim ativa: Testar ObterValor */

	/* Testar Obter Valor */
		
	else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "iii" ,
		           &inxLista , &inxCarta , &ValEsp ) ;
		
		if ( ( numLidos != 3 )
		  || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) 
		  || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )))
		{
		   return TST_CondRetParm ;
		} /* if */
		
		pCarta = ( BAR_tppCarta ) LIS_ObterValor( vtListas[ inxLista ] ) ;
		
		if ( ValEsp == 0 )
		{
		   return TST_CompararPonteiroNulo( 0 , pCarta ,
		             "Valor n�o deveria existir." ) ;
		} /* if */
		
		if ( pCarta == NULL )
		{
		   return TST_CompararPonteiroNulo( 1 , pCarta ,
		             "Dado tipo um deveria existir." ) ;
		} /* if */
		
		if( TST_CompararInt( BAR_ObterNaipe( pCarta ) , BAR_ObterNaipe(vtCartas[ inxCarta ]) ,
                     "Naipe das cartas n�o est�o iguais") == TST_CondRetErro)
		{
			return TST_CondRetErro;
		}

		return TST_CompararInt( BAR_ObterNumero( pCarta )  , BAR_ObterNumero(vtCartas[ inxCarta ]) ,
                     "N�mero das cartas n�o est�o iguais");

	} /* fim ativa: Testar obter valor do elemento corrente */


	/* Testar ir para o elemento inicial */

	else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "i" , &inxLista ) ;

		if ( ( numLidos != 1 )
		  || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
		{
		   return TST_CondRetParm ;
		} /* if */

		LIS_IrInicioLista( vtListas[ inxLista ] ) ;

		return TST_CondRetOK ;

	} /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

	else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "i" , &inxLista ) ;

		if ( ( numLidos != 1 )
		  || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
		{
		   return TST_CondRetParm ;
		} /* if */

		LIS_IrFinalLista( vtListas[ inxLista ] ) ;

		return TST_CondRetOK ;

	} /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avan�ar elemento */

	else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
		                    &CondRetEsp ) ;

		if ( ( numLidos != 3 )
		  || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
		{
		   return TST_CondRetParm ;
		} /* if */

		return TST_CompararInt( CondRetEsp ,
		          LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
		          "Condicao de retorno errada ao avancar" ) ;

	} /* fim ativa: LIS  &Avan�ar elemento */

	return TST_CondRetNaoConhec;

} /* Fim fun��o: TBAR &Testar baralho */


  /*****  C�digo das fun��es encapsuladas no m�dulo  *****/

  /***********************************************************************
  *
  *  $FC Fun��o: TBAR -Validar indice de lista
  *
  ***********************************************************************/

int ValidarInxLista(int inxLista, int Modo)
{

	if ((inxLista <  0)
		|| (inxLista >= DIM_VT_LISTA))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtListas[inxLista] != 0)
		{
			return FALSE;
		} /* if */
	}
	else
	{
		if (vtListas[inxLista] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim fun��o: TBAR -Validar indice de lista */

  /***********************************************************************
  *
  *  $FC Fun��o: TBAR -Validar indice de carta
  *
  ***********************************************************************/

int ValidarInxCarta(int inxCarta, int Modo)
{

	if ((inxCarta <  0)
		|| (inxCarta >= DIM_VT_CARTA))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtCartas[inxCarta] != 0)
		{
			return FALSE;
		} /* if */
	}
	else
	{
		if (vtCartas[inxCarta] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim fun��o: TBAR -Validar indice de carta */

  /***********************************************************************
  *
  *  $FC Fun��o: TBAR -Receber Valores
  *
  ***********************************************************************/

void RecebeValores( BAR_tppCarta cartaDestino, BAR_tppCarta cartaRemetente )
{
	cartaDestino->num = cartaRemetente->num;
	cartaDestino->naipe = cartaRemetente->naipe;
} /* Fim fun��o: TBAR -Receber Valores */

  /********** Fim do m�dulo de implementa��o: TBAR Teste baralho de cartas **********/

