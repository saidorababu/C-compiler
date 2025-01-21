%{
	#include "TreeNode.h"
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	int yylex();
	int yyerror(const char *s);
	int yyparse();
	extern void display();
	struct entry{
		char arr[20];
		int scope;
		char dtype[10];
		int value;
	};
	extern struct entry symbolTable[100];

	typedef struct threeAddrCode{
		int index;
		int blockNo;
		char *result;
		char* operation;
		char* op1;
		char* op2;
	} threeAddrCode;


	threeAddrCode* createCode(char* result, char* operation, char* op1, char* op2){
		threeAddrCode* code = (threeAddrCode*)malloc(sizeof(threeAddrCode));
		code->result = (char*)malloc(strlen(result)+1);
		strcpy(code->result, result);
		code->operation = (char*)malloc(strlen(operation)+1);
		strcpy(code->operation, operation);
		code->op1 = (char*)malloc(strlen(op1)+1);
		strcpy(code->op1, op1);
		code->op2 = (char*)malloc(strlen(op2)+1);
		strcpy(code->op2, op2);
		return code;
	}

	void printCode(threeAddrCode* code){
		printf("%s = %s %s %s\n", code->result, code->op1, code->operation, code->op2);
	}

	List* newList(int i){
		List* list = (List*)malloc(sizeof(List));
		list->curr = i;
		list->next = NULL;
		return list;
	}

	List* mergeList(List* list1, List* list2){
		if(list1 == NULL) return list2;
		if(list2 == NULL) return list1;
		struct List *newList = (struct List*)malloc(sizeof(struct List));
		newList->curr = list1->curr;
		newList->next = mergeList(list1->next, list2);
		return newList;
	}
	int tempVarNo = 1;
	struct threeAddrCode* icg[1000];
	int icgIndex = 0;
	void generateCode(char* operation, char* op1, char* op2, char* result){
		icg[icgIndex++] = createCode(result, operation, op1, op2);
	}
	char* new_label(){
		char* label = (char*)malloc(10);
		sprintf(label, "L%d", tempVarNo++);
		return label;
	}
	char* new_temp(){
		char* temp = (char*)malloc(10);
		sprintf(temp, "t%d", tempVarNo++);
		return temp;
	}
	void backpatch(List* list, int label){
		// printf("backpatching %d\n",label);
		List* temp = list;
		while(temp != NULL){
			char* index = (char*)malloc(10);
			sprintf(index, "L%d", label);
			icg[temp->curr]->result = (char*)malloc(10);
			printf("backpatching %d\n",temp->curr);
			strcpy(icg[temp->curr]->result, index);
			temp = temp->next;
		}
	}
	void displayICG(){
		printf("Intermediate Code Generation\n");
		for(int i = 0; i < icgIndex; i++){
			icg[i]->index = i;
			if(icg[i]->operation[0] == 'g'){
				printf("%2d %s %s\n", i, icg[i]->operation, icg[i]->result);
			}else if(icg[i]->operation[0] == '='){
				printf("%2d %s = %s\n", i, icg[i]->result, icg[i]->op1);
			}else if( icg[i]->operation[0] == 'i'){
				printf("%2d %s %s %s %s\n", i, icg[i]->operation, icg[i]->op1,icg[i]->op2, icg[i]->result);
			}else if(icg[i]->operation[0] == 'p'){
				printf("%2d %s %s \n", i, icg[i]->operation, icg[i]->op1);
			}else if(icg[i]->operation[0] == 'c'){
				printf("%2d %s %s %s\n", i, icg[i]->operation , icg[i]->op1 , icg[i]->op2);
			}else{
				printf("%2d %s = %s %s %s\n", i, icg[i]->result, icg[i]->op1, icg[i]->operation, icg[i]->op2);
			}
		}
	}
	void printList(List* list){
		printf("List: ");
		List* temp = list;
		while(temp != NULL){
			printf("%d ", temp->curr);
			temp = temp->next;
		}
		printf("\n");
	}

	typedef struct Block{
		struct Block* next;
		threeAddrCode* code[100];
		int index;
		int start;
		int end;
	}block;

	block* createBlock(){
		block* b = (block*)malloc(sizeof(block));
		b->next = NULL;
		return b;
	}
	block* startBlock = NULL;
	void createBasicBlocks() {
		block* currentBlock = createBlock();
		startBlock = currentBlock;
		int i = 0;
		int blockNo = 1;
		while (i < icgIndex) {
			
			if (strcmp(icg[i]->operation, "if") == 0 || strcmp(icg[i]->operation, "goto") == 0) {
				icg[i]->blockNo = blockNo;
				currentBlock->code[currentBlock->index++] = icg[i];
				currentBlock->end = icg[i]->index;
				currentBlock->next = createBlock();
				blockNo++;
				currentBlock = currentBlock->next;
				currentBlock->start = icg[i]->index + 1;
			} else if (strcmp(icg[i]->result, "return") == 0) {
				icg[i]->blockNo = blockNo;
				currentBlock->code[currentBlock->index++] = icg[i];
				currentBlock->end = icg[i]->index;
				currentBlock->next = createBlock();
				blockNo++;
				currentBlock = currentBlock->next;
				currentBlock->start = icg[i]->index + 1;
			} else {
				icg[i]->blockNo = blockNo;
				currentBlock->code[currentBlock->index++] = icg[i];
			}
			i++;
		}
		currentBlock = startBlock;
		//assigning the next block to each block
		printf("----------------------------------------------------------------------------");
		for(int i = 0;i<icgIndex;i++){
			if(strcmp(icg[i]->operation,"if") == 0){
				// block* temp = startBlock;
				int label = atoi(icg[i]->result+1);
				for(int j = 0;j<icgIndex;j++){
				
					if(icg[j]->index == label){
						sprintf(icg[i]->result,"B%d",icg[j]->blockNo);
						break;
					}
				}
				
			}else if(strcmp(icg[i]->operation,"goto") == 0){
				int label = atoi(icg[i]->result+1);
				for(int j = 0;j<icgIndex;j++){
					if(icg[j]->index == label){
						sprintf(icg[i]->result,"B%d",icg[j]->blockNo);
						break;
					}
				}
			}
		}
		
	}

	
	void printBasicBlocks(block* startBlock) {
		block* currentBlock = startBlock;
		int blockIndex = 1;
		while (currentBlock != NULL) {
			printf("Basic Block %d:\n", blockIndex);
			for (int i = 0; i < currentBlock->index; i++) {
				threeAddrCode* code = currentBlock->code[i];
				// printf("%2d %s %s %s %s\n", currentBlock->code[i]->index, currentBlock->code[i]->operation, currentBlock->code[i]->op1, currentBlock->code[i]->op2, currentBlock->code[i]->result);
				if(code->operation[0] == 'g'){
					printf("%2d %s %s\n", code->index, code->operation, code->result);
				}else if(code->operation[0] == '='){
					printf("%2d %s = %s\n", code->index, code->result, code->op1);
				}else if( code->operation[0] == 'i'){
					printf("%2d %s %s %s %s\n", code->index, code->operation, code->op1,code->op2, code->result);
				}else if(code->operation[0] == 'p'){
					printf("%2d %s %s \n", code->index, code->operation, code->op1);
				}else if(code->operation[0] == 'c'){
					printf("%2d %s %s %s\n", code->index, code->operation , code->op1 , code->op2);
				}else{
					if(code->operation == "eliminated"){
						printf("%2d Dead Code eliminated\n",code->index);
						continue;
					}
					printf("%2d %s = %s %s %s\n", code->index, code->result, code->op1, code->operation, code->op2);
				}
			}
			printf("\n");
			currentBlock = currentBlock->next;
			blockIndex++;
		}
	}


	void constantFolding(block* startBlock) {
		block* currentBlock = startBlock;
		while (currentBlock != NULL) {
			int i = 0;
			while (i < currentBlock->index) {
				threeAddrCode* code = currentBlock->code[i];
				// printf("Constant folding: %s %s %s\n", code->op1, code->operation, code->op2);
				if (code->operation[0] != '=' && code->operation[0] != 'g' && code->operation[0] != 'i' && code->operation[0] != 'p' && code->operation[0] != 'c') {
					int op1_value = atoi(code->op1);
					int op2_value = atoi(code->op2);
					if (isdigit(code->op1[0]) && isdigit(code->op2[0])) {
						printf("Constant folding: %d %s %d------------------------\n", op1_value, code->operation, op2_value);
						int result;
						switch (code->operation[0]) {
							case '+':
								result = op1_value + op2_value;
								break;
							case '-':
								result = op1_value - op2_value;
								break;
							case '*':
								result = op1_value * op2_value;
								break;
							case '/':
								result = op1_value / op2_value;
								break;
							default:
								result = 0;
								break;
						}
						//printf("Result: %d----------------------------------------------\n", result);
						sprintf(code->op1, "%d", result);
						code->operation = "";
						code->op2 = "";
					}
				}
				i++;
			}
			currentBlock = currentBlock->next;
		}
		printf("Constant Folding Completed");
	}
	void commonsubexpression(block* startBlock) {
		block* currentBlock = startBlock;
		while (currentBlock != NULL) {
			int i = 0;
			while (i < currentBlock->index) {
				threeAddrCode* code = currentBlock->code[i];
				if (code->operation[0] != 'g' && code->operation[0] != 'i' && code->operation[0] != 'p' && code->operation[0] != 'c') {
					int j = i + 1;
					while (j < currentBlock->index) {
						if (strcmp(currentBlock->code[j]->op1, code->op1) == 0 && strcmp(currentBlock->code[j]->op2, code->op2) == 0 && strcmp(currentBlock->code[j]->operation, code->operation) == 0) {
							currentBlock->code[j]->operation = "";
							currentBlock->code[j]->op1 = code->result;
							currentBlock->code[j]->op2 = "";
						}
						j++;
					}
				}
				i++;
			}
			currentBlock = currentBlock->next;
		}
	}
	void deadCodeElimination(){
		
		int eliminations[1000];
		for(int i = 0;i<1000;i++){
			eliminations[i] = 0;
		}
		for(int i = 0;i<icgIndex;i++){
			
			if(icg[i]->operation[0] == '='){
				int flag = 0;
				for(int i = 0;i<1000;i++){
					eliminations[i] = 0;
				}
				for(int j = i+1;j<icgIndex;j++){
					
					if(strcmp(icg[j]->op1,icg[i]->result) == 0 || strcmp(icg[j]->op2,icg[i]->result) == 0){
						flag = 1;
						continue;
					}
					if(strcmp(icg[j]->result,icg[i]->result) == 0){
						
						eliminations[j] = 1;
					}
				}
				if(flag == 0){
					for(int x= 0;x<icgIndex;x++){
						if(eliminations[x] == 1){
							icg[x]->result = "";
							icg[x]->op1 = "";
							icg[x]->op2 = "";
							icg[x]->operation = "eliminated";
						}
					}
				}
			}
		}
		
	}
	void copyPropagation(){
		block* currentBlock = startBlock;
		while (currentBlock != NULL) {
			int i = 0;
			while (i < currentBlock->index) {
				threeAddrCode* code = currentBlock->code[i];
				if (code->operation[0] != 'g' && code->operation[0] != 'i' && code->operation[0] != 'p' && code->operation[0] != 'c') {
					int j = i + 1;
					while (j < currentBlock->index) {
						if (strcmp(currentBlock->code[j]->op1, code->result) == 0) {
							currentBlock->code[j]->op1 = code->op1;
						}
						if (strcmp(currentBlock->code[j]->op2, code->result) == 0) {
							currentBlock->code[j]->op2 = code->op1;
						}
						j++;
					}
				}
				i++;
			}
			currentBlock = currentBlock->next;
		}
		
	}
	// void printTree(struct Node* node, int level);
	TreeNode *head = NULL;
	struct TreeNode *create_Node(char *label, int value, char *value_str,char *dtype, int num_children, ...) {
		struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
		newNode->label = label;
		newNode->value = value;
		newNode->value_str = (char*)malloc(sizeof(char) * strlen(value_str) + 1);
		strcpy(newNode->value_str,value_str);
		newNode->num_children = num_children;
		newNode->dtype= dtype;
		newNode->scope = -1;
		newNode->children = NULL;
		if(num_children<1) return newNode;
		newNode->children = malloc(sizeof(TreeNode*) * num_children);

		va_list args;
		va_start(args, num_children);

		for (int i = 0; i < num_children; i++) {
			newNode->children[i] = va_arg(args, struct TreeNode*);
		}

		va_end(args);

		return newNode;
	}

	void printTree(TreeNode *root,int level){
		if(root == NULL){
			return;
		}
		for(int i = 0;i<level;i++){
			printf("   ");
		}
		if(root->value ==-1 && strcmp(root->dtype,"NULL") == 0){
			if(strcmp(root->value_str,"NULL") == 0){
				printf("|--%d.%s\n",level, root->label);
			}else{
				printf("|--%d.%s\n",level, root->value_str);
			}
		}
		else{
			printf("|--%d.(%s,%d,%s,%s)\n",level, root->label,root->value,root->value_str,root->dtype);
		}
		
		for(int i = 0;i<root->num_children;i++){
			printTree(root->children[i],level+1);
		}
	}
	void addEntry(char *name, char *dtype,int scope,int value){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,name) == 0 && symbolTable[i].scope == scope){
				//printf("Variable: %s, dtype:%s  \n",name,symbolTable[i].dtype);

				if(strcmp(symbolTable[i].dtype,"null") != 0 ){
					printf("Variable %s is already declared\n",name); 
					yyerror("Variable already declared");
					break;
					return;
				}
				symbolTable[i].value = value;
				strcpy(symbolTable[i].dtype,dtype);
				// printf("Variable: %s, dtype: %s \n",name,symbolTable[i].dtype);
				break;
			}
		}
	}
	void addFunctionValue(char *name, int value){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,name) == 0){
				symbolTable[i].value = value ;
				break;
			}
		}
	}
	struct Pair{
		char *dtype;
		int scope;
	};
	struct Pair make_pair(char* dtype, int scope) {
		struct Pair p;
		p.dtype = dtype;
		p.scope = scope;
		return p;
	}

	struct Pair checkIdentifier(char *name){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,name) == 0){
				return make_pair(symbolTable[i].dtype,symbolTable[i].scope);
				break;
			}
		}
		return make_pair("NULL",-1);
	}
	int checkEntry(char *name,char *dtype,int scope,int value){
		for(int i = 0;i<100;i++){
			
			if(strcmp(symbolTable[i].arr,name) == 0 && symbolTable[i].scope <= scope && strcmp(symbolTable[i].dtype,dtype) == 0){
				symbolTable[i].value = value;
				return 1;
			}
		}
		return 0;
	}
	void checkid(TreeNode *root){
		char x = root->value_str[0];
		if(x == 't') return;
		struct Pair p = checkIdentifier(root->value_str);
		if(p.dtype == "keyword"){
			printf("variable %s using the keyword declare again\n",root->value_str);
			yyerror("Variable using keyword");
			return;
		}

		if(p.dtype == "NULL"){
			printf("Variable %s is not declared\n",root->value_str); 
			yyerror("Variable not declared");
			return ;
		}else{
			root->dtype = p.dtype;
		}
		if(checkEntry(root->value_str,root->dtype,root->scope,root->value) == 0){
			
			printf("Variable %s,%s,%d is not declared\n",root->value_str,root->dtype,root->scope); 
			yyerror("Variable not declared");
			return;
		};
	}
	void checkType(TreeNode* a, TreeNode* b){
		if((a->dtype != b->dtype) && (strcmp(a->dtype, "string") == 0 || strcmp(b->dtype, "string") == 0)){
			yyerror("Type mismatch");
			return;
		}
	}
	int checkfnArguments(TreeNode* a){
		int flag = 0;
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,a->value_str) == 0){
				if(symbolTable[i].value != a->value){
					yyerror("Number of arguments mismatch");
					return 0;
				}else{
					flag == 1;
					return 1;
				}
			}
		}
		if(flag == 0){
			yyerror("Function not declared");
			return 0;
		}
		return 1;
	}
%}

%union {
    int num;
    char *str;
	struct TreeNode *node;
}

%start program
%error-verbose
%token<node> PLUS MINUS MUL DIV number define swap  size using namespace std vector AND OR NOT if_x else_x while_x for_x return_x printf_x main_x assignmentop comparisionop logicalop datatype unary identifier string character cout cin insert extract header LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET SEMICOLON COMMA
%type<node> E T F M N unary_statement namespace_statement swap_statement function_call parameter arg_list decl_id vectordatatype list assignment_statement dec_assignment statement_list function_declarations function_declaration declaration_statement id_list insert_statement extract_statement if_statement while_statement for_statement return_statement cout_statement cin_statement statement combined_stmt headers parameter_list program
/* rules */

%%

program: headers namespace_statement function_declarations {  $$ = create_Node("program", -1, "NULL","NULL", 3,$1,$2, $3);if(!head) head = $$;} ;
function_declarations:
	function_declaration function_declarations { $$ = create_Node("function_declarations", -1, "NULL","NULL", 2,$1,$2); }
	| ;


headers: header {$$ = create_Node("headers", -1, "NULL","NULL",1,$1);}
	| header headers { $$ = create_Node("headers", -1,"NULL","NULL", 2, $1, $2);};

function_declaration: datatype identifier {$2->dtype = $1->dtype;} LPAREN parameter_list { addEntry($2->value_str,$2->dtype,$2->scope,$5->value);} RPAREN combined_stmt {
	$$ = create_Node("function_declaration", -1, "NULL","NULL", 4, $1, $2, $5, $8);
};

parameter_list: 
	  parameter COMMA parameter_list { 
		$$ = create_Node("parameter_list", -1, "NULL","NULL", 2, $1, $3);
		$$->value = $3->value + 1;
	 }
	 | parameter { $$ = create_Node("parameter_list", -1, "NULL","NULL", 1, $1); $$->value = 1; }
	 ;
 parameter: 
 	datatype identifier {
		$2->dtype = $1->dtype;
		$$ = create_Node("parameter", -1, "NULL","NULL",2, $1, $2);
		$$->value = 1;
		// addEntry($2->value_str,$2->dtype,$2->scope,$2->value);
	}
	| vectordatatype identifier {
		$2->dtype = $1->dtype;
		$$ = create_Node("parameter", -1, "NULL","NULL",2, $1, $2);
		$$->value = 1;
		// addEntry($2->value_str,$2->dtype,$2->scope,$2->value);
	}
	| { $$ = NULL; };

combined_stmt: LBRACE statement_list RBRACE { $$ = create_Node("combined_stmt", -1,"NULL","NULL", 3,$1,$2,$3); $$->nextList = $2->nextList; }
	| statement { $$ = $1;  }
	;
statement_list: 
	statement_list M statement { 
			$$ = $1;
			// printf("2222222222backpatching %d\n",$2->nextList->curr);
			backpatch($1->nextList,$2->nextList->curr);
			// printf("PRINTING AFTER STMT\n");
			// printList($1->nextList);
			$$->nextList = $3->nextList;
		}
	| statement { $$ = $1; $$->nextList = $1->nextList; }
	|;

M : {$$ = create_Node("M", -1, "st_if","NULL", 0);$$->nextList = newList(icgIndex);}
N : {$$ = create_Node("N", -1, "st_if","NULL", 0);$$->nextList = newList(icgIndex);generateCode("goto","","","");}

statement: declaration_statement { $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| assignment_statement SEMICOLON {printf("assignment_statement\n"); $$ = create_Node("statement", -1,"NULL","NULL",2, $1, $2);}
	| define_statement { $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| for_statement { $$=$1; }
	| if_statement { $$=$1; }
	| while_statement { $$ = $1; }
	| cout_statement {printf("cout_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| cin_statement {printf("cin_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| return_statement {printf("return_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| function_call SEMICOLON {printf("function_call\n"); $$ = create_Node("statement", -1, "NULL","NULL",2,$1,$2); }
	| unary_statement SEMICOLON {printf("unary_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",2,$1,$2); }
	| swap_statement SEMICOLON {printf("swap_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",2,$1,$2); }
	| error SEMICOLON { $$ = create_Node("error", -1, "NULL","NULL",0); };

define_statement: define identifier number { $$ = create_Node("define_statement", -1, "NULL","NULL",2,$1,$2); addEntry($1->value_str,"int",$1->scope,$2->value); }
	;
unary_statement : unary identifier { $$ = create_Node("unary_statement", -1, "NULL","NULL",2,$1,$2);  $$->dtype = $2->dtype; generateCode("+", $2->value_str, "1", $2->value_str); }
	| identifier unary { $$ = create_Node("unary_statement", -1, "NULL","NULL",2,$1,$2); $$->dtype = $1->dtype; generateCode("+", $1->value_str, "1", $1->value_str); }
	;
swap_statement: swap LPAREN E COMMA E RPAREN { $$ = create_Node("swap_statement", -1, "NULL","NULL", 3, $1, $3, $5); checkid($3); checkid($5); generateCode("swap", $3->value_str, $5->value_str, ""); }
	;
namespace_statement: using namespace std SEMICOLON { $$ = create_Node("namespace_statement", -1, "NULL","NULL", 1, $1); }
	;
function_call: identifier LPAREN arg_list RPAREN { 
		$$ = create_Node("function_call", -1, "function_call","NULL", 4, $1, $2, $3, $4); 
		$1->value = $3->value;
		printf("Function is being called-------------------- %s;Arguments:%d\n",$1->value_str,$3->value);
		int x = checkfnArguments($1);
		if(x){
			// printf("arguments %d\n",$3->value);
			// for(int i = 0;i<$3->value;i++){
			// 	printf("arguments %s\n",$3->children[i]->value_str);
			// 	//generateCode("param", $3->children[i]->value_str, "", "");
			// }
			generateCode("call", $1->value_str, "", "");
		}
	}	
	| identifier LPAREN RPAREN { $$ = create_Node("function_call", -1, "NULL","NULL", 3, $1, $2, $3); }
	;

arg_list: E { 
		$$ = create_Node("arg_list", -1, $1->value_str,"NULL", 1, $1); $$->value = 1; 
		generateCode("param", $1->value_str, "", "");
	}
	| E COMMA arg_list { $$ = create_Node("arg_list", -1, "NULL","NULL", 2, $1, $3); $$->value = $3->value + 1; generateCode("param", $1->value_str, "", ""); }	
	;

if_statement: if_x LPAREN E RPAREN M combined_stmt { 
		$$ = create_Node("if_statement", -1,"NULL","NULL", 5,$1,$2,$3,$4,$6);
		backpatch($3->trueList,$5->nextList->curr);
		$$->nextList = mergeList($3->falseList,$6->nextList);
	}
	| if_x LPAREN E RPAREN M combined_stmt else_x N M combined_stmt {
		$$ = create_Node("if_statement", -1,"NULL","NULL", 9,$1,$2,$3,$4,$6,$7,$8,$9,$10);
		backpatch($3->trueList,$5->nextList->curr);
		backpatch($3->falseList,$9->nextList->curr);
		$$->nextList = mergeList(mergeList($6->nextList,$8->nextList),$10->nextList);
	}

while_statement: while_x M LPAREN E RPAREN M combined_stmt {
	$$ = create_Node("while_statement", -1, "NULL","NULL", 7, $1, $2, $3, $4, $5, $6, $7);
	backpatch($4->trueList,$6->nextList->curr);
	backpatch($7->nextList,$2->nextList->curr);
	$$->nextList = $4->falseList;
	char* x = malloc(10);
	sprintf(x,"L%d",$2->nextList->curr);
	generateCode("goto", "", "", x);
 };

for_statement: for_x M LPAREN declaration_statement E SEMICOLON M E RPAREN combined_stmt { 
	$$ = create_Node("for_statement", -1, "NULL","NULL", 9, $1, $3, $4, $5, $6, $7, $8, $9,$10);
	backpatch($5->trueList,$7->nextList->curr);
	backpatch($10->nextList,$2->nextList->curr);
	$$->nextList = $5->falseList;
	char* x = malloc(10);
	sprintf(x,"L%d",$2->nextList->curr);
	generateCode("goto", "", "", x);
	// backpatch($4->falseList,$9->nextList->curr);
};
return_statement: return_x E SEMICOLON { $$ = create_Node("return_statement", -1,"NULL","NULL", 2, $1, $2); generateCode($2->value_str, "", "", "return") }
| return_x SEMICOLON { $$ = create_Node("return_statement", -1, "NULL","NULL", 2, $1,$2); generateCode("return", "","", "")};

cout_statement: cout insert_statement SEMICOLON { $$ = create_Node("cout_statement", -1,"NULL","NULL", 2, $1, $2); };

insert_statement: insert E insert_statement { $$ = create_Node("insert_statement", -1,"NULL","NULL", 3, $1, $2, $3); }
    | insert string insert_statement { $$ = create_Node("insert_statement", -1, "NULL","NULL", 3, $1, $2, $3); }
	| insert E { $$ = create_Node("insert_statement", -1, "NULL","NULL", 2, $1, $2); }
	| insert string { $$ = create_Node("insert_statement", -1, "NULL","NULL", 2, $1, $2); }

cin_statement: cin extract_statement SEMICOLON { $$ = create_Node("cin_statement", -1, "NULL","NULL", 3, $1, $2, $3); };

extract_statement: extract identifier extract_statement { $$ = $3; }
| extract identifier { $$ = create_Node("extract_statement", -1, "NULL","NULL", 2, $1, $2); } 
;


declaration_statement: datatype id_list SEMICOLON { $2->dtype = $1->dtype;  $$ = create_Node("declaration_statement", -1, "NULL","NULL", 3, $1, $2, $3); }
	| vectordatatype identifier LBRACE list RBRACE SEMICOLON {
		$$ = create_Node("id_list", -1, "NULL","NULL", 3, $1, $2, $4);
		$2->dtype = $1->dtype;
		addEntry($2->value_str,$2->dtype,$2->scope,$4->value);
	}
	| vectordatatype identifier LPAREN number RPAREN SEMICOLON {
		$$ = create_Node("id_list", -1, "NULL","NULL", 3, $1, $2, $4);
		$2->dtype = $1->dtype;
		addEntry($2->value_str,$2->dtype,$2->scope,$4->value);
	};
vectordatatype: vector comparisionop datatype comparisionop {$$ = create_Node("vectordatatype", -1, "NULL","NULL", 2, $1, $3); $$->dtype = $3->dtype;}
	;
id_list: id_list {$1->dtype = $<node>0->dtype;} COMMA decl_id {
		$$ = create_Node("id_list", -1, "NULL","NULL", 3, $1, $3, $4); 
		$4->dtype = $<node>0->dtype;
		$1->dtype = $<node>0->dtype;
		addEntry($4->value_str,$4->dtype,$4->scope,$4->value);
	}
	| decl_id {
		$$ = $1;
		$1->dtype = $<node>0->dtype;
	};

decl_id:
	 identifier LBRACKET number RBRACKET {
		$$ = create_Node("id_list", -1, "NULL","NULL", 4, $1, $2, $3, $4);
		$1->dtype = $<node>0->dtype;
		addEntry($1->value_str,$1->dtype,$1->scope,$1->value);
	}
	| dec_assignment {
		$$ = create_Node("id_list", -1, "NULL","NULL", 1, $1);
		$1->dtype = $<node>0->dtype; 
	}
	| identifier { 
		$$ = create_Node("id_list", -1, "NULL","NULL", 1, $1);
		$1->dtype = $<node>0->dtype;
		//printf("dtype %s %s %s %s\n",$<node>0->dtype,$<node>-1->dtype,$<node>-2->dtype,$<node>-3->dtype);
		addEntry($1->value_str,$1->dtype,$1->scope,$1->value); 
	}
	;
list: list COMMA number { $$ = create_Node("list", -1, "NULL","NULL", 3, $1, $2, $3); }
	| number { $$ = create_Node("list", -1, "NULL","NULL", 1, $1); }
	;

dec_assignment: 
	identifier assignmentop E { 
		$$ = create_Node("dec_assignment", -1, "NULL","NULL", 3, $1, $2, $3); 
		checkType($1,$3);
		$1->value = $3->value;
		if($<node>0->dtype != $<node>-1->dtype) $1->dtype = $<node>0->dtype;
		else $1->dtype = $<node>-3->dtype;
		// printf("dtype %s %s %s %s\n",$<node>0->dtype,$<node>-1->dtype,$<node>-2->dtype,$<node>-3->dtype);
		addEntry($1->value_str,$1->dtype,$1->scope,$1->value);
		char *x = malloc(10);
		sprintf(x,"%s",$3->value_str);
		generateCode("=", x,"", $1->value_str);
	}

assignment_statement:
	identifier assignmentop E  {
		$$ = create_Node("assignment_statement", -1, "NULL","NULL", 3, $1, $2, $3);
		$1->value = $3->value;
		checkid($1);
		checkType($1,$3);
		generateCode("=", $3->value_str, "", $1->value_str);
	}
	| identifier LBRACKET E RBRACKET assignmentop E {
		$$ = create_Node("assignment_statement", -1, "NULL","NULL", 5, $1, $2, $3, $4, $5);
		checkid($1);
		checkType($1,$5);
		char *t = new_temp();
		generateCode("*", $3->value_str, "4", t);
		char *x = malloc(strlen($1->value_str)+strlen(t)+1);
		sprintf(x,"(%s)",$1->value_str);
		generateCode("+", t, x, t);
		generateCode("=", $5->value_str, "", t);
	}
;

E: identifier assignmentop E  { $$ = create_Node("E", -1,  "NULL","NULL", 3, $1, $2, $3); $1->value = $3->value;  checkid($1); checkType($1,$3); }
	|	E comparisionop E { $$ = create_Node("E", -1,  "NULL","NULL", 3, $1, $2, $3); checkType($1,$3); 
			$$->trueList = newList(icgIndex);
			$$->falseList = newList(icgIndex+1);
			printList($$->trueList);
			printList($$->falseList);
			char *x = malloc(strlen($2->value_str)+strlen($1->value_str)+strlen($3->value_str)+1);
			int k = 0;
			for(int i = 0;i<strlen($1->value_str);i++){
				x[k++] = $1->value_str[i];
			}
			for(int i = 0;i<strlen($2->value_str);i++){
				x[k++] = $2->value_str[i];
			}
			for(int i = 0;i<strlen($3->value_str);i++){
				x[k++] = $3->value_str[i];
			}
			generateCode("if", x,"goto","");
			generateCode("goto","","","");
	}
	|	E AND M E { $$ = create_Node("E", -1,  "NULL","NULL", 3, $1, $2, $4); checkType($1,$4); 
		
		backpatch($1->trueList, $3->nextList->curr);
		$$->trueList = $4->trueList;
		$$->falseList = mergeList($1->falseList, $4->falseList);
	}
	|	E OR M E { $$ = create_Node("E", -1,  "NULL","NULL", 3, $1, $2, $4); checkType($1,$4); 

		backpatch($1->falseList, $3->nextList->curr);
		$$->falseList = $4->falseList;
		$$->trueList = mergeList($1->trueList, $4->trueList);
	}
	| NOT E { $$ = create_Node("E", !$2->value,  new_temp(),"NULL", 2, $1, $2); $$->value = !$2->value; $$->trueList = $2->falseList; $$->falseList = $2->trueList; }
	|   E PLUS T { $$ = create_Node("E", $1->value+$3->value, new_temp(),"NULL", 3, $1, $2, $3); checkType($1,$3);  generateCode("+", $1->value_str, $3->value_str, $$->value_str); }
	|   E MINUS T { $$ = create_Node("E", $1->value-$3->value, new_temp(),"NULL", 3, $1, $2, $3); checkType($1,$3); generateCode("-", $1->value_str, $3->value_str, $$->value_str);}
	|   T { $$ = create_Node("E", $1->value, $1->value_str,"NULL", 1, $1);  $$->value = $1->value; $$->dtype = $1->dtype; }
	;
	
T: T MUL F { $$ = create_Node("T", $1->value*$3->value, new_temp(),"NULL", 3, $1, $2, $3); checkType($1,$3); generateCode("*",  $1->value_str, $3->value_str, $$->value_str);}
	|	T DIV F { $$ = create_Node("T", $1->value/$3->value, new_temp(),"NULL", 3, $1, $2, $3);checkType($1,$3); generateCode("/", $1->value_str, $3->value_str, $$->value_str);}
	|	F { $$ = create_Node("T", $1->value, $1->value_str,"NULL", 1, $1); $$->dtype = $1->dtype;  $$->value = $1->value;} 
	;

F: number { $$ = create_Node(new_temp(), -1, $1->value_str,"NULL", 1, $1);  $$->dtype = $1->dtype; $$->value = $1->value;  }
	| character { $$ = create_Node("F", -1, "NULL","NULL", 1, $1);  $$->dtype = $1->dtype;  }
	| LPAREN E RPAREN { $$ = $2;  $$->dtype = $2->dtype;  }
	| identifier { $$ = create_Node("F", -1, $1->value_str,"NULL", 1, $1); checkid($1);  $$->dtype = $1->dtype; }
	| unary identifier { $$ = create_Node("F", -1, $1->value_str,"NULL", 2, $1, $2); checkid($2);  $$->dtype = $2->dtype; generateCode("+", $2->value_str, "1", $2->value_str); }
	| identifier unary { $$ = create_Node("F", -1, $1->value_str,"NULL", 2, $1, $2); checkid($1);  $$->dtype = $1->dtype; generateCode("+", $1->value_str, "1", $1->value_str); }
	| string { $$ = create_Node("F", -1, "NULL","NULL", 1, $1); $$->dtype = $1->label;}
	| identifier LBRACKET E RBRACKET {
		$$ = create_Node("F", -1, new_temp(),"NULL", 4, $1, $2, $3, $4); $$->dtype = $1->dtype;
		checkid($1);
		char *t = new_temp();
		generateCode("*", $3->value_str, "4", t);
		char *x = malloc(strlen($1->value_str)+strlen(t)+1);
		sprintf(x,"(%s)",$1->value_str);
		generateCode("+", t, x, $$->value_str);
	}
	| function_call { $$ = $1; }
	| identifier '.' size LPAREN RPAREN { $$ = create_Node("F", -1, $3->value_str,"NULL", 1, $1); $$->dtype = "int";}
	;

%%
#include <ctype.h>
int yyerror(const char *s)
{
  	extern int yylineno;
  	// valid = 0;
	if(yylineno != 27){
		printf("Line no: %d \n The error is: %s\n",yylineno,s);
	}
}
extern FILE *yyin;
int main(int argc,char **argv){
	if(argc<2)
	{
		printf("Usage: %s <filename>\n",argv[0]);
		return 1;
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		printf("Error: File not found\n");
		return 1;
	}
	// initializeSymbolTable()
	extern char *yytext;
	yyin=fp;
	yyparse();
	// yyparse();
	printf("---------------\n");
	printTree(head,0);
	printf("---------------\n");
	display();

	printf("---------------\n");
	displayICG();
	printf("---------------\n");
	createBasicBlocks();
	printf("--------------Blocks--------------\n");
	printBasicBlocks(startBlock);
	// deadCodeElimination(startBlock);
	deadCodeElimination();
	printf("--------------Dead Code Eliminated-------------------\n");
	constantFolding(startBlock);
	printf("---------------\n");
	commonsubexpression(startBlock);
	printf("--------------common sub Expression done------------------");
	printf("--------------Blocks After Optimization--------------\n");
	printBasicBlocks(startBlock);
	
}