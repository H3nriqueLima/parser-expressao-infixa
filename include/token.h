#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum {
	NUMBER,
	OPERATOR,
	GROUPING_SYMBOL
} ParserTokenType;

typedef union {
	int number_value;
	char symbol_value;
} TokenValue;

typedef struct {
	ParserTokenType token_type;
	TokenValue token_value;
} Token;

typedef struct {
	Token* token_data;
	size_t size;
	size_t capacity;
} TokenList;

static inline TokenList* token_list_create(size_t initial_capacity) {
	TokenList* new_token_list = (TokenList*)malloc(sizeof(TokenList));
	if (new_token_list != NULL) {
		new_token_list->token_data = (Token*)malloc(sizeof(Token) * initial_capacity);
		if (new_token_list->token_data == NULL) {
			free(new_token_list);
			return NULL;
		}

		new_token_list->size = 0;
		new_token_list->capacity = initial_capacity;
	} else {
		return NULL;
	}

	return new_token_list;
}

static inline bool token_list_ensure_capacity(TokenList* token_list) {
	if (token_list->size < token_list->capacity) return true;

	size_t new_capacity = token_list->capacity * 2;

	Token* new_token_data = (Token*)realloc(token_list->token_data, new_capacity * sizeof(Token));
	if (new_token_data == NULL) return false;

	token_list->token_data = new_token_data;
	token_list->capacity = new_capacity;

	return true;
}

static inline bool token_list_add(TokenList* token_list, ParserTokenType token_type, TokenValue token_value) {
	if (token_list == NULL) return false;
	if (!token_list_ensure_capacity(token_list)) return false;

	token_list->token_data[token_list->size].token_type = token_type;
	token_list->token_data[token_list->size].token_value = token_value;

	token_list->size++;

	return true;
}

static inline void token_list_destroy(TokenList** token_list) {
	if (token_list == NULL) {
		return;
	} else if (*token_list == NULL) return;

	free((*token_list)->token_data);
	free(*token_list);
	
	*token_list = NULL;
}

static inline void token_list_print(TokenList* token_list) {
	if (token_list == NULL) return;

	printf("Lista de Token atual:\n Tamanho da lista: %zu\n Capacidade da lista: %zu\n Dados da lista:\n", token_list->size, token_list->capacity);

	for (size_t i = 0; i < token_list->size; i++) {
		Token current = token_list->token_data[i];

		switch (current.token_type) {
			case NUMBER:
				printf("  [%zu] NUMBER: %d\n", i, current.token_value.number_value);
				break;
			case OPERATOR:
				printf("  [%zu] OPERATOR: %c\n", i, current.token_value.symbol_value);
				break;
			case GROUPING_SYMBOL:
				printf("  [%zu] GROUPING_SYMBOL: %c\n", i, current.token_value.symbol_value);
				break;
		}
	}
}