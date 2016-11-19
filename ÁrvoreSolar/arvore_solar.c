#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define TAM 4 //DefiniÃ§Ã£o do tamanho das colunas e linhas das matrizes.
#define MAX 10 //capacidade da lista
#define AREA 100 //Ã¡rea de um painel
#define EFIC_MAX 0.22 //eficiÃªncia mÃ¡xima de um painel
#define LIMITE 5 //MÃ¡ximo de vezes que o usuÃ¡rio pode errar uma opÃ§Ã£o do Menu

/**	Componentes:
*   Mat:			Nome:
*   201602493		Gustavo Henrique da Silva Batista
*   201609824		Saulo de AraÃºjo Calixto
*
*	Este programa realiza o controle de dados
*	hetereogêneos, utilizando como tema o gerenciamentos
*	dos Painéis solares de uma companhia de energia solar,
*	dispostas em setores, utilizando-se de árvores
*	para sua representação.
*	TAD: Dados heterogêneos
*	1 - Verificar Árvore Vazia
*	2 - Inserir Dado na Árvore
*	3 - Consultar Elemento
*	4 - Exibir Elemento
*       -pré-ordem
*       -pós-ordem
*       -in-ordem
*	5 - Procurar Descendentes
*	6 - Procurar Sucessores
*	7 - Remover Elemento
*	8 - Exibir Relatório
**/

int cod_painel = 10000;

typedef struct{
	int identificacao_painel; // recebe o cÃ³digo do painel de 5 dÃ­gitos.
	int ativo; //recebe 0 {inativo} ou 1 {ativo}
	float geracao; //recebe geraÃ§Ã£o em Watts
	float eficiencia; //recebe ((geraÃ§Ã£o/AREA)/EFIC_MAX)/10
}Painel;

typedef struct{
	int identificacao_setor; // recebe o cÃ³digo do setor de atÃ© 4 dÃ­gitos.
    Painel paineis[TAM][TAM]; //matriz simÃ©trica de paineis pertencentes ao vetor
    float eficiencia_setor; //quantidade de energia gerada pelo setor
}Setor_Painel;

typedef struct nd{
    Setor_Painel Elem;
    struct nd *esq, *dir;
    }Nodo;

typedef Nodo *Arvore_Binaria;

int Verifica_Arvore_Vazia(Arvore_Binaria arvore) {
    return (arvore == NULL);
}

void Inserir_Elemento_Arvore(Arvore_Binaria *arvore, Setor_Painel setor) {

    if((*arvore) == NULL) {
        (*arvore) = (Arvore_Binaria) malloc(sizeof (Nodo));
        (*arvore)->esq = NULL;
        (*arvore)->dir = NULL;
        (*arvore)->Elem = setor;
    } else if ((*arvore)->Elem.eficiencia_setor > setor.eficiencia_setor) {
        Insere_Elemento_Arvore(&((*arvore)->dir), setor);
    } else if ((*arvore)->Elem.eficiencia_setor < setor.eficiencia_setor) {
        Insere_Elemento_Arvore(&((*arvore)->esq), setor);
    } else {
        (*arvore)->Elem = setor;
    }
}

float Calc_Efic(float geracao){
	return (((geracao / AREA) / EFIC_MAX) / 10);
}

float Get_Random_Float(){
    double a = Get_Random_Int(3000, 10000);
    float r = ((double)rand()/(double)(RAND_MAX)) * a;
    return r + Get_Random_Int(10000, 12000);
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
        //cÃ³digo especifico para linux
        //system ("clear");//poderia ser este mas escolhi este outro pois Ã© mais a cara do C
        printf("\e[H\e[2J");
        #elif defined WIN32
        //cÃ³digo especÃ­fico para windows
        system ("cls");
    #else
        printf("\e[H\e[2J");
    #endif
}

int Menu (int index, Arvore_Binaria *arvore,Setor_Painel *setor){

    int escolha, erros = 0, opcao;

    switch (index) {

		case 0:
		    printf("Obrigado por usar o APOLO MANAGER.");
			return 0;

		case 1:
		    Ler_Setor(&(*setor) );
		    Insere_Elemento_Arvore(&arvore,setor);
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

        case 10:
        	break;

		default:
            erros++;
            break;
		}

		return erros;
}

int main ( ) {
	int index = 1, erros = 0, aux;
	Arvore_Binaria arvore;
	Setor_Painel setor;
	srand((unsigned int)time(NULL));

    printf("************Bem vindo ao Apolo Manager************\n\n");

	//Continua a execuÃ§Ã£o atÃ© que se digite 0.
	while (index != 0 && erros < LIMITE){
		//Fornece as opÃ§Ãµes do TAD.
		printf("=============MENU Apolo Manager=============\n\n");
		printf("Escolha alguma das opcoes abaixo:\n\n");
		printf("0 - Sair do Sistema.\n");
		printf("1 - Inserir Setor\n");
		printf("2 - Exibir Setor\n");
		printf("3 - \n");
		printf("4 - \n");
		printf("5 - \n");
		printf("6 - \n");
		printf("7 - \n");
		printf("8 - \n");
		printf("9 - \n");
		printf("10 - \n");
		printf("=============================================\n");

		scanf("%d", &index);

        aux = Menu(index, &arvore, &setor);

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
