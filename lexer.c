// Batch : 52 
// Authors
// Deepikaa Suresh : 2008B4A7552
// Nitin Gangahar : 2008B4A7733 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "lexerDef.h"

#define IS_WS(c) (c==' ' || c == '\n' || c=='\t')
#define ISCAP(c) (c>='A' && c<='Z')
#define ISSMALL(c) (c>='a' && c<='z')
#define ISNUM(c) (c>='0' && c<='9')
#define ISALPHA(c) (ISSMALL(c) || ISCAP(c))
#define ISKEYW(c) (ISALPHA(c) || c=='_') // is a part of keyword

#define MOD 83
#define BASE 59

/* Variables required by the program */
// Input file stream defined as a global 
FILE *in;
char buf;
int line; // global for line number
int eof; // marks eof - set to 1 if eof is reached
char input_file[30];
tok curr;
int token_cnt;
typedef struct {
	int flag;
	char keyword[30];	
	int pos; // Position in the token_list
}hash;
tokenInfo tokenInfoList;
// List of tokens needed by us
char token_list[][30] = {
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
};
char keyword_list[][30] = {
	"integer",
	"real",
	"boolean",
	"of",
	"array",
	"start",
	"end",
	"declare",
	"module",
	"driver",
	"program",
	"get_value",
	"print",
	"use",
	"with",
	"parameters",
	"true",
	"false",
	"takes",
	"input",
	"returns",
	"AND",
	"OR",
	"for",
	"in",
	"switch",
	"case",
	"break",
	"default",
	"while",
};

hash hash_table[MOD];

/* Function declarations
 *
 *
 * */
void get_token();
FILE *getStream(FILE *fp){
	if(fscanf(fp, "%c", &buf) == EOF)
		eof = 1; // eof reached
	return fp;
}

void init_hash(); // Initialises the hash table

inline void print_token(tok curr) {
	printf("Line No : %d\tName : %s\tValue : %s\n", curr.lineno+1, curr.name, curr.val);
}
inline void print_token_list() {
	tokenInfoList = getNextToken();
	int curr = 0;
	while(curr < token_cnt) {
		print_token(tokenInfoList[curr]);
		curr++;	
	}
}
tokenInfo getNextToken() {
	in = fopen(input_file, "r");
	if(in == NULL) {
		printf("No such input file\n");
		return NULL;
	}
	in = getStream(in);
	line = 0;
	eof = 0;
	init_hash();
	int curr_pos = 0;	
	tokenInfo tokenInfoList;
	tokenInfoList = (tokenInfo)(malloc(sizeof(tok) * MAX_TOKENS));
	while(1) {
		get_token();
		if(eof == 1) {
			token_cnt = curr_pos;
			break;
		}
		if(curr.pos == -1) {
			printf("ERROR_3 : Unknown pattern %s\n",curr.val);
		}
		tokenInfoList[curr_pos++] = curr;
		/*if(eof == 1)
		{
//			break;
			printf("EOF reached\n");
			tok eof_token;
			eof_token.lineno = line;
			strcpy(eof_token.val, "EOF");
			strcpy(eof_token.name, "EOF");
			eof_token.pos = -10;
			tokenInfoList[curr_pos++] = eof_token;
			break;
		}	*/
		//print_token(curr);
	}
	return tokenInfoList; 
}

tok handle_num()
{
	tok numtok;		
	char num[10000];
	int sz=1;
	int curr_state=1;
	num[0]=buf;
	
	while(1)
	{
		in = getStream(in);
		if(ISNUM(buf))
		{
			if(curr_state==1 || curr_state==3 || curr_state==6)
			{
				//continue;	
			}
			else if(curr_state==2)
			{
				curr_state=3;
			}
			else if(curr_state==4)
			{
				curr_state=6;
			}
			else if(curr_state==5)
			{
				curr_state=6;
			}

		}
		else if(buf=='.' && curr_state==2) {
			fseek(in, -1, SEEK_CUR);
			curr_state = 1;
			sz--;
			break;
		}
		else if(buf=='.' && curr_state==1)
		{
			curr_state=2;
		}
		else if((buf=='e'||buf=='E') && (curr_state==1||curr_state==3))
		{
			curr_state=4;
		}
		else if((buf=='+'||buf=='-')&& (curr_state==4))
		{
			curr_state=5;
		}
		else
		{
			break;
		}
		
		num[sz++]=buf;
	}	
	
	if(curr_state==1)
	{
		num[sz++]='\0';
		strcpy(numtok.name,"NUM");
		strcpy(numtok.val,num);
		numtok.pos = 106;
	}
	else if(curr_state==3 || curr_state==6)
	{
		num[sz++]='\0';
		strcpy(numtok.name,"RNUM");
		strcpy(numtok.val,num);
		numtok.pos = 107;
	}
	
	return numtok;
}

/* Tokenizing functions along with other input manip functions */
// Returns 0 on success and -1 on EOF
void get_token() {
	//printf("Get token called\n");	
	char id[10000];
	int size, valid;
	int idx = 0; // current index in the buffer
	while(IS_WS(buf) && !eof) {
			// check if its a keyword or an identifier
			if(buf == '\n')
			line++;
			in = getStream(in);
	}
	tok ans;
	strcpy(ans.name, "INVALID");
	ans.pos = -1;
	if(buf == '+') {
			strcpy(ans.name, "PLUS");
			strcpy(ans.val, "+");
			ans.pos = 31;
			in = getStream(in);
	}
	else if(buf == '-') {
			strcpy(ans.name,"MINUS");
			strcpy(ans.val, "-");
			ans.pos = 32;
			in = getStream(in);
	}
	else if(buf == '*')
	 {
			in = getStream(in);
			if(buf == '*') {
				strcpy(ans.name,"COMMENTMARK");	
				char pbuf = 'a';
				while(buf != EOF && !(pbuf=='*' && buf=='*')) {
					pbuf = buf;
					in = getStream(in);
				}
				in = getStream(in); //check
			}
			else
			{
				strcpy(ans.name,"MUL");
				strcpy(ans.val, "*");
				ans.pos = 33;
			}
	}
	else if(buf == '/') {
			strcpy(ans.name, "DIV");
			strcpy(ans.val, "/");
			in = getStream(in);
			ans.pos = 34;
	}
	else if(buf == '=') {
			in = getStream(in);
			if(buf == '=') {
				strcpy(ans.name, "EQ");
				strcpy(ans.val, "==");
				in = getStream(in);
				ans.pos = 39;
			}
	}
	else if(buf == '<') {
			in = getStream(in);
			if(buf == '=') {
				strcpy(ans.name, "LE");
				strcpy(ans.val, "<=");
				ans.pos = 36;
				in = getStream(in);
			}
			else if(buf == '<') {
				in = getStream(in);
				if(buf == '<') {
					strcpy(ans.name, "DRIVERDEF");
					strcpy(ans.val, "<<<");
					ans.pos = 108;
					in = getStream(in);
				}
				else {
					strcpy(ans.name, "DEF");
					strcpy(ans.val, "<<");
					ans.pos = 41;
				}
				
			}
			else {
				strcpy(ans.name, "LT");
				strcpy(ans.val, "<");
			    ans.pos = 35;
			}
	}
	else if(buf == '>') {
			in = getStream(in);
			if(buf == '=') {
				strcpy(ans.name, "GE");
				strcpy(ans.val, ">=");
				ans.pos = 37;
				in = getStream(in);
			}
			else if(buf == '>') {
				in = getStream(in);
				if(buf == '>') {
					strcpy(ans.name, "DRIVERENDDEF");
					strcpy(ans.val, ">>>");
					ans.pos = 109;
					in = getStream(in);
				}
				else {
					strcpy(ans.name, "ENDDEF");
					strcpy(ans.val, ">>");
					ans.pos = 42;
				}
			}
			else {
				strcpy(ans.name, "GT");
				strcpy(ans.val, ">");
				ans.pos = 38;
			}
	}		
	else if(buf == ':') {
		in = getStream(in);
		if(buf == '=') {
			strcpy(ans.name, "ASSIGNOP");
			strcpy(ans.val, ":=");
			ans.pos = 47;
			in = getStream(in);
		}
		else {
			strcpy(ans.name, "COLON");
			strcpy(ans.val, ":");
			ans.pos = 43;
		}
	}
	else if(buf == '[') {
		strcpy(ans.name, "SQBO");
		strcpy(ans.val, "[");
		in = getStream(in);
		ans.pos = 48;
	}
	else if(buf == ']') {
		strcpy(ans.name, "SQBC");
		strcpy(ans.val, "]");
		in = getStream(in);
		ans.pos = 49;
	}
	else if(buf == '(') {
		strcpy(ans.name, "BO");
		in = getStream(in);
		strcpy(ans.val, "(");
		ans.pos = 50;
	}
	else if(buf == ')') {
		strcpy(ans.name, "BC");
		in = getStream(in);
		strcpy(ans.val, ")");
	    ans.pos = 51;
	}
	else if(buf == '.') {
		in = getStream(in);
		if(buf == '.') {
			strcpy(ans.name, "RANGEOP");
			in = getStream(in);
			strcpy(ans.val, "..");
			ans.pos = 44;
		}
		else {
			strcpy(ans.val, ".");
		} 
	}
	else if(buf == ',') {
		strcpy(ans.name, "COMMA");
		in = getStream(in);
		strcpy(ans.val, ",");
		ans.pos = 46;
	}
	else if(buf == ';') {
		strcpy(ans.name, "SEMICOL");
		in = getStream(in);
		strcpy(ans.val, ";");
		ans.pos = 45;
	}
	else if(buf == '!') {
		in = getStream(in);
		if(buf == '=') {
			strcpy(ans.name, "NE");
			strcpy(ans.val, "!=");
			ans.pos = 40;
		}
		else {
			strcpy(ans.val, "!");
		}
	}
	else if(ISNUM(buf)) {
		ans = handle_num();
	}
	else if(ISALPHA(buf))
	{
		
		id[0]=buf;
		size=1;
		valid=1;

		while(1)
		{
			in = getStream(in);
			if(!(ISALPHA(buf) || ISNUM(buf) || buf=='_')) // write macroi 
			{
				break;
			}
			id[size++]=buf;				
			
		}			
		id[size++]='\0';
		
		
		if(valid==1)
		{
			int check;
			check=find_keyword(id);
			if(check<0 && size<=9)
			{
				strcpy(ans.name,"ID");
				ans.pos = 30; // For ID
			}	
			else if(check >= 0)
			{
				strcpy(ans.name, token_list[check]); // appropriate return value to get token prob from some array
				ans.pos = check;
			}
			else {
				printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 8 characters.\n", line+1);
			}
			strcpy(ans.val,id);				
		}			

	}	
	else if(!eof){
		char lbuf[] = {buf, '\0'};
		strcpy(ans.val, lbuf);
		printf("ERROR_2 : Unknown symbol %s at line %d\n", lbuf, line+1);
		in = getStream(in);
	}
	curr=ans; 
	curr.lineno = line;
}

int hash_value(char *id) {
	int ret = 0;
	int sz = strlen(id);
	int i;
	for(i=0;i<sz;i++) {
		if(!ISKEYW(id[i]))
			return -1;
		ret = ((ret*BASE)%MOD+id[i])%MOD;	
	}
	return ret;
}
void init_hash() {
	int i;
	for(i=0;i<MOD;i++) {
		hash_table[i].flag = 0;	 // marking the entries as unused	
	}
	for(i=0;i<30;i++) {
		// Hash this keyword
		int val = hash_value(keyword_list[i])%MOD; 
			// Start quadratic probing 
			int j;
			for(j=0;j<MOD;j++) {
				val = (val + j + j*j)%MOD;
				if(hash_table[val].flag == 0)
				{
					strcpy(hash_table[val].keyword,keyword_list[i]);
					hash_table[val].flag = 1;
					hash_table[val].pos = i;
					break;
				}
			}
			if(j == MOD)
				printf("%s couldn't be inserted\n", keyword_list[i]);
	}
	// Printing the hash table
	/**
	for(i=0;i<MOD;i++) {
		printf("%d %s\n", i, hash_table[i].keyword);
	}**/
	
}

int find_keyword(char *keyword)
{
	int pos;
	pos=hash_value(keyword);
	if(pos == -1) {
		return -1;
	}
	else {
		// Does not exist
		if(hash_table[pos].flag == 0)
			return -1;
		else {
			int i;
			for(i=0;i<MOD;i++) {
				pos = (pos + i + i*i)%MOD;
				if(strcmp(keyword, hash_table[pos].keyword) == 0) {
					return hash_table[pos].pos;
				}
			}
			return -1;
		} 
		
	}
}


void removeComments(char *testcaseFile, char *cleanFile) {
	FILE *test = fopen(testcaseFile, "r");
	FILE *clean = fopen(cleanFile, "w");
	if(test==NULL) {
		printf("No such test file.Quitting!\n");
		return;
	}
	char buf;
	while(fscanf(test, "%c", &buf) != EOF) {
		if(buf == '*') {
			fscanf(test,"%c", &buf);
			if(buf == '*') {
				char pbuf = 'a';
				while(buf != EOF && !(pbuf=='*' && buf=='*')) {
					pbuf = buf;
					fscanf(test, "%c", &buf);
				}
			}
			else {
				fprintf(clean, "*");
				fprintf(clean, "%c", buf);
			}
		}
		else
		{
			fprintf(clean, "%c", buf);
		}
	}
	fclose(test);
	fclose(clean);
}
