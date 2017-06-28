/***************************************************************************
*  $MCI Módulo de implementação: PAR  Partida
*
*  Arquivo gerado:              PARTIDA.c
*  Letras identificadoras:      PAR
*
*  Projeto: INF 1301 / FreeCell
*  Autores: Handel Scholze e Miguel Corti
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <string.h>
#include   <stdlib.h>
#include "CELULABASE.h"
#include "CELULAEXTRA.h"
#include "COLUNAVISIVEL.h"

#define TRUE 1
#define FALSE 0
#define NUMCV 8
#define NUMCB 4
#define MAX_ERROS 2

/*****  Dados encapsulados no módulo  *****/

static LIS_tppLista listaDeListas;
static int contadorDica;

/***** Protótipos das funções encapuladas no módulo *****/
static void PAR_MenuInicial();

static void PAR_InicializarPartida();

static void PAR_DividirBaralho(LIS_tppLista vetorBaralhos[], LIS_tppLista baralho);

static void PAR_Partida(LIS_tppLista listaDeListas);

static int PAR_MenuDeAcoes();

static void PAR_ImprimirPartida(LIS_tppLista listaDeListas);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: CV  &Criar coluna visível
*  ****/

void PAR_LiberarLista(void* lista)
{
    CV_DestruirColunaVisivel((LIS_tppLista) lista);
}

void PAR_MenuInicial()
{
	contadorDica = 0;
	printf("Bem Vindo ao Free Cell!\n");
	printf("Para iniciar um novo jogo, aperte <enter>!\n");
	getchar();
	
}

void PAR_InicializarPartida()
{
	//BAR_tppCarta carta = BAR_CriarCarta(1, 2);
	int i; // variáveis para iterar
	LIS_tppLista listaDeListas;
	LIS_tppLista celulasExtras;
	LIS_tppLista vetorDeColunas[NUMCV];
	LIS_tppLista vetorBaralhos[NUMCV];
	LIS_tppLista vetorDeCBs[NUMCB];
	LIS_tppLista baralho;


	/* Criando a Lista de Listas e progressivamente inserindo as listas conforme são criadas */
	listaDeListas = LIS_CriarLista(PAR_LiberarLista);

	/* Criando e embaralhando o baralho */
	baralho = BAR_CriarBaralho();

	if(BAR_Embaralhar(baralho) != LIS_CondRetOK)
	{
		printf("Erro embaralhando");
	}


	/* Criando e inicializando as colunas visiveis */
	PAR_DividirBaralho(vetorBaralhos, baralho);
	
	LIS_IrInicioLista(baralho);

	i = 0;

	while(i < NUMCV)
	{
		vetorDeColunas[i] = CV_CriarColunaVisivel();

		CV_InicializarColunaVisivel(vetorBaralhos[i], vetorDeColunas[i]);

		LIS_InserirElementoApos(listaDeListas, vetorDeColunas[i]);
		i++;
	}

	/* Criando celulas base */
	i = 0;
	while (i < NUMCB)
	{
		vetorDeCBs[i] = CB_CriarCelulaBase();
		LIS_InserirElementoApos(listaDeListas, vetorDeCBs[i]);
		i++;
	}

	/* Criando lista de celulas extra */
	celulasExtras = CE_CriarCelulasExtras();
	LIS_InserirElementoApos(listaDeListas, celulasExtras);

	printf("****** Inicio de Jogo ******\n\n");
	PAR_ImprimirPartida(listaDeListas);

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
		}// As primeiras quatro colunas começam com 7 cartas
		else
		{
			maxCartas = 6;
		}// As ultimas quatro colunas começam com 6 cartas
		
		for(j=0; j < maxCartas && condRetAvancar == CV_CondRetOK; j++)
		{
			cartaAtual = (BAR_tppCarta)LIS_ObterValor(baralho);
			LIS_InserirElementoApos(vetorBaralhos[i], cartaAtual);
			condRetAvancar = (CV_tpCondRet) LIS_AvancarElementoCorrente(baralho, 1);
		}

		i++;
	}
}

int PAR_ChecarMovimento(LIS_tppLista listaDeListas, int num1, int num2, char ini[], char fim[])
{
	LIS_tppLista colunaIniEscolhida;
	LIS_tppLista colunaFimEscolhida;
	BAR_tppCarta cartaIniEscolhida;
	BAR_tppCarta cartaAlocada;
	int cmdInvalido = TRUE;
	int numero, naipe;

	LIS_IrInicioLista(listaDeListas);

	/* Se o jogador está querendo tirar uma carta de uma coluna visivel */
	if(strcmp(ini, "cv") == 0 && num1<9)
	{			
		LIS_AvancarElementoCorrente(listaDeListas, num1-1);
		colunaIniEscolhida = LIS_ObterValor(listaDeListas);
		LIS_IrFinalLista(colunaIniEscolhida);
		cartaIniEscolhida = LIS_ObterValor(colunaIniEscolhida);

		naipe = BAR_ObterNaipe( cartaIniEscolhida );
		numero = BAR_ObterNumero( cartaIniEscolhida );
		cartaAlocada = BAR_CriarCarta(naipe, numero);
		
		/* Se estiver tentando mover para outra coluna visivel */
		if(strcmp(fim, "cv") == 0 && num2<9)
		{
			cmdInvalido = FALSE;

			LIS_IrInicioLista(listaDeListas);
			LIS_AvancarElementoCorrente(listaDeListas, num2-1);
			colunaFimEscolhida = LIS_ObterValor(listaDeListas);

			if(CV_InserirCarta(colunaFimEscolhida, cartaAlocada)==CV_CondRetOK)
			{
				CV_RemoverCarta(colunaIniEscolhida);
				printf("\nTroca de coluna feita com sucesso!\n\n");
			}
			else
			{
				printf("Nao eh possivel colocar a carta da coluna %d na coluna %d\n", num1, num2);
				contadorDica++;
				if(contadorDica >= MAX_ERROS)
				{
					printf("Dica: tome cuidado com as cores dos naipes das cartas, elas tem que intercalar!\n");
					contadorDica = 0;
				}
				printf("\n");
				BAR_LiberarCarta(cartaAlocada);
			}
		}

		/* Se estiver tentando mover para uma celula extra */
		else if(strcmp(fim, "ce")==0 && num2 < 5)
		{
			cmdInvalido = FALSE;

			LIS_IrFinalLista(listaDeListas);
			colunaFimEscolhida = LIS_ObterValor(listaDeListas);
			if(CE_InserirCarta(colunaFimEscolhida, cartaAlocada) == CE_CondRetOK)
			{
				CV_RemoverCarta(colunaIniEscolhida);
				printf("\nCarta colocada em Celula Extra com sucesso!\n\n");
			}
			else
			{
				printf("Nao eh possivel colocar a carta da coluna %d na celula %d\n\n", num1, num2);
				contadorDica++;
				BAR_LiberarCarta(cartaAlocada);
			}
		}

		/* Se estiver tentando mover para uma celula base */
		else if(strcmp(fim, "cb")==0 && num2<5)
		{
			cmdInvalido = FALSE;

			LIS_IrInicioLista(listaDeListas);
			LIS_AvancarElementoCorrente(listaDeListas, 7+num2);
			colunaFimEscolhida = LIS_ObterValor(listaDeListas);
			if(CB_InserirCarta(colunaFimEscolhida, cartaAlocada) == CB_CondRetOK)
			{
				CV_RemoverCarta(colunaIniEscolhida);
				printf("\nCarta inserida na Celula Base com sucesso!\n\n");
			}
			else
			{
				printf("Nao eh possivel colocar a carta da coluna %d na celula base %d\n", num1, num2);
				contadorDica++;
				if(contadorDica >= MAX_ERROS)
				{
					printf("Lembre: na base as cartas tem que ser de mesmo naipe para cada celula e estar em ordem!\n");
					contadorDica = 0;
				}
				printf("\n");
				BAR_LiberarCarta(cartaAlocada);
			}
		}
	}

	/* Se o jogador está querendo tirar uma carta de uma celula extra */
	else if(strcmp(ini, "ce") == 0 && num1 < 5)
	{
		LIS_IrFinalLista(listaDeListas);
		colunaIniEscolhida = LIS_ObterValor(listaDeListas);
		LIS_IrInicioLista(colunaIniEscolhida);
		LIS_AvancarElementoCorrente(colunaIniEscolhida, num1-1);
		cartaIniEscolhida = LIS_ObterValor(colunaIniEscolhida);

		naipe = BAR_ObterNaipe( cartaIniEscolhida );
		numero = BAR_ObterNumero( cartaIniEscolhida );
		cartaAlocada = BAR_CriarCarta(naipe, numero);

		/* Se estiver tentando mover para uma coluna visivel */
		if(strcmp(fim, "cv") == 0 && num2<9)
		{
			cmdInvalido = FALSE;

			LIS_IrInicioLista(listaDeListas);
			LIS_AvancarElementoCorrente(listaDeListas, num2-1);
			colunaFimEscolhida = LIS_ObterValor(listaDeListas);

			if(CV_InserirCarta(colunaFimEscolhida, cartaAlocada)==CV_CondRetOK)
			{
				CV_RemoverCarta(colunaIniEscolhida);
				printf("\nCarta colocada na coluna com sucesso!\n\n");
			}
			else
			{
				printf("Nao eh possivel colocar a carta da celula %d na coluna %d", num1, num2);
				contadorDica++;
				if(contadorDica >= MAX_ERROS)
				{
					printf("Dica: tome cuidado com as cores dos naipes das cartas, elas tem que intercalar!\n");
					contadorDica = 0;
				}
				printf("\n");
				BAR_LiberarCarta(cartaAlocada);
			}
		}

		/* Se estiver tentando mover para uma celula base */
		else if(strcmp(fim, "cb") == 0  && num2 < 5)
		{
			cmdInvalido = FALSE;
			LIS_IrInicioLista(listaDeListas);
			LIS_AvancarElementoCorrente(listaDeListas, 7+num2);
			colunaFimEscolhida = LIS_ObterValor(listaDeListas);
			if(CB_InserirCarta(colunaFimEscolhida, cartaAlocada) == CB_CondRetOK)
			{
				CE_RemoverCarta(colunaIniEscolhida, num2-1);
				printf("\nCarta inserida na Celula Base com sucesso!\n\n");
			}
			else
			{
				printf("Nao eh possivel colocar a carta da celula %d na celula base %d\n", num1, num2);
				contadorDica++;
				if(contadorDica >= MAX_ERROS)
				{
					printf("Lembre: na base as cartas tem que ser de mesmo naipe para cada celula e estar em ordem!\n");
					contadorDica = 0;
				}
				printf("\n");
				BAR_LiberarCarta(cartaAlocada);
			}
		}
	}

	return cmdInvalido;
}


void PAR_Partida(LIS_tppLista listaDeListas)
{
	while(TRUE)
	{
		char ini[100];
		char fim[100];
		int num1;
		int num2;
		char acao;

		printf("****** Menu de Acoes ******\n");
		printf("1. Exibir o Jogo todo\n");
		printf("2. Movimentar cartas\n");
		printf("5. Desistir da Partida\n");
		printf("Digite o numero correspondente para realizar a acao desejada\n");
		scanf(" %c", &acao);
		
		/* Confere a opcao escolhida */
		if(acao == '1')
		{
			PAR_ImprimirPartida(listaDeListas);
		}
		else if(acao == '5')
		{
			break;
		}
		else if(acao == '2')
		{
			int cmdInvalido;
			scanf("%s %d %s %d", ini, &num1, fim, &num2);
			
			cmdInvalido = PAR_ChecarMovimento(listaDeListas, num1, num2, ini, fim);
			
			/* Checa se o comando foi invalido em algum momento*/
			if(cmdInvalido)
			{
				printf("Comando nao existente, qualquer duvida siga as instrucoes do leia-me.\n\n");
			}
		}
		else
		{
			printf("Comando nao existente, digite 1, 2 ou 5.\n\n");
		}
	}

	LIS_DestruirLista(listaDeListas);
	exit(1);
	//PAR_Partida(listaDeListas);
}

void PAR_ImprimirPartida(LIS_tppLista listaDeListas)
{
	/* Imprimindo as Celulas Extras */
	LIS_IrInicioLista(listaDeListas);


	printf("\n\nCelulas Extras: ");
	LIS_AvancarElementoCorrente(listaDeListas, 12);
	CE_ExibirCelulasExtras((LIS_tppLista) LIS_ObterValor(listaDeListas));

	printf("\n\n");

	/* Imprimindo a primeira carta do topo das celulas bases */
	LIS_IrInicioLista(listaDeListas);

	printf("Celulas Base:\n1. ");
	LIS_AvancarElementoCorrente(listaDeListas, 8);
	CB_ExibirCelulaBase((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n2. ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CB_ExibirCelulaBase((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n3. ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CB_ExibirCelulaBase((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n4. ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CB_ExibirCelulaBase((LIS_tppLista) LIS_ObterValor(listaDeListas));
	
	printf("\n\n\n");



	/* Imprimindo as colunas visiveis */
	LIS_IrInicioLista(listaDeListas);

	printf("Coluna 01: ");
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n");

	printf("Coluna 02: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n");

	printf("Coluna 03: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n");

	printf("Coluna 04: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n");

	printf("Coluna 05: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n");

	printf("Coluna 06: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n");

	printf("Coluna 07: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n");

	printf("Coluna 08: ");
	LIS_AvancarElementoCorrente(listaDeListas, 1);
	CV_ExibirColunaVisivel((LIS_tppLista) LIS_ObterValor(listaDeListas));
	printf("\n");

	printf("\n\n");
}

int main()
{
	PAR_MenuInicial();
	PAR_InicializarPartida();

	return 0;
}