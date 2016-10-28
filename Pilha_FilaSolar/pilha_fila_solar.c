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

int Menu (int index, Pilha_est *P, Fila_est *F, Setor_Painel *setor){

    int escolha, erros = 0, opcao;

    switch (index) {

		case 0:
		    printf("Obrigado por usar o APOLO MANAGER.");
			return 0;

		case 1:
		    Ler_Elemento(&setor);
		    Enfileirar(&(*F), *setor);
            break;

		case 2:
			break;

		case 3:
			break;
		case 4:
		    break;

		case 5:
		    break;

		case 6:
		    break;
		case 7:
            break;

        case 8:
        	break;

        case 9:
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
		printf("5 - Consultar Painel no Setor\n");
		printf("6 - Consultar Setores mais Proximos\n");
		printf("7 - Setores abaixo da eficiencia media\n");
		printf("8 - Relatorio de um Setor\n");
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
