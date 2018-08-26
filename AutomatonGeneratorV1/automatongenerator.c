#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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



#pragma once
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#define TAM_MAX 200

//Types
typedef struct {
	int qtAlfabect,
		states,
		finalStates,
		inicialState,
		*finalStatesvector,
		**transitionMatrix,
		type;
	char *alfabect,
		programName[TAM_MAX];
} Automaton;


//Functions


int linearSearch(int *v, int tam, int n) {
	int i;
	for (i = 0; i < tam; i++) {
		if (v[i] == n)
			return 1;

		return 0;
	}
}

char * tabFunction(int tam) {
	int i;
	char  *str;
	str = malloc(tam + 1);
	for (i = 0; i < tam; i++)
		str[i] = '\t';
	str[i] = '\0';

	return str;
}

void insertLibraries(FILE *arq) {
	fprintf(arq, "#include <stdio.h>\n#include <stdlib.h>\n\n");
}

void insertPrototypes(FILE *arq, Automaton *aut) {
	int i;
	fprintf(arq, "//Protótipos das funções\nvoidaceita();\nvoid rejeita();\n");
	for (i = 0; i < aut->states; i++)
	{
		fprintf(arq, "void e%d();\n", i);
	}

	fprintf(arq, "\n");
}

void insertMain(FILE* arq, Automaton *aut) {
	fprintf(arq, "//Main\nint main(){\n%sgets(palavra);\n%spos = 0;\n%se%d();\n", tabFunction(1), tabFunction(1), tabFunction(1), aut->inicialState);
}

void closeMain(FILE* arq) {
	fprintf(arq, "}\n\n");
}

void insertGlobalsVariables(FILE *arq) {
	fprintf(arq, "//Variáveis globais\nchar palavra[100];\nint pos = 0;\n\n");
}

void insertFunctions(FILE *arq, Automaton *aut) {
	int i, j, auxIni = 0, auxEnd = 0;

	fprintf(arq, "void aceita(){\n%sprintf(\"Aceita!\");\n}\n\nvoid rejeita(){\n%sprintf(\"Rejeita!\");\n}\n\n", tabFunction(1), tabFunction(1));

	for ( i = 0; i < aut->states; i++)
	{
		fprintf(arq,"void e%d(){\n", i);
		auxEnd = 0;
		auxIni = 0;

		for ( j = 0; j < aut->qtAlfabect; j++)
		{
			if (aut->transitionMatrix[i][j] != -1)
			{
				fprintf(arq, "%s%s(palavra[pos] == '%c'){\n%spos++;\n%se%d();\n%s}",
					auxIni == 0 ? tabFunction(1) : "", auxIni == 0 ? "if" : "else if",
					aut->alfabect[j], tabFunction(2), tabFunction(2), aut->transitionMatrix[i][j], tabFunction(1));
				auxEnd++;
				auxIni;

			}
		}
		if (linearSearch(aut->finalStatesvector, aut->finalStates, i))
		{
			fprintf(arq, "%s%sif(palavra[pos] == '\\0'){\n%saceita();\n%s}",
				auxIni == 0 ? tabFunction(1) : "", auxEnd == 0 ? "" : "else ", tabFunction(2), tabFunction(1));
		}
		fprintf(arq, "else\n%srejeita();\n}\n\n", tabFunction(2));

	}
}

void generateCodeAutomatons(Automaton *aut){
	FILE *arq;
	arq = fopen(strcat(aut->programName, ".c"), "w+");
	insertLibraries(arq);
	insertGlobalsVariables(arq);
	insertPrototypes(arq,aut);
	
	if (aut->type == 2)
		insertFunctions(arq, aut);
	else
		//insereGoTo(arq, aut);	

	
	fclose(arq);

	insertMain(arq, aut);
	closeMain(arq);
	
}





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

	aut->alfabect = malloc(aut->qtAlfabect * sizeof(char));

	for (i = 0; i < aut->qtAlfabect; i++) {
		printf("Qual o simbolo %d?", i);
		scanf("%c", &aut->alfabect + i);
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

	aut->finalStates = malloc(aut->finalStates * sizeof(int));
	for (i = 0; i < aut->finalStates; i++)
	{
		printf("Qual o estado final %d? ", i);
		scanf("%d", &aut->finalStates + i);
		fflush(stdin);
	}

	//creation of transition matrix
	aut->transitionMatrix = malloc(aut->states * sizeof(int*));
	for (i = 0; i < aut->states; i++) {
		aut->transitionMatrix[i] = malloc(aut->qtAlfabect * sizeof(int));
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
	New = malloc(sizeof(Automaton));
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
