#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define TAM 4 //Defini��o do tamanho das colunas e linhas das matrizes.
#define MAX 10 //capacidade da lista
#define AREA 100 //�rea de um painel
#define EFIC_MAX 0.22 //efici�ncia m�xima de um painel
#define LIMITE 5 //M�ximo de vezes que o usu�rio pode errar uma op��o do Menu

int cod_painel = 10000;

typedef struct{
	int identificacao_painel; // recebe o c�digo do painel de 5 d�gitos.
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
	int identificacao_setor; // recebe o c�digo do setor de at� 4 d�gitos.
    Painel paineis[TAM][TAM]; //matriz sim�trica de paineis pertencentes ao vetor
    float geracao_setor; //quantidade de energia gerada pelo setor
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

int Verifica_Lista_Cheia(Lista_est Setor_Aux){
	return (Setor_Aux.Ult == MAX);
}

float Calc_Efic(float geracao){
	return (((geracao / AREA) / EFIC_MAX) / 10);
}

void Insere_Elemento_Lista(Lista_est *Setor_Aux, Setor_Painel setor){

	int p;

	p = Setor_Aux->Prim;


		if(Verifica_Lista_Cheia(*Setor_Aux)){
			printf("Lista lotada, n�o pode ser adicionado mais dados");
		}
		else {
			p = Setor_Aux->Prim;

			while ((p < Setor_Aux->Ult) && (setor.geracao_setor < Setor_Aux->Item[p].geracao_setor)) {
				p++;
			}
			if (p == Setor_Aux->Ult){
				Setor_Aux->Item[p] = setor;
				Setor_Aux->Ult++;
			}
			else {
				if ((setor.geracao_setor != Setor_Aux->Item[p].geracao_setor)){
					int i;
					for(i = Setor_Aux->Ult; i > p; i--){
						Setor_Aux->Item[i] = Setor_Aux->Item[i-1];
					}
					Setor_Aux->Item[p] = setor;
					Setor_Aux->Ult++;
				}
			}
		}
}

void Remove_Elemento_Lista(Lista_est *Setor_Aux, Setor_Painel *setor){

	int p, i;

	if(Verifica_Lista_Vazia(*Setor_Aux)){
		printf("A lista j� est� vazia, imposs�vel remover elemento.");
	}
	else {
		p = Setor_Aux->Prim;

		while ((p < Setor_Aux->Ult) && (setor->geracao_setor > Setor_Aux->Item[p].geracao_setor)) {
			p++;
		}
		if (p == Setor_Aux->Ult || (setor->geracao_setor != Setor_Aux->Item[p].geracao_setor)){
			printf("Elemento nao foi encontrado na Lista - Remove\n");
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

float Get_Random_Float(){
    double a = 7000.0;
    float r = ((double)rand()/(double)(RAND_MAX)) * a;
    return r + 15000.0;
}

void Ler_Setor(Setor_Painel *A, Lista_est Setor_Aux) {
	int i = 0, j, ativos = 0;
	float soma_geracao = 0;

	printf("\nEntre com o codigo identificador de 4 digitos do setor: ");
	scanf("%d", &A->identificacao_setor);

	while ((i < Setor_Aux.Ult) && (A->identificacao_setor != Setor_Aux.Item[i].identificacao_setor))
        i++;

    if(i < Setor_Aux.Ult) {
        printf("Codigo de identifcacao ja existe na Lista.");

        Ler_Setor(&(*A), Setor_Aux);
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
        		ativos++;
			}
			else{
				A->paineis[i][j].geracao = 0;
				A->paineis[i][j].eficiencia = 0;
			}

			soma_geracao += A->paineis[i][j].geracao;
		}

		getchar();
	}

	soma_geracao = soma_geracao / ativos;

	A->geracao_setor = Calc_Efic(soma_geracao);
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
			printf("\t\t\t\tEficiencia Media: %.2f%%\t\t\t\t\n\n", L.Item[P].geracao_setor);

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

void Exibir_Setor(Lista_est L, int P){
    int i, j;

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

}

void Consultar_Elemento_Setor(Lista_est Setor_Aux, int codigo_setor){
    int i;

    if(Verifica_Lista_Vazia(Setor_Aux)) {
        printf("A lista est� vazia.");
    }
    else {
        i = Setor_Aux.Prim;

        while ((i < Setor_Aux.Ult) && (codigo_setor != Setor_Aux.Item[i].identificacao_setor))
            i++;
        if(i < Setor_Aux.Ult) {

            Exibir_Setor(Setor_Aux, i);

        }

    }

}

void cls(void)
{
    printf("\e[H\e[2J");

    #ifdef LINUX
        //c�digo especifico para linux
        //system ("clear");//poderia ser este mas escolhi este outro pois � mais a cara do C
        printf("\e[H\e[2J");
        #elif defined WIN32
        //c�digo espec�fico para windows
        system ("cls");
    #else
        printf("\e[H\e[2J");
    #endif

}

int Menu (int index, Lista_est *Setor_Aux, Setor_Painel Setor){

    int escolha, erros = 0, opcao, i, j;

    switch (index) {

		case 0:
		    printf("Obrigado por usar o APOLO MANAGER.");
			return 0;

		case 1:
            Ler_Setor(&Setor, *Setor_Aux);
            Insere_Elemento_Lista(*(&Setor_Aux), Setor);
            break;

		case 2:

			break;

		case 3:

		    Exibir_Lista(*Setor_Aux);

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

//		Case default para tentativas falsas.
		default:

            erros++;
            break;
		}

		return erros;
}

int main ( ) {
	int index = 1, erros = 0, aux;
	Lista_est Setor_Aux;
	Setor_Painel Setor;
	srand((unsigned int)time(NULL));

	Criar_Lista_Vazia(&Setor_Aux);

    printf("************Bem vindo ao Apolo Manager************\n\n");

	//Continua a execu��o at� que se digite 0.
	while (index != 0 && erros < LIMITE){
		//Fornece as op��es do TAD.
		printf("=============MENU Apolo Manager=============\n\n");
		printf("Escolha alguma das opcoes abaixo:\n\n");
		printf("0 - Sair do programa.\n"); //implementado :]
		printf("1 - Inserir Setor na Lista\n"); //implementado
		printf("2 - Remover Setor da Lista\n"); // implementado
		printf("3 - Exibir Lista\n"); //implementado
		printf("4 - Consultar Setor na Lista\n"); //implementado
		printf("5 - Consultar Painel no Setor\n"); //implementado
		printf("6 - Consultar Setores mais Pr�ximos\n"); //implementado
		printf("7 - Buscar elementos em uma matriz\n"); //implementado
		printf("8 - Relatorio Geral\n\n"); //implementado
		printf("=============================================\n");

		scanf("%d", &index);

        aux = Menu(index, &Setor_Aux, Setor);

        if(aux){
            erros += aux;
            printf("\nErro: Opcao inexistente. Tentativas restantes = %d\n\n", LIMITE - erros);
        }

		getchar();
		getchar();

		printf("Tecle enter para continuar");

		cls();
	}

	return 0;
}
