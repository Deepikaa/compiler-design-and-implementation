#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include "parser.h"
#include "lexer.h"
#define ST_SIZE 5000
typedef struct {
	int type;
	char scope[20];
	int offset; // Dont know about this one right now
}symbol_entry;

typedef symbol_entry symbol_table[ST_SIZE];
void init_symbol_tables(parseTree pt);
void symbol_init_hash(symbol_table st, parseTree pt);
int symbol_hash_value(char *id);
void symbol_insert_hash(symbol_table st, parseTree pt);

#endif
