#include "symbol.h"
#include "parser.h"
#include "lexer.h"
#define SMAX 100
symbol_table driver_table; // Symbol table for the driver module - will contain pointers to other symbol tables
symbol_table symbol_tables[SMAX];

/**********Hash functions ***********
*
*/
void init_symbol_tables(parseTree pt) {
    
}

int symbol_hash_value(char *id) {
	int ret = 0;
	int sz = strlen(id);
	int i;
	for(i=0;i<sz;i++) {
		ret = ((ret*BASE)%ST_SIZE+id[i])%ST_SIZE;	
	}
	return ret;
}

void symbol_init_hash() {
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
	
}

/**** End of hash functions ***/







