#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define TAM 4 //Definição do tamanho das colunas e linhas das matrizes.
#define MAX 10 //capacidade da lista
#define AREA 100 //área de um painel
#define EFIC_MAX 0.22 //eficiência máxima de um painel
#define LIMITE 5 //Máximo de vezes que o usuário pode errar uma opção do Menu

/**	Componentes:
*   Mat:			Nome:
*   201602493		Gustavo Henrique da Silva Batista
*   201609824		Saulo de Araújo Calixto
*
*	Este programa realiza o controle de dados
*	heterogêneos, utilizando como tema o gerenciamentos
*	dos painéis solares de uma companhia de energia solar,
*	dispostas em setores, utilizando-se de matrizes
*	para sua representação.
*	TAD: Dados heterogêneos
*	1 - Criar lista vazia
*	2 - Inserir setor na lista
*	3 - Remover setor da lista
*	4 - Consultar setor da lista
*	5 - Exibe a lista
*	6 - Exibir os setores com baixa eficiencia
*	7 - Redistribuir de acordo com a eficiencia de cada setor
*	8 - Gerar um relatório do setor
**/
typedef struct{
	int identificacao_painel; // recebe o código do painel de 5 dígitos.
	int ativo; //recebe 0 {inativo} ou 1 {ativo}
	float geracao; //recebe geração em Watts
	float eficiencia; //recebe ((geração/AREA)/EFIC_MAX)/10
}Painel;

//Define o tamanho do vetor esepcial da matriz simétrica de acordo com
//a quantidade de elementos existentes nela.
int Tam_Vet_Esp(int qtde_paineis){
	return ((qtde_paineis + (sqrt(qtde_paineis)) ) / 2);
}

typedef struct{
	int identificacao_setor; // recebe o código do setor de até 4 dígitos.
    Painel paineis[TAM][TAM]; //matriz simétrica de paineis pertencentes ao vetor
    float eficiencia_setor; //quantidade de energia gerada pelo setor
}Setor_Painel;

typedef struct {
    Setor_Painel Item[MAX];
    int Inicio, Fim, Total;
} Fila_est;

typedef struct {
    Setor_Painel Item[MAX];
    int Topo;
} Pilha_est;

void Criar_Fila_Vazia(Fila_est* F)
{
    F->Inicio = 0;
    F->Fim = 0;
    F->Total = 0;
}

void Criar_Pilha_Vazia(Pilha_est* P)
{
    P->Topo = 0;
}

int Verifica_Fila_Vazia(Fila_est F)
{
    return(F.Inicio == F.Fim);
}

int Verifica_Pilha_Vazia(Pilha_est P)
{
    return(P.Topo == 0);
}

int Verifica_Fila_Cheia(Fila_est F)
{
    return((F.Fim + 1) % MAX == F.Fim );
}

int Verifica_Pilha_Cheia(Pilha_est P)
{
    return(P.Topo == MAX);
}

void Enfileirar(Fila_est* F, Setor_Painel setor)
{
    if(Verifica_Fila_Cheia(*F)) {
        printf("Não podem ser inseridos mais setores, fila cheia.");
    }
    else {
        F->Item[F->Fim] = setor;
        F->Fim = (F->Fim + 1) % MAX;
        F->Total++;
    }
}

void Empilhar(Pilha_est* P, Setor_Painel setor)
{
    if(Verifica_Pilha_Cheia(*P)) {
        printf("Não podem ser inseridos mais setores, pilha cheia.");
    }
    else {
        P->Item[P->Topo] = setor;
        P->Topo++;
    }
}

void Desenfileirar(Fila_est *F, Setor_Painel *setor)
{
    if(Verifica_Fila_Vazia(*F)) {
        printf("Nao há setores na fila.");
    }
    else {
        *setor = F->Item[F->Inicio];
        F->Inicio = (F->Inicio + 1) % MAX;
        F->Total--;
    }
}

void Desempilhar(Pilha_est *P, Setor_Painel *setor)
{
    if(Verifica_Pilha_Vazia(*P)) {
        printf("Nao há setores na pilha.");
    }
    else {
        P->Topo--;
        *setor = P->Item[P->Topo];
    }
}
