// Batch : 52 
// Authors
// Deepikaa Suresh : 2008B4A7552
// Nitin Gangahar : 2008B4A7733 
#ifndef _PARSERDEF_H_
#define _PARSERDEF_H_


typedef int grammar[100][20]; //100or 92?f
typedef int table[150][150]; 
table T;
int nullable[200];
int first[200][200]; 
int follow[200][200];
int sz_grammar[100];
int sz_first[200];
int sz_follow[200];

/*****************************
 * Parse tree related stuff
 * **************************/
struct NODE;
typedef struct NODE node;
typedef node* parseTree;
struct NODE
{
	tok t;
	int rule;
	node *sibling;
	node *child;
	node *parent;
};
#endif
