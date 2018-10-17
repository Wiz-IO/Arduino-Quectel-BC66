/*
 * ext_api_ril.h
 *
 *  Created on: 17.10.2018
 *      Author: Georgi Angelov
 */

#ifndef EXT_API_RIL_H_
#define EXT_API_RIL_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

int str_starts_with(const char *line, const char *prefix);
void skip_white_space(char **p_cur);
void skip_next_comma(char **p_cur);
char * next_tok(char **p_cur);
int at_tok_start(char **p_cur);
int at_tok_nextint_base(char **p_cur, int *p_out, int base, int uns);
int at_tok_nextint(char **p_cur, int *p_out);
int at_tok_nexthexint(char **p_cur, int *p_out);
int at_tok_nextbinint(char **p_cur, int *p_out);
int at_tok_nextstr(char **p_cur, char **p_out);
char * at_get_one_line(char **p_cur);
char at_get_next_packet(const char *buf);

#endif /* EXT_API_RIL_H_ */
