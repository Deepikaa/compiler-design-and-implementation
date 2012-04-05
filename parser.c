// Batch : 52 
// Authors
// Deepikaa Suresh : 2008B4A7552
// Nitin Gangahar : 2008B4A7733 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
/******************************
 * Defining the macros required 
 ******************************/
#define RULE_CNT 95
#define EPS 105
#define TERM_CNT 53
#define TOKEN_CNT 112
#define DOLLAR 110
#define DEBUG1 0
#define DEBUG2 0 
#define PRINT_RULE(x,i) for(i=0;i<sz_grammar[x];i++) printf("%s ", parserTokenList[G[x][i]]); printf("\n");
/**** Macro Definitions End Here ***/
int token_pos = 0;
tokenInfo tokenList; //tokeninfo yet to be defined in lexer.h
extern int token_cnt;
extern char input_file[30];
grammar G = {
	{ 53, 54, 55, 59, 55, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 54, 57, 54, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 54,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 57,  7,  8, 30, 45, -1, -1, -1, -1, -1, -1, -1, -1}, 
	{ 55, 58, 55, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 55,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 59,108,  9, 10,109, 60, -1, -1, -1, -1, -1, -1, -1},
	{ 58, 41,  8, 30, 42, 18, 19, 48, 61, 49, 45, 62, 60, -1}, // modified this rule
	{ 62, 20, 48, 63, 49, 45, -1, -1, -1, -1, -1, -1, -1},
	{ 62,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
	{ 61, 30, 43, 64, 65, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 65, 46, 30, 43, 64, 65, -1, -1, -1, -1, -1, -1, -1},
	{ 65,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 63, 30, 43, 67, 66, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 66, 46, 30, 43, 67, 66, -1, -1, -1, -1, -1, -1, -1},
	{ 66,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 64,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
	{ 64,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 64,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 64,  4, 48, 68, 49,  3, 67, -1, -1, -1, -1, -1, -1},
	{ 67,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 67,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
	{ 67,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 60,  5, 69,  6, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 69, 70, 69, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 69,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 70, 71, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 70, 72, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 70, 73, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 70, 74, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
	{ 70, 75, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 71, 11, 50, 30, 51, 45, -1, -1, -1, -1, -1, -1, -1},
	{ 71, 12, 50, 76, 51, 45, -1, -1, -1, -1, -1, -1, -1},
	{ 76, 30, 77, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 76,106, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 76,107, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 77, 48, 30, 49, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 77,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
	{ 72, 78, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 72, 79, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 78, 30, 80, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 80, 81, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 80, 82, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 81, 47, 83, 45, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 82, 48, 84, 49, 47, 83, 45, -1, -1, -1, -1, -1, -1},
	{ 84,106, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 84, 30, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 79, 85, 13,  8, 30, 14, 15, 86, 45, -1, -1, -1, -1},
	{ 85, 48, 86, 49, 47, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 85,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 86, 30, 87, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 87, 46, 30, 87, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 87,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
	{ 83, 88, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 83, 32, 50, 89, 51, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 88, 90, 91, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 91,100, 90, 91, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 91,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 90, 89, 92, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 92, 93, 89, 92, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 92,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 96, 50, 88, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 89, 94, 95, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 95, 98, 94, 95, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 95,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 94, 96, 97, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 97, 99, 96, 97, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 97,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
	{ 96, 76, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 98, 31, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 98, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 99, 33, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 99, 34, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{100, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{100, 22, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 93, 35, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 93, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 93, 37, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 93, 38, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 93, 39, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 93, 40, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ 73,  7, 86, 43, 64, 45, -1, -1, -1, -1, -1, -1, -1},
	{ 74, 25, 50, 30, 51,  5,101,104,  6, -1, -1, -1, -1},
	{101, 26,103, 43, 69, 27, 45,102, -1, -1, -1, -1, -1},
	{102, 26,103, 43, 69, 27, 45,102, -1, -1, -1, -1, -1},
	{102,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{103,106, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{103, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{103, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{104, 28, 43, 69, 27, 45, -1, -1, -1, -1, -1, -1, -1},
	{ 75, 23, 50, 30, 24, 68, 51,  5, 69,  6, -1, -1, -1},
	{ 75, 29, 50, 88, 51,  5, 69,  6, -1, -1, -1, -1, -1},
	{ 68,106, 44,106, -1, -1, -1, -1, -1, -1, -1, -1, -1},  
	{111, 53,110, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{104,105, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};
char parserTokenList[][30] = {
	"INTEGER",
	"REAL",
	"BOOLEAN",
	"OF",
	"ARRAY",
	"START",
	"END",
	"DECLARE",
	"MODULE",
	"DRIVER",
	"PROGRAM",
	"GET_VALUE",
	"PRINT",
	"USE",
	"WITH",
	"PARAMETERS",
	"TRUE",
	"FALSE",
	"TAKES",
	"INPUT",
	"RETURNS",
	"AND",
	"OR",
	"FOR",
	"IN",
	"SWITCH",
	"CASE",
	"BREAK",
	"DEFAULT",
	"WHILE",
	"ID",
	"PLUS",
	"MINUS",
	"MUL",
	"DIV",
	"LT",
	"LE",
	"GE",
	"GT",
	"EQ",
	"NE",
	"DEF",
	"ENDDEF",
	"COLON",
	"RANGEOP",
	"SEMICOL",
	"COMMA",
	"ASSIGNOP",
	"SQBO",
	"SQBC",
	"BO",
	"BC",
	"COMMENTMARK",
	"program",
	"moduleDeclarations",
	"otherModules",
	"driverModules",
	"moduleDeclaration",
	"module",
	"driverModule",
	"moduleDef",
	"input_plist",
	"ret",
	"output_plist",
	"dataType",
	"N1",
	"N2",
	"type",
	"range",
	"statements",
	"statement",
	"ioStmt",
	"simpleStmt",
	"declareStmt",
	"conditionalStmt",
	"iterativeStmt",
	"var",
	"whichId",
	"assignmentStmt",
	"moduleReuseStmt",
	"whichStmt",
	"lvalueIDStmt",
	"lvalueARRStmt",
	"expression",
	"index",
	"optional",
	"idList",
	"N3",
	"arithmeticOrBooleanExpr",
	"arithmeticExpr",
	"AnyTerm",
	"N7",
	"N8",
	"relationalOp",
	"term",
	"N4",
	"factor",
	"N5",
	"op1",
	"op2",
	"logicalOp",
	"caseStmts",
	"N9",
	"value",
	"default",
	"epsilon",
	"NUM",
	"RNUM",
	"DRIVERDEF",
	"DRIVERENDDEF",
	"DOLLAR",
	"program'"
};



/*******Functions needed to calculate the parse table*******
 ***********************************************************/
// Returns 1 if the set F changed, otherwise 0 otherwise
int do_union(int F, int S, int type) {
	if(type == 0) {
		// Both first sets
		int sz_first_F = sz_first[F];
		int sz_first_S = sz_first[S];
		int i,j;
		if(sz_first_S==0)
		{
		    return 0;
		}
		for(i=0;i<sz_first_S;i++){
			for(j=0;j<sz_first_F;j++){
				if(first[S][i] == first[F][j]){
					break;
				}
			}
			// Not found in F, thus add to F
			if(j == sz_first_F) {
				first[F][sz_first_F++] = first[S][i];
			}
		}
		if(sz_first_F != sz_first[F]){
			sz_first[F] = sz_first_F;
			return 1;
		}
		else
			return 0;
	}
	else if(type == 1) {
		// Both follow sets
		int sz_follow_F = sz_follow[F];
		int sz_follow_S = sz_follow[S];
		int i,j;
		for(i=0;i<sz_follow_S;i++){
			for(j=0;j<sz_follow_F;j++){
				if(follow[S][i] == follow[F][j]){
					break;
				}
			}
			// Not found in F, thus add to F
			if(j == sz_follow_F) {
				follow[F][sz_follow_F++] = follow[S][i];
			}
		}
		if(sz_follow_F != sz_follow[F]){
			sz_follow[F] = sz_follow_F;
			return 1;
		}
		else
			return 0;
	}

	else {
		// F is follow, S is first
		int sz_follow_F = sz_follow[F];
		int sz_first_S = sz_first[S];
		int i,j;
		for(i=0;i<sz_first_S;i++){
			for(j=0;j<sz_follow_F;j++){
				if(first[S][i] == follow[F][j]){
					break;
				}
			}
			// Not found in F, thus add to F
			if(j == sz_follow_F && first[S][i]!=EPS) {
				follow[F][sz_follow_F++] = first[S][i];
			}
		}
		if(sz_follow_F != sz_follow[F]){
			sz_follow[F] = sz_follow_F;
			return 1;
		}
		else
			return 0;
	}
}

void createParseTable(table T) {
	calcFirstAndFollow();
	if(DEBUG1)
	printFirstAndFollow();
	int i,j,k;
  	for(i=0;i<150;i++)
		for(j=0;j<150;j++)
			T[i][j] = -1;
	for(i=0;i<RULE_CNT;i++)
	{
		j = 1;
		int LHS = G[i][0]; 
		while(j<sz_grammar[i] && nullable[G[i][j]]) {
		    for(k=0;k<sz_first[G[i][j]];k++) {
		        int curr = first[G[i][j]][k];
						assert((T[LHS][curr] == i) || (T[LHS][curr] == -1));
						if(T[LHS][curr]==-1)			
		        	T[LHS][curr] = i;   
		    }
		    j++;
		}
		if(j<sz_grammar[i]) {
			for(k=0;k<sz_first[G[i][j]];k++) {
		        	int curr = first[G[i][j]][k];
			       	assert((T[LHS][curr] == i) || (T[LHS][curr] == -1));
				if(T[LHS][curr]==-1)
				T[LHS][curr] = i;   
			}
		}
		// Epsilon is in first of the RHS
		if(j==sz_grammar[i]) {
		    int LHS = G[i][0];
		    for(k=0;k<sz_follow[LHS];k++) {
		        int curr = follow[LHS][k];
		        assert((T[LHS][curr] == i) || (T[LHS][curr] == -1));
		        T[LHS][curr] = i;
					
		    }
		}
	}
}


inline int rest_nullable(int rule, int pos) {
	int ret = 1;
	int i;
	for(i=pos+1;i<sz_grammar[rule];i++) {
		int tok = G[rule][i];
		if(!nullable[tok]) {
			ret = 0;
			break;	
		}
	}
	return ret;
}
void calcFirstAndFollow() {
	int i,j,k;

	memset(nullable, 0, sizeof nullable);
	memset(first,    -1, sizeof first);
	memset(follow,   -1, sizeof follow);
	memset(sz_grammar,  0, sizeof sz_grammar);
	memset(sz_first,  0, sizeof sz_first);
	// Calculating nullable and size of each rule
	nullable[EPS] = 1; 
	for(i=0;i<RULE_CNT;i++) {
		j = 0;
		while(G[i][j] != -1)
			j++;
		sz_grammar[i] = j;
	}
		for(i=0;i<RULE_CNT;i++) {
			j = 1;
			/*while(G[i][j] != -1 && nullable[G[i][j]]) {
				j++;
			}
			if(G[i][j] == -1) {
				if(!nullable[G[i][0]]) {
				nullable[G[i][0]] = 1;
				ch_flag = 1;
				}
			}*/
			if(G[i][1] == EPS) {
				nullable[G[i][0]] = 1;
			}
		}
	// Done with nullable
	if(DEBUG1) {	
		for(i=0;i<TOKEN_CNT;i++) {
		if(nullable[i])
		printf("%s:%d is nullable\n", parserTokenList[i],i);
		}
	}
	// Initializing first
	for(i=0;i<TERM_CNT;i++) {
		first[i][0] = i;
		sz_first[i]++;
	}
	// For NUM and RNUM
	
	first[105][0]=105;
	sz_first[105]++;
	first[106][0] = 106;
	first[107][0] = 107;
	sz_first[106]++;
	sz_first[107]++;
	
	first[108][0] = 108;
	first[109][0] = 109;
	sz_first[108]++;
	sz_first[109]++;

	first[110][0] = 110;
	sz_first[110]++;

	
	while(1) {
		int flag = 0; // were there any changes
		for(i=0;i<RULE_CNT;i++) {
			int sz_rule = sz_grammar[i];
			int cnt = 1;
			
			while(G[i][cnt] != -1)
			{
			        flag = (do_union(G[i][0], G[i][cnt], 0)?1:flag);
			        if(!nullable[G[i][cnt]])
			        break;
			        cnt++;
			}
			
			
		}
		if(!flag) {
			break;
		}
	}
	/*first[105][0] = 105;
	sz_first[105]++;
	for(i=0;i<TOKEN_CNT;i++) {
		if(nullable[i]){
			printf("NULLABLE : %s\n",parserTokenList[i]);
			do_union(i, EPS, 0);	
		}
	}*/
	// removing epsilons
	
	for(i=0;i<TOKEN_CNT;i++) {
		if(!nullable[i]) {
			int j;
			for(j=0;j<sz_first[i];j++){ 
				if(first[i][j] == 105) {
					int k;
					if(DEBUG1) {
						printf("Size of token %s first is %d\n",parserTokenList[i], sz_first[i]);
						printf("removing for %d:%s more random : %d\n",i,parserTokenList[i],j);
					
						for(k=0;k<sz_first[i];k++) {
							printf("%s\n",parserTokenList[first[i][k]]);
						}
					}
					for(k=j;k<sz_first[i];k++) {
						first[i][k] = first[i][k+1];
					}
					first[i][sz_first[i]-1] = -1;
					sz_first[i]--;
					if(DEBUG2) {
						for(k=0;k<sz_first[i];k++) {
							printf("%s\n",parserTokenList[first[i][k]]);
						}
					}
				}
			}
		}
	}
	while(1) {
		int flag = 0; // were there any changes
		for(i=0;i<RULE_CNT;i++) {
			int sz_rule = sz_grammar[i];
			int cnt = 1;
			for(cnt=1;cnt<=sz_grammar[i];cnt++)
			{
				int l;
				for(l=cnt+1;l<=sz_grammar[i];l++)
				{
					int check=0;
					int k;
					for(k=cnt+1;k<l;k++)
					{
						if(!nullable[G[i][k]])
						check=1;
					}
					if(check==0 || cnt+1==l)
					{
					flag = (do_union(G[i][cnt], G[i][l], 2)?1:flag);	
					}
					if(cnt==sz_grammar[i] || rest_nullable(i,cnt))
					flag = (do_union(G[i][cnt], G[i][0], 1)?1:flag);
					
				}
			}	
		}
		if(!flag) {
			break;
		}
	}
}

void printFirstAndFollow() {
	int i,j;
	printf("Following are nullable\n");
	for(i=0;i<TOKEN_CNT;i++) {
		if(nullable[i]) {
			printf("%d : %s\n",i,parserTokenList[i]);
		}
	}
	for(i=0;i<TOKEN_CNT;i++) {
		printf("For token %s : \n", parserTokenList[i]);
		printf("First consists of : ");
		for(j=0;j<sz_first[i];j++) {
			printf("%s %d  ", parserTokenList[first[i][j]],first[i][j]);
		}
		printf("\n");
		printf("Follow consists of : ");
		for(j=0;j<sz_follow[i];j++) {
			printf("%s  ", parserTokenList[follow[i][j]]);
		}
		printf("\n");
	}
}


parseTree initParseTree()
{
	
	parseTree p = (parseTree)malloc(sizeof(node));
	p->child = NULL;
	p->sibling = NULL;
	p->rule = -1;
	p->parent = NULL;
	return p;
}

inline int is_terminal(int curr_node)
{
	if(curr_node<53 || (curr_node>=105 && curr_node<111)) //check limits
	return 1;
	else
	return 0;
}

parseTree  parseInputSourceCode(char *testcaseFile, table T)
{   
	parseTree p;
	strcpy(input_file, testcaseFile);
	tokenList=getNextToken(); //assuming this is an array of tokens, t- global variable	
	int curr_node=111;//value for <program> - check
	p=build_tree(curr_node); 
	return p;	
}

parseTree build_tree(int curr_node)
{
	if(token_pos >= token_cnt)
		return NULL;
	int j;
	parseTree pnode = initParseTree();
	(pnode->t).pos=-1;

	pnode->rule=-1;
	
	if(is_terminal(curr_node))
	{
		if(curr_node==105) {
			strcpy(pnode->t.val, "epsilon");
			strcpy(pnode->t.name, "EPSILON");
			pnode->t.pos=105;
			pnode->t.lineno = -1;
			return pnode;
		}
		else if(token_pos >= token_cnt) {
			return NULL;
		}
		else if(tokenList[token_pos].pos==curr_node)
		{
			
			pnode->t=tokenList[token_pos];
			pnode->rule=-1; //setting the rule to -1 for the terminal

			if(DEBUG2)
			printf("Terminal matches with token in input. Building token number : %d:%s\n\n",token_pos, parserTokenList[tokenList[token_pos].pos]);

			token_pos++;
			return pnode;
		}
		else
		{
			/*if(DEBUG2)
			{printf("Going to epsilon\n");
			printf("not EPS no match error\n");
			printf("Curr node is %d\n",curr_node);
			printf("Building token number : %d:%s\n\n",token_pos, parserTokenList[tokenList[token_pos].pos]);
			}*/
			tok t_c = tokenList[token_pos];
			printf("Error_4 : The token %s for lexeme %s does not match at line %d. Expected token here is %s\n", t_c.val, parserTokenList[t_c.pos], t_c.lineno,parserTokenList[curr_node]);
			token_pos++;
			return pnode;			
			//error
		}

	}
	else
	{
		int rule;
		rule=T[curr_node][tokenList[token_pos].pos];
		
		if(rule==-1)
		{
			//printf("Cant find rule ::: building token number : %d and curr_node is %d",token_pos,curr_node);
			//printf(" and seen token is %d\n",tokenList[token_pos].pos);
			printf("-1 rule :: Error in parse table\n");
			return pnode;			
			//return pnode with appropriate error value

		}
		else
		{
				// Check things you wanna make sure with asserts, not ifs
				//printf("Rule : %d curr_node %d \n",rule,curr_node);
				int i;
				if(DEBUG2) {
					PRINT_RULE(rule,i);
				}
				(pnode->t).pos=curr_node;
				strcpy(pnode->t.name,parserTokenList[curr_node]);
				
				(pnode->t).lineno = -1;
				pnode->rule=rule;
				
				/*if(G[rule][1]==105)
				printf("EPS being called");*/

				parseTree child = build_tree(G[rule][1]); 
				if(child != NULL) {
					child->parent = pnode;
					parseTree curr = child;
					pnode->child = child;
					strcpy((pnode->t).val, parserTokenList[G[rule][0]]);
					for(i=2;i<sz_grammar[rule];i++){
						curr->sibling = build_tree(G[rule][i]);
						if(curr->sibling == NULL) {
							break;
						}
						(curr->sibling)->parent = pnode;
						curr = curr->sibling;
					}
					if(DEBUG2)
					printf("Building token number : %d\n",token_pos);	
				}
				return pnode;
		}
	}
}
void printParseTreeToFile(parseTree PT, FILE *fp);
void printParseTree(parseTree PT, char *outfile) {
	FILE *fp = fopen(outfile, "w");
	if(fp == NULL) {
		printf("Such an output file doesn't exist\n");
		return;
	}
	fprintf(fp, "%-15s  %-3s %-25s %-15s %-25s %-5s  %-10s\n\n","lexemeCurrNode", "lno", "token", "valueifNum", "parentNode", "Leaf", "nodeSymbol"); 
	printParseTreeToFile(PT, fp);
	printf("Parse Tree written to file");
	fclose(fp);
}
void printParseTreeToFile(parseTree  PT, FILE *fp) {
	if(PT == NULL) 
		return; // for safety
	if(PT != NULL) {

		if(PT->child != NULL) {
			fprintf(fp,"%-15s  %-3d  %-25s  ","----", -1, "----");
			fprintf(fp,"%-15s  ","----");
			if(PT->parent != NULL)
				fprintf(fp,"%-25s  ", (PT->parent)->t.val);
			else 
				fprintf(fp,"%-25s  ","ROOT");
			
			fprintf(fp,"%-5s  ","NO");
			fprintf(fp,"%-10s\n",(PT->t).name);
		}
		//leaf
		else {
			fprintf(fp,"%-15s  %-3d  %-25s  ", (PT->t).val, (PT->t).lineno+1, (PT->t).name);
			fprintf(fp,"%-15s  ", ((PT->t).pos==106 || (PT->t).pos==107)?(PT->t).val:"----");	
			if(PT->parent != NULL)
				fprintf(fp,"%-25s  ", (PT->parent)->t.val);
			else 
				fprintf(fp,"%-25s  ","ROOT");
			fprintf(fp,"%-5s  ","YES");
			fprintf(fp,"%-10s\n","----");
			
			
		}
	}
	if(PT->child != NULL) 
		printParseTreeToFile(PT->child,fp);
	if(PT->sibling != NULL) 
		printParseTreeToFile(PT->sibling,fp);
	return;
}
/*
int main(){
	int i,j;
	for(i=0;i<93;i++) {
		for(j=0;j<13;j++) {
			printf("%d    ", G[i][j]);
		}
		printf("\n");
	}
	createParseTable(T);
	parseTree p;
	p = parseInputSourceCode("input", T);
	printParseTree(p);
	return 0;
}*/
