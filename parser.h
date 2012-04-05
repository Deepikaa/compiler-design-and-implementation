// Batch : 52 
// Authors
// Deepikaa Suresh : 2008B4A7552
// Nitin Gangahar : 2008B4A7733 
#ifndef _PARSER_H_
#define _PARSER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lexer.h"
#include "parserDef.h"

/***************************
 * For storing/calculating the grammmar and also
 * the first and follow sets. 
 * *************************/

void calcFirstAndFollow();
void printFirstAndFollow();
void createParseTable(table T);

/*****************************
 * Parse tree related stuff
 * **************************/


parseTree parseInputSourceCode(char *testcaseFile, table T);
void printParseTree(parseTree PT, char* outfile);
parseTree build_tree(int curr_node);
#endif
