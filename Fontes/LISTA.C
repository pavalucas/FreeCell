/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

#ifdef _DEBUG
   #include   "Generico.h"
   #include   "CONTA.H"
   #include   "CESPDIN.h"
   #include   "..\\tabelas\\IdTiposEspaco.def"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         #ifdef _DEBUG

         struct LIS_tagLista * pCabeca ;
               /* Ponteiro para a cabe�a da lista
               *
               *$ED Descri��o
               *   Todos os n�s da lista devem apontar para a respectiva cabe�a.
               *   Esse ponteiro corresponde a um identificador da lista para fins
               *   de verifica��o da integridade. */

         #endif

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

   } LIS_tpLista ;

/*****  Dados encapsulados no m�dulo  *****/

   #ifdef _DEBUG

   static char EspacoLixo[ 256 ] =
          "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
         /* Espa�o de dados lixo usado ao testar */

   #endif

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

#ifdef _DEBUG

   static LIS_tpCondRet VerificarNo( tpElemLista * pNo ) ;

#endif

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      LIS_tpLista * pLista = NULL ;

      #ifdef _DEBUG
         CNT_CONTAR( "Criar Lista" ) ;
      #endif

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Alocar lista continuou nula" ) ;
         #endif
         return NULL ;
      } /* if */

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pLista , LIS_TipoEspacoCabeca ) ;
      #endif

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

      #ifdef _DEBUG
         CNT_CONTAR( "Lista Alocada e Criada" ) ;
      #endif

      return pLista ;

   } /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "Destruir Lista" ) ;
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         CNT_CONTAR( "Esvaziar Lista" ) ;
         assert( pLista != NULL ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Entrou no loop de esvaziar" ) ;
         #endif
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;

      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         CNT_CONTAR( "Inserir Elemento Antes" ) ;
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inserir antes */
         pElem = CriarElemento( pLista , pValor ) ;

         if ( pElem == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Elemento Nulo em inserir antes" ) ;
            #endif
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Lista vazia em inserir antes" ) ;
            #endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Encadeou elemento antes" ) ;
               #endif
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Corrente eh origem em inserir antes" ) ;
               #endif
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;



      #ifdef _DEBUG
         CNT_CONTAR( "Inserir Elemento Apos" ) ;
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inserir ap�s */
         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Elemento Nulo em inserir apos" ) ;
            #endif
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Lista vazia em inserir apos" ) ;
            #endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Encadeou elemento apos" ) ;
               #endif
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Corrente eh fim em inserir apos" ) ;
               #endif
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         CNT_CONTAR( "Excluir Elemento" ) ;
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Lista Vazia em excluir elemento" ) ;
         #endif
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia � esquerda */

         if ( pElem->pAnt != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Desencadeou a esquerda em excluir elemento" ) ;
            #endif
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            #ifdef _DEBUG
               CNT_CONTAR( "Corrente eh origem em excluir elemento" ) ;
            #endif
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pElem->pProx != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Desencadeou a direita em excluir elemento" ) ;
            #endif
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Corrente eh fim em excluir elemento" ) ;
            #endif
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

   void * LIS_ObterValor( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "Obter Valor" ) ;
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Corrente eh nulo em obter valor" ) ;
         #endif
        return NULL ;
      } /* if */
      #ifdef _DEBUG
         CNT_CONTAR( "Retornou Valor de corrente em obter valor" ) ;
      #endif
      return pLista->pElemCorr->pValor ;

   } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

   void LIS_IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "Ir Inicio Lista" ) ;
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

   void LIS_IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "Ir Final Lista" ) ;
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) 
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
         CNT_CONTAR( "Avancar Elemento Corrente" ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Elemento corrente eh nulo em Avancar Elemento Corrente" ) ;
            #endif

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avan�ar para frente */

         if ( numElem > 0 )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Numero de elementos para avan�ar eh positivo" ) ;
            #endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Entrou no loop de avan�ar positivo" ) ;
               #endif

               if ( pElem == NULL )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "Avancou ate elemento nulo com avanco positivo" ) ;
                  #endif

                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Elemento final nao eh nulo no avanco positivo" ) ;
               #endif
               
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

         else if ( numElem < 0 )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Numero de elementos para avan�ar eh negativo" ) ;
            #endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Entrou no loop de avan�ar negativo" ) ;
               #endif

               if ( pElem == NULL )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "Avancou ate elemento nulo com avanco negativo" ) ;
                  #endif

                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Elemento final nao eh nulo no avanco negativo" ) ;
               #endif

               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */

         #ifdef _DEBUG
            CNT_CONTAR( "Nao houve avanco" ) ;
         #endif

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {

         if ( pElem->pValor == pValor )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim fun��o: LIS  &Procurar elemento contendo valor */


#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: LIS  &Verificar uma lista
*  ****/

   LIS_tpCondRet LIS_VerificarLista( void * pListaParm )
   {

      LIS_tpLista * pLista = NULL ;

      if ( LIS_VerificarCabeca( pListaParm ) != LIS_CondRetOK )
      {
         return LIS_CondRetErroEstrutura ;
      } /* if */

      CED_MarcarEspacoAtivo( pListaParm ) ;

      pLista = ( LIS_tpLista * ) ( pListaParm ) ;

      return VerificarNo( pLista->pOrigemLista ) ;

   } /* Fim fun��o: LIS  &Verificar uma lista */

#endif 

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: LIS  &Verificar um n� cabe�a
*  ****/

   LIS_tpCondRet LIS_VerificarCabeca( void * pCabecaParm )
   {

      LIS_tpLista * pLista = NULL ;
         
      /* Verifica o tipo do espa�o */

         if ( pCabecaParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar cabe�a inexistente." ) ;
            return LIS_CondRetErroEstrutura ;
         } /* if */

         if ( ! CED_VerificarEspaco( pCabecaParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espa�o acusou erro." ) ;
            return LIS_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoCabeca ,
              CED_ObterTipoEspaco( pCabecaParm ) ,
              "Tipo do espa�o de dados n�o � cabe�a de lista." ) != TST_CondRetOK )
         {
            return LIS_CondRetErroEstrutura ;
         } /* if */

         pLista = ( LIS_tpLista * )( pCabecaParm ) ;

      /* Verifica origem da lista */

         if ( pLista->pOrigemLista != NULL )
         {
            if ( TST_CompararPonteiro( pCabecaParm , pLista->pOrigemLista->pCabeca ,
                 "N� raiz n�o aponta para cabe�a." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else {
            if ( TST_CompararPonteiro( NULL , pLista->pElemCorr ,
                 "Lista vazia tem n� corrente n�o NULL." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      /* Verifica corrente */

         if ( pLista->pElemCorr != NULL )
         {
            if ( TST_CompararPonteiro( pCabecaParm , pLista->pElemCorr->pCabeca ,
                 "N� corrente n�o aponta para cabe�a." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else {
            if ( TST_CompararPonteiro( NULL , pLista->pOrigemLista ,
                 "Lista n�o vazia tem n� corrente NULL." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Verificar um n� cabe�a */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: LIS  &Verificar um n� de estrutura
*  ****/

   LIS_tpCondRet LIS_VerificarNo( void * pNoParm )
   {

      tpElemLista * pNo     = NULL ;
      LIS_tpLista   * pLista = NULL ;

      /* Verificar se � n� estrutural */

         if ( pNoParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar n� inexistente." ) ;
            return LIS_CondRetErroEstrutura ;

         } /* if */

         if ( ! CED_VerificarEspaco( pNoParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espa�o acusou erro." ) ;
            return LIS_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoNo ,
              CED_ObterTipoEspaco( pNoParm ) ,
              "Tipo do espa�o de dados n�o � n� de lista." ) != TST_CondRetOK )
         {
            return LIS_CondRetErroEstrutura ;
         } /* if */

         pNo     = ( tpElemLista * )( pNoParm ) ;
         pLista = pNo->pCabeca ;

      /* Verificar cabe�a */

         if ( pLista->pOrigemLista != NULL  )
         {
            if ( TST_CompararPonteiro( pLista , pLista->pOrigemLista->pCabeca ,
                 "N� n�o pertence � lista." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else
         {
            return TST_NotificarFalha( "N� pertence a lista vazia." ) ;
         } /* if */

      /* Verificar antecessor */

         if ( pNo->pAnt != NULL )
         {
            if (pNo->pAnt->pProx != pNo )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else
         {
            if ( TST_CompararPonteiro( pNo , pLista->pOrigemLista ,
                 "Primeiro n� da lista n�o � apontado por pOrigemLista." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      /* Verificar sucessor */

         if ( pNo->pProx != NULL )
         {
            if ( pNo->pProx->pAnt != pNo )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else
         {
            if ( TST_CompararPonteiro( pNo , pLista->pFimLista ,
                 "�ltimo n� da lista n�o � apontado por pFimLista." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Verificar um n� de estrutura */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: LIS  &Deturpar lista
*  ****/

   void LIS_Deturpar( void * pListaParm ,
                      LIS_tpModosDeturpacao ModoDeturpar )
   {

      LIS_tpLista * pLista = NULL ;

      if ( pListaParm == NULL )
      {
         return ;
      } /* if */

      pLista = ( LIS_tpLista * )( pListaParm ) ;

      switch ( ModoDeturpar ) {

      /* Modifica o tipo da cabe�a */

         case DeturpaTipoCabeca :
         {

            CED_DefinirTipoEspaco( pLista , CED_ID_TIPO_VALOR_NULO ) ;

            break ;

         } /* fim ativa: Modifica o tipo da cabe�a */

      /* Deturpa n� */

         default :

         if ( pLista->pElemCorr != NULL )
         {

            switch ( ModoDeturpar ) {

            /* Modifica tipo n� corrente */

            /* Anula ponteiro do elemento anterior */

               case DeturpaPtAntNulo :
               {

                  pLista->pElemCorr->pAnt = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro do elemento anterior */

            /* Anula ponteiro do elemento posterior  */

               case DeturpaPtProxNulo :
               {

                  pLista->pElemCorr->pProx = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro do elemento posterior */

            } /* fim seleciona: Deturpa n� */

            break ;

         } /* fim ativa: Deturpa n� */

      } /* fim seleciona: Raiz de LIS  &Deturpar lista */

   } /* Fim fun��o: LIS  &Deturpar lista */

#endif


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {
      #ifdef _DEBUG
         CNT_CONTAR("Liberar Elemento");
      #endif

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         #ifdef _DEBUG
            CNT_CONTAR("Elemento nao eh nulo em liberar elemento");
         #endif
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {
      tpElemLista * pElem ;

      #ifdef _DEBUG
         CNT_CONTAR("Criar Elemento");
      #endif

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR("Alocar elemento recebeu nulo");
         #endif

         return NULL ;
      } /* if */

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pElem , LIS_TipoEspacoNo ) ;
         pElem->pCabeca = pLista ;
      #endif

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      #ifdef _DEBUG
         CNT_CONTAR("Elemento Criado com Sucesso");
      #endif

      return pElem ;

   } /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {
      #ifdef _DEBUG
         CNT_CONTAR("Limpar Cabeca");
      #endif

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */


#ifdef _DEBUG

/*=======
*  $FC Fun��o: LIS  -Explorar verificando os n�s de uma lista
*
*  $ED Descri��o da fun��o
*     Percorre recursivamente a lista verificando os n�s � medida que forem
*     visitados. Caso seja encontrado alguma falha, a verifica��o ser�
*     suspensa. Portanto, no caso de falha, � poss�vel que nem todos
*     os n�s da lista sejam visitados.
*
***********************************************************************/

   LIS_tpCondRet VerificarNo( tpElemLista * pNo )
   {

      LIS_tpCondRet CondErro = LIS_CondRetOK ;

      if ( pNo == NULL )
      {
         return LIS_CondRetOK ;
      } /* if */

      CED_MarcarEspacoAtivo( pNo ) ;

      CondErro = LIS_VerificarNo( pNo ) ;

      if ( CondErro == LIS_CondRetOK )
      {
         CondErro = VerificarNo( pNo->pProx ) ;
      } /* if */

      return CondErro ;

   } /* Fim fun��o: LIS  -Explorar verificando os n�s de uma lista */

#endif

/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/
