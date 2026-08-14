#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <token.h>

int main() {
	SetConsoleOutputCP(CP_UTF8);

	char test_string[] = "3 + 4 * (22 - 1)";

	TokenList* token_list = token_list_create(10);
	if (token_list == NULL) return 1;

	for (size_t i = 0; i < strlen(test_string); i++) {

		if (isdigit(test_string[i]) != 0) {
			char number[32] = {0};
			size_t j = 0;

			while (isdigit(test_string[i]) != 0) {
				number[j] = test_string[i];

				i++;
				j++;
			}

			int value = atoi(number);
			TokenValue t_v;
			t_v.number_value = value;

			if (!token_list_add(token_list, NUMBER, t_v)) {
				printf("Erro: falha ao adicionar token (memoria).\n");
				token_list_destroy(&token_list);
				return 1;
			}
			
			i--;

		} else if (test_string[i] == '+') {
			TokenValue t_v;
			t_v.symbol_value = '+';
			if (!token_list_add(token_list, OPERATOR, t_v)) {
				printf("Erro: falha ao adicionar token (memoria).\n");
				token_list_destroy(&token_list);
				return 1;
			}
		} else if (test_string[i] == '-') {
			TokenValue t_v;
			t_v.symbol_value = '-';
			if (!token_list_add(token_list, OPERATOR, t_v)) {
				printf("Erro: falha ao adicionar token (memoria).\n");
				token_list_destroy(&token_list);
				return 1;
			}
		} else if (test_string[i] == '*') {
			TokenValue t_v;
			t_v.symbol_value = '*';
			if (!token_list_add(token_list, OPERATOR, t_v)) {
				printf("Erro: falha ao adicionar token (memoria).\n");
				token_list_destroy(&token_list);
				return 1;
			}
		} else if (test_string[i] == '/') {
			TokenValue t_v;
			t_v.symbol_value = '/';
			if (!token_list_add(token_list, OPERATOR, t_v)) {
				printf("Erro: falha ao adicionar token (memoria).\n");
				token_list_destroy(&token_list);
				return 1;
			}
		} else if (test_string[i] == '(') {
			TokenValue t_v;
			t_v.symbol_value = '(';
			if (!token_list_add(token_list, GROUPING_SYMBOL, t_v)) {
				printf("Erro: falha ao adicionar token (memoria).\n");
				token_list_destroy(&token_list);
				return 1;
			}
		} else if (test_string[i] == ')') {
			TokenValue t_v;
			t_v.symbol_value = ')';
			if (!token_list_add(token_list, GROUPING_SYMBOL, t_v)) {
				printf("Erro: falha ao adicionar token (memoria).\n");
				token_list_destroy(&token_list);
				return 1;
			}
		} else if (isspace(test_string[i]) != 0) {
			// Ignorando espaço.
		} else {
			printf("Erro: caractere inválido '%c'\n", test_string[i]);
			token_list_destroy(&token_list);

			return 1;
		}

	}

	token_list_print(token_list);

	system("pause");

	token_list_destroy(&token_list);

	return 0;
}