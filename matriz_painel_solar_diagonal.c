#include <stdio.h>
#include <string.h>
#define TAM 4 //Definição do tamanho das colunas e linhas das matrizes.
#define LIMITE 5 //Limite de erros possíveis
#define CAP 30 //capacidade de geração dos painéis em Watt/hora

/*
	Este programa realiza o controle de matrizes.
	Componentes:
		Mat:			Nome:



	TAD: Dados int e float
	1 - Ler Matrizes
	2 - Somar elementos de matrizes
	3 - Subtrair elementos de matrizes
	4 - Multiplicar elementos de matrizes
	5 - Caclular média de elementos de matrizes
	6 - Exibir matriz
	7 - Buscar elementos na matriz
*/


typedef struct{
	int ativo; //recebe 0 {inativo} ou 1 {ativo}
	float geracao; //recebe geração em Watts no último x período de tempo
	float atividade; //recebe quantidade de horas em atividade no último x período de tempo
	float eficiencia; //recebe (geração/atividade)/capacidade
	float inclinacao; //inclinação em graus
}Painel;

typedef Painel matriz_solar[TAM];

//void Inicializar(matriz_solar a){
//	int i, j;
//
//	for(i = 0; i < TAM; i++){
//		for(j = 0; j < TAM; j++){
//			a[i][j].geracao = 0;
//            a[i][j].atividade = 0;
//            a[i][j].eficiencia = 0;
//            a[i][j].inclinacao = 0;
//		}
//	}
//}

void Ler_Mat(matriz_solar a) {
	int i, j;
//	Inicializar(a);
	for(i = 0; i < TAM; i++){

        a[i].ativo = 1;
        printf("\nEntre com a geracao em Watts do painel [%d][%d]: ", i + 1, i + 1);
        scanf("%f", &a[i].geracao);
        printf("\nEntre com o tempo de atividade em horas do painel [%d][%d]: ", i + 1, i + 1);
        scanf("%f", &a[i].atividade);
        a[i].eficiencia = ((a[i].geracao / a[i].atividade) / CAP) * 100;
        printf("\nA eficiencia do painel [%d][%d] e: %.2f%%", i + 1, i + 1, a[i].eficiencia);
        printf("\nEntre com a inclinacao do painel [%d][%d]: ", i + 1, i + 1);
        scanf("%f", &a[i].inclinacao);

	}
}

void Exibir_Mat(matriz_solar a) {
    int i, j;

    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){

                printf("Painel [%d][%d]", i + 1, j + 1);

            printf("\t\t");
        }

        printf("\n");

        for(j = 0; j < TAM; j++){

            printf("Ativo: ");
            if(i == j)
                printf("SIM");
            else printf("NAO");
            printf("\t\t");
        }

        printf("\n");

        for(j = 0; j < TAM; j++){

            if( i == j){
                printf("Ger.: %.2f W", a[i].geracao );
            }
            else printf("Ger.: 0.00 W" );
            if(a[i].geracao > 9999 || a[i].geracao < -999) printf("\t");
            else printf("\t\t");
        }
        printf("\n");

            for(j = 0; j < TAM; j++){

            if(i == j){
                printf("Ativ.: %.2f h", a[i].atividade );
            }
            else printf("Ativ.: 0 h" );
            if(a[i].atividade > 99 || a[i].atividade < -99) printf("\t");
            else printf("\t\t");
        }
        printf("\n");

        for(j = 0; j < TAM; j++){

            if(i == j){
                printf("Efic.: %.2f%%", a[i].eficiencia );
            }
            else printf("Efic.: 0%%");
            if(a[i].eficiencia > 9999 || a[i].eficiencia < -999) printf("\t");
            else printf("\t\t");

        }
        printf("\n");

        for(j = 0; j < TAM; j++){

            if(i == j){
                printf("Incl.: %.2f", a[i].inclinacao );
            }
            else printf("Incl.: 0");

            if(a[i].inclinacao > 9999 || a[i].inclinacao < -99) printf("\t");
            else printf("\t\t");
        }
        printf("\n\n");
    }

}


void Somar_Elemento_Mat(matriz_solar a, matriz_solar b, matriz_solar c) {
	int i, j;

        for(i = 0; i < TAM; i++){

            c[i].geracao = (a[i].geracao) + (b[i].geracao);
            c[i].ativo = a[i].ativo;
            c[i].atividade = (a[i].atividade) + (b[i].atividade);
            c[i].eficiencia = ((c[i].geracao / c[i].atividade) / CAP) * 100;
            c[i].inclinacao = (a[i].inclinacao) + (b[i].inclinacao);
        }

    Exibir_Mat(c);
}
//
//void Subtrair_Elemento_Mat(matriz_solar a, matriz_solar b, matriz_solar c) {
//    int i, j;
//
//    for(i = 0; i < TAM; i++){
//        for(j = 0; j < TAM; j++){
//            c[i][j].geracao = (a[i][j].geracao) - (b[i][j].geracao);
//            c[i][j].atividade = (a[i][j].atividade) - (b[i][j].atividade);
//            c[i][j].inclinacao = (a[i][j].inclinacao) - (b[i][j].inclinacao);
//            if(c[i][j].atividade){
//            	c[i][j].eficiencia = ((c[i][j].geracao / c[i][j].atividade) / CAP) * 100;
//			}
//			else c[i][j].eficiencia = 0;
//            c[i][j].ativo = (a[i][j].ativo) + (b[i][j].ativo);
//            //Ativo continua como soma, pois se um deles estiver ativo, já basta.
//        }
//    }
//
//    Exibir_Mat(c);
//}
//
//void Multiplicar_Elemento_Mat(matriz_solar a, matriz_solar b, matriz_solar c) {
//
//	Inicializar(c);
//    int i, j, k;
//
//	for (i = 0; i < TAM; i++) {
//      for (j = 0; j < TAM; j++) {
//        for (k = 0; k < TAM; k++) {
//          c[i][j].geracao += (a[i][k].geracao * b[k][j].geracao);
//          c[i][j].atividade += (a[i][k].atividade * b[k][j].atividade);
//          if(c[i][j].atividade){
//            	c[i][j].eficiencia += ((c[i][j].geracao / c[i][j].atividade) / CAP);
//			}
//		  else c[i][j].eficiencia += 0;
//          c[i][j].inclinacao += (a[i][k].inclinacao * b[k][j].inclinacao);
//          c[i][j].ativo += (a[i][k].ativo * b[k][j].ativo);
//        }
//      }
//    }
//
//    Exibir_Mat(c);
//}
//
//void Media_Elemento_Mat(matriz_solar a, matriz_solar b, matriz_solar c) {
//	int i, j;
//
//	for(i = 0; i < TAM; i++){
//		for(j = 0; j < TAM; j++){
//			c[i][j].geracao = (a[i][j].geracao + b[i][j].geracao) / 2;
//			c[i][j].atividade = (a[i][j].atividade + b[i][j].atividade) / 2;
//			c[i][j].eficiencia = (a[i][j].eficiencia + b[i][j].eficiencia) / 2;
//			c[i][j].inclinacao = (a[i][j].inclinacao + b[i][j].inclinacao) / 2;
//		}
//	}
//
//	Exibir_Mat(c);
//}
//
void Buscar_Elemento_Mat(int f, int i, int j, matriz_solar a) {
	if(i == j){
        switch(f){
        case 0:
            printf("\n\n%d", a[i - 1].ativo); //ativo
            break;

        case 1:
            printf("\n\n%.2f W", a[i - 1].geracao); //geracao
            break;

        case 2:
            printf("\n\n%.2f h", a[i - 1].atividade); //atividade
            break;

        case 3:
            printf("\n\n%.2f%%", a[i - 1].eficiencia); //eficiencia
            break;

        case 4:
            printf("\n\n%.2f", a[i - 1].inclinacao); //inclinacao
            break;

        default:
            break;
        }
    }
    else printf("\n\n0");
}

int Menu (int index, matriz_solar a, matriz_solar b, matriz_solar c){

    int escolha, erros = 0, opcao, i, j;

    switch (index) {

		case 0:
			return 0;

		case 1:
			printf("0 - Matriz A\n");
			printf("1 - Matriz B\n");
			scanf("%d", &escolha);
                switch(escolha){
                case 0:
                    Ler_Mat(a);
                    break;

                case 1:
                    Ler_Mat(b);
                    break;

                default:
                    Menu(index, a, b, c);
                    break;
                }
			break;

		case 2:
			Somar_Elemento_Mat(a, b, c);
			break;

//		case 3:
//			printf("0 - Matriz A - Matriz B\n1 - Matriz B - Matriz A\n");
//			int escolha;
//			scanf("%d", &escolha);
//			if(escolha == 1)
//                Subtrair_Elemento_Mat(b, a, c);
//            else if(escolha == 0)
//                Subtrair_Elemento_Mat(a, b, c);
//            else Menu(index, a, b, c);
//			break;
//
//		case 4:
//			Multiplicar_Elemento_Mat(a, b, c);
//			break;
//
//		case 5: //media dos elementos
//			Media_Elemento_Mat(a, b, c);
//			break;
//
		case 6:
			printf("0 - Matriz A\n");
			printf("1 - Matriz B\n");
			printf("2 - Matriz C\n");
			scanf("%d", &escolha);
			switch(escolha){
			case 0:
				Exibir_Mat(a);
				break;

			case 1:
				Exibir_Mat(b);
				break;

			case 2:
				Exibir_Mat(c);
				break;

			default:
			    Menu(index, a, b, c);
				break;
			}
			break;
//
		case 7:
			printf("\n0 - Ativo\n");
			printf("1 - Geracao\n");
			printf("2 - Atividade\n");
			printf("3 - Eficiencia\n");
			printf("4 - Inclinacao\n");

			scanf("%d", &opcao);

			if(opcao > 4 || opcao < 0){
                Menu(index, a, b, c);
			}
			else{
                printf("Digite a posicao da matriz (1 a %d): ", TAM);

                printf("\nLINHA: ");
                scanf("%d", &i);
                printf("\nCOLUNA: ");
                scanf("%d", &j);

                printf("0 - Matriz A\n1 - Matriz B\n2 - Matriz C\n");

                scanf("%d", &escolha);

                switch(escolha){
                case 0:
                    Buscar_Elemento_Mat(opcao, i, j, a);
                    break;

                case 1:
                    Buscar_Elemento_Mat(opcao, i, j, b);
                    break;

                case 2:
                    Buscar_Elemento_Mat(opcao, i, j, c);
                    break;

                default:
                    Menu(index, a, b, c);
                    break;
                }
                break;
			}

//		Case default para tentativas falsas.
		default:
			erros++;
			break;
		}
		return erros;
}

int main ( ) {
	int index = 1, erros = 0, aux;
	matriz_solar a, b, c;
//	Inicializar(a);
//	Inicializar(b);
//	Inicializar(c);

	//Continua a execução até que se digite 0.
	while (index != 0 && erros < LIMITE){
		//Fornece as opções do TAD.
		printf("0 - Sair do programa.\n"); //implementado :]
		printf("1 - Ler matriz\n"); //implementado
		printf("2 - Somar matrizes e seus elementos\n"); // implementado
		printf("3 - Subtrair matrizes e seus elementos\n"); //implementado
		printf("4 - Multiplicar matrizes e seus elementos\n"); //implementado
		printf("5 - Calcular media das matrizes e seus elementos\n"); //implementado
		printf("6 - Exibir matrizes e seus elementos\n"); //implementado
		printf("7 - Buscar elementos em uma matriz\n\n"); //implementado

		scanf("%d", &index);

        aux = Menu(index, a, b, c);

        if(aux){
            erros += aux;
            printf("\nErro: Opcao inexistente. Tentativas restantes = %d\n\n", LIMITE - erros);
        }

		getchar();
		getchar();

		system ("clear");
		system ("cls");
	}

	return 0;
}
