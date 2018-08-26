#include <stdio.h>
#include <stdlib.h>

//Variáveis globais
char palavra[100];
int pos = 0;

//Main
int main(){
	gets(palavra);
	pos = 0;
	goto E0;

ACEITA:
	printf("Aceita!");
	exit(0);

REJEITA:
	printf("Rejeita!");
	exit(1);

E0:
	if(palavra[pos] == 'a'){
		pos++;
		goto E1;
	}
	else
		goto REJEITA;

E1:
	if(palavra[pos] == 'b'){
		pos++;
		goto E1;
	}
	else
		if(palavra[pos] == '\0'){
			goto ACEITA;
		}
		else
			goto REJEITA;

}

