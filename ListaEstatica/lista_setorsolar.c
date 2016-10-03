#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define TAM 4 //Definição do tamanho das colunas e linhas das matrizes.
#define MAX 10 //capacidade da lista
#define AREA 100 //área de um painel
#define EFIC_MAX 0.22 //eficiência máxima de um painel
#define LIMITE 5 //Máximo de vezes que o usuário pode errar uma opção do Menu

/*
	Este programa realiza o controle de dados
	heterogêneos, utilizando como tema o gerenciamentos
	dos painéis solares de uma companhia de energia solar,
	dispostas em setores, utilizando-se de matrizes
	para sua representação.

	TAD: Dados heterogêneos

	1 - Criar lista vazia
	2 - Inserir setor na lista
	3 - Remover setor da lista
	4 - Consultar setor da lista
	5 - Exibe a lista
	6 - Exibir os setores com baixa eficiencia
	7 - Redistribuir de acordo com a eficiencia de cada setor
	8 - Gerar um relatório do setor
	9 - Gerar um relatório da lista

*/

int cod_painel = 10000;

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
    float eficiencia_setor; //quantidade de energia gerada pelo setor
}Setor_Painel;

typedef struct {
    Setor_Painel Item[MAX]; //criação da lista
    int Prim, Ult; //auxiliares para primeira e última posição da lista.
}Lista_est;

void Criar_Lista_Vazia (Lista_est *Lista_Usina){
    Lista_Usina->Prim = 0;
    Lista_Usina->Ult = Lista_Usina->Prim;
}

int Verifica_Lista_Vazia(Lista_est Lista_Usina){
    return (Lista_Usina.Prim == Lista_Usina.Ult);
}

int Verifica_Lista_Cheia(Lista_est Lista_Usina){
	return (Lista_Usina.Ult == MAX);
}

float Calc_Efic(float geracao){
	return (((geracao / AREA) / EFIC_MAX) / 10);
}

void Insere_Elemento_Lista(Lista_est *Lista_Usina, Setor_Painel setor){

	int p;

	p = Lista_Usina->Prim;


		if(Verifica_Lista_Cheia(*Lista_Usina)){
			printf("Lista lotada, não pode ser adicionado mais dados");
		}
		else {
			p = Lista_Usina->Prim;

			while ((p < Lista_Usina->Ult) && (setor.eficiencia_setor < Lista_Usina->Item[p].eficiencia_setor)) {
				p++;
			}
			if (p == Lista_Usina->Ult){
				Lista_Usina->Item[p] = setor;
				Lista_Usina->Ult++;
			}
			else {
				if ((setor.eficiencia_setor != Lista_Usina->Item[p].eficiencia_setor)){
					int i;
					for(i = Lista_Usina->Ult; i > p; i--){
						Lista_Usina->Item[i] = Lista_Usina->Item[i-1];
					}
					Lista_Usina->Item[p] = setor;
					Lista_Usina->Ult++;
				}
			}
		}
}

void Remove_Elemento_Lista(Lista_est *Lista_Usina, Setor_Painel *setor){

	int p, i;

	if(Verifica_Lista_Vazia(*Lista_Usina)){
		printf("A lista já está vazia, impossível remover elemento.");
	}
	else {
		p = Lista_Usina->Prim;

		while ((p < Lista_Usina->Ult) && (setor->identificacao_setor > Lista_Usina->Item[p].identificacao_setor)) {
			p++;
		}
		if (p == Lista_Usina->Ult){
			printf("Setor nao foi encontrado no sistema!\n");
		}
		else {
			*setor = Lista_Usina->Item[p];
            printf("Setor removido do sistema!\n");
			for(i = p; i < Lista_Usina->Ult; i++) {
				Lista_Usina->Item[i] = Lista_Usina->Item[i + 1];
			}
			Lista_Usina->Ult--;
		}
	}
}

int Get_Random_Int(int min, int max){
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    do{
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

float Get_Random_Float(){
    double a = Get_Random_Int(3000, 10000);
    float r = ((double)rand()/(double)(RAND_MAX)) * a;
    return r + Get_Random_Int(10000, 12000);
}

void Ler_Setor(Setor_Painel *A, Lista_est Lista_Usina) {
	int i = 0, j;
	float soma_geracao = 0;

	printf("\nEntre com o codigo identificador de 4 digitos do setor: ");
	scanf("%d", &A->identificacao_setor);

	while ((i < Lista_Usina.Ult) && (A->identificacao_setor != Lista_Usina.Item[i].identificacao_setor))
        i++;

    if(i < Lista_Usina.Ult) {
        printf("Codigo de identifcacao ja existe na Lista.");

        return Ler_Setor(&(*A), Lista_Usina);
    }

	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
            float temp;

			printf("\nEntre com o codigo identificador de 5 digitos do painel: ");
			printf("%d", cod_painel);
			A->paineis[i][j].identificacao_painel = cod_painel;
			cod_painel++;

			printf("\nEntre se o painel %d esta ativo: \n0 - NAO\n1 - SIM\n", A->paineis[i][j].identificacao_painel);
			scanf("%d", &A->paineis[i][j].ativo);

			if(A->paineis[i][j].ativo){
				printf("\nEntre com quantos Watts o painel %d gerou: ", A->paineis[i][j].identificacao_painel);
				temp = Get_Random_Float();
				printf("%.2f", temp);
      			A->paineis[i][j].geracao = temp;

        		A->paineis[i][j].eficiencia = Calc_Efic(A->paineis[i][j].geracao);
        		printf("\nA eficiencia do painel %d e: %.2f%%\n", A->paineis[i][j].identificacao_painel, A->paineis[i][j].eficiencia);
			}
			else{
				A->paineis[i][j].geracao = 0;
				A->paineis[i][j].eficiencia = 0;
			}

			soma_geracao += A->paineis[i][j].geracao;
		}

		getchar();
	}

	soma_geracao = soma_geracao / (TAM*TAM);

	A->eficiencia_setor = Calc_Efic(soma_geracao);
}

void Exibir_Lista(Lista_est Lista_Usina) {
	if(Verifica_Lista_Vazia(Lista_Usina)){
		printf("A lista esta vazia. -Exibe lista\n");
	}
	else{
		int i, j, k = 0, P = Lista_Usina.Prim;

		printf("\n");

		for(i = 0; i < TAM / 2; i++){
			printf("********************");
		}

		printf("Exibe Lista");

		for(i = 0; i < TAM / 2; i++){
			printf("********************");
		}

		printf("\n");

		while(P < Lista_Usina.Ult){
			printf("\t\t\t\t\tSetor %d\t\t\t\t\t\n\n", Lista_Usina.Item[P].identificacao_setor);
			printf("\t\t\t\tEficiencia Media: %.2f%%\t\t\t\t\n\n", Lista_Usina.Item[P].eficiencia_setor);

			for(i = 0; i < TAM; i++){
        		for(j = 0; j < TAM; j++){
					printf("Painel %d", Lista_Usina.Item[P].paineis[i][j].identificacao_painel);
					printf("\t\t");
        		}
				printf("\n");

        		for(j = 0; j < TAM; j++){
					printf("Ativo: ");
        		    if(Lista_Usina.Item[P].paineis[i][j].ativo) printf("SIM");
					else printf("NAO");
					printf("\t\t");
				}
        		printf("\n");

        		for(j = 0; j < TAM; j++){
            		printf("Ger.: %.2f W", Lista_Usina.Item[P].paineis[i][j].geracao );
          			if(Lista_Usina.Item[P].paineis[i][j].geracao > 9999 || Lista_Usina.Item[P].paineis[i][j].geracao < -999) printf("\t");
         		   	else printf("\t\t");
				}
			    printf("\n");

				for(j = 0; j < TAM; j++){
    			    printf("Efic.: %.2f%%", Lista_Usina.Item[P].paineis[i][j].eficiencia );
    			    if(Lista_Usina.Item[P].paineis[i][j].eficiencia > 9999 || Lista_Usina.Item[P].paineis[i][j].eficiencia < -999) printf("\t");
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

void Exibir_Setor(Lista_est Lista_Usina, int P){
    int i, j;

    printf("\t\t\t\t\tSetor %d\n\n", Lista_Usina.Item[P].identificacao_setor);
    printf("\t\t\t\tEficiencia Media: %.2f%%\n\n", Lista_Usina.Item[P].eficiencia_setor);

    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){
            printf("Painel %d", Lista_Usina.Item[P].paineis[i][j].identificacao_painel);
            printf("\t\t");
        }
        printf("\n");

        for(j = 0; j < TAM; j++){
            printf("Ativo: ");
            if(Lista_Usina.Item[P].paineis[i][j].ativo) printf("SIM");
            else printf("NAO");
            printf("\t\t");
        }
        printf("\n");

        for(j = 0; j < TAM; j++){
            printf("Ger.: %.2f W", Lista_Usina.Item[P].paineis[i][j].geracao );
            if(Lista_Usina.Item[P].paineis[i][j].geracao > 9999 || Lista_Usina.Item[P].paineis[i][j].geracao < -999) printf("\t");
            else printf("\t\t");
        }
        printf("\n");

        for(j = 0; j < TAM; j++){
            printf("Efic.: %.2f%%", Lista_Usina.Item[P].paineis[i][j].eficiencia );
            if(Lista_Usina.Item[P].paineis[i][j].eficiencia > 9999 || Lista_Usina.Item[P].paineis[i][j].eficiencia < -999) printf("\t");
            else printf("\t\t");
        }
        printf("\n\n");
    }

}

void Consultar_Elemento_Setor(Lista_est Lista_Usina, int codigo_setor){
    int i;

    if(Verifica_Lista_Vazia(Lista_Usina)) {
        printf("A lista está vazia.");
    }
    else {
        i = Lista_Usina.Prim;

        while ((i < Lista_Usina.Ult) && (codigo_setor != Lista_Usina.Item[i].identificacao_setor))
            i++;
        if(i < Lista_Usina.Ult) {

            Exibir_Setor(Lista_Usina, i);

        }

    }

}

void Efic_Setores(Lista_est Lista_Usina){
	int low_effic = 0;
	
	if(Verifica_Lista_Vazia(Lista_Usina)) {
        printf("A lista está vazia.");
    }
    
    int cont = Lista_Usina.Prim;
    
    while(cont < Lista_Usina.Ult){
   		if((Lista_Usina.Item[cont].eficiencia_setor * EFIC_MAX) >= 13){
   			low_effic++;
			printf("\t\t\t\t***ABAIXO DA MEDIA DE EFICIENCIA***\n");
			Exibir_Setor(Lista_Usina, cont);
			getchar();
			getchar();
		}
		else{
			if((Lista_Usina.Item[cont].eficiencia_setor * EFIC_MAX) < 13){
				low_effic++;
				printf("\t\t\t\t***EFICIENCIA BAIXA***\n");
				Exibir_Setor(Lista_Usina, cont);
				getchar();
				getchar();
			}
		}
		cont++;
	}
	
	if(low_effic == 0){
		printf("Parabens! Nenhum setor abaixo da producao media esperada!\n");
	}
}

void Relatorio_Setor(Lista_est Lista_Usina, Setor_Painel setor){
	int p;
	
	if(Verifica_Lista_Vazia(Lista_Usina)){
		printf("A lista esta vazia.");
	}
	else {
		p = Lista_Usina.Prim;

		while ((p < Lista_Usina.Ult) && (setor.identificacao_setor > Lista_Usina.Item[p].identificacao_setor)) {
			p++;
		}
		if (p == Lista_Usina.Ult){
			printf("Setor nao foi encontrado no sistema!\n");
		}
		else {
			int i, j, quant_ativos = 0;
		    float somaWatts = 0, somaEff = 0, eficienciatotal;

		    for(i = 0; i < TAM; i++){
    			for(j = 0; j < TAM; j++){
    				somaWatts += setor.paineis[i][j].geracao;
        		    if(setor.paineis[i][j].ativo){
        		    	quant_ativos++;
					}
				}
		    }
		
		    printf("\n************RELATORIO GERAL**************\n");
		    printf("*  \t\t\t\t\t*\n*\t\t\t\t\t*\n");
		    printf("*  Paineis Ativados: %d\t\t\t*\n", quant_ativos);
		    printf("*  Paineis Desativados: %d\t\t*\n", (TAM * TAM) - quant_ativos );
		    if(somaWatts > 999999){
		    	printf("*  Total Energ. Ger.: %.2f\t*\n", somaWatts);
			}
			else{
				printf("*  Total Energ. Ger.: %.2f\t\t*\n", somaWatts);
			}
			if((somaWatts/(TAM*TAM)) > 999999){
		    	printf("*  Media Energ. Ger.: %.2f\t*\n", somaWatts / (TAM*TAM)); //a média é em relação todos os paineis, até os desativados
			}
			else{
				printf("*  Media Energ. Ger.: %.2f\t\t*\n", somaWatts / (TAM*TAM)); //a média é em relação todos os paineis, até os desativados
			}
		    printf("*  Media Eficiencia: %.2f%%\t\t*\n", setor.eficiencia_setor);
		    if((setor.eficiencia_setor * EFIC_MAX) >= 16){
		    	printf("*  EFICIENCIA ALTA\t\t\t*\n");
			}
			else{
				if((setor.eficiencia_setor * EFIC_MAX) >= 15){
					printf("*  ACIMA DA MEDIA DE EFICIENCIA\t\t*\n");
				}
				else{
					if((setor.eficiencia_setor * EFIC_MAX) >= 14){
						printf("*  EFICIENCIA MEDIA\t\t\t*\n");
					}
					else{
						if((setor.eficiencia_setor * EFIC_MAX) >= 13){
							printf("*  ABAIXO DA MEDIA DE EFICIENCIA\t\t*\n");
						}
						else{
							printf("*  EFICIENCIA BAIXA\t\t\t*\n");
						}
					}
				}
			}
		    printf("*  \t\t\t\t\t*\n*\t\t\t\t\t*\n*****************************************\n");
		}
	}
}

void cls(void){
    printf("\e[H\e[2J");

    #ifdef LINUX
        //código especifico para linux
        //system ("clear");//poderia ser este mas escolhi este outro pois é mais a cara do C
        printf("\e[H\e[2J");
        #elif defined WIN32
        //código específico para windows
        system ("cls");
    #else
        printf("\e[H\e[2J");
    #endif

}

int Menu (int index, Lista_est *Lista_Usina, Setor_Painel *Setor){

    int escolha, erros = 0, opcao;

    switch (index) {

		case 0:
		    printf("Obrigado por usar o APOLO MANAGER.");
			return 0;

		case 1:
            Ler_Setor(&(*Setor), *Lista_Usina);
            Insere_Elemento_Lista(&(*Lista_Usina), *Setor);
            break;

		case 2:
		    printf("Digite a identificacao do setor a ser removido: ");
		    scanf("%d", &opcao);
		    Setor->identificacao_setor = opcao;
		    Remove_Elemento_Lista(&(*Lista_Usina), &(*Setor));

			break;

		case 3:

		    Exibir_Lista(*Lista_Usina);

			break;

		case 4:
		    printf("Digite a identificacao do setor a ser consultado: ");
		    scanf("%d", &opcao);
		    Consultar_Elemento_Setor(*Lista_Usina, opcao);

		    break;

		case 5:

		    break;

		case 6:

			break;

		case 7:
			Efic_Setores(*Lista_Usina);
            break;
            
        case 8:
        	printf("Digite a identificacao do setor a ser gerado relatorio: ");
		    scanf("%d", &opcao);
        	Relatorio_Setor(*Lista_Usina, *Setor);
        	break;
        	
        case 9:
        	
        	break;

//		Case default para tentativas falsas.
		default:

            erros++;
            break;
		}

		return erros;
}

int main ( ) {
	int index = 1, erros = 0, aux;
	Lista_est Lista_Usina;
	Setor_Painel Setor;
	srand((unsigned int)time(NULL));

	Criar_Lista_Vazia(&Lista_Usina);

    printf("************Bem vindo ao Apolo Manager************\n\n");

	//Continua a execução até que se digite 0.
	while (index != 0 && erros < LIMITE){
		//Fornece as opções do TAD.
		printf("=============MENU Apolo Manager=============\n\n");
		printf("Escolha alguma das opcoes abaixo:\n\n");
		printf("0 - Sair do Sistema.\n"); //implementado :]
		printf("1 - Inserir Setor no Sistema\n"); //implementado
		printf("2 - Remover Setor do Sistema\n"); //implementado
		printf("3 - Exibir Lista\n"); //implementado
		printf("4 - Consultar Setor no Sistema\n"); //implementado
		printf("5 - Consultar Painel no Setor\n"); //
		printf("6 - Consultar Setores mais Proximos\n"); //ou realocar energia para setores?
		printf("7 - Setores abaixo da eficiencia media\n"); //implementado
		printf("8 - Relatorio de um Setor\n"); //implementado
		printf("9 - Relatorio Geral\n\n"); //
		printf("=============================================\n");

		scanf("%d", &index);

        aux = Menu(index, &Lista_Usina, &Setor);

        if(aux){
            erros += aux;
            printf("\nErro: Opcao inexistente. Tentativas restantes = %d\n\n", LIMITE - erros);
        }


		getchar();
		getchar();

		cls();
	}

	return 0;
}
