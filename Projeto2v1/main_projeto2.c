// ConsoleApplication2.cpp : define o ponto de entrada para o aplicativo do console.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char entrada[200], tempS[10], m[40][10];
int tempN;
int p = 0, pos = 0, pS = 0;;

void e0();
void e1();
void e2();
int iguais(char    um[], char dois[]);
void copiaM(char f[]);
void copiaT(char f);
void copiaN(char f);
void inicializaMatriz();
void finalizaTempS();
int existe();
void printatabela();
int copiaN2(char f[]);

void inicializaMatriz() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 10; j++)
		{
			m[i][j] = '\0';
		}
	}
}
void finalizaTempS() {
	int j;
	for (j = 0; j < 10; j++)
	{
		tempS[j] = '\0';
	}
}
void printatabela() {
	int i, j;
	for (i = 0; i < p; i++) {
		printf("%d....", i);
		for (j = 0; j<10; j++) {
			printf("%c", m[i][j]);
		}
		printf("\n");
	}

}
void e0() {

	if (entrada[pos] == ' ') {
		pos++;
		e0();
	}
	if ((entrada[pos] >= 'a' && entrada[pos] <= 'z') || (entrada[pos] >= 'A' && entrada[pos] <= 'Z')) {
		copiaT(entrada[pos]);
		pS++;
		pos++;
		e1();
	}
	else if (entrada[pos] >= '0' && entrada[pos] <= '9') {
		copiaN(entrada[pos]);
		pos++;
		e2();
	}
	if (entrada[pos] == '\0') {
		if (m[0][0] == '\0') {
			printf("\n");
			getchar();
			exit(0);
		}
		else {
			printf("\n===================");
			printf("\nVariables Table\n");
			printf("===================\n");
			printatabela();
			getchar();
			exit(0);
		}
	}

}

void e1() {

	if ((entrada[pos] >= 'a' && entrada[pos] <= 'z') || (entrada[pos] >= 'A' && entrada[pos] <= 'Z')) {
		copiaT(entrada[pos]);
		pS++;
		pos++;
		e1();
	}
	else if (entrada[pos] >= '0' && entrada[pos] <= '9') {
		copiaT(entrada[pos]);
		pS++;
		pos++; 
		e1();
	}
	else {
		int e = existe();
		if (e == -1) {
			copiaM(tempS);
			printf("V(%d) ", p);
			p++;
			finalizaTempS();
			pS = 0;
		}
		else {
			printf("V(%d) ", e);
			finalizaTempS();
			pS = 0;
		}

	}
	e0();
}

void e2() {
	if (entrada[pos] >= '0' && entrada[pos] <= '9') {
		tempN = tempN * 10 + (entrada[pos ] - '0');
		pos++;
		e2();
	}
	else {
		printf("N(%d) ", tempN);
		e0();
	}
}
int iguais(char    um[], char dois[]) {
	int c;
	for (c = 0; um[c] != 0; c++) {
		if (um[c] != dois[c]) {
			return 0;
		}
	}
	if (um[c] != dois[c])
		return 0;
	else
		return 1;
}
int existe() {
	int i;
	for (i = 0; i <= p; i++)
		if (iguais(m[i], tempS))
			return i;

	return -1;
}
void copiaM(char f[]) {
	int c;
	for (c = 0; f[c] != '\0'; c++)
		m[p][c] = f[c];
	m[p][c] = '\0';
}
void copiaT(char f) {
	tempS[pS] = f;
}
void copiaN(char f) {
	tempN = f - '0';
}
int main() {

	gets(entrada);
	inicializaMatriz();
	e0();
	printatabela();
	system("pause");
	return 0;
}
