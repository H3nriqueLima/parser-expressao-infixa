#pragma once

#include <stdlib.h>

typedef enum {
	NUMBER,
	OPERATOR,
	GROUPING_SYMBOL
} TokenType;

typedef struct {
	TokenType token_type;
	union {
		int number_value;
		char symbol_value;
	};
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