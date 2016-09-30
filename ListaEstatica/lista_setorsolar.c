#include <stdio.h>
#include <math.h>
#define TAM 4 //Definição do tamanho das colunas e linhas das matrizes.
#define M (((TAM * TAM) + TAM) / 2) //Definição do tamanho do vetor da matriz especial.
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
    Painel paineis[M]; //matriz simétrica de paineis pertencentes ao vetor
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

int Map_Mat(int i, int j){
	int pos;
	pos = (((i * i) - i) / 2) + j - 1;
	return pos;
}

float Calc_Efic(float geracao){
	return (((geracao / AREA) / EFIC_MAX) / 10);
}

void Ler_Setor(Setor_Painel *A) {
	int i, j, k = 0;
	
	printf("\nEntre com o codigo identificador de 4 digitos do setor:");
	scanf("%d", &A->identificacao_setor);
	
	for(i = 0; i < TAM; i++){
		for(j = 0; j <= i; j++){
			printf("\nEntre com o codigo identificador de 5 digitos do painel:");
			scanf("%d", &A->paineis[k].identificacao_painel);
			
			printf("\nEntre se o painel [%d][%d] esta ativo: \n0 - NAO\n1 - SIM\n", i + 1, j + 1);
			scanf("%d", &A->paineis[k].ativo);
			
			if(A->paineis[k].ativo){
				printf("\nEntre com quantos Watts o painel [%d][%d] gerou: ", i + 1, j + 1);
      			scanf("%f", &A->paineis[k].geracao);
      			
        		A->paineis[k].eficiencia = Calc_Efic(A->paineis[k].geracao);
        		printf("\nA eficiencia do painel [%d][%d] e: %.2f%%\n", i + 1, j + 1, A->paineis[k].eficiencia);
			}
			else{
				A->paineis[k].geracao = 0;
				A->paineis[k].eficiencia = 0;
			}

        	k++;
		}
	}
}

void Exibir_Lista(Lista_est L) {
	if(Verifica_Lista_Vazia(L)){
		printf("A lista esta vazia. -Exibe lista\n");
	}
	else{
		int P = L.Prim;
		printf("\n*********************Exibe Lista*************************\n");
		
		while(P < L.Ult){
			int i, j, k;
			
			printf("\t\t\t\t\tSetor %d\t\t\t\t\t\n\n", L.Item[P].identificacao_setor);
			
			for(i = 0; i < TAM; i++){
        		for(j = 0; j < TAM; j++){
					printf("Painel %d", L.Item[P].paineis[k].identificacao_painel);
					printf("\t\t");
        		}

        		printf("\n");

        		for(j = 0; j < TAM; j++){

        		    printf("Ativo: ");
        		    if(i < j){
            			k = Map_Mat(j + 1, i + 1);
						if(L.Item[P].paineis[k].ativo)
							printf("SIM");
						else
							printf("NAO");
					}
            		else{
            			k = Map_Mat(i + 1, j + 1);
						if(L.Item[P].paineis[k].ativo)
							printf("SIM");
						else
							printf("NAO");
						}
        			    printf("\t\t");

        			}

        			printf("\n");

        			for(j = 0; j < TAM; j++){

		            	if(i < j){
        		    		k = Map_Mat(j + 1, i + 1);
            			    printf("Ger.: %.2f W", L.Item[P].paineis[k].geracao );
          		  	    if(L.Item[P].paineis[k].geracao > 9999 || L.Item[P].paineis[k].geracao < -999) printf("\t");
         		   		else printf("\t\t");
            			}
		            	else {
		            		k = Map_Mat(i + 1, j + 1);
    		        		printf("Ger.: %.2f W", L.Item[P].paineis[k].geracao );
    		   	        	if(L.Item[P].paineis[k].geracao > 9999 || L.Item[P].paineis[k].geracao < -999) printf("\t");
    		   		     	else printf("\t\t");
						}

    			    }
			        printf("\n");

					for(j = 0; j < TAM; j++){

   				        if(i < j){
   		        			k = Map_Mat(j + 1, i + 1);
    			            printf("Efic.: %.2f%%", L.Item[P].paineis[k].eficiencia );
    			            if(L.Item[P].paineis[k].eficiencia > 9999 || L.Item[P].paineis[k].eficiencia < -999) printf("\t");
    			       		else printf("\t\t");
    			        }
    			        else {
    			        	k = Map_Mat(i + 1, j + 1);
    			        	printf("Efic.: %.2f%%", L.Item[P].paineis[k].eficiencia );
    			            if(L.Item[P].paineis[k].eficiencia > 9999 || L.Item[P].paineis[k].eficiencia < -999) printf("\t");
    	    		   		else printf("\t\t");
						}

    			    }
			        printf("\n\n");
			    }
			P++;
		}
		
		printf("\n*******************Fim Lista***************************\n");
	}
}

int main(){
	Setor_Painel x;
	
	Lista_est y;
	
	Criar_Lista_Vazia(&y);
	
	Ler_Setor(&x);
	
	Insere_Elemento_Lista;
	
	Exibir_Lista(y);
	
	return 0;
}
