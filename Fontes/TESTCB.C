/***************************************************************************
*  $MCI Módulo de implementação: TCB Teste célula base
*
*  Arquivo gerado:              TESTCB.c
*  Letras identificadoras:      TCB
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Miguel Corti
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include 	"CELULABASE.H"

static const char CRIAR_CARTA_CMD        [ ] = "=criarcarta";
static const char CRIAR_CB_CMD           [ ] = "=criarcelulabase";
static const char INSERIR_CMD            [ ] = "=inserircarta";
static const char DESTRUIR_CMD           [ ] = "=destruircelulabase";



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VT_CARTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[DIM_VT_LISTA];
BAR_tppCarta   vtCartas[DIM_VT_CARTA];


/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxLista(int inxLista, int Modo);

static int ValidarInxCarta(int inxCarta, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TCB &Testar célula base
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =criarcarta                       <inxCarta>    <naipe>      <numero>
*	  =criarcelulabase                  <inxCelula>
*     =inserircarta                     <inxCelula>   <inxCarta>   <condRetEsp>
*     =destruircelulabase               <inxCelula>
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	int inxCelula = -1,
		inxCarta = -1,
		numLidos = -1,
		CondRetEsp = -1;

	TST_tpCondRet CondRet;


	/* Testar CriarCarta*/

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

	/* Testar CriarCelulaBase */
	
	if (strcmp(ComandoTeste, CRIAR_CB_CMD) == 0)
	{
		numLidos = LER_LerParametros("i",
			&inxCelula);

		if ((numLidos != 1)
			|| (!ValidarInxLista(inxCelula, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		vtListas[inxCelula] =
			CB_CriarCelulaBase();

		return TST_CompararPonteiroNulo(1, vtListas[inxCelula],
			"Erro em ponteiro de nova celula.");

	} /* fim ativa: Testar CriarCelulaBase */

	/* Testar Inserir */

	if(strcmp(ComandoTeste, INSERIR_CMD) == 0)
	{
		numLidos = LER_LerParametros("iii",
			&inxCelula, &inxCarta, &CondRetEsp);

		if ((numLidos != 3)
			|| (!ValidarInxLista(inxCelula, NAO_VAZIO))
			|| (!ValidarInxCarta(inxCarta, NAO_VAZIO)) )
		{
			return TST_CondRetParm;
		}
		
		CondRet = CB_InserirCarta(vtListas[inxCelula], vtCartas[inxCarta]);

		return TST_CompararInt( CondRetEsp ,
                      CondRet ,
                     "Condicao de retorno errada ao inserir."   ) ;
	} /* fim ativa: Testar Inserir */

	/* Testar Destruir */

	if(strcmp(ComandoTeste, DESTRUIR_CMD) == 0)
	{
		numLidos = LER_LerParametros("i",
			&inxCelula);

		if ((numLidos != 1)
			|| (!ValidarInxLista(inxCelula, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		}
		
		CondRet = CB_DestruirCelulaBase(vtListas[inxCelula]);
		vtListas[inxCelula] = NULL;

		return TST_CondRetOK;
	} /* fim ativa: Testar Destruir */


	return TST_CondRetNaoConhec;

} /* Fim função: TCB &Testar célula base */


  /*****  Código das funções encapsuladas no módulo  *****/

  /***********************************************************************
  *
  *  $FC Função: TCB -Validar indice de lista
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

} /* Fim função: TCB -Validar indice de lista */

  /***********************************************************************
  *
  *  $FC Função: TCB -Validar indice de carta
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

} /* Fim função: TCB -Validar indice de lista */


  /********** Fim do módulo de implementação: TCB Teste célula base **********/

