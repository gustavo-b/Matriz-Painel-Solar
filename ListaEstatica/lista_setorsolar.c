#include <stdio.h>
#include <math.h>
#define MAX 10 //capacidade da lista
#define AREA 100 //área de um painel
#define EFIC_MAX 0.22 //eficiência máxima de um painel

typedef struct{
	int identificacao_painel // recebe o código do painel de 5 dígitos.
	int ativo; //recebe 0 {inativo} ou 1 {ativo}
	float geracao; //recebe geração em Watts
	float eficiencia; //recebe ((geração/AREA)/EFIC_MAX)/10
}Painel;

//Define o tamanho do vetor esepcial da matriz simétrica de acordo com
//a quantidade de elementos existentes nela.
int Tam_Vet_Esp(int qtde_paineis){
	return ((qtde_paineis + (sqrt(qtde_paineis)) )/ 2);
}

typedef struct{
    int qtd_paineis; // Quantos paineis solares terá o setor
    int identificacao_setor; // recebe o código do setor de até 4 dígitos.
    Painel paineis[Tam_Vet_Esp(qtde_paineis)]; //matriz simétrica de paineis pertencentes ao vetor
}Setor_Painel;

typedef struct {
    Setor_Painel Item[MAX]; //criação da lista
    int Prim, Ult; //auxiliares para primeira e última posição da lista.
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
