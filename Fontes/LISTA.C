/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
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
               /* Ponteiro para a cabeça da lista
               *
               *$ED Descrição
               *   Todos os nós da lista devem apontar para a respectiva cabeça.
               *   Esse ponteiro corresponde a um identificador da lista para fins
               *   de verificação da integridade. */

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
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
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
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tpLista ;

/*****  Dados encapsulados no módulo  *****/

   #ifdef _DEBUG

   static char EspacoLixo[ 256 ] =
          "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
         /* Espaço de dados lixo usado ao testar */

   #endif

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

#ifdef _DEBUG

   static LIS_tpCondRet VerificarNo( tpElemLista * pNo ) ;

#endif

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
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

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "Destruir Lista" ) ;
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
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

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
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

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;



      #ifdef _DEBUG
         CNT_CONTAR( "Inserir Elemento Apos" ) ;
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inserir após */
         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Elemento Nulo em inserir apos" ) ;
            #endif
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

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

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
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

      /* Desencadeia à esquerda */

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

      /* Desencadeia à direita */

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

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
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

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void LIS_IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "Ir Inicio Lista" ) ;
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void LIS_IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "Ir Final Lista" ) ;
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
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

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Numero de elementos para avançar eh positivo" ) ;
            #endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Entrou no loop de avançar positivo" ) ;
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

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Numero de elementos para avançar eh negativo" ) ;
            #endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Entrou no loop de avançar negativo" ) ;
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

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         #ifdef _DEBUG
            CNT_CONTAR( "Nao houve avanco" ) ;
         #endif

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
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

   } /* Fim função: LIS  &Procurar elemento contendo valor */


#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar uma lista
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

   } /* Fim função: LIS  &Verificar uma lista */

#endif 

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar um nó cabeça
*  ****/

   LIS_tpCondRet LIS_VerificarCabeca( void * pCabecaParm )
   {

      LIS_tpLista * pLista = NULL ;
         
      /* Verifica o tipo do espaço */

         if ( pCabecaParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
            return LIS_CondRetErroEstrutura ;
         } /* if */

         if ( ! CED_VerificarEspaco( pCabecaParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            return LIS_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoCabeca ,
              CED_ObterTipoEspaco( pCabecaParm ) ,
              "Tipo do espaço de dados não é cabeça de lista." ) != TST_CondRetOK )
         {
            return LIS_CondRetErroEstrutura ;
         } /* if */

         pLista = ( LIS_tpLista * )( pCabecaParm ) ;

      /* Verifica origem da lista */

         if ( pLista->pOrigemLista != NULL )
         {
            if ( TST_CompararPonteiro( pCabecaParm , pLista->pOrigemLista->pCabeca ,
                 "Nó raiz não aponta para cabeça." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else {
            if ( TST_CompararPonteiro( NULL , pLista->pElemCorr ,
                 "Lista vazia tem nó corrente não NULL." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      /* Verifica corrente */

         if ( pLista->pElemCorr != NULL )
         {
            if ( TST_CompararPonteiro( pCabecaParm , pLista->pElemCorr->pCabeca ,
                 "Nó corrente não aponta para cabeça." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else {
            if ( TST_CompararPonteiro( NULL , pLista->pOrigemLista ,
                 "Lista não vazia tem nó corrente NULL." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Verificar um nó cabeça */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar um nó de estrutura
*  ****/

   LIS_tpCondRet LIS_VerificarNo( void * pNoParm )
   {

      tpElemLista * pNo     = NULL ;
      LIS_tpLista   * pLista = NULL ;

      /* Verificar se é nó estrutural */

         if ( pNoParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar nó inexistente." ) ;
            return LIS_CondRetErroEstrutura ;

         } /* if */

         if ( ! CED_VerificarEspaco( pNoParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            return LIS_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoNo ,
              CED_ObterTipoEspaco( pNoParm ) ,
              "Tipo do espaço de dados não é nó de lista." ) != TST_CondRetOK )
         {
            return LIS_CondRetErroEstrutura ;
         } /* if */

         pNo     = ( tpElemLista * )( pNoParm ) ;
         pLista = pNo->pCabeca ;

      /* Verificar cabeça */

         if ( pLista->pOrigemLista != NULL  )
         {
            if ( TST_CompararPonteiro( pLista , pLista->pOrigemLista->pCabeca ,
                 "Nó não pertence à lista." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else
         {
            return TST_NotificarFalha( "Nó pertence a lista vazia." ) ;
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
                 "Primeiro nó da lista não é apontado por pOrigemLista." ) != TST_CondRetOK )
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
                 "Último nó da lista não é apontado por pFimLista." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Verificar um nó de estrutura */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Deturpar lista
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

      /* Modifica o tipo da cabeça */

         case DeturpaTipoCabeca :
         {

            CED_DefinirTipoEspaco( pLista , CED_ID_TIPO_VALOR_NULO ) ;

            break ;

         } /* fim ativa: Modifica o tipo da cabeça */

      /* Deturpa nó */

         default :

         if ( pLista->pElemCorr != NULL )
         {

            switch ( ModoDeturpar ) {

            /* Modifica tipo nó corrente */

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

            } /* fim seleciona: Deturpa nó */

            break ;

         } /* fim ativa: Deturpa nó */

      } /* fim seleciona: Raiz de LIS  &Deturpar lista */

   } /* Fim função: LIS  &Deturpar lista */

#endif


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
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

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
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

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
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

   } /* Fim função: LIS  -Limpar a cabeça da lista */


#ifdef _DEBUG

/*=======
*  $FC Função: LIS  -Explorar verificando os nós de uma lista
*
*  $ED Descrição da função
*     Percorre recursivamente a lista verificando os nós à medida que forem
*     visitados. Caso seja encontrado alguma falha, a verificação será
*     suspensa. Portanto, no caso de falha, é possível que nem todos
*     os nós da lista sejam visitados.
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

   } /* Fim função: LIS  -Explorar verificando os nós de uma lista */

#endif

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/
