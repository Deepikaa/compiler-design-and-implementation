// Batch : 52 
// Authors
// Deepikaa Suresh : 2008B4A7552
// Nitin Gangahar : 2008B4A7733 
#ifndef _LEXER_H_
#define _LEXER_H_
#include "lexerDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TOKENS 100000
/* Token list and other hardwired stuff */

void init_lexer(char *input_file); 
tokenInfo getNextToken();
#endif
