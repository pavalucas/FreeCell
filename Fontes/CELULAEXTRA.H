#if ! defined( CELULAEXTRA_ )
#define CELULAEXTRA_ 
/***************************************************************************
*  $MCD Módulo de definição: CE  Celula extra 
*
*  Arquivo gerado:              CELULAEXTRA.h
*  Letras identificadoras:      CE
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Handel Scholze Marques
*
***************************************************************************/

#if defined( CELULAEXTRA_OWN )
   #define CELULAEXTRA_EXT
#else
   #define CELULAEXTRA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

#include "BARALHO.h"


/***********************************************************************
*
*  $TC Tipo de dados: CE Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de Célula Extra
*
***********************************************************************/
	typedef enum {

         CE_CondRetOK ,
               /* Concluiu corretamente */

         CE_CondRetListaVazia ,
               /* A lista não contém elementos */

         CE_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         CE_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         CE_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um elemento de lista */
		
         CE_CondRetListaCheia
               /* Quantidade máxima de elementos já foi atingida (4) */

   } CE_tpCondRet ;



/***********************************************************************
*  $FC Função: CE  &Criar Lista
*
*  $ED Descrição da função
*     Cria uma lista que terão as cartas que estão nas células extras
*
*  $FV Valor retornado
*     CE_CondRetOK
*     CE_CondRetFaltouMemoria
***********************************************************************/

	LIS_tppLista CE_CriarCelulasExtras(void);


/***********************************************************************
*  $FC Função: CE  &Inserir Carta
*
*  $ED Descrição da função
*     Insere uma carta em uma das células extras, no máximo teremos 4, 
*     caso já tenhamos 4 ela não é inserida e retornamos que a lista está cheia.
*
*  $EP Parâmetros
*     carta - ponteiro para a carta
*
*  $FV Valor retornado
*     CE_CondRetOK
*     CE_CondRetFaltouMemoria
*     CE_CondRetListaCheia
***********************************************************************/
	CE_tpCondRet CE_InserirCarta(LIS_tppLista lista, BAR_tppCarta carta); 


/***********************************************************************
*  $FC Função: CE  &Exibir
*
*  $ED Descrição da função
*     Mostra as cartas que estão nas células extras
*
*  $EP Parâmetros
*     lista - Ponteiro para as células extras
*
*  $FV Valor retornado
*     CondRetFimLista   - se foram imprimidos todos os elementos até 
*                         o final da lista
*     CondRetListaVazia - se a lista está vazia
***********************************************************************/

	CE_tpCondRet CE_ExibirCelulasExtras(LIS_tppLista lista);

/***********************************************************************
*  $FC Função: CE  &Remover Carta
*
*  $ED Descrição da função
*     Retira a carta que está na célula "posicao"
*
*  $EP Parâmetros
*     lista - Ponteiro para as células extras
*     posicao - posição da carta que deve ser retirada
*
*  $FV Valor retornado
*     CV_CondRetOK           - Se excluiu a carta especificada
*     CV_CondRetFimLista     - Se posicao ultrapassa a quantidade de elementos na lista
*     CE_CondRetNaoAchou     - Se posicao menor que zero ou maior que a quantidade máxima de elementos
*     CV_CondRetListaVazia   - Se a lista está vazia
*
***********************************************************************/

	CE_tpCondRet CE_RemoverCarta(LIS_tppLista lista, int posicao);


/***********************************************************************
*
*  $FC Função: CE  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista de células extras fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

	CE_tpCondRet CE_DestruirCelulasExtras(LIS_tppLista lista);

#undef CELULAEXTRA_EXT

/********** Fim do módulo de definição: CE  Celula extra **********/

#else
#endif






