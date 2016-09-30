#include <stdio.h>
#include <math.h>
#define TAM 4 //Definição do tamanho das colunas e linhas das matrizes.
#define MAX 10 //capacidade da lista
#define AREA 100 //área de um painel
#define EFIC_MAX 0.22 //eficiência máxima de um painel

typedef struct{
	int identificacao_painel; // recebe o código do painel de 5 dígitos.
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
	int identificacao_setor; // recebe o código do setor de até 4 dígitos.
    Painel paineis[TAM][TAM]; //matriz simétrica de paineis pertencentes ao vetor
    float geracao_setor; //quantidade de energia gerada pelo setor
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

int Verifica_Lista_Cheia(Lista_est Setor_Aux){
	return (Setor_Aux.Ult == MAX);
}

float Calc_Efic(float geracao){
	return (((geracao / AREA) / EFIC_MAX) / 10);
}

void Insere_Elemento_Lista(Lista_est *Setor_Aux, Setor_Painel setor){

	int p;

	if(Verifica_Lista_Cheia(*Setor_Aux)){
		printf("Lista lotada, não pode ser adicionado mais dados");
	}
	else {
		p = Setor_Aux->Prim;

		while ((p < Setor_Aux->Ult) && (setor.geracao_setor > Setor_Aux->Item[p].geracao_setor)) {
			p++;
		}
		if (p == Setor_Aux->Ult){
			Setor_Aux->Item[p] = setor;
			Setor_Aux->Ult++;
		}
		else {
			if (setor.geracao_setor != Setor_Aux->Item[p].geracao_setor){
				int i;
				for(i = Setor_Aux->Ult; i > p; i--){
					Setor_Aux->Item[i] = Setor_Aux->Item[i-1];
				}
				Setor_Aux->Item[p] = setor;
				Setor_Aux->Ult++;
			}
			else printf(" ELEMENTO JÁ EXISTE NA LISTA \n");
		}
	}
}

void Remove_Elemento_Lista(Lista_est *Setor_Aux, Setor_Painel *setor){

	int p, i;

	if(Verifica_Lista_Vazia(*Setor_Aux)){
		printf("A lista já está vazia, impossível remover elemento.");
	}
	else {
		p = Setor_Aux->Prim;

		while ((p < Setor_Aux->Ult) && (setor->geracao_setor > Setor_Aux->Item[p].geracao_setor)) {
			p++;
		}
		if (p == Setor_Aux->Ult || (setor->geracao_setor != Setor_Aux->Item[p].geracao_setor)){
			printf("Elemento nao foi encontrado na Lista - Remove \n");
		}
		else {
			*setor = Setor_Aux->Item[p];

			for(i = p; i < Setor_Aux->Ult; i++) {
				Setor_Aux->Item[i] = Setor_Aux->Item[i + 1];
			}
			Setor_Aux->Ult--;
		}
	}
}


void Ler_Setor(Setor_Painel *A) {
	int i, j;
	float soma_geracao = 0;

	printf("\nEntre com o codigo identificador de 4 digitos do setor:");
	scanf("%d", &A->identificacao_setor);

	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			printf("\nEntre com o codigo identificador de 5 digitos do painel:");
			scanf("%d", &A->paineis[i][j].identificacao_painel);

			printf("\nEntre se o painel %d esta ativo: \n0 - NAO\n1 - SIM\n", A->paineis[i][j].identificacao_painel);
			scanf("%d", &A->paineis[i][j].ativo);

			if(A->paineis[i][j].ativo){
				printf("\nEntre com quantos Watts o painel %d gerou: ", A->paineis[i][j].identificacao_painel);
      			scanf("%f", &A->paineis[i][j].geracao);

        		A->paineis[i][j].eficiencia = Calc_Efic(A->paineis[i][j].geracao);
        		printf("\nA eficiencia do painel %d e: %.2f%%\n", A->paineis[i][j].identificacao_painel, A->paineis[i][j].eficiencia);
			}
			else{
				A->paineis[i][j].geracao = 0;
				A->paineis[i][j].eficiencia = 0;
			}

			soma_geracao += A->paineis[i][j].geracao;
		}
	}

	A->geracao_setor = soma_geracao;
}

void Exibir_Lista(Lista_est L) {
	if(Verifica_Lista_Vazia(L)){
		printf("A lista esta vazia. -Exibe lista\n");
	}
	else{
		int i, j, k = 0, P = L.Prim;
		
		printf("\n");
		
		for(i = 0; i < TAM / 2; i++){
			printf("********************");
		}
		
		printf("Exibe Lista");
		
		for(i = 0; i < TAM / 2; i++){
			printf("********************");
		}
		
		printf("\n");

		while(P < L.Ult){
			printf("\t\t\t\t\tSetor %d\t\t\t\t\t\n\n", L.Item[P].identificacao_setor);
			printf("\t\t\t\tGeracao total: %.2f\t\t\t\t\n\n", L.Item[P].geracao_setor);

			for(i = 0; i < TAM; i++){
        		for(j = 0; j < TAM; j++){
					printf("Painel %d", L.Item[P].paineis[i][j].identificacao_painel);
					printf("\t\t");
        		}
				printf("\n");

        		for(j = 0; j < TAM; j++){
					printf("Ativo: ");
        		    if(L.Item[P].paineis[i][j].ativo) printf("SIM");
					else printf("NAO");
					printf("\t\t");
				}
        		printf("\n");

        		for(j = 0; j < TAM; j++){
            		printf("Ger.: %.2f W", L.Item[P].paineis[i][j].geracao );
          			if(L.Item[P].paineis[i][j].geracao > 9999 || L.Item[P].paineis[i][j].geracao < -999) printf("\t");
         		   	else printf("\t\t");
				}
			    printf("\n");

				for(j = 0; j < TAM; j++){
    			    printf("Efic.: %.2f%%", L.Item[P].paineis[i][j].eficiencia );
    			    if(L.Item[P].paineis[i][j].eficiencia > 9999 || L.Item[P].paineis[i][j].eficiencia < -999) printf("\t");
    			    else printf("\t\t");
    			}
			    printf("\n\n");
			}
			
			P++;
		}
		
		printf("\n");
		
		for(i = 0; i < TAM / 2; i++){
			printf("********************");
		}
		
		printf("*Fim Lista*");
		
		for(i = 0; i < TAM / 2; i++){
			printf("********************");
		}
		
		printf("\n");
	}
}

int main(){
	Setor_Painel x;

	Lista_est y;

	Criar_Lista_Vazia(&y);

	Ler_Setor(&x);

	Insere_Elemento_Lista(&y, x);

	Exibir_Lista(y);
	
	getchar();
	getchar();
	getchar();
	getchar();
	
	return 0;
}
