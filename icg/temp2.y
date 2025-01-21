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
				printf("Variable: %s, dtype: %s \n",name,symbolTable[i].dtype);
				// symbolTable[i].value = 0;
				
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
				break;
			}
		}
		return 0;
	}
	void checkid(TreeNode *root){
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
	void checkfnArguments(TreeNode* a){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,a->value_str) == 0){
				if(symbolTable[i].value != a->value){
					yyerror("Number of arguments mismatch");
					return;
				}
			}
		}
	}
%}

%union {
    int num;
    char *str;
	struct TreeNode *node;
}

%start program
%error-verbose
%token<node> PLUS MINUS MUL DIV number AND OR NOT if_x else_x while_x for_x return_x printf_x main_x assignmentop comparisionop logicalop datatype unary identifier string character cout cin insert extract header LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET SEMICOLON COMMA
%type<node> E T F M N function_call arg_list decl_id assignment_statement dec_assignment statement_list function_declarations function_declaration declaration_statement id_list insert_statement extract_statement if_statement while_statement for_statement return_statement cout_statement cin_statement statement combined_stmt headers parameter_list program
/* rules */

%%

program: headers function_declarations {  $$ = create_Node("program", -1, "NULL","NULL", 2,$1,$2);if(!head) head = $$;} ;
function_declarations:
	function_declaration function_declarations { $$ = create_Node("function_declarations", -1, "NULL","NULL", 2,$1,$2); }
	| ;


headers: header {$$ = create_Node("headers", -1, "NULL","NULL",1,$1);}
	| header headers { $$ = create_Node("headers", -1,"NULL","NULL", 2, $1, $2);};

function_declaration: datatype identifier LPAREN parameter_list RPAREN combined_stmt {
	$2->dtype = $1->dtype;
	$$ = create_Node("function_declaration", -1, "NULL","NULL", 6, $1, $2, $3, $4, $5,$6);
	$$->value = $4->value;
	addEntry($2->value_str,$2->dtype,$2->scope,$4->value);
	addFunctionValue($2->value_str, $4->value);
};

parameter_list: datatype identifier COMMA parameter_list { 
	$$ = create_Node("parameter_list", -1, "NULL","NULL",4, $1, $2, $3, $4);
	$2->dtype = $1->dtype;
	$$->value = $4->value + 1;
	addEntry($2->value_str,$2->dtype,$2->scope,$2->value);
	 }
 | datatype identifier {
	$2->dtype = $1->dtype;
	$$ = create_Node("parameter_list", -1, "NULL","NULL",2, $1, $2);
	$$->value = 1;
	addEntry($2->value_str,$2->dtype,$2->scope,$2->value);
 }
	| { $$ = create_Node("parameter_list", -1, "NULL","NULL",0); $$->value = 0 };

combined_stmt: LBRACE statement_list RBRACE { $$ = create_Node("combined_stmt", -1,"NULL","NULL", 3,$1,$2,$3); $$->nextList = $2->nextList; }
	| statement { $$ = $1;  }
	;
statement_list: 
	statement_list M statement { 
			$$ = create_Node("statement_list", -1, "NULL","NULL", 2, $1, $3);
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
	| for_statement { $$=$1; }
	| if_statement { $$=$1; }
	| while_statement { $$ = $1; }
	| cout_statement {printf("cout_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| cin_statement {printf("cin_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| return_statement {printf("return_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| function_call SEMICOLON {printf("function_call\n"); $$ = create_Node("statement", -1, "NULL","NULL",2,$1,$2); }
	| error SEMICOLON { $$ = create_Node("error", -1, "NULL","NULL",0); };



function_call: identifier LPAREN arg_list RPAREN { 
		$$ = create_Node("function_call", -1, "function_call","NULL", 4, $1, $2, $3, $4); 
		$1->value = $3->value;
		checkfnArguments($1);
		printf("arguments %d\n",$3->value);
		for(int i = 0;i<$3->value;i++){
			generateCode("param", $3->children[i]->value_str, "", "");
		}
		generateCode("call", $1->value_str, "", "");
	}	
	| identifier LPAREN RPAREN { $$ = create_Node("function_call", -1, "NULL","NULL", 3, $1, $2, $3); }
	;

arg_list: identifier { $$ = create_Node("arg_list", -1, $1->value_str,"NULL", 1, $1); $$->value = 1; }
	| identifier COMMA arg_list { $$ = create_Node("arg_list", -1, "NULL","NULL", 2, $1, $3); $$->value = $3->value + 1; }	
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


declaration_statement: datatype id_list SEMICOLON { $2->dtype = $1->dtype;  $$ = create_Node("declaration_statement", -1, "NULL","NULL", 3, $1, $2, $3); };

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
	};

dec_assignment: 
	identifier assignmentop E { 
		$$ = create_Node("dec_assignment", -1, "NULL","NULL", 3, $1, $2, $3); 
		checkType($1,$3);
		$1->value = $3->value;
		if($<node>0->dtype != $<node>-1->dtype) $1->dtype = $<node>0->dtype;
		else $1->dtype = $<node>-3->dtype;
		printf("dtype %s %s %s %s\n",$<node>0->dtype,$<node>-1->dtype,$<node>-2->dtype,$<node>-3->dtype);
		addEntry($1->value_str,$1->dtype,$1->scope,$1->value);
		char *x = malloc(10);
		sprintf(x,"%d",$3->value);
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
	// printTree(head,0);
	printf("---------------\n");
	display();

	printf("---------------\n");
	displayICG();
}