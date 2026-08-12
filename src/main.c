/*
Fase 1 — Tokenização 
Pensa em como transformar a string "3 + 4 * (2 - 1)" numa sequência de "pedaços com significado": 
números, operadores (+ - * /), parênteses. 

Decide a estrutura pra representar um token (pode ser um struct simples com tipo + valor). 

O resultado dessa fase é uma lista de tokens, não mais uma string crua.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

int main() {
	SetConsoleOutputCP(CP_UTF8);

	char test_string[] = "3 + 4 * (22 - 1)";

	for (size_t i = 0; i < strlen(test_string); i++) {

		if (isdigit(test_string[i]) != 0) {
			char number[32] = {0};
			size_t j = 0;

			while (isdigit(test_string[i]) != 0) {
				number[j] = test_string[i];

				i++;
				j++;
			}

			printf("Numero: %s\n", number);
			i--;

		} else if (test_string[i] == '+') {
			printf("É soma!\n");
		} else if (test_string[i] == '-') {
			printf("É subtração!\n");
		} else if (test_string[i] == '*') {
			printf("É multiplicação!\n");
		} else if (test_string[i] == '/') {
			printf("É divisão!\n");
		} else if (test_string[i] == '(') {
			printf("É parêntese-abre!\n");
		} else if (test_string[i] == ')') {
			printf("É parêntese-fecha!\n");
		} else if (isspace(test_string[i]) != 0) {
			// Ignorando espaço.
		} else {
			printf("Erro: caractere inválido '%c'\n", test_string[i]);
			return 1;
		}

	}

	return 0;
}