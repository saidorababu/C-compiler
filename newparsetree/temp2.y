%{
	#include "TreeNode.h"
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

	
	TreeNode *head = NULL;
	struct TreeNode *create_Node(char *label, int value, char *value_str, int num_children, ...) {
		struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
		newNode->label = label;
		newNode->value = value;
		newNode->value_str = (char*)malloc(sizeof(char) * strlen(value_str) + 1);
		strcpy(newNode->value_str,value_str);
		newNode->num_children = num_children;
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

		if(root->value ==-1 && strcmp(root->value_str,"NULL") == 0){
			printf("%d.%s\n",level, root->label);
		}else if(root->value == -1){
			printf("%d.%s\n", level,root->value_str);
		}else{
			printf("%d.(%s,%d)\n",level, root->label, root->value);
		}
		// printf("(%s,%d)\n", root->label,root->value);
		for(int i = 0;i<root->num_children;i++){
			printTree(root->children[i],level+1);
		}
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
%type<node> E T F assignment_statement statement_list function_declaration declaration_statement id_list insert_statement extract_statement if_statement else_statement if_else_statement while_statement for_statement return_statement cout_statement cin_statement statement headers parameter_list program
/* rules */
%%

program: headers function_declaration program { printf("program No: %d\n",$$); $$ = create_Node("program", -1, "NULL", 3,$1,$2,$3);head = $$;} 
| statement_list program {$$ = create_Node("program", -1, "NULL", 2,$1,$2); head = $$;}
| EOL program {$$ = create_Node("program", -1, "NULL", 1,$2); head = $$;}
| EOL {$$ = NULL;}
|;


headers: header {printf("headers1\n"); $$ = create_Node("headers", -1, "NULL",1,$1);}
| headers EOL headers {printf("headers\n"); $$ = create_Node("headers", -1,"NULL", 2, $1, $3);}
| EOL headers {printf("headers\n"); $$ = create_Node("headers", -1, "NULL",1, $2);}
| EOL{ $$ = NULL; };

function_declaration: datatype identifier LPAREN parameter_list RPAREN LBRACE statement_list RBRACE statement_list {printf("Function NO: %d\n",$$); $$ = create_Node("function_declaration", -1, "NULL", 9, $1,$2,$3, $4, $5, $6, $7, $8, $9); };

parameter_list: datatype identifier COMMA parameter_list { $$ = create_Node("parameter_list", -1, "NULL",4, $1, $2, $3, $4); }
 | datatype identifier { $$ = create_Node("parameter_list", -1, "NULL",2, $1, $2);}
| EOL {$$ = NULL;}
| { $$ = NULL; };


statement_list: 
	statement statement_list {printf("statement_list\n"); $$ = create_Node("statement_list", -1, "NULL", 2, $1, $2);}
|	EOL statement_list { $$ = create_Node("statement_list", -1, "NULL", 1, $2);}
|	EOL {$$ = NULL;}
|
;

statement: declaration_statement {printf("declaration_statement\n"); $$ = create_Node("declaration_statement", -1, "NULL",0); }
| assignment_statement SEMICOLON {printf("assignment_statement\n"); $$ = create_Node("assignment_statement", -1,"NULL",2, $1, $2);}
| for_statement {printf("for_statement\n"); $$ = create_Node("for_statement", -1, "NULL",1,$1); }
| if_statement {printf("if_statement\n"); $$ = create_Node("if_statement", -1, "NULL",1,$1); }
| if_else_statement {printf("if_else_statement\n"); $$ = create_Node("if_else_statement", -1, "NULL",1,$1); }
| while_statement {printf("while_statement\n"); $$ = create_Node("while_statement", -1, "NULL",1,$1); }
| cout_statement {printf("cout_statement\n"); $$ = create_Node("cout_statement", -1, "NULL",1,$1); }
| cin_statement {printf("cin_statement\n"); $$ = create_Node("cin_statement", -1, "NULL",1,$1); }
| return_statement {printf("return_statement\n"); $$ = create_Node("return_statement", -1, "NULL",1,$1); }
| error SEMICOLON { $$ = create_Node("error", -1, "NULL",0); }
| EOL { $$ = NULL; }
;

if_statement: if_x LPAREN E RPAREN LBRACE statement_list RBRACE { $$ = create_Node("if_statement", -1,"NULL", 7,$1,$2,$3,$4,$5,$6,$7);}
| if_x LPAREN E RPAREN  statement { $$ = create_Node("if_statement", -1,"NULL", 5,$1,$2,$3,$4,$5);}
| if_statement EOL  { $$ = create_Node("if_statement", -1,"NULL", 1,$1);}

else_statement: else_x LBRACE statement_list RBRACE { $$ = create_Node("else_statement", -1, "NULL", 3, $1, $2, $3); }
 | else_x statement { $$ = create_Node("else_statement", -1, "NULL", 2, $1, $2); }
 | else_statement EOL { $$ = create_Node("else_statement", -1, "NULL", 1, $1); }
 ;

if_else_statement: if_statement else_statement { $$ = create_Node("if_else_statement", -1, "NULL", 2, $1, $2); };

while_statement: while_x LPAREN E RPAREN LBRACE statement_list RBRACE { $$ = create_Node("while_statement", -1, "NULL", 7, $1, $2, $3, $4, $5, $6, $7); };

for_statement: for_x LPAREN declaration_statement E SEMICOLON E RPAREN LBRACE statement_list RBRACE { $$ = create_Node("for_statement", -1, "NULL", 9, $1, $2, $3, $4, $5, $6, $7, $8, $9); };

return_statement: return_x E SEMICOLON { $$ = create_Node("return_statement", -1,"NULL", 2, $1, $2); }
| return_x SEMICOLON { $$ = create_Node("return_statement", -1, "NULL", 2, $1,$2); };

cout_statement: cout insert_statement SEMICOLON { $$ = create_Node("cout_statement", -1,"NULL", 2, $1, $2); };

insert_statement: insert E insert_statement { $$ = create_Node("insert_statement", -1,"NULL", 3, $1, $2, $3); }
| insert string insert_statement { $$ = create_Node("insert_statement", -1, "NULL", 3, $1, $2, $3); }
| insert E { $$ = create_Node("insert_statement", -1, "NULL", 2, $1, $2); }
| insert string { $$ = create_Node("insert_statement", -1, "NULL", 2, $1, $2); }

cin_statement: cin extract_statement SEMICOLON { $$ = create_Node("cin_statement", -1, "NULL", 3, $1, $2, $3); };

extract_statement: extract identifier extract_statement { $$ = create_Node("extract_statement", -1, "NULL", 3, $1, $2, $3); }
| extract identifier { $$ = create_Node("extract_statement", -1, "NULL", 2, $1, $2); } 
;

declaration_statement: datatype id_list SEMICOLON { $$ = create_Node("declaration_statement", -1, "NULL", 3, $1, $2, $3); };

id_list: identifier COMMA id_list { $$ = create_Node("id_list", -1, "NULL", 3, $1, $2, $3); }
| assignment_statement COMMA id_list { $$ = create_Node("id_list", -1, "NULL", 3, $1, $2, $3); }
| assignment_statement { $$ = create_Node("id_list", -1, "NULL", 1, $1); }
| identifier { $$ = create_Node("id_list", -1, "NULL", 1, $1); }

assignment_statement:
   F assignmentop E  { printf("assignment-statement\n");$$ = create_Node("assignment_statement", -1, "NULL", 3, $1, $2, $3); $1->value = $3->value; }
;

E: F assignmentop E  { $$ = create_Node("E", -1,  "NULL", 3, $1, $2, $3); $1->value = $3->value; }
|	E comparisionop T { $$ = create_Node("E", -1,  "NULL", 3, $1, $2, $3); 
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
|   E PLUS T { $$ = create_Node("E", $1->value+$3->value, "NULL", 3, $1, $2, $3); }
|   E MINUS T { $$ = create_Node("E", $1->value-$3->value, "NULL", 3, $1, $2, $3); }
|   T { $$ = create_Node("E", $1->value, "NULL", 1, $1); }
;

T:
	T MUL F { $$ = create_Node("T", $1->value*$3->value, "NULL", 3, $1, $2, $3);}
|	T DIV F { $$ = create_Node("T", $1->value/$3->value, "NULL", 3, $1, $2, $3);}
|	F { $$ = create_Node("T", $1->value, "NULL", 1, $1); }
;

F:
	number { $$ = create_Node("F", -1, "NULL" , 1, $1); }
| character { $$ = create_Node("F", -1, "NULL", 1, $1); }
|	LPAREN E RPAREN { $$ = create_Node("F",$2->value, "NULL", 3, $1, $2, $3); }
|   identifier { $$ = create_Node("identifier", -1, "NULL", 1, $1); }
| unary identifier { $$ = create_Node("F", -1, "NULL", 2, $1, $2); }
| identifier unary { $$ = create_Node("F", -1, "NULL", 2, $1, $2); }
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
	printf("---------------\n");
	printTree(head,0);
	printf("---------------\n");
	display();
}
