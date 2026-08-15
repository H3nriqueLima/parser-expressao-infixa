#pragma once

#include <stdio.h>
#include <string.h>

static inline void read_input(char* buffer, size_t buffer_size) {
	fgets(buffer, buffer_size, stdin);

	if (strchr(buffer, '\n') == NULL) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
	} else {
		buffer[strcspn(buffer, "\n")] = '\0';
	}
}