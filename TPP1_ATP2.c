//Operações sobre Conjuntos – Arrays/Arranjos
//TRABALHO PRÁTICO DE PROGRAMAÇÃO 1
//ALGORITMOS E TÉCNICAS DE PROGRAMAÇÃO II
//GRUPO: VINÍCIUS VEDOVOTTO e JOÃO PEDRO DA SILVA BAPTISTA
//CIÊNCIA DA COMPUTAÇÃO, 2017
//FCT/UNESP - PRESIDENTE PRUDENTE
//AMBIENTE Linux - Ubuntu 16.04 LTS.

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>

#define PULA "\n\n\n"

//=============================SCOPO=============================================

int   Menu(void);
short Continua(void);
void  Imprime(int *V1, int dim);
void  GerarA(int *V, int dim);
void  GerarB(int *V, int dim);
void  Ordena(int *V, int dim);
void  Troca(int *V1, int i);
int   Encontra_Inter(int *inter, int *V1, int *V2, int dim1, int dim2);
void  Encontra_Uniao(int *uniao, int *V1, int *V2, int dim1, int dim2);
int   Encontra_Diferenca(int *dif, int* V1, int* V2, int dim1, int dim2);
short Busca_Binaria_Iterativa(int *V1, int chave, int dim);
short Busca_Linear(int *V, int dim);

//============================ MAIN =============================================

int main(void) {

	setlocale(LC_ALL, "Portuguese");

	printf("          =======================================================\n");
	printf("          = BEM VINDO AO PROGRAMA DE OPERAÇÕES SOBRE CONJUNTOS! =\n");
	printf("          =======================================================\n");

	int m, n, resp, opcao, DimInter, DimDif1, DimDif2, chave, erro = 0, verificador;
	printf("\n>Qual o tamanho do seu conjunto A?\n");
	scanf("%d", &m);
	printf("\n>Qual o tamanho do seu conjunto B?\n");
	scanf("%d", &n);

	int A[m], B[n], Inter[m+n], Uniao[m+n], Diferenca1[m], Diferenca2[n];

	do {
		printf("\n>Gerar randomicamente o conjunto A e B? [S,N] \n");
		scanf("%d", &resp);
		resp = getchar();
		resp = toupper(resp);
		erro = 0;

		switch(resp) {
			case 'S':

				GerarA(A, m);

				GerarB(B, n);
			break;

			case 'N':

				printf(">Entre com os valores do conjunto A: \n");
				for(int i=0; i<m; i++) {
					printf("A[%d] = ", i);
					scanf("%d", &A[i]);
				}
				puts(PULA);
				printf(">Entre com os valores do conjunto B: \n");
				for(int i=0; i<n; i++) {
					printf("B[%d] = ", i);
					scanf("%d", &B[i]);
				}
			break;

			default:
				printf("Entrada Inválida! Entre com S para SIM e N para NÃO. \n");
				erro = 1;
			break;
		}
	}
	while(erro);

	puts(PULA);

	printf("Seus conjuntos estão criados! \n");
	printf("Ordenando...   (aguarde)\n\n");

	Ordena(A, m);
	printf("Conjunto A:  \n");
    Imprime(A, m);

	Ordena(B, n);
	printf("\n\nConjunto B: \n");
	Imprime(B, n);

	do {
		puts(PULA);
		opcao = Menu();
		printf("\nVocê escolheu a opção %d\n", opcao);

		switch(opcao) {
			case 1:

				printf("\n\nA intersecção entre A e B é: \n");
				DimInter = Encontra_Inter(Inter, A, B, m, n);

				if(DimInter) {
					Imprime(Inter, DimInter);
				}
				else printf("\n⌀n");
			break;

			case 2:
				printf("\n\nA união de A e B é: \n");
				Encontra_Uniao(Uniao, A, B, m, n);
				Ordena(Uniao, m+n);
				Imprime(Uniao, (m+n));
			break;

			case 3:
				printf("A diferença (A-B) é: \n");
				DimDif1 = Encontra_Diferenca( Diferenca1, A, B, m, n);
				if(DimDif1)
					Imprime(Diferenca1, DimDif1);
				else printf("\n⌀\n");
			break;

			case 4:
				printf("A diferença (B-A) é: \n");
				DimDif2 = Encontra_Diferenca( Diferenca2, B, A, n, m);
				if(DimDif2)
					Imprime(Diferenca2, DimDif2);
    			else printf("\n⌀\n");
			break;

			case 5:

					printf(">Que valor deseja verificar se pertente a algum conjunto?\n");
					printf(">RESPOSTA: ");
					scanf("%d", &chave);

                do {
					printf("\n>Em que conjunto deseja procurar: A ou B?\n");
					printf(">RESPOSTA: ");
					scanf("%d", &resp);
					resp = getchar();
					resp = toupper(resp);
					erro = 0;

					switch(resp) {
						case 'A':
							verificador = Busca_Binaria_Iterativa( A, chave, m);
							if(verificador)
								printf("\n>>%d pertence ao conjunto A!\n\n", chave);
							else printf("\n>>%d não pertence a A!\n\n", chave);
						break;

						case 'B':
							verificador = Busca_Binaria_Iterativa( B, chave, n);
							if(verificador)
								printf("\n\n>>%d pertence ao conjunto B!\n\n", chave);
							else printf("\n\n>>%d não pertence a B!\n\n", chave);
						break;

						default:
							printf("\nEntre com A OU B! \n");
							erro = 1;
						break;
					}
				}
				while(erro);
			break;

			case 6:
                do {
					printf("\nEm que conjunto deseja verificar se possui elementos repetidos: A ou B?\n");
					printf(">RESPOSTA: ");
					scanf("%d", &resp);
					resp = getchar();
					resp = toupper(resp);
                    erro = 0;

					switch(resp) {
						case 'A':
							if (Busca_Linear(A, m))
								printf("\nExistem elementos repetidos no conjunto A!\n\n");
							else printf("\nNão existem elementos repetidos em A!\n\n");
						break;

						case 'B':
							if (Busca_Linear(B, n))
								printf("\nExistem elementos repetidos no conjunto B!\n\n");
							else printf("\nNão existem elementos repetidos em B!\n\n");
						break;

						default:
							printf("\nEntre com A OU B! \n");
							erro = 1;
						break;
					}
                }
                while(erro);
			break;

            case 7:  //Obs: Poderia ter criado apenas esta opção no lugar das opções 1, 2, 3 e 4.
                printf("\n>CONJUNTO A: \n");
                Imprime(A, m);

                printf("\n\n>CONJUNTO B: \n");
                Imprime(B, n);

                printf("\n\n>A ∩ B: \n");
                DimInter = Encontra_Inter(Inter, A, B, m, n);
				if(DimInter)
					Imprime(Inter, DimInter);
				else printf("\n⌀\n");

                printf("\n\n>A U B: \n");
                Encontra_Uniao(Uniao, A, B, m, n);
				Ordena(Uniao, m+n);
				Imprime(Uniao, (m+n));

                printf("\n\n>A - B: \n");
                DimDif1 = Encontra_Diferenca( Diferenca1, A, B, m, n);
				if(DimDif1)
					Imprime(Diferenca1, DimDif1);
				else printf("\n⌀\n");

                printf("\n\n>B - A: \n");
                DimDif2 = Encontra_Diferenca( Diferenca2, B, A, n, m);
				if(DimDif2)
					Imprime(Diferenca2, DimDif2);
    			else printf("\n⌀\n");
            break;

            case 8:
                printf("\n                   ================ ENCERRADO ================");
            break;

			default:
				printf("ERRO! Entre com as opções de 1 a 7.\n");
			break;
		}

		puts(PULA);
	}
	while(Continua());

	return 0;
}//Main

//======================== MINHAS FUNÇÕES =======================================


int Menu(void) {
	int opcao, erro;

	do {
        erro = 0;
		printf("    ESCOLHA A OPÇÃO DESEJADA:    \n");

		printf("1 - Intersecção entre A e B.\n");
		printf("2 - União entre A e B.\n");
		printf("3 - Diferença A menos B (A-B).\n");
		printf("4 - Diferença B menos A (B-A).\n");
		printf("5 - Verificar se um valor pertence a algum conjunto.\n");
		printf("6 - Verificar se há elementos repetidos em A ou em B.\n");
		printf("7 - Visualizar todos os conjuntos.\n");
        printf("8 - SAIR.\n");

		printf("> RESPOSTA: ");
		scanf("%d", &opcao);
		if((opcao<1) || (opcao>8)) {
            erro = 1;
            printf("\nEntre com um número de 1 a 8!\n\n");
		}
	}
	while(erro);

	return opcao;
}//Menu

//===============================================================================

short Continua(void) {
	int ch, erro;

	do {
		printf(">Deseja escolher outra opção? [S,N]\n");
		printf(">RESPOSTA: ");
		scanf("%d", &ch);
		ch = getchar();
		ch = toupper(ch);
		erro = 0;

		if((ch != 'S') && (ch != 'N')) erro = 1;
	}
	while (erro);

	if (ch == 'S') return 1;
	else return 0;
}//Continua

//===============================================================================

void GerarA(int *V, int dim) {
	time_t t;
	int i;

	srand((unsigned) time(&t));
	for ( i=0; i<dim; i++) {
		*(V+i) = rand()%1000;
	}
}//GerarA

//===============================================================================

void GerarB(int *V, int dim) {
	int i;

	for (i=0; i<dim; i++) {
		*(V+i) = rand()%1000;
	}
}//GerarB

//===============================================================================

void Ordena(int *V, int dim) { //Método Bolha
	int i=1, j, continua, lim;

	while((i < dim) && continua) {
		continua = 0;
		lim = dim - i;
		for(j=0; j < lim; j++)
			if(*(V+j+1) < *(V+j)) {
				Troca(V, j);
				continua = 1;
			}
		i++;
	}
}//Ordena

//===============================================================================

void Troca(int *V1, int i) {
	int aux;

	aux = *(V1+i+1);
	*(V1+i+1) = *(V1+i);
	*(V1+i) = aux;
}//Troca

//===============================================================================

int Encontra_Inter(int *inter, int *V1, int *V2, int dim1, int dim2) {
	int k=0, i, j;

	for ( i = 0; i < dim1; i++) {
		for( j = 0; j < dim2; j++) {
			if( *(V1+i) == *(V2+j) ) {
				*(inter+k) = *(V1+i);
				k++;
				break;
			}
		}
	}
	return k;
}//Intersecção

//===============================================================================

void Encontra_Uniao(int *uniao, int *V1, int *V2, int dim1, int dim2) {
	int i, k=0;

	for ( i = 0; i<dim1; i++) {
		*(uniao+k) = *(V1+i);
		k++;
	}
	for (i = 0; i<dim2; i++) {
		*(uniao+k) = *(V2+i);
		k++;
	} 
}//União

//===============================================================================

int Encontra_Diferenca(int *dif, int* V1, int* V2, int dim1, int dim2) {
	int i, j, k = 0, repete = 0;

	for ( i = 0; i < dim1; i++) {
		for ( j = 0; j < dim2; j++) {
			if( V1[i] == V2[j] ) {
				repete = 1;
				break;
			}
		}
		if (!repete) {
			dif[k] = V1[i];
			k++;
		}
		repete = 0;
	}
	return k;
}//Diferença

//===============================================================================

short Busca_Binaria_Iterativa(int *V1, int chave, int dim) {
	int ini = 0, meio, fim = dim - 1;

	while(ini <= fim) {
		meio = (ini + fim)/2;
		if(*(V1+meio) == chave) return 1;
		else if(chave < *(V1+meio)) {
			fim = meio - 1;
		}
		else ini = meio + 1;
	}
	return 0;
}//Busca Binária Iterativa

//===============================================================================

short Busca_Linear(int *V, int dim) {
	int i, j;

	for( i = 0; i < dim; i++)
		if(*(V+i) == *(V+i+1))
			return 1;
	return 0;
}//Busca Linear

//===============================================================================

void Imprime(int *V1, int dim) {
	int i;

    for( i = 0; i < dim; i++)
        printf("[%.3d]", *(V1+i));
}//Imprime

//===============================================================================



