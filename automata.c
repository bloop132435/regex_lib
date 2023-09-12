#include "automata.h"
#include <stdlib.h>
#include <stdbool.h>

static bool rcr_eq(regex_char_range_t a, regex_char_range_t b){
	// TODO
	return false;
}
static bool rc_eq(regex_char_t a, regex_char_t b){
	// TODO
	return false;
}

void automata_create_from_regex(int regex_len, const regex_char_t* regex_str, automata_t* out_auto){
	two_tuple_t (*arr)[CHAR_SIZE] = malloc(regex_len * sizeof(two_tuple_t[CHAR_SIZE]));

	out_auto->transitions = arr;
	uint32_t state_cntr = 0;
	for(state_cntr = 0;state_cntr < regex_len;state_cntr++){
		const regex_char_t rc = regex_str[state_cntr];
		if(rc.question){
			// TODO
			if(state_cntr == regex_len - 1){
				out_auto->final_state = (two_tuple_t) {
					.size = 2,
					.data = {state_cntr, regex_len - 1}
				};
			}
		} else if(rc.starred){
			int c;
			for(c = 0;c < 64;c++){
				if(rc.rcr.a & ((uint64_t) 1 << (uint64_t) c)){
					out_auto->transitions[state_cntr][c] = (two_tuple_t) {
						.size = 1,
						.data = {state_cntr + 1, state_cntr}
					};
				}
			}
			for(c = 0;c < 64;c++){
				if(rc.rcr.b & ((uint64_t) 1 << (uint64_t) c)){
					out_auto->transitions[state_cntr][c + 64] = (two_tuple_t) {
						.size = 1,
						.data = {state_cntr + 1, state_cntr}
					};
				}
			}
		} else{
			int c;
			for(c = 0;c < 64;c++){
				if(rc.rcr.a & ((uint64_t) 1 << (uint64_t) c)){
					out_auto->transitions[state_cntr][c] = (two_tuple_t) {
						.size = 1,
						.data = {state_cntr + 1, 0}
					};
				}
			}
			for(c = 0;c < 64;c++){
				if(rc.rcr.b & ((uint64_t) 1 << (uint64_t) c)){
					out_auto->transitions[state_cntr][c + 64] = (two_tuple_t) {
						.size = 1,
						.data = {state_cntr + 1, 0}
					};
				}
			}
		}
	}
}
