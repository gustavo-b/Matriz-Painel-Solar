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
*	1 - Criar fila vazia
*	2 - Criar pilha vazia
*	3 - Inserir setor na fila
*	4 - Inserir setor na pilha
*	5 - Remover setor da fila
*	6 - Remover setor da pilha
*	7 - Consultar setor da fila
*	8 - Consultar setor da pilha
*	9 - Gerar um relatório do setor
**/

int cod_painel = 10000;

typedef struct{
	int identificacao_painel; // recebe o código do painel de 5 dígitos.
	int ativo; //recebe 0 {inativo} ou 1 {ativo}
	float geracao; //recebe geração em Watts
	float eficiencia; //recebe ((geração/AREA)/EFIC_MAX)/10
}Painel;

//Define o tamanho do vetor especial da matriz simétrica de acordo com
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

float Get_Random_Float(){
    double a = Get_Random_Int(3000, 10000);
    float r = ((double)rand()/(double)(RAND_MAX)) * a;
    return r + Get_Random_Int(10000, 12000);
}

float Calc_Efic(float geracao){
	return (((geracao / AREA) / EFIC_MAX) / 10);
}

void Ler_Setor(Setor_Painel *setor) {

	int i = 0, j;
	float soma_geracao = 0;

	printf("\nEntre com o codigo identificador de 4 digitos do setor: ");
	scanf("%d", &setor->identificacao_setor);

	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
            float temp;

			printf("\nEntre com o codigo identificador de 5 digitos do painel: ");
			printf("%d", cod_painel);
			setor->paineis[i][j].identificacao_painel = cod_painel;
			cod_painel++;

			printf("\nEntre se o painel %d esta ativo: \n0 - NAO\n1 - SIM\n", setor->paineis[i][j].identificacao_painel);
			scanf("%d", &setor->paineis[i][j].ativo);

			if(setor->paineis[i][j].ativo){
				printf("\nEntre com quantos Watts o painel %d gerou: ", setor->paineis[i][j].identificacao_painel);
				temp = Get_Random_Float();
				printf("%.2f", temp);
      			setor->paineis[i][j].geracao = temp;

        		setor->paineis[i][j].eficiencia = Calc_Efic(setor->paineis[i][j].geracao);
        		printf("\nA eficiencia do painel %d e: %.2f%%\n", setor->paineis[i][j].identificacao_painel, setor->paineis[i][j].eficiencia);
			}
			else{
				setor->paineis[i][j].geracao = 0;
				setor->paineis[i][j].eficiencia = 0;
			}

			soma_geracao += setor->paineis[i][j].geracao;
		}

		getchar();
	}

	soma_geracao = soma_geracao / (TAM*TAM);

	setor->eficiencia_setor = Calc_Efic(soma_geracao);
}

void Exibir_Setor(Setor_Painel setor){
    int i, j;

    printf("\t\t\t\t\tSetor %d\n\n", setor.identificacao_setor);
    printf("\t\t\t\tEficiencia Media: %.2f%%\n\n", setor.eficiencia_setor);

    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){
            printf("Painel %d", setor.paineis[i][j].identificacao_painel);
            printf("\t\t");
        }
        printf("\n");

        for(j = 0; j < TAM; j++){
            printf("Ativo: ");
            if(setor.paineis[i][j].ativo) printf("SIM");
            else printf("NAO");
            printf("\t\t");
        }
        printf("\n");

        for(j = 0; j < TAM; j++){
            printf("Ger.: %.2f W", setor.paineis[i][j].geracao );
            if(setor.paineis[i][j].geracao > 9999 || setor.paineis[i][j].geracao < -999) printf("\t");
            else printf("\t\t");
        }
        printf("\n");

        for(j = 0; j < TAM; j++){
            printf("Efic.: %.2f%%", setor.paineis[i][j].eficiencia );
            if(setor.paineis[i][j].eficiencia > 9999 || setor.paineis[i][j].eficiencia < -999) printf("\t");
            else printf("\t\t");
        }
        printf("\n\n");
    }

    getchar();
}


void Relatorio_Setor(Setor_Painel setor){
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

    printf("\n***************RELATORIO*****************\n");
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
		printf("*  Media Energ. Ger.: %.2f\t*\n", somaWatts / (TAM*TAM)); //a m�dia � em rela��o todos os paineis, at� os desativados
	}
	else{
		printf("*  Media Energ. Ger.: %.2f\t\t*\n", somaWatts / (TAM*TAM)); //a m�dia � em rela��o todos os paineis, at� os desativados
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
					printf("*  ABAIXO DA MEDIA DE EFICIENCIA\t*\n");
				}
				else{
					printf("*  EFICIENCIA BAIXA\t\t\t*\n");
				}
			}
		}
	}
	printf("*  \t\t\t\t\t*\n*\t\t\t\t\t*\n*****************************************\n");
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
        Relatorio_Setor(setor);
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
        Relatorio_Setor(setor);
    }
}

void Desenfileirar(Fila_est *F, Setor_Painel *setor)
{
    if(Verifica_Fila_Vazia(*F)) {
        printf("Nao há setores na fila.");
    }
    else {
        *setor = F->Item[F->Inicio];
        printf("Setor Removido:\n");
		Exibir_Setor(*setor);
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
        printf("Setor Removido:\n");
		Exibir_Setor(*setor);
    }
}

void Inverter_Pilha(Pilha_est *PA){
	Pilha_est PB;
	Criar_Pilha_Vazia(&PB);

	Setor_Painel X;

	if(Verifica_Pilha_Vazia(*PA)){
		printf("A pilha est� vazia.\n");
	}
	else{
		while(!(Verifica_Pilha_Vazia(*PA))){
			Desempilhar(&(*PA), &X);
			Empilhar(&PB, X);
		}
		*PA = PB;
		Criar_Pilha_Vazia(&PB);
	}
}

void Inverter_Fila(Fila_est *FA){
	Pilha_est P;
	Setor_Painel X;

	Criar_Pilha_Vazia(&P);

	if(Verifica_Fila_Vazia(*FA)){
		printf("A Fila est� vazia.\n");
	}
	else{
		while(!Verifica_Fila_Vazia(*FA)){
			Desenfileirar(&(*FA), &X);
			Empilhar(&P, X);
		}
		while(!Verifica_Pilha_Vazia(P)){
			Desempilhar(&P, &X);
			Enfileirar(&(*FA), X);
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

void cls(void){
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

int Menu (int index, Pilha_est *P, Fila_est *F, Setor_Painel *setor){

    int escolha, erros = 0, opcao;

    switch (index) {

		case 0:
		    printf("Obrigado por usar o APOLO MANAGER.");
			return 0;

		case 1:
		    Ler_Setor(&(*setor) );
		    Enfileirar(&(*F), *setor);
            break;

		case 2:
		    Ler_Setor(&(*setor) );
		    Empilhar(&(*P), *setor);
			break;

		case 3:
		    Desenfileirar(&(*F), &(*setor));
			break;
		case 4:
		    Desempilhar(&(*P), &(*setor));
		    break;

		case 5:
			if(Verifica_Fila_Vazia(*F)){
				printf("A Fila esta vazia.\n");
			} else {
				Exibir_Setor(F->Item[F->Inicio]);
			}
		    break;

		case 6:
			if(Verifica_Pilha_Vazia(*P)){
				printf("A Pilha esta vazia.\n");
			} else {
				Exibir_Setor(P->Item[P->Topo-1]);
			}
		    break;

		case 7:
			if(Verifica_Fila_Vazia(*F)){
				printf("A Fila esta vazia.\n");
			} else {
				Relatorio_Setor(F->Item[F->Inicio]);
			}
            break;

		case 8:
			if(Verifica_Pilha_Vazia(*P)){
				printf("A Pilha esta vazia.\n");
			} else {
				Relatorio_Setor(P->Item[P->Topo-1]);
			}
            break;

        case 9:
        	Inverter_Fila(&(*F));
        	break;

        case 10:
        	Inverter_Pilha(&(*P));
        	break;

		default:
            erros++;
            break;
		}

		return erros;
}

int main ( ) {
	int index = 1, erros = 0, aux;
	Pilha_est P;
	Fila_est F;
	Setor_Painel setor;
	srand((unsigned int)time(NULL));

	Criar_Fila_Vazia(&F);
	Criar_Pilha_Vazia(&P);

    printf("************Bem vindo ao Apolo Manager************\n\n");

	//Continua a execução até que se digite 0.
	while (index != 0 && erros < LIMITE){
		//Fornece as opções do TAD.
		printf("=============MENU Apolo Manager=============\n\n");
		printf("Escolha alguma das opcoes abaixo:\n\n");
		printf("0 - Sair do Sistema.\n");
		printf("1 - Inserir Setor na Fila\n");
		printf("2 - Inserir Setor na Pilha\n");
		printf("3 - Desenfileirar Setor\n");
		printf("4 - Desempilhar Setor\n");
		printf("5 - Consultar primeiro Elemento da Fila\n");
		printf("6 - Consultar elemento que está no topo da Pilha\n");
		printf("7 - Relatorio do primeiro Setor da Fila\n");
		printf("8 - Relatorio do Setor que esta no topo da Pilha\n");
		printf("9 - Inverter Fila\n");
		printf("10 - Inverter Pilha\n");
		printf("=============================================\n");

		scanf("%d", &index);

        aux = Menu(index, &P, &F, &setor);

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
