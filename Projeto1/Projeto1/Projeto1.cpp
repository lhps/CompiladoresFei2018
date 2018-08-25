#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdafx.h"
#include "Archives.h"

/*
Fácil
2
a
b
2
0
1
1
1
-1
-1
1
Nome
1
Difícil
3
a
b
c
3
0
1
2
1
-1
-1
-1
2
0
-1
-1
-1
Nome
1
*/
//Global variables
int tabLevel = 0;

//Functions


void initializeGlobalVars() {
	int i;
	tabLevel = 0;
}

// Main Functions

void initialize(Automaton *aut) {
	int i, j;

	printf("Quantos simbolos tem o alfabeto? ");
	scanf("%d", &aut->qtAlfabect);
	fflush(stdin);

	aut->alfabect = (char*)malloc(aut->qtAlfabect * sizeof(char));

	for (i = 0; i < aut->qtAlfabect; i++) {
		printf("Qual o simbolo %d?", i);
		scanf("%c", aut->alfabect + i);
		fflush(stdin);
	}

	printf("Quantos estados tem o automato? ");
	scanf("%d", &aut->states);
	fflush(stdin);

	printf("Qual o estado inicial? ");
	scanf("%d", &aut->inicialState);
	fflush(stdin);

	printf("Quantos estados finais? ");
	scanf("%d", &aut->finalStates);
	fflush(stdin);

	aut->finalStates = (int)malloc(aut->finalStates * sizeof(int));
	for (i = 0; i < aut->finalStates; i++)
	{
		printf("Qual o estado final %d? ", i);
		scanf("%d", aut->finalStates + i);
		fflush(stdin);
	}

	//creation of transition matrix
	aut->transitionMatrix = (int**)malloc(aut->states * sizeof(int*));
	for (i = 0; i < aut->states; i++) {
		aut->transitionMatrix[i] = (int*)malloc(aut->qtAlfabect * sizeof(int));
	}

	for (i = 0; i < aut->states; i++) {
		for (j = 0; j < aut->qtAlfabect; j++)
		{
			printf("Para o estado e%d e o simbolo %c, qual o proximo estado? ", i, aut->alfabect[j]);
			scanf("%d", *(aut->transitionMatrix + i) + j);
			//scanf("%d", aut->transitionMatrix[i][j]);
			fflush(stdin);
		}
	}

	printf("Qual nome deseja dar para o programa? ");
	scanf("%s", &aut->programName);
	fflush(stdin);

	printf("(1) goto, (2) funcao? ");
	scanf("%d", &aut->type);
	fflush(stdin);
}

void destructObject(Automaton *aut) {
	int i;
	for (i = 0; i < aut->states; i++)
		free(aut->transitionMatrix[i]);

	free(aut->transitionMatrix);
	free(aut->alfabect);
	free((int*)aut->finalStates);
	free(aut);

}


int main(int argc, char *argv[])
{

	char opcao;
	Automaton *New;
	New =(Automaton*) malloc(sizeof(Automaton));
	initializeGlobalVars();
	printf("*********** GERADOR DE PROGRAMA ***********\n");
    initialize(New);
	generateCodeAutomatons(New);
    printf("*********** PROGRAMA GERADO COM SUCESSO ***********\n\n");
	system("pause");


	//printf("Deseja testar o automato em questao? [S/N]");
	//scanf("%c", &opcao);

	//Tentar compilar e abrir o programa gerado pelo comando system

	destructObject(New);

	return 0;
}