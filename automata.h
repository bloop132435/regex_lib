#ifndef AUTOMATA_H
#define AUTOMATA_H
#include <stdbool.h>
#include <stdint.h>
#include "regex.h"
#define CHAR_SIZE 128

typedef struct two_tuple {
	uint8_t size;
	uint32_t data[2];
} two_tuple_t;

typedef struct automata {
	// starting state is 0
	uint32_t size;
	two_tuple_t (*transitions)[CHAR_SIZE];
	two_tuple_t final_state;
} automata_t;

// will allocate, up to user to free transitions
void automata_create_from_regex(int regex_len, const regex_char_t* regex_str, automata_t* out_auto);
bool automata_matches(const automata_t* auto_checker, char* str);


#endif
