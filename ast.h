#ifndef _AST_H_
#define _AST_H_
#include "parser.h"
#include "lexer.h"
struct astNODE;
typedef struct astNODE astNode;
typedef astNode* AST;
struct astNODE {
	AST sibling;
	AST child;
	AST parent; // Lest we may need it
	int lineno;
	int pos;
	char val[50];
};
AST r_construct(parseTree pt);
#endif
