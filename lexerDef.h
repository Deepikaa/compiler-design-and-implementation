// Batch : 52 
// Authors
// Deepikaa Suresh : 2008B4A7552
// Nitin Gangahar : 2008B4A7733 
#ifndef _LEXERDEF_H_
#define _LEXERDEF_H_
typedef struct {
	int lineno;
	char name[30]; // name of the token
	char val[50]; // the actual value of the token 
	int pos; 
}tok; 
typedef tok* tokenInfo;


#endif
