#include <stdio.h>
#include <math.h>
#define MAX 10 //capacidade da lista
#define AREA 100 //�rea de um painel
#define EFIC_MAX 0.22 //efici�ncia m�xima de um painel

typedef struct{
	int identificacao_painel // recebe o c�digo do painel de 5 d�gitos.
	int ativo; //recebe 0 {inativo} ou 1 {ativo}
	float geracao; //recebe gera��o em Watts
	float eficiencia; //recebe ((gera��o/AREA)/EFIC_MAX)/10
}Painel;

//Define o tamanho do vetor esepcial da matriz sim�trica de acordo com
//a quantidade de elementos existentes nela.
int Tam_Vet_Esp(int qtde_paineis){
	return ((qtde_paineis + (sqrt(qtde_paineis)) )/ 2);
}

typedef struct{
    int qtd_paineis; // Quantos paineis solares ter� o setor
    int identificacao_setor; // recebe o c�digo do setor de at� 4 d�gitos.
    Painel paineis[Tam_Vet_Esp(qtde_paineis)]; //matriz sim�trica de paineis pertencentes ao vetor
}Setor_Painel;

typedef struct {
    Setor_Painel Item[MAX]; //cria��o da lista
    int Prim, Ult; //auxiliares para primeira e �ltima posi��o da lista.
}Lista_est;

void Criar_Lista_Vazia (Lista_est *Setor_Aux){
    Setor_Aux->Prim = 0;
    Setor_Aux->Ult = Setor_Aux->Prim;
}

int Verifica_Lista_Vazia(Lista_est Setor_Aux){
    return (Setor_Aux.Prim == Setor_Aux.Ult);
}

int Verifica_Lista_Vazia(Lista_est Setor_Aux){
	return (Setor_Aux.Ult == MAX);
}
