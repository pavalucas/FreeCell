/***************************************************************************
*  $MCI M�dulo de implementa��o: PAR  Partida
*
*  Arquivo gerado:              PARTIDA.c
*  Letras identificadoras:      PAR
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Miguel Corti
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include "CELULABASE.h"
#include "CELULAEXTRA.h"
#include "COLUNAVISIVEL.h"

#define TRUE 1
#define FALSE 0
#define NUMCV 8
#define NUMCB 4

/*****  Dados encapsulados no m�dulo  *****/

static LIS_tppLista listaDeListas;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/
static void PAR_MenuInicial();

static void PAR_InicializarPartida();

static void PAR_DividirBaralho(LIS_tppLista vetorBaralhos[], LIS_tppLista baralho);

static void PAR_Partida(LIS_tppLista listaDeListas);

static int PAR_MenuDeAcoes();

static void PAR_ImprimirPartida(LIS_tppLista listaDeListas);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: CV  &Criar coluna vis�vel
*  ****/

void PAR_MenuInicial()
{
	printf("Bem Vindo ao Free Cell!\n");
	printf("Para iniciar um novo jogo, aperte <enter>!\n");
	getchar();
	printf("OK!\n");
	PAR_InicializarPartida();
}

void PAR_InicializarPartida()
{
	int i; // vari�vel para iterar
	LIS_tppLista listaDeListas;
	LIS_tppLista celulasExtras;
	LIS_tppLista vetorDeColunas[NUMCV];
	LIS_tppLista vetorBaralhos[NUMCV];
	LIS_tppLista vetorDeCBs[NUMCB];
	LIS_tppLista baralho;


	/* Criando a Lista de Listas e progressivamente inserindo as listas conforme s�o criadas */
	listaDeListas = LIS_CriarLista(NULL);

	/* Criando e embaralhando o baralho */
	baralho = BAR_CriarBaralho();
	if(BAR_Embaralhar(baralho) != LIS_CondRetOK)
	{
		printf("Erro embaralhando");
	}

	/* Criando e inicializando as colunas visiveis */
	PAR_DividirBaralho(vetorBaralhos, baralho);
	i = 0;
	while (i < NUMCV)
	{
		vetorDeColunas[i] = CV_CriarColunaVisivel();
		CV_InicializarColunaVisivel(vetorDeColunas[i], vetorBaralhos[i]);
		LIS_InserirElementoApos(listaDeListas, vetorDeColunas[i]);
		i++;
	}

	/* Criando celulas base */
	i = 0;
	while (i < NUMCB)
	{
		vetorDeCBs[i] = CB_CriarCelulaBase();
		LIS_InserirElementoApos(listaDeListas, vetorDeColunas[i]);
		i++;
	}

	/* Criando lista de celulas extra */
	celulasExtras = CE_CriarCelulasExtras();
	LIS_InserirElementoApos(listaDeListas, celulasExtras);

	PAR_Partida(listaDeListas);

}

void PAR_DividirBaralho(LIS_tppLista vetorBaralhos[], LIS_tppLista baralho)
{
	int i = 0;
	CV_tpCondRet condRetAvancar = CV_CondRetOK;
	LIS_IrInicioLista(baralho);

	while (i < NUMCV)
	{
		int j, maxCartas;
		BAR_tppCarta cartaAtual;
		vetorBaralhos[i] = LIS_CriarLista(BAR_LiberarCarta);

		if(i < 4)
		{
			maxCartas = 7;
		}// As primeiras quatro colunas come�am com 7 cartas
		else
		{
			maxCartas = 6;
		}// As ultimas quatro colunas come�am com 6 cartas
		
		j = 0;
		while (j < maxCartas || condRetAvancar != CV_CondRetFimLista)
		{
			cartaAtual = (BAR_tppCarta)LIS_ObterValor(baralho);
			LIS_InserirElementoApos(vetorBaralhos[i], cartaAtual);
			condRetAvancar = (CV_tpCondRet) LIS_AvancarElementoCorrente(baralho, 1);
		}

		i++;
	}
}

void PAR_Partida(LIS_tppLista listaDeListas)
{
	//int acao;
	
	

	printf("****** Inicio de Jogo ******\n\n");
	PAR_ImprimirPartida(listaDeListas);


	//acao = PAR_MenuDeAcoes();

}

int PAR_MenuDeAcoes()
{
	int acao;
	printf("****** Menu de Acoes ******\n");
	printf("1. Exibir o Jogo todo\n");
	printf("2. Desistir da Partida\n");
	printf("Digite o numero correspondente para realizar a acao desejada\n");
	scanf("%d", &acao);

}

void PAR_ImprimirPartida(LIS_tppLista listaDeListas)
{
	/* Imprimindo as Celulas Extras */
	LIS_IrInicioLista(listaDeListas);

	printf("Celulas Extras: ");
	LIS_AvancarElementoCorrente(listaDeListas, 12);
	CE_ExibirCelulasExtras((LIS_tppLista) LIS_ObterValor(listaDeListas));

	printf("\n\n");

	/* Imprimindo a primeira carta do topo das celulas bases */
	LIS_IrInicioLista(listaDeListas);

	printf("Celulas Base: 1. ");
	LIS_AvancarElementoCorrente(listaDeListas, 8);
	CB_ExibirCelulaBase((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("2. ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CB_ExibirCelulaBase((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("3. ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CB_ExibirCelulaBase((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("4. ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CB_ExibirCelulaBase((LIS_tppLista) LIS_ObterValor(listaDeListas));
	
	printf("\n\n");

	/* Imprimindo as colunas visiveis */
	LIS_IrInicioLista(listaDeListas);

	printf("Coluna 01: ");
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));

	printf("Coluna 02: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));

	printf("Coluna 03: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));

	printf("Coluna 04: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));

	printf("Coluna 05: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));

	printf("Coluna 06: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));

	printf("Coluna 07: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));

	printf("Coluna 08: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));

	printf("\n\n");
}

int main()
{
	PAR_MenuInicial();

	return 0;
}