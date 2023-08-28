#ifndef REGEX_H
#define REGEX_H
#include <stdbool.h>
#include <stdint.h>

typedef struct regex_char {
	uint64_t a;
	uint64_t b;
	bool question;
	bool starred;
	uint8_t size;
} regex_char_t;

void regex_print_char(const regex_char_t *rc);
int regex_get_next_char_offset(const char *str, regex_char_t *out_rc);

#endif
