#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int valida(char v[], char linguagem[]) {
	int aux = 0;
	for (int i = 0; v[i] != 0; i++) {
		for (int j = 0; linguagem[j] != 0; j++)
			if (v[i] == linguagem[j])
				aux++;

		if (aux == 0)
			return i;

		aux = 0;
	}

	return -1;
}

int valida(char v[]) {
	int i = 0;
	while (v[i] != 0) {
		if (v[i] == 'i' && v[i + 1] == 'f')
			i += 2;
		else if (v[i] == 'e' && v[i + 1] == 'l' && v[i + 2] == 's' && v[i + 3] == 'e')
			i += 4;
		else if (v[i] == 'a')
			i++;
		else if (v[i] == 'b')
			i++;
		else
			return i;
	}

	return -1;
}

int main()
{
	char linguagem[5] = "ab+=",
		linguagem2[4][5] = { "if",
		"else",
		"a",
		"b"
	};
	char input[100];
	char erro1 = 45, erro2 = 94;
	int res, a;
	scanf("%s", &input);
	//res = valida(input, linguagem);
	res = valida(input);
	if (res == -1)
		printf("Aceita\n");
	else {
		printf("Rejeitado:\n%s\n", input);
		for (a = 0; a < res; a++)
			printf("%c", erro1);
		printf("%c\n", erro2);
	}

	system("pause");
	return 0;
}