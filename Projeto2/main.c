// ConsoleApplication1.cpp : define o ponto de entrada para o aplicativo do console.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char entrada[200], tempS[10], m[40][10];
char tempN[10];
int p = 0, pos = 0;

void e0();
void e1();
void e2();
int iguais(char    um[], char dois[]);
void copiaM(char f[]);
void copiaT(char f[]);
int copiaN(char f[]);
void inicializaMatriz();
int existe();
void printatabela();
int copiaN2(char f[]);

void inicializaMatriz() {
    int i, j;
    for (i = 0; i < 40; i++) {
        //printf("Linha %d:", i);
        for ( j = 0; j < 10; j++)
        {
            m[i][j] = '\0';
            //printf("%c", m[i][j]);
        }
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
    if ((entrada[pos] >= 'a' && entrada[pos] <= 'z') ||  (entrada[pos] >= 'A' && entrada[pos] <= 'Z')) {
        copiaT(entrada);
        e1();
    }
    else if (entrada[pos] >= '0' && entrada[pos] <= '9') {
        copiaN(entrada);
        e2();
    }
    if (entrada[pos] == '\0') {
        printf("\nTabela de variaveis\n");
        printatabela();
        exit(0);
    }

}

void e1() {
    int e = existe();
    if (e == -1) {
        copiaM(tempS);
        printf("V(%d) ", p);
        p++;
    }
    else {
        printf("V(%d) ", e);
    }
    //pos++;
    e0();
}

void e2() {
    int tamanho = copiaN2(tempN);
    int numero = 0, cs_decimal = 1, i;
    for (i = 0; i <= tamanho; i++) {
        numero += (tempN[tamanho - i] - '0') * cs_decimal;
        cs_decimal *= 10;
    }
    printf("N(%d) ", numero);
    //pos++;
    e0();
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
    for (i = 0; i<=p; i++)
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
void copiaT(char f[]) {
    int c;
    for (c = 0; f[pos] != ' ' && f[pos] != '\0'; c++){
        tempS[c] = f[pos];
        pos++;
    }
    /*
    for (c = 0;f[pos] != ' '; c++){
        tempS[c] = f[pos];
        pos++;
    }*/


    tempS[c] = 0;
}
int copiaN(char f[]) {
    int c;
    for (c = 0; f[pos] != ' ' && f[pos] != '\0'; c++, pos++) {
        tempN[c] = f[pos];
    }
    tempN[c] = 0;
    return c - 1;
}
int copiaN2(char f[]) {
    int c;
    for (c = 0; f[c] != ' ' && f[c] != '\0'; c++) {
        //tempN[c] = f[pos];
    }
    tempN[c] = 0;
    return c - 1;
}
int main() {

    gets(entrada);
    inicializaMatriz();
    e0();
    printatabela();
    system("pause");
    return 0;
}