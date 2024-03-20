%{
	#include "temp.tab.h"
	// #include "lex.yy.c"
	#include<stdio.h>
	int valid=1;
	int yylex();
	int yyerror(const char *s);
	int yyparse();
	// int yywrap();

	extern int st[100];
	int top;
	extern int up;
	extern int count;
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

	TreeNode *createNode(char *label, int value, TreeNode *left, TreeNode *right){
		TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
		newNode->label = label;
		newNode->value = value;
		newNode->left = left;
		newNode->right = right;
		return newNode;
	}

	void printTree(TreeNode *root,int level){
		if(root == NULL){
			return;
		}
		for(int i = 0;i<level;i++){
			printf(" ");
		}
		if(root->value!=-1){
			printf("%s %d\n", root->label, root->value);
		}else{
			printf("%s\n", root->label);
		}
		printf("%s %d\n", root->label, root->value);
		printTree(root->left,level+1);
		printTree(root->right,level+1);
	}
%}

%union {
    int num;
    char *str;
}

%start program
%token EOL
%error-verbose
%token <num> number
%type <num> E T F assignment_statement
%token PLUS MINUS MUL DIV if_x else_x while_x for_x return_x printf_x main_x assignmentop comparisionop logicalop datatype unary identifier string character cout cin insert extract

/* rules */
%%

program: function_declaration program | statement_list program | EOL program | EOL |;

function_declaration: datatype identifier '(' parameter_list ')' '{' statement_list '}' statement_list;

parameter_list: datatype identifier ',' parameter_list | datatype identifier | EOL | ;


statement_list: 
	statement statement_list //{$$ = createNode("declaration", -1, $1, NULL);}
|	EOL statement_list
|	EOL
|
;

statement: declaration_statement 
| assignment_statement ';'
| for_statement 
| if_statement 
| if_else_statement 
| while_statement 
| cout_statement 
| cin_statement 
| return_statement 
;

if_statement: if_x '(' E ')' '{' statement_list '}' | if_x '(' E ')'  statement | if_statement EOL  {printf("if statement\n");};
else_statement: else_x '{' statement_list '}' | else_x statement | else_statement EOL;
if_else_statement: if_statement else_statement;

while_statement: while_x '(' E ')' '{' statement_list '}'

for_statement: for_x '(' declaration_statement E ';' E ')' '{' statement_list '}'

return_statement: return_x E ';' | return_x ';'

cout_statement: cout insert_statement ';'

insert_statement: insert E insert_statement 
| insert string insert_statement 
| insert E | insert string ;

cin_statement: cin extract_statement ';'

extract_statement: extract identifier extract_statement | extract identifier ;

declaration_statement: datatype id_list ';' ;

id_list: identifier ',' id_list 
| assignment_statement ',' id_list 
| assignment_statement 
| identifier ;

assignment_statement:
   E assignmentop E  //{$$ = createNode("assignment", -1, $1, $3);}
;
E: E assignmentop E  //{  $$ = createNode("assignment", -1, $1, $3);
|	E comparisionop T  //{$$ = createNode("comparision", -1, $1, $3);}
|   E PLUS T //{$$ = createNode('+',-1,$1,$3);} //{ $$ = $1 + $3; printf("this is an expression whose value is %d\n",$$);}
|   E MINUS T //{$$ = createNode('-',-1,$1,$3);}//{ $$ = $1 - $3; printf("this is an expression whose value is %d\n",$$);}
|   T {$$ = $1;}
;

T:
	T MUL F //{$$ = createNode('*',-1,$1,$3);}//{ $$ = $1 * $3; printf("this is an expression whose value is %d\n",$$);}
|	T DIV F //{$$ = createNode('/',-1,$1,$3);}//{ $$ = $1 / $3; printf("this is an expression whose value is %d\n",$$);}
|	F { $$ = $1;}
;

F:
	number | character
|	'(' E ')'  //{ $$ = $2; printf("this is an expression whose value is %d\n",$$);}
|   identifier | unary identifier | identifier unary
;


%%
#include <ctype.h>
int yyerror(const char *s)
{
  	extern int yylineno;
  	valid = 0;
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
	// while(yyparse()){
	// 	int token = yylex();
	// 	if(token == 0 || token == -1){
	// 		break;
	// 	}
	// } ;// Loop until parsing succeeds
		// printf("%d ",yyparse());
        // while (yylex() != 0) { // Consume tokens until a semicolon is found
        //     if (yytext[0] == ';') {
        //         break; // Found a semicolon, break out of the loop
        //     }
        // }
    
	printf("---------------\n");
	//printTree($1,0);
	display();
}
