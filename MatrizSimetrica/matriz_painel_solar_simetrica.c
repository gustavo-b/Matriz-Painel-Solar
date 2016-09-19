#include <stdio.h>
#include <string.h>
#define TAM 4 //Definição do tamanho das colunas e linhas das matrizes.
#define M (((TAM * TAM) + TAM) / 2) //Definição do tamanho do vetor da matriz especial.
#define LIMITE 5 //Limite de erros possíveis
#define AREA 100 //capacidade de geração dos painéis em Watt/hora
#define EFIC_MAX 0.22 //eficiência máxima de um painel

/*
	Este programa realiza o controle de matrizes,
	utilizando como tema o gerenciamentos dos
	painéis solares de uma usina.


	TAD: Dados int e float
	1 - Ler Matrizes
	2 - Somar elementos de matrizes
	3 - Subtrair elementos de matrizes
	4 - Multiplicar elementos de matrizes
	5 - Caclular média de elementos de matrizes
	6 - Exibir matriz
	7 - Buscar elementos na matriz
	8 - Gerar um relatório dos dados presentes na matriz
*/


typedef struct{
	int ativo; //recebe 0 {inativo} ou 1 {ativo}
	float geracao; //recebe geração em Watts
	float eficiencia; //recebe ((geração/AREA)/EFIC_MAX)/10
}Painel;

typedef Painel vetor_solar[M];

void Inicializar(vetor_solar a){
	int i;

	for(i = 0; i < TAM; i++){
		a[i].geracao = 0;
	    a[i].eficiencia = 0;
	}
}

int Map_Mat(int i, int j){
	int k;
	k = (((i * i) - i) / 2) + j - 1;
	return k;
}

void Ler_Mat(vetor_solar a) {
	int i, j, k = 0;

	for(i = 0; i < TAM; i++){
		for(j = 0; j <= i; j++){
			printf("\nEntre se o painel [%d][%d] esta ativo: \n0 - NAO\n1 - SIM\n", i + 1, j + 1);
			scanf("%d", &a[k].ativo);
			if(a[k].ativo){
				printf("Entre com quantos Watts o painel [%d][%d] gerou: ", i + 1, j + 1);
      			scanf("%f", &a[k].geracao);
        		a[k].eficiencia = (float)((a[k].geracao / AREA) / EFIC_MAX) / 10;
        		printf("A eficiencia do painel [%d][%d] e: %.2f%%\n", i + 1, j + 1, a[k].eficiencia);
			}
			else{
				a[k].geracao = 0;
				a[k].eficiencia = 0;
			}

        	k++;
		}
	}
}

void Exibir_Mat(vetor_solar a) {
    int i, j, k;

    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){

                printf("Painel [%d][%d]", i + 1, j + 1);

            printf("\t\t");
        }

        printf("\n");

        for(j = 0; j < TAM; j++){

            printf("Ativo: ");
            if(i < j){
            	k = Map_Mat(j + 1, i + 1);
				if(a[k].ativo)
					printf("SIM");
				else
					printf("NAO");
			}
            else{
            	k = Map_Mat(i + 1, j + 1);
				if(a[k].ativo)
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
                printf("Ger.: %.2f W", a[k].geracao );
                if(a[k].geracao > 9999 || a[k].geracao < -999) printf("\t");
            	else printf("\t\t");
            }
            else {
            	k = Map_Mat(i + 1, j + 1);
            	printf("Ger.: %.2f W", a[k].geracao );
                if(a[k].geracao > 9999 || a[k].geracao < -999) printf("\t");
            	else printf("\t\t");
			}

        }
        printf("\n");

		for(j = 0; j < TAM; j++){

            if(i < j){
            	k = Map_Mat(j + 1, i + 1);
                printf("Efic.: %.2f%%", a[k].eficiencia );
                if(a[k].eficiencia > 9999 || a[k].eficiencia < -999) printf("\t");
           		else printf("\t\t");
            }
            else {
            	k = Map_Mat(i + 1, j + 1);
            	printf("Efic.: %.2f%%", a[k].eficiencia );
                if(a[k].eficiencia > 9999 || a[k].eficiencia < -999) printf("\t");
           		else printf("\t\t");
			}

        }
        printf("\n\n");
    }
}


void Somar_Mat(vetor_solar a, vetor_solar b, vetor_solar c) {
	int i;

	for(i = 0; i < M; i++){
		c[i].ativo = a[i].ativo + b[i].ativo;
		c[i].geracao = (a[i].geracao) + (b[i].geracao);
        c[i].eficiencia = ((c[i].geracao / (AREA * 2)) / EFIC_MAX) / 10;
    }

    Exibir_Mat(c);
}

void Subtrair_Mat(vetor_solar a, vetor_solar b, vetor_solar c) {
   int j;

    for(j = 0; j < M; j++){
    	c[j].ativo = a[j].ativo + b[j].ativo;
        c[j].geracao = (a[j].geracao) - (b[j].geracao);
        c[j].eficiencia = ((c[j].geracao / (AREA * 2)) / EFIC_MAX) / 10;
        //Ativo continua como soma, pois se um deles estiver ativo, já basta.
    }

    Exibir_Mat(c);
}

void Multiplicar_Mat(vetor_solar a, vetor_solar b, vetor_solar c) {

	Inicializar(c);
    int i;

	for (i = 0; i < M; i++) {
		c[i].ativo = a[i].ativo + b[i].ativo;
		c[i].geracao = (a[i].geracao * b[i].geracao);
    	c[i].eficiencia = ((c[i].geracao / (AREA * ((TAM * 2) - 1) )) / EFIC_MAX) / 100000;
	}

    Exibir_Mat(c);
}

void Media_Mat(vetor_solar a, vetor_solar b, vetor_solar c) {
	int j;

	for(j = 0; j < M; j++){
		c[j].ativo = a[j].ativo + b[j].ativo;
		c[j].geracao = (a[j].geracao + b[j].geracao) / 2;
		c[j].eficiencia = (a[j].eficiencia + b[j].eficiencia) / 2;
	}

	Exibir_Mat(c);
}

void Relatorio (vetor_solar a){

    int i = 0, quant_ativos = 0;
    float somaWatts = 0, somaEff = 0, eficienciatotal;

    for(i = 0; i < M; i++){
		if(Map_Mat(i, i) != i){ //A Matriz simétrica tem seu valor duplicado somente quando estamos fora da diagonal.
            somaWatts += (a[i].geracao * 2);
            somaEff += (a[i].eficiencia * 2);
		}
		else{
            somaWatts += a[i].geracao;
            somaEff += a[i].eficiencia;
		}

		if(a[i].ativo){
            if(Map_Mat(i, i) != i) //A Matriz simétrica tem seu valor duplicado somente quando estamos fora da diagonal.
                quant_ativos += 2;
            else quant_ativos++;
		}

    }

	eficienciatotal = somaEff / (TAM * TAM);

    printf("\n************RELATORIO GERAL**************\n");
    printf("*  \t\t\t\t\t*\n*\t\t\t\t\t*\n");
    printf("*  Paineis Ativados: %d\t\t\t*\n", quant_ativos);
    printf("*  Paineis Desativados: %d\t\t*\n", M - quant_ativos );
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
    printf("*  Media Eficiencia: %.2f%%\t\t*\n", eficienciatotal );
    if(eficienciatotal >= 16){
    	printf("*  EFICIENCIA ALTA\t\t\t*\n");
	}
	else{
		if(eficienciatotal >= 15){
			printf("*  ACIMA DA MEDIA DE EFICIENCIA\t\t*\n");
		}
		else{
			if(eficienciatotal >= 14){
				printf("*  EFICIENCIA MEDIA\t\t\t*\n");
			}
			else{
				if(eficienciatotal >= 13){
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

void Buscar_Elemento_Mat(int f, int i, int j, vetor_solar a) {
	int k;
	if(i < j){
        k = Map_Mat(j, i);
        switch(f){
        case 0:
            if(a[k].ativo)
                printf("\n\nATIVADO");
            else
                printf("\n\nDESATIVADO");
            break;

        case 1:
            printf("\n\nO Painel[%d][%d] gerou um total de: %.2f W\n", i , j , a[k].geracao); //geracao
            break;

        case 2:
            printf("\n\nO Painel[%d][%d] apresentou uma eficiencia de: %.2f%%\n", i, j, a[k].eficiencia); //eficiencia
            break;

        default:
            break;
        }
    }
    	else{
            k = Map_Mat(i, j);
            switch(f){
            case 0:
                if(a[k].ativo)
                    printf("\n\nATIVADO");
                else
                    printf("\n\nDESATIVADO");
                break;

            case 1:
                printf("\n\nO Painel[%d][%d] gerou um total de: %.2f W\n", i , j , a[k].geracao); //geracao
                break;

            case 2:
                printf("\n\nO Painel[%d][%d] apresentou uma eficiencia de: %.2f%%\n", i, j, a[k].eficiencia); //eficiencia
                break;

            default:
                break;
        }
    }
}

int Menu (int index, vetor_solar a, vetor_solar b, vetor_solar c){

    int escolha, erros = 0, opcao, i, j;

    switch (index) {

		case 0:
		    printf("Obrigado por usar o APOLO MANAGER.");
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
			Somar_Mat(a, b, c);
			break;

		case 3:
			printf("0 - Matriz A - Matriz B\n1 - Matriz B - Matriz A\n");
			int escolha;
			scanf("%d", &escolha);
			if(escolha == 1)
				Subtrair_Mat(b, a, c);
			else if(escolha == 0)
				Subtrair_Mat(a, b, c);
			else Menu(index, a, b, c);
			break;

		case 4:
			Multiplicar_Mat(a, b, c);
			break;

		case 5: //media dos elementos
			Media_Mat(a, b, c);
			break;

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

		case 7:
			printf("\n0 - Ativo\n");
			printf("1 - Geracao\n");
			printf("2 - Eficiencia\n");

			scanf("%d", &opcao);

			if(opcao > 2 || opcao < 0){
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

        case 8:
            printf("0 - Matriz A\n1 - Matriz B\n2 - Matriz C\n");

            scanf("%d", &escolha);

            switch(escolha){
            case 0:
                Relatorio(a);
                break;

            case 1:
                Relatorio(b);
                break;

            case 2:
                Relatorio(c);
                break;

            default:
                Menu(index, a, b, c);
                break;
            }
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
	vetor_solar a, b, c;
	Inicializar(a);
	Inicializar(b);
	Inicializar(c);

    printf("==========Bem vindo ao Apolo Manager==========\n\n");

	//Continua a execução até que se digite 0.
	while (index != 0 && erros < LIMITE){
		//Fornece as opções do TAD.
		printf("Escolha alguma das opcoes abaixo para gerenciar os Paineis Solares:\n\n");
		printf("0 - Sair do programa.\n"); //implementado :]
		printf("1 - Ler matriz\n"); //implementado
		printf("2 - Somar matrizes e seus elementos\n"); // implementado
		printf("3 - Subtrair matrizes e seus elementos\n"); //implementado
		printf("4 - Multiplicar matrizes e seus elementos\n"); //implementado
		printf("5 - Calcular media das matrizes e seus elementos\n"); //implementado
		printf("6 - Exibir matrizes e seus elementos\n"); //implementado
		printf("7 - Buscar elementos em uma matriz\n"); //implementado
		printf("8 - Relatorio Geral\n\n"); //implementado

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
