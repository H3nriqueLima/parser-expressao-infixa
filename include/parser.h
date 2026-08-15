/*
Parser recursivo descendente (expression -> term -> power -> factor).
Recebe uma TokenList e calcula o valor da expressão, sinalizando erro de sintaxe/cálculo via ParserState->has_error.
*/

#pragma once

#include <token.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	TokenList* token_list;
	size_t position;
	bool has_error;
} ParserState;

static inline double expression(ParserState* token_state);

static inline Token __current_token(ParserState* token_state) {
	if (token_state->position >= token_state->token_list->size) {
		Token invalid_token;
		invalid_token.token_type = END_OF_INPUT;
		invalid_token.token_value.symbol_value = '\0';
		return invalid_token;
	}

	return token_state->token_list->token_data[token_state->position];
}

static inline double __parse_group(ParserState* token_state, ParserTokenType open_token, ParserTokenType close_token) {
	Token current_token = __current_token(token_state);

	if (current_token.token_type != open_token) {
		printf("Erro de sintaxe: Delimitador de abertura inesperado!\n");

		token_state->has_error = true;

		return 0;
	}

	token_state->position++;

	double value = expression(token_state);
	if (token_state->has_error) return 0;

	current_token = __current_token(token_state);

	if (current_token.token_type != close_token) {
		printf("Erro de sintaxe: delimitador nao fechado!\n");
		token_state->has_error = true;

		return 0;
	}

	token_state->position++;

	return value;
}

static inline ParserState* parser_state_create(TokenList* token_list) {
	ParserState* new_parser_state = (ParserState*)malloc(sizeof(ParserState));
	if (new_parser_state != NULL) {
		if (token_list != NULL) {
			new_parser_state->token_list = token_list;
			new_parser_state->position = 0;
			new_parser_state->has_error = false;
		} else {
			free(new_parser_state);
			return NULL;
		}
	} else {
		return NULL;
	}

	return new_parser_state;
}

static inline double factor(ParserState* token_state) {
	Token current_token = __current_token(token_state);

	if (current_token.token_type == END_OF_INPUT) {
		printf("Erro de sintaxe: Fim inesperado da expressao.\n");
		token_state->has_error = true;

		return 0;
	} else if (current_token.token_type == SUB_OPERATOR) {
		token_state->position++;

		double value = factor(token_state);
		if (token_state->has_error) return 0;

		return -value;
	} else if (current_token.token_type == SUM_OPERATOR) {
		token_state->position++;

		return factor(token_state);
	} else if (current_token.token_type == NUMBER) {
		token_state->position++;

		return current_token.token_value.number_value;
	} else if (current_token.token_type == OPEN_BRACES) {
		return __parse_group(token_state, OPEN_BRACES, CLOSE_BRACES);
	} else if (current_token.token_type == OPEN_BRACKETS) {
		return __parse_group(token_state, OPEN_BRACKETS, CLOSE_BRACKETS);
	} else if (current_token.token_type == OPEN_PARENTHESES) {
		return __parse_group(token_state, OPEN_PARENTHESES, CLOSE_PARENTHESES);
	} else {
		printf("Erro de sintaxe!\n");
		token_state->has_error = true;

		return 0;
	}
}

static inline double power(ParserState* token_state) {
	double base = factor(token_state);
	if (token_state->has_error) return 0;

	Token current_token = __current_token(token_state);

	if (current_token.token_type == POW_OPERATOR) {
		token_state->position++;

		double exponent = power(token_state);
		if (token_state->has_error) return 0;

		return pow(base, exponent);
	}

	return base;
}

static inline double term(ParserState* token_state) {
	double value = power(token_state);

	if (token_state->has_error) return 0;

	Token current_token = __current_token(token_state);

	while (current_token.token_type == MULT_OPERATOR || current_token.token_type == DIV_OPERATOR) {
		ParserTokenType current_operator = current_token.token_type;

		token_state->position++;

		double next_value = power(token_state);

		if (token_state->has_error) return 0;

		if (current_operator == MULT_OPERATOR) {
			value = value * next_value;
		} else {
			if (next_value == 0) {
				printf("Erro: divisao por zero.\n");
				token_state->has_error = true;
				return 0;
			}

			value = value / next_value;
		}

		current_token = __current_token(token_state);
	}

	return value;
}

static inline double expression(ParserState* token_state) {
	double value = term(token_state);

	if (token_state->has_error) return 0;

	Token current_token = __current_token(token_state);

	while (current_token.token_type == SUM_OPERATOR || current_token.token_type == SUB_OPERATOR) {
		ParserTokenType current_operator = current_token.token_type;

		token_state->position++;

		double next_value = term(token_state);

		if (token_state->has_error) return 0;

		if (current_operator == SUM_OPERATOR) {
			value = value + next_value;
		} else value = value - next_value;

		current_token = __current_token(token_state);
	}

	return value;
}