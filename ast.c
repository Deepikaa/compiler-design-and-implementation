#include "ast.h"
#include "parser.h"
#include "lexer.h"

AST initAST() {	
	AST p = (AST)malloc(sizeof(astNode));
	p->child = NULL;
	p->sibling = NULL;
	p->parent = NULL;
	int rule = -1;
	return p;
}

AST construct(parseTree p) {
	return r_construct(p);
}
AST makeLeaf(parseTree pt) {
	AST ast = initAST();
	ast->lineno = (pt->t).lineno;
	strcpy(ast->val, (pt->t).val);
	ast->pos = (pt->t).pos;
	return ast;
}
AST r_construct(parseTree pt) {
	if(pt == NULL)
		return NULL; // no AST for an empty parse tree
	AST ast = initAST();

	// Copy stuff
	strcpy(ast->val, (pt->t).val);
	ast->lineno = (pt->t).lineno;
	ast->pos = (pt->t).pos;
	// Done copying

	parseTree curr_pt = pt->child;
	int child_cnt = 0; // if its the first child or not
	AST head = NULL; // construct pointer to the first one
	AST curr = initAST();
	AST prev;	
	while(curr_pt != NULL) {
		if(!is_terminal(curr_pt->t.pos)) {
			printf("NT : %s \n",curr_pt->t.val);
			if(curr_pt->t.pos == 88) {
				AST N7 = 
				ast->pos = 
			}
			
			curr = r_construct(curr_pt);	
			if(child_cnt == 0){ 
				head = curr;
				prev=curr;
			}
			else
			{
				if(curr != NULL)
					prev->sibling=curr;
				prev=prev->sibling;
			}
			
			curr_pt = curr_pt->sibling;
			child_cnt++;
		}
		else if(curr_pt->t.pos == 30){
			printf("Id: %s\n",curr_pt->t.val); 
			// Its an ID
			curr = makeLeaf(curr_pt);
			if(child_cnt==0) {
				head=curr;
				prev = curr;
			}
			else {
				if(curr != NULL) 
					prev->sibling = curr;
				prev = prev->sibling;
			}

			curr_pt = curr_pt->sibling;
			child_cnt++;
		}
		else {
			printf("rest\n");
			curr_pt = curr_pt->sibling;	// In case something else has to be retained
			
		}
	}
	if(child_cnt == 1)
		ast = head;
	else 
		ast->child = head;
	return ast;

}

void printAST(AST ast) {
	if(ast == NULL) 
		return;
	printf("AST.val = %s\n", ast->val);
	printAST(ast->child);
	printAST(ast->sibling);
}
