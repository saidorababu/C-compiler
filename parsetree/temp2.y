%{
	// #include "temp.tab.h"
	// #include "lex.yy.c"
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	// int valid=1;
	int yylex();
	int yyerror(const char *s);
	int yyparse();
	// int yywrap();

	extern int st[100];
	//int top;
	extern int up;
	//extern int count;
	extern void display();
	struct entry{
		char arr[20];
		int scope;
		char dtype[10];
		int value;
	};
	extern struct entry symbolTable[100];

	typedef struct TreeNode{
		char *label;
		int value;
		struct TreeNode *left;
		struct TreeNode *right;
	} TreeNode;
	
	TreeNode *head = NULL;
	extern TreeNode *createNode(char *label, int value, TreeNode *left, TreeNode *right);

	void printTree(TreeNode *root,int level){
		if(root == NULL){
			return;
		}
		for(int i = 0;i<level;i++){
			printf("  ");
		}
		/*if(root->value!=-1){
			printf("%s %d\n", root->label, root->value);
		}else{
			printf("%s\n", root->label);
		}*/
		//printf("%s %d\n", root->label, root->value);
		printf("(%s,%d)\n", root->label,root->value);
		printTree(root->left,level+1);
		printTree(root->right,level+1);
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
%token PLUS MINUS MUL DIV number if_x else_x while_x for_x return_x printf_x main_x assignmentop comparisionop logicalop datatype unary identifier string character cout cin insert extract header

%type<str> comparisionop
%type<node> number
%type<node> E T F header assignment_statement statement_list function_declaration declaration_statement id_list insert_statement extract_statement if_statement else_statement if_else_statement while_statement for_statement return_statement cout_statement cin_statement statement headers identifier string character cout cin insert extract parameter_list program
/* rules */
%%

program: headers function_declaration program { printf("program No: %d\n",$$); $$ = createNode("program", -1, $1, $2);head = $$;} 
| statement_list program {$$ = createNode("program", -1, $1, $2); head = $$;}
| EOL program {$$ = createNode("program", -1, NULL, $2); head = $$;}
| EOL {$$ = NULL;}
|;


headers: header {printf("headers\n"); $$ = createNode("header", -1, $1, NULL);}
| headers EOL headers {printf("headers\n"); $$ = createNode("headers", -1, $1, $3);}
| EOL headers {printf("headers\n"); $$ = createNode("headers", -1, NULL, $2);}
| EOL{ $$ = NULL; };

function_declaration: datatype identifier '(' parameter_list ')' '{' statement_list '}' statement_list {printf("Function NO: %d\n",$$); $$ = createNode("function_declaration", -1, $4, $7);};

parameter_list: datatype identifier ',' parameter_list { $$ = createNode("parameter_list", -1, NULL, $4); }
 | datatype identifier { $$ = createNode("parameter_list", -1, NULL, NULL); }
| EOL {$$ = createNode("parameter_list", -1, NULL, NULL);}
| { $$ = NULL; };


statement_list: 
	statement statement_list {printf("statement_list\n"); $$ = createNode("statement_list", -1, $1, $2); }
|	EOL statement_list { $$ = createNode("statement_list", -1, NULL, $2); }
|	EOL {$$ = NULL;}
|
;

statement: declaration_statement {printf("declaration_statement\n"); $$ = createNode("declaration_statement", -1, $1, NULL); }
| assignment_statement ';' {printf("assignment_statement\n"); $$ = createNode("assignment_statement", -1, $1, NULL); }
| for_statement {printf("for_statement\n"); $$ = createNode("for_statement", -1, $1, NULL); }
| if_statement {printf("if_statement\n"); $$ = createNode("if_statement", -1, $1, NULL); }
| if_else_statement {printf("if_else_statement\n"); $$ = createNode("if_else_statement", -1, $1, NULL); }
| while_statement {printf("while_statement\n"); $$ = createNode("while_statement", -1, $1, NULL); }
| cout_statement {printf("cout_statement\n"); $$ = createNode("cout_statement", -1, $1, NULL); }
| cin_statement {printf("cin_statement\n"); $$ = createNode("cin_statement", -1, $1, NULL); }
| return_statement {printf("return_statement\n"); $$ = createNode("return_statement", -1, $1, NULL); }
| error ';' {printf("error\n"); $$ = createNode("error", -1, NULL, NULL); }
| EOL { $$ = NULL; }
;

if_statement: if_x '(' E ')' '{' statement_list '}' { $$ = createNode("if_statement", -1, $3, $6);}
| if_x '(' E ')'  statement { $$ = createNode("if_statement", -1, $3, $5); }
| if_statement EOL  { $$ = createNode("if_statement", -1, $1, NULL); };

else_statement: else_x '{' statement_list '}' | else_x statement | else_statement EOL;

if_else_statement: if_statement else_statement { $$ = createNode("if_else_statement", -1, $1, $2); };

while_statement: while_x '(' E ')' '{' statement_list '}' { $$ = createNode("while_statement", -1, $3, $6); };

for_statement: for_x '(' declaration_statement E ';' E ')' '{' statement_list '}' { $$ = createNode("for_statement", -1, $3, $9); };

return_statement: return_x E ';' { $$ = createNode("return_statement", -1, $2, NULL); };
| return_x ';' { $$ = createNode("return_statement", -1, NULL, NULL); };

cout_statement: cout insert_statement ';' { $$ = createNode("cout_statement", -1, $2, NULL); };

insert_statement: insert E insert_statement { $$ = createNode("insert_statement", -1, $2, $3); }
| insert string insert_statement { $$ = createNode("insert_statement", -1, NULL, $3); }
| insert E { $$ = createNode("insert_statement", -1, $2, NULL); }
| insert string { $$ = createNode("insert_statement", -1, NULL, NULL); } ;

cin_statement: cin extract_statement ';' { $$ = createNode("cin_statement", -1, $2, NULL); };

extract_statement: extract identifier extract_statement { $$ = createNode("extract_statement", -1, NULL, $3); }
| extract identifier { $$ = createNode("extract_statement", -1, NULL, NULL); };

declaration_statement: datatype id_list ';' { $$ = createNode("declaration_statement", -1, $2, NULL); }; ;

id_list: identifier ',' id_list { $$ = createNode("id_list", -1, NULL, $3); }
| assignment_statement ',' id_list { $$ = createNode("id_list", -1, $1, $3); }
| assignment_statement { $$ = createNode("id_list", -1, $1, NULL); }
| identifier { $$ = createNode("id_list", -1, NULL, NULL); } ;

assignment_statement:
   F assignmentop E  { $$ = createNode("assignment_statement", -1, $1, $3); $1->value = $3->value;}
;

E: F assignmentop E  { $$ = createNode("E", -1, $1, $3); $1->value = $3->value;}
|	E comparisionop T { $$ = createNode("E", -1, $1, $3); 
		if (strcmp($2, "<=") == 0) {
		$$->value = $1->value <= $3->value;
	} else if (strcmp($2, ">=") == 0) {
		$$->value = $1->value >= $3->value;
	} else if (strcmp($2, "==") == 0) {
		$$->value = $1->value == $3->value;
	} else if (strcmp($2, "!=") == 0) {
		$$->value = $1->value != $3->value;
	}
	else if (strcmp($2, "<") == 0) {
		$$->value = $1->value < $3->value;
	}
	else if (strcmp($2, ">") == 0) {
		$$->value = $1->value > $3->value;
	}
}
|   E PLUS T { $$ = createNode("E", $1->value+$3->value, $1, $3);}
|   E MINUS T { $$ = createNode("E", $1->value-$3->value, $1, $3);}
|   T { $$ = createNode("E", $1->value, $1, NULL); }
;

T:
	T MUL F { $$ = createNode("T", $1->value*$3->value, $1, $3); }
|	T DIV F { $$ = createNode("T", $1->value/$3->value, $1, $3);}
|	F { $$ = createNode("T", $1->value, $1, NULL); }
;

F:
	number { $$ = createNode("F", -1, $1, NULL); }
| character { $$ = createNode("F", -1, NULL, NULL); }
|	'(' E ')' { $$ = createNode("F",$2->value, NULL, $2); } 
|   identifier { $$ = createNode("identifier", -1, NULL, NULL); }
| unary identifier { $$ = createNode("F", -1, NULL, NULL); }
| identifier unary { $$ = createNode("F", -1, NULL, NULL); }
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
	printf("--------------------------------------\n");
	printTree(head,0);
	printf("--------------------------------------\n");
	display();
}
