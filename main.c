#include "regex.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	printf("%s\n", argv[1]);
	char *str = argv[1];
	while (strlen(str)) {
		regex_char_t rc;
		str += regex_get_next_char_offset(str, &rc);
		regex_print_char(&rc);
	}
}
