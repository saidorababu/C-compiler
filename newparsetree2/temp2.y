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

		// if(root->value ==-1 && strcmp(root->value_str,"NULL") == 0){
		// 	printf("%d.%s\n",level, root->label);
		// }else if(root->value == -1){
		// 	printf("%d.%s\n", level,root->value_str);
		// }else{
		// 	printf("%d.(%s,%d)\n",level, root->label, root->value);
		// }
		 printf("%d.(%s,%d,%s,%s)\n",level, root->label,root->value,root->value_str,root->dtype);
		for(int i = 0;i<root->num_children;i++){
			printTree(root->children[i],level+1);
		}
	}
	void addEntry(char *name, char *dtype,int scope){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,name) == 0 && symbolTable[i].scope == scope){
				//printf("Variable: %s, dtype:%s  \n",name,symbolTable[i].dtype);

				if(strcmp(symbolTable[i].dtype,"null") != 0 ){
					printf("Variable %s is already declared\n",name); 
					yyerror("Variable already declared");
					break;
					return;
				}

				strcpy(symbolTable[i].dtype,dtype);
				printf("Variable: %s, dtype: %s \n",name,symbolTable[i].dtype);
				// symbolTable[i].value = 0;
				
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
	int checkEntry(char *name,char *dtype,int scope){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,name) == 0 && symbolTable[i].scope <= scope && strcmp(symbolTable[i].dtype,dtype) == 0){
				return 1;
				break;
			}
		}
		return 0;
	}
	void checkid(TreeNode *root){
		struct Pair p = checkIdentifier(root->value_str);
		if(p.dtype == "NULL"){
			printf("Variable %s is not declared\n",root->value_str); 
			yyerror("Variable not declared");
			return ;
		}else{
			root->dtype = p.dtype;
		}
		if(checkEntry(root->value_str,root->dtype,root->scope) == 0){
			printf("Variable %s,%s,%d is not declared\n",root->value_str,root->dtype,root->scope); 
			yyerror("Variable not declared");
		};
	}
%}

%union {
    int num;
    char *str;
	struct TreeNode *node;
}

%start program
%token EOL
%error-verbose
%token<node> PLUS MINUS MUL DIV number if_x else_x while_x for_x return_x printf_x main_x assignmentop comparisionop logicalop datatype unary identifier string character cout cin insert extract header LBRACE RBRACE LPAREN RPAREN SEMICOLON COMMA
%type<node> E T F assignment_statement dec_assignment statement_list function_declaration declaration_statement id_list insert_statement extract_statement if_statement else_statement if_else_statement while_statement for_statement return_statement cout_statement cin_statement statement headers parameter_list program
/* rules */
%%

program: headers function_declaration program { printf("program No: %d\n",$$); $$ = create_Node("program", -1, "NULL","NULL", 3,$1,$2,$3);if(!head) head = $$;} 
| statement_list program {$$ = create_Node("program", -1, "NULL","NULL", 2,$1,$2); head = $$;}
| EOL program {$$ = create_Node("program", -1, "NULL","NULL", 1,$2); head = $$;}
| EOL {$$ = NULL;}
|;

headers: header {$$ = create_Node("headers", -1, "NULL","NULL",1,$1);}
| headers EOL headers { $$ = create_Node("headers", -1,"NULL","NULL", 2, $1, $3);}
| EOL headers { $$ = create_Node("headers", -1, "NULL","NULL",1, $2);}
| EOL{ $$ = NULL; };

function_declaration: datatype identifier LPAREN parameter_list RPAREN LBRACE statement_list RBRACE statement_list {printf("Function NO: %d\n",$$); $2->dtype = $1->value_str; $$ = create_Node("function_declaration", -1, "NULL","NULL", 9, $1,$2,$3, $4, $5, $6, $7, $8, $9); };

parameter_list: datatype identifier COMMA parameter_list { 
	$$ = create_Node("parameter_list", -1, "NULL","NULL",4, $1, $2, $3, $4);
	$2->dtype = $1->dtype;
	addEntry($2->value_str,$2->dtype,$2->scope);
	 }
 | datatype identifier { 
	$2->dtype = $1->dtype;
	$$ = create_Node("parameter_list", -1, "NULL","NULL",2, $1, $2);
	addEntry($2->value_str,$2->dtype,$2->scope);
 }
| EOL {$$ = NULL;}
| { $$ = NULL; };


statement_list: 
	statement statement_list { $$ = create_Node("statement_list", -1, "NULL","NULL", 2, $1, $2);}
|	EOL statement_list { $$ = create_Node("statement_list", -1, "NULL","NULL", 1, $2);}
|	EOL {$$ = NULL;}
|
;


statement: declaration_statement { $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
| assignment_statement SEMICOLON {printf("assignment_statement\n"); $$ = create_Node("statement", -1,"NULL","NULL",2, $1, $2);}
| for_statement {printf("for_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
| if_statement {printf("if_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
| if_else_statement {printf("if_else_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
| while_statement {printf("while_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
| cout_statement {printf("cout_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
| cin_statement {printf("cin_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
| return_statement {printf("return_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
| error SEMICOLON { $$ = create_Node("error", -1, "NULL","NULL",0); }
| EOL { $$ = NULL; };

if_statement: if_x LPAREN E RPAREN LBRACE statement_list RBRACE { $$ = create_Node("if_statement", -1,"NULL","NULL", 7,$1,$2,$3,$4,$5,$6,$7);}
| if_x LPAREN E RPAREN  statement { $$ = create_Node("if_statement", -1,"NULL","NULL", 5,$1,$2,$3,$4,$5);}
| if_statement EOL  { $$ = create_Node("if_statement", -1,"NULL","NULL", 1,$1);};


else_statement: else_x LBRACE statement_list RBRACE { $$ = create_Node("else_statement", -1, "NULL","NULL", 3, $1, $2, $3); }
 | else_x statement { $$ = create_Node("else_statement", -1, "NULL","NULL", 2, $1, $2); }
 | else_statement EOL { $$ = create_Node("else_statement", -1, "NULL","NULL", 1, $1); }
 ;

if_else_statement: if_statement else_statement { $$ = create_Node("if_else_statement", -1, "NULL","NULL", 2, $1, $2); };

while_statement: while_x LPAREN E RPAREN LBRACE statement_list RBRACE { $$ = create_Node("while_statement", -1, "NULL","NULL", 7, $1, $2, $3, $4, $5, $6, $7); };

for_statement: for_x LPAREN declaration_statement E SEMICOLON E RPAREN LBRACE statement_list RBRACE { $$ = create_Node("for_statement", -1, "NULL","NULL", 9, $1, $2, $3, $4, $5, $6, $7, $8, $9); };


return_statement: return_x E SEMICOLON { $$ = create_Node("return_statement", -1,"NULL","NULL", 2, $1, $2); }
| return_x SEMICOLON { $$ = create_Node("return_statement", -1, "NULL","NULL", 2, $1,$2); };

cout_statement: cout insert_statement SEMICOLON { $$ = create_Node("cout_statement", -1,"NULL","NULL", 2, $1, $2); };

insert_statement: insert E insert_statement { $$ = create_Node("insert_statement", -1,"NULL","NULL", 3, $1, $2, $3); }
| insert string insert_statement { $$ = create_Node("insert_statement", -1, "NULL","NULL", 3, $1, $2, $3); }
| insert E { $$ = create_Node("insert_statement", -1, "NULL","NULL", 2, $1, $2); }
| insert string { $$ = create_Node("insert_statement", -1, "NULL","NULL", 2, $1, $2); }

cin_statement: cin extract_statement SEMICOLON { $$ = create_Node("cin_statement", -1, "NULL","NULL", 3, $1, $2, $3); };

extract_statement: extract identifier extract_statement { $$ = create_Node("extract_statement", -1, "NULL","NULL", 3, $1, $2, $3); }
| extract identifier { $$ = create_Node("extract_statement", -1, "NULL","NULL", 2, $1, $2); } 
;

declaration_statement: datatype id_list SEMICOLON { $2->dtype = $1->dtype;  $$ = create_Node("declaration_statement", -1, "NULL","NULL", 3, $1, $2, $3); };

id_list: id_list COMMA identifier {
	$$ = create_Node("id_list", -1, "NULL","NULL", 3, $1, $2, $3); 
	$3->dtype = $<node>0->dtype;
	$1->dtype = $<node>0->dtype;
	addEntry($3->value_str,$3->dtype,$3->scope);
}
| id_list {$1->dtype = $<node>0->dtype;} COMMA dec_assignment {
	$$ = create_Node("id_list", -1, "NULL","NULL", 3, $1, $3, $4);
	$3->dtype = $<node>0->dtype;
}
| dec_assignment {
	$$ = create_Node("id_list", -1, "NULL","NULL", 1, $1);
	$1->dtype = $<node>0->dtype; 
}
| identifier { 
	$$ = create_Node("id_list", -1, "NULL","NULL", 1, $1);
	$1->dtype = $<node>-1->dtype;
	addEntry($1->value_str,$1->dtype,$1->scope); 
}

dec_assignment: 
	identifier assignmentop E { 
		$$ = create_Node("dec_assignment", -1, "NULL","NULL", 3, $1, $2, $3); 
		$1->value = $3->value;
		$1->dtype = $<node>0->dtype; 
		addEntry($1->value_str,$1->dtype,$1->scope);
	}

assignment_statement:
	identifier assignmentop E  {
		$$ = create_Node("assignment_statement", -1, "NULL","NULL", 3, $1, $2, $3);
		$1->value = $3->value;
		checkid($1);
	}
;

E: identifier assignmentop E  { $$ = create_Node("E", -1,  "NULL","NULL", 3, $1, $2, $3); $1->value = $3->value;  checkid($2); }
|	E comparisionop E { $$ = create_Node("E", -1,  "NULL","NULL", 3, $1, $2, $3); 

		if (strcmp($2->value_str, "<=") == 0) {
			$$->value = $1->value <= $3->value;
		} else if (strcmp($2->value_str, ">=") == 0) {
			$$->value = $1->value >= $3->value;
		} else if (strcmp($2->value_str, "==") == 0) {
			$$->value = $1->value == $3->value;
		} else if (strcmp($2->value_str, "!=") == 0) {
			$$->value = $1->value != $3->value;
		}
		else if (strcmp($2->value_str, "<") == 0) {
			$$->value = $1->value < $3->value;
		}
		else if (strcmp($2->value_str, ">") == 0) {
			$$->value = $1->value > $3->value;
		}
}
|   E PLUS T { $$ = create_Node("E", $1->value+$3->value, "NULL","NULL", 3, $1, $2, $3); }
|   E MINUS T { $$ = create_Node("E", $1->value-$3->value, "NULL","NULL", 3, $1, $2, $3); }
|   T { $$ = create_Node("E", $1->value, "NULL","NULL", 1, $1); }
;

T:
	T MUL F { $$ = create_Node("T", $1->value*$3->value, "NULL","NULL", 3, $1, $2, $3);}
|	T DIV F { $$ = create_Node("T", $1->value/$3->value, "NULL","NULL", 3, $1, $2, $3);}
|	F { $$ = create_Node("T", $1->value, "NULL","NULL", 1, $1); }
;

F:
	number { $$ = create_Node("F", -1, "NULL","NULL", 1, $1); }
| character { $$ = create_Node("F", -1, "NULL","NULL", 1, $1); }
|	LPAREN E RPAREN { $$ = create_Node("F",$2->value, "NULL","NULL", 3, $1, $2, $3); }
|   identifier { 
		$$ = create_Node("F", -1, "NULL","NULL", 1, $1);
		checkid($1);
	}
| unary identifier { $$ = create_Node("F", -1, "NULL","NULL", 2, $1, $2); checkid($2); }
| identifier unary { $$ = create_Node("F", -1, "NULL","NULL", 2, $1, $2); checkid($1); }
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
	extern char *yytext;
	yyin=fp;
	yyparse();
	// yyparse();
	printf("---------------\n");
	// printTree(head,0);
	printf("---------------\n");
	display();
}
