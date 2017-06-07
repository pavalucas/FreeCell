/***************************************************************************
*  $MCI Módulo de implementação: TCV Teste coluna visível
*
*  Arquivo gerado:              TESTCV.c
*  Letras identificadoras:      TCV
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Lucas Pavanelli
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "ColunaVisivel.h"

static const char CRIAR_CARTA_CMD         [ ] = "=criarcarta"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;
static const char CRIAR_CV_CMD            [ ] = "=criarcv"        ;
static const char INICIALIZAR_CMD         [ ] = "=inicializarcv"  ;
static const char REMOVER_CMD             [ ] = "=removercv"      ;
static const char INSERIR_CMD             [ ] = "=inserircv"      ;
static const char DESTRUIR_CMD            [ ] = "=destruircv"     ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_CV     10
#define DIM_VT_LISTA  10
#define DIM_VT_CARTA  10
#define DIM_VALOR     100

LIS_tppLista   vtColunaVisivel[ DIM_VT_CV ];
LIS_tppLista   vtListas       [ DIM_VT_LISTA ] ;
BAR_tppCarta   vtCartas       [ DIM_VT_CARTA ];


/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxCarta(int inxCarta, int Modo);

static int ValidarInxLista( int inxLista , int Modo );

static int ValidarInxColunaVisivel(int inxCV, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TCV &Testar coluna visivel
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, 10 cartas e 10 colunas visíveis,
*     identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*   
*     =criarcarta                  <inxCarta>  <naipe>       <numero>
*     =compararcartatopo           <inxCarta>
*     =criarlista                  <inxLista>
*     =inselemapos                 <inxLista>  <inxCarta>    <CondRetEsp>
*     =obtervalorelem              <inxCV>     <inxCarta>    <CondretPonteiro>
*     =irinicio                    <inxCV>
*     =avancarelem                 <inxCV>     <numElem>     <CondRetEsp>
*     =criarcv                     <inxCV>
*     =inicializarcv               <inxLista>  <inxCV>
*     =removercv                   <inxCV>     <CondRetEsp>
*     =inserircv                   <inxCV>     <inxCarta>    <CondRetEsp>
*     =destruircv                  <inxCV>
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	int inxCV = -1,
		inxLista = -1,
		inxCarta = -1,
		numLidos = -1,
		CondRetEsp = -1;

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

	/* Testar CriarLista */

	else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "i" ,
		           &inxLista ) ;

		if ( ( numLidos != 1 )
		  || ( ! ValidarInxLista( inxLista , VAZIO )))
		{
		   return TST_CondRetParm ;
		} /* if */

		vtListas[ inxLista ] =
		     LIS_CriarLista( BAR_LiberarCarta ) ;

		return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
		   "Erro em ponteiro de nova lista."  ) ;

	} /* fim ativa: Testar CriarLista */

	/* Testar CriarColunaVisivel */
	
	else if (strcmp(ComandoTeste, CRIAR_CV_CMD) == 0)
	{
		numLidos = LER_LerParametros("i",
			&inxCV);

		if ((numLidos != 1)
			|| (!ValidarInxColunaVisivel(inxCV, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		vtColunaVisivel[inxCV] =
			CV_CriarColunaVisivel();

		return TST_CompararPonteiroNulo(1, vtColunaVisivel[inxCV],
			"Erro em ponteiro de nova lista.");

	} /* fim ativa: Testar CriarColunaVisivel */

	/* Testar Inicializar */

	else if(strcmp(ComandoTeste, INICIALIZAR_CMD) == 0)
	{
		numLidos = LER_LerParametros("iii",
			&inxLista, &inxCV, &CondRetEsp);

		if ((numLidos != 3)
			|| (!ValidarInxColunaVisivel(inxCV, NAO_VAZIO))
			|| (!ValidarInxLista(inxLista, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = CV_InicializarColunaVisivel(vtListas[inxLista], vtColunaVisivel[inxCV]);

		return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inicializar.");
	} /* fim ativa: Testar Inicializar */
	
	/* Testar Remover */
	
	else if(strcmp(ComandoTeste, REMOVER_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii",
			&inxCV, &CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarInxColunaVisivel(inxCV, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = CV_RemoverCarta(vtColunaVisivel[inxCV]);

		return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao remover.");
	} /* fim ativa: Testar Remover */
	
	/* Testar Inserir */
	
	else if(strcmp(ComandoTeste, INSERIR_CMD) == 0)
	{
		numLidos = LER_LerParametros("iii",
			&inxCV, &inxCarta, &CondRetEsp);

		if ((numLidos != 3)
			|| (!ValidarInxColunaVisivel(inxCV, NAO_VAZIO))
			|| (!ValidarInxCarta(inxCarta, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = CV_InserirCarta(vtColunaVisivel[inxCV], vtCartas[inxCarta]);

		return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir.");
	} /* fim ativa: Testar Inserir */

	/* Testar Destruir */
	
	else if(strcmp(ComandoTeste, DESTRUIR_CMD) == 0)
	{
		numLidos = LER_LerParametros( "i" ,
                               &inxCV ) ;

        if ( ( numLidos != 1 )
          || ( ! ValidarInxColunaVisivel( inxCV , NAO_VAZIO )))
        {
           return TST_CondRetParm ;
        } /* if */

        CV_DestruirColunaVisivel( vtColunaVisivel[ inxCV ] ) ;
        vtColunaVisivel[ inxCV ] = NULL ;

        return TST_CondRetOK ;
	} /* fim ativa: Testar Destruir */
	
	/* Testar inserir elemento apos */

	else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
	{
	
		numLidos = LER_LerParametros( "iii" ,
		           &inxLista , &inxCarta , &CondRetEsp ) ;
		
		if ( ( numLidos != 3 )
		  || ( ! ValidarInxLista( inxLista , NAO_VAZIO ))
		  || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )) )
		{
		   return TST_CondRetParm ;
		} /* if */
		
		CondRet = LIS_InserirElementoApos( vtListas[ inxLista ] , vtCartas[ inxCarta ] ) ;
		
		return TST_CompararInt( CondRetEsp , CondRet ,
		         "Condicao de retorno errada ao inserir apos."                   ) ;
	
	} /* fim ativa: Testar inserir elemento apos */
	
	/* Testar obter valor do elemento corrente */

	else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
	{
	
		numLidos = LER_LerParametros( "iii" ,
		           &inxCV , &inxCarta , &ValEsp ) ;
		
		if ( ( numLidos != 3 )
		  || ( ! ValidarInxColunaVisivel( inxCV , NAO_VAZIO )) 
		  || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )))
		{
		   return TST_CondRetParm ;
		} /* if */
		
		pCarta = ( BAR_tppCarta ) LIS_ObterValor( vtColunaVisivel[ inxCV ] ) ;
		
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
		numLidos = LER_LerParametros( "i" , &inxCV ) ;
		
		if ( ( numLidos != 1 )
		  || ( ! ValidarInxColunaVisivel( inxCV , NAO_VAZIO )) )
		{
		   return TST_CondRetParm ;
		} /* if */
		
		LIS_IrInicioLista( vtColunaVisivel[ inxCV ] ) ;
		
		return TST_CondRetOK ;
	
	} /* fim ativa: Testar ir para o elemento inicial */
	
	/* Testar avançar elemento */
	
	else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
	{
	
		numLidos = LER_LerParametros( "iii" , &inxCV , &numElem ,
		                    &CondRetEsp ) ;
		
		if ( ( numLidos != 3 )
		  || ( ! ValidarInxColunaVisivel( inxCV , NAO_VAZIO )) )
		{
		   return TST_CondRetParm ;
		} /* if */
		
		return TST_CompararInt( CondRetEsp ,
		          LIS_AvancarElementoCorrente( vtColunaVisivel[ inxCV ] , numElem ) ,
		          "Condicao de retorno errada ao avancar" ) ;
	
	} /* fim ativa: Testar avançar elemento */

	return TST_CondRetNaoConhec;

} /* Fim função: TCV &Testar coluna visível */


  /*****  Código das funções encapsuladas no módulo  *****/
  
  /***********************************************************************
  *
  *  $FC Função: TCV -Validar indice de carta
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

} /* Fim função: TCV -Validar indice de carta */

/***********************************************************************
*
*  $FC Função: TCV -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TCV -Validar indice de lista */

  /***********************************************************************
  *
  *  $FC Função: TCV -Validar indice da coluna visível
  *
  ***********************************************************************/

int ValidarInxColunaVisivel(int inxCV, int Modo)
{

	if ((inxCV <  0)
		|| (inxCV >= DIM_VT_CV))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtColunaVisivel[inxCV] != 0)
		{
			return FALSE;
		} /* if */
	}
	else
	{
		if (vtColunaVisivel[inxCV] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TCV -Validar indice da coluna visível */




  /********** Fim do módulo de implementação: TCV Teste coluna visível **********/

