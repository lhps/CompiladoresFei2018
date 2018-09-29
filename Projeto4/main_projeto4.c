// ConsoleApplication2.cpp : define o ponto de entrada para o aplicativo do console.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//5+3*2-1

//5+(2*(2+1*5)*3)+5
char entrada[200], tempS[10], m[40][10], tempC;
int tempN;
int p = 0, pos = 0, pS = 0;;

void E();
void A();
void B();
void C();
void D();


void inicializaMatriz() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 10; j++)
		{
			m[i][j] = '\0';
		}
	}
}

void E() {
	A();
}
void A() {
	if (entrada[pos] >= '0' && entrada[pos] <= '9') {
		pos++;
		B();
	}
	else if (entrada[pos] == '(') {
		pos++;
		C();
	}
	else if (p > 0) {
		D();
	}
	else {
		printf("Rejeita!\n");
	}
}

void B() {
	if (entrada[pos] == '+' || entrada[pos] == '-' || entrada[pos] == '*' || entrada[pos] == '/') {
		pos++;
		A();
	}
	else if (p > 0 && entrada[pos] == ')') {
		D();
	}
	else if (entrada[pos] == '\0' && p == 0) {
		printf("Aceita!\n");
	}
	else {
		printf("Rejeita!\n");
	}
}

void C() {
	p++;
	E();
}

void D() {
	if (entrada[pos] == ')') {
		p--;
		pos++;
		B();
	}
}




int main() {

	gets(entrada);
	E();
	system("pause");
	return 0;
}

