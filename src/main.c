#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <windows.h>
#include <token.h>
#include <parser.h>
#include <input.h>

static void calculate(const char* input_expression) {
	TokenList* token_list = token_list_create(10);
	if (token_list == NULL) {
		printf("Erro: Falha ao alocar memória.\n");
		return;
	}

	size_t len = strlen(input_expression);

	for (size_t i = 0; i < len; i++) {

		if (isdigit(input_expression[i]) != 0 || input_expression[i] == '.') {
			char number[64] = { 0 };
			size_t j = 0;
			bool has_dot = false;

			while (j < sizeof(number) - 1 && (isdigit(input_expression[i]) != 0 || (input_expression[i] == '.' && !has_dot))) {
				
				if (input_expression[i] == '.') has_dot = true;

				number[j] = input_expression[i];

				i++;
				j++;
			}

			errno = 0;
			char* end_ptr = NULL;
			double value = strtod(number, &end_ptr);

			if (errno == ERANGE || end_ptr == number) {
				printf("Erro: numero invalido ou fora do intervalo '%s'\n", number);
				token_list_destroy(&token_list);
				return;
			}

			if (!token_list_add_value_number(token_list, value)) return;

			i--;
		} else if (input_expression[i] == '+') {
			if (!token_list_add_value_symbol(token_list, SUM_OPERATOR, '+')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (input_expression[i] == '-') {
			if (!token_list_add_value_symbol(token_list, SUB_OPERATOR, '-')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (input_expression[i] == '*') {
			if (!token_list_add_value_symbol(token_list, MULT_OPERATOR, '*')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (input_expression[i] == '/') {
			if (!token_list_add_value_symbol(token_list, DIV_OPERATOR, '/')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (input_expression[i] == '^') {
			if (!token_list_add_value_symbol(token_list, POW_OPERATOR, '^')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (input_expression[i] == '(') {
			if (!token_list_add_value_symbol(token_list, OPEN_PARENTHESES, '(')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (input_expression[i] == ')') {
			if (!token_list_add_value_symbol(token_list, CLOSE_PARENTHESES, ')')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (input_expression[i] == '[') {
			if (!token_list_add_value_symbol(token_list, OPEN_BRACKETS, '[')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (input_expression[i] == ']') {
			if (!token_list_add_value_symbol(token_list, CLOSE_BRACKETS, ']')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (input_expression[i] == '{') {
			if (!token_list_add_value_symbol(token_list, OPEN_BRACES, '{')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (input_expression[i] == '}') {
			if (!token_list_add_value_symbol(token_list, CLOSE_BRACES, '}')) {
				token_list_destroy(&token_list);

				return;
			}
		} else if (isspace(input_expression[i]) != 0) {
			// Ignorando espaco.
		} else {
			printf("Erro: Caractere inválido '%c'\n", input_expression[i]);
			token_list_destroy(&token_list);

			return;
		}

	}

	ParserState* token_state = parser_state_create(token_list);
	if (token_state == NULL) {
		printf("Erro: Falha ao alocar memória.\n");
		token_list_destroy(&token_list);

		return;
	}

	double result = expression(token_state);

	if (token_state->has_error) {
		printf("\nErro: Expressão inválida, não foi possível calcular.\n");
	} else {
		printf("\nResultado: %g\n", result);
	}

	token_list_destroy(&token_list);
	free(token_state);
}

int main() {
	SetConsoleOutputCP(CP_UTF8);

	system("cls");

	while (true) {
		printf("------ Calculadora (Parser) ------\n");
		printf("1. Calcular\n");
		printf("2. Sair\n");

		char option[8] = { 0 };

		printf("Opção: ");
		read_input(option, sizeof(option));

		system("cls");

		if (strcmp(option, "1") == 0) {
			char calc[256] = { 0 };

			printf("Expressão: ");
			read_input(calc, sizeof(calc));

			calculate(calc);

			printf("\n");
			system("pause");
			system("cls");

		} else if (strcmp(option, "2") == 0) {
			printf("Finalizando programa...\n");
			break;
		} else {
			printf("Opção inválida.\n\n");
		}
	}

	return 0;
}