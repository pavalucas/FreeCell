/***************************************************************************
*  $MCI Módulo de implementação: TCB Teste célula extra
*
*  Arquivo gerado:              TESTCE.c
*  Letras identificadoras:      TCE
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Handel Scholze Marques
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "CelulaExtra.h"

static const char CRIAR_CARTA_CMD         [ ] = "=criarcarta"     ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;

static const char CRIAR_LISTA_CE_CMD      [ ] = "=criarlistace"   ;
static const char INSERIR_CARTA_CE_CMD    [ ] = "=inserircartace" ;
static const char REMOVER_CARTA_CE_CMD    [ ] = "=removercartace" ;
static const char DESTRUIR_LISTA_CE_CMD   [ ] = "=destruirlistace";


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA_CE 10
#define DIM_VT_CARTA    10
#define DIM_VALOR      100


LIS_tppLista   vtListaCE      [ DIM_VT_LISTA_CE ] ;
BAR_tppCarta   vtCartas       [ DIM_VT_CARTA ];


/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxCarta(int inxCarta, int Modo);

static int ValidarInxLista( int inxLista , int Modo );

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TCE &Testar Célula Extra
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10 
*     e 10 cartas identificadas pelo mesmo intervalo de índice
*
*     Comandos disponíveis:
*   
*     =criarcarta                  <inxCarta>  <naipe>       <número>
*     =obtervalorelem              <inxCE>     <inxCarta>    <CondretPonteiro>
*     =irinicio                    <inxCE>
*     =avancarelem                 <inxCE>     <numElem>     <CondRetEsp>
*     =criarlistace                <inxCE>
*     =inserircartace              <inxCE>     <inxCarta>    <CondRetEsp>
*     =removercartace              <inxCE>     <pos>         <CondRetEsp>
*     =destruirlistace             <inxCE>     <CondRetEsp>
*
***********************************************************************/


TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	int inxCE = -1,
		inxCarta = -1,
		numLidos = -1,
		CondRetEsp = -1,
		pos = -1;

	TST_tpCondRet CondRet;

	BAR_tppCarta pCarta;

	int ValEsp = -1;

	int numElem = -1;

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
	
	/* Testar CriarListaCelulaExtra */
 	
	else if ( strcmp( ComandoTeste , CRIAR_LISTA_CE_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "i" ,
		           &inxCE ) ;

		if ( ( numLidos != 1 )
		  || ( ! ValidarInxLista( inxCE , VAZIO )))
		{
		   return TST_CondRetParm ;
		} /* if */

		vtListaCE[ inxCE ] = CE_CriarCelulasExtras();

		return TST_CompararPonteiroNulo( 1 , vtListaCE[ inxCE ] ,
		   "Erro em ponteiro de nova lista."  ) ;

	} /* fim ativa: Testar CriarListaCE */
	
	/* Testar inserir carta */
	else if( strcmp( ComandoTeste,  INSERIR_CARTA_CE_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iii" ,
		           &inxCE, &inxCarta, &CondRetEsp ) ;

		if ((numLidos != 3)
			|| (!ValidarInxLista(inxCE, NAO_VAZIO))
			|| (!ValidarInxCarta(inxCarta, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = CE_InserirCarta(vtListaCE[inxCE], vtCartas[inxCarta]);

		return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir.");
	} /* fim ativa: Testar inserir carta */

	/* Testar remover carta */
	else if( strcmp( ComandoTeste,  REMOVER_CARTA_CE_CMD ) == 0 )
	{
		numLidos = LER_LerParametros("iii",
			&inxCE, &pos, &CondRetEsp);
		if ((numLidos != 3)
			|| (!ValidarInxLista(inxCE, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = CE_RemoverCarta(vtListaCE[inxCE], pos);

		return TST_CompararInt( CondRetEsp , CondRet ,
                     "Erro ao tentar remover carta.");

	} /* fim ativa: Testar remover carta */

	/* Testar destruir lista */
	else if(strcmp( ComandoTeste,  DESTRUIR_LISTA_CE_CMD ) == 0)
	{
		numLidos = LER_LerParametros("ii",
			&inxCE, &CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarInxLista(inxCE, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = CE_DestruirCelulasExtras(vtListaCE[inxCE]);

		return TST_CompararInt( CondRetEsp , CondRet ,
                     "Erro ao tentar destruir lista de células extras.");

	} /* fim ativa: Testar destruir lista	
	
	/* Testar obter valor do elemento corrente */

	else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
	{
	
		numLidos = LER_LerParametros( "iii" ,
		           &inxCE , &inxCarta , &ValEsp ) ;
		
		if ( ( numLidos != 3 )
		  || ( ! ValidarInxLista( inxCE , NAO_VAZIO )) 
		  || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )))
		{
		   return TST_CondRetParm ;
		} /* if */
		
		pCarta = ( BAR_tppCarta ) LIS_ObterValor( vtListaCE[ inxCE ] ) ;
		
		if ( ValEsp == 0 )
		{
		   return TST_CompararPonteiroNulo( 0 , pCarta ,
		             "Valor não deveria existir." ) ;
		} /* if */
		
		if ( pCarta == NULL )
		{
		   return TST_CompararPonteiroNulo( 1 , pCarta ,
		             "Dado tipo um deveria existir." ) ;
		} /* if */
		
		return TST_CompararPonteiro( vtCartas[inxCarta] , pCarta ,
		             "Valor do elemento errado." ) ;
	
	} /* fim ativa: Testar obter valor do elemento corrente */
	
	/* Testar ir para o elemento inicial */

	else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "i" , &inxCE ) ;
		
		if ( ( numLidos != 1 )
		  || ( ! ValidarInxLista( inxCE , NAO_VAZIO )) )
		{
		   return TST_CondRetParm ;
		} /* if */
		
		LIS_IrInicioLista( vtListaCE[ inxCE ] ) ;
		
		return TST_CondRetOK ;
	
	} /* fim ativa: Testar ir para o elemento inicial */
	
	/* TCE  &Avançar elemento */
	
	else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
	{
	
		numLidos = LER_LerParametros( "iii" , &inxCE , &numElem ,
		                    &CondRetEsp ) ;
		
		if ( ( numLidos != 3 )
		  || ( ! ValidarInxLista( inxCE , NAO_VAZIO )) )
		{
		   return TST_CondRetParm ;
		} /* if */
		
		return TST_CompararInt( CondRetEsp ,
		          LIS_AvancarElementoCorrente( vtListaCE[ inxCE ] , numElem ) ,
		          "Condicao de retorno errada ao avancar" ) ;
	
	} /* fim ativa: TCE  &Avançar elemento */

	return TST_CondRetNaoConhec;

} /* Fim função: TCE &Testar célula extra */

/***********************************************************************
*
*  $FC Função: TCE -Validar indice de carta
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

} /* Fim função: TCE -Validar indice de carta */

/***********************************************************************
*
*  $FC Função: TCE -Validar indice de lista
*
***********************************************************************/

int ValidarInxLista( int inxLista , int Modo )
{

  if ( ( inxLista <  0 )
    || ( inxLista >= DIM_VT_LISTA_CE ))
  {
     return FALSE ;
  } /* if */
     
  if ( Modo == VAZIO )
  {
     if ( vtListaCE[ inxLista ] != 0 )
     {
        return FALSE ;
     } /* if */
  } else
  {
     if ( vtListaCE[ inxLista ] == 0 )
     {
        return FALSE ;
     } /* if */
  } /* if */
     
  return TRUE ;

} /* Fim função: TCE -Validar indice de lista */




  /********** Fim do módulo de implementação: TCE Teste Célula Extra **********/

