#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <token.h>

static bool token_list_add_value_number(TokenList* token_list, int number) {
	TokenValue t_v;
	t_v.number_value = number;

	if (!token_list_add(token_list, NUMBER, t_v)) {
		printf("Erro: falha ao adicionar token (memória).\n");
		token_list_destroy(&token_list);
		return false;
	}

	return true;
}

static bool token_list_add_value_symbol(TokenList* token_list, ParserTokenType token_type, char symbol) {
	TokenValue t_v;
	t_v.symbol_value = symbol;

	if (!token_list_add(token_list, token_type, t_v)) {
		printf("Erro: falha ao adicionar token (memória).\n");
		token_list_destroy(&token_list);
		return false;
	}

	return true;
}

int main() {
	SetConsoleOutputCP(CP_UTF8);

	char test_string[] = "3 + 4 * { 7 / 2 + [ 8 - 182 * (22 - 1)]}";

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
			if (!token_list_add_value_number(token_list, value)) return 1;
			
			i--;

		} else if (test_string[i] == '+') {
			if (!token_list_add_value_symbol(token_list, OPERATOR, '+')) return 1;
		} else if (test_string[i] == '-') {
			if (!token_list_add_value_symbol(token_list, OPERATOR, '-')) return 1;
		} else if (test_string[i] == '*') {
			if (!token_list_add_value_symbol(token_list, OPERATOR, '*')) return 1;
		} else if (test_string[i] == '/') {
			if (!token_list_add_value_symbol(token_list, OPERATOR, '/')) return 1;
		} else if (test_string[i] == '(') {
			if (!token_list_add_value_symbol(token_list, GROUPING_SYMBOL, '(')) return 1;
		} else if (test_string[i] == ')') {
			if (!token_list_add_value_symbol(token_list, GROUPING_SYMBOL, ')')) return 1;
		} else if (test_string[i] == '[') {
			if (!token_list_add_value_symbol(token_list, GROUPING_SYMBOL, '[')) return 1;
		} else if (test_string[i] == ']') {
			if (!token_list_add_value_symbol(token_list, GROUPING_SYMBOL, ']')) return 1;
		} else if (test_string[i] == '{') {
			if (!token_list_add_value_symbol(token_list, GROUPING_SYMBOL, '{')) return 1;
		} else if (test_string[i] == '}') {
			if (!token_list_add_value_symbol(token_list, GROUPING_SYMBOL, '}')) return 1;
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