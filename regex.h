#ifndef REGEX_H
#define REGEX_H
#include <stdbool.h>
#include <stdint.h>

typedef struct regex_char_range{
	uint64_t a;
	uint64_t b;
	uint8_t size;
} regex_char_range_t;

typedef struct regex_char {
	regex_char_range_t rcr;
	bool question;
	bool starred;
} regex_char_t;

void regex_print_char(const regex_char_t *rc);
int regex_get_next_char_offset(const char *str, regex_char_t *out_rc);

#endif
