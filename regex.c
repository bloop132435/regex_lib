#include "regex.h"
#include <stdio.h>

void regex_print_char(const regex_char_t *rc) {
	for (int c = 0; c < 64; c++) {
		if (rc->a & ((uint64_t)1 << (uint8_t)c)) {
			printf("%c, ", (char)c);
		}
	}
	for (int c = 0; c < 64; c++) {
		if (rc->b & ((uint64_t)1 << (uint8_t)c)) {
			printf("%c, ", (char)(c + 64));
		}
	}
	printf("\n");
	if (rc->question) {
		printf("Either 1 or 0 \n");
	} else if (rc->starred) {
		printf("0 or more\n");
	}
	printf("size: %d\n", rc->size);
}

void regex_add_char(regex_char_t *out_rc, char to_add) {
	if (to_add > 64)
		out_rc->b |= (uint64_t)1 << (uint64_t)(to_add - 64);
	else
		out_rc->a = (uint64_t)1 << (uint64_t)to_add;
	out_rc->size++;
}

int regex_get_next_char_offset(const char *str, regex_char_t *out_rc) {
	int len = 1;
	char c = str[0];
	out_rc->question = false;
	out_rc->starred = false;
	out_rc->a = 0;
	out_rc->b = 0;
	out_rc->size = 0;
	// check if backslash
	if (c == '\\') {
		c = str[1];
		len++;
		goto normal_char;
	}
	// check if brackets
	if (c == '[') {
		char prev_char;
		while (true) {
			c = str[len];
			len++;
			if (c == ']')
				break;
			if (c == '-') {
				//		multiple: check for dash (range)
				c = str[len];
				len++;
				// from prev_char to c
				for (char x = prev_char; x <= c; x++) {
					regex_add_char(out_rc, x);
				}
			} else if (c == '\\') {
				//		multiple: check for backslash
				c = str[len];
				len++;
				regex_add_char(out_rc, c);
			}

			prev_char = c;
		}
		//		check end brackets
		goto end_normal_parse;
	}
	// normal char
normal_char:
	regex_add_char(out_rc, c);
end_normal_parse:
	c = str[len];
	// post mod check star
	if (c == '*') {
		out_rc->starred = true;
		len++;
	}
	// post mod check question
	if (c == '?') {
		out_rc->question = true;
		len++;
	}
	return len;
}
