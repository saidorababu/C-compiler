%option yylineno
%{
	#include "temp2.tab.h"
	#include<stdio.h>
	#include<stdlib.h>
	#include <string.h>
	#include <stdarg.h>
	#include "TreeNode.h"
	int st[100];
	int top,count,currscope,up,declared = 0;
	char decl[20];
	int flag = 0;
	void installID(char *text);
	void display();
	struct entry
	{
		char arr[20];
		int scope;
		char dtype[10];
		int value;
	};
	struct entry symbolTable[100];

	TreeNode *createNode(char *label, int value, char *value_str,char *dtype,int scope, int num_children, ...) {
		TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
		newNode->label = label;
		newNode->value = value;
		newNode->value_str = (char*)malloc(sizeof(char) * strlen(value_str) + 1);
		strcpy(newNode->value_str,value_str);
		// strcpy(newNode->dtype, );
		if(strcmp(label,"datatype") == 0) newNode->dtype = newNode->value_str;
		else newNode->dtype = "NULL";

		newNode->scope = scope;
		newNode->num_children = num_children;
		newNode->children = NULL;
		if(num_children == 0) return newNode;
		newNode->children = malloc(sizeof(TreeNode*) * num_children);
		
		va_list args;
		va_start(args, num_children);

		for (int i = 0; i < num_children; i++) {
			newNode->children[i] = va_arg(args, TreeNode*);
		}

		va_end(args);

		return newNode;
	}
%}

/* regular definitions */
delim [ \t] 
ws {delim}+ 
letter [a-zA-Z] 
digit [0-9] 
id {letter}({letter}|{digit})* 
comparisionop (<=|>=|==|!=|<|>) 
plus [+] 
minus [-] 
mult [*] 
div [/] 
num ({digit}+)
increment {plus}{plus} 
decrement {minus}{minus} 
assignop = 
string (\"(\\.|[^\\"])*\") 
character (\'(\\.|[^\\'])*\') 
comment (\/\/.*|\/\*([^*]|(\*+[^*/]))*\*+\/[\n]*)

%%
[\n] {}
#include<[^>]+> {printf( "header:%s\n",yytext); yylval.node = createNode("header",-1,yytext,"NULL",0,0); printf("done");  return header;};
#include\"([^\"]+)\" {printf( "header:%s\n",yytext); yylval.node = createNode("header",-1,yytext,"NULL",0,0);  return header;};
if { printf("if\n");  yylval.node = createNode("if",-1,yytext,"NULL",0,0); return if_x; }
else { printf("else\n");  yylval.node = createNode("else",-1,yytext,"NULL",0,0);  return else_x; }
while { printf("while\n"); yylval.node = createNode("while",-1,yytext,"NULL",0,0);   return while_x; }
for {printf("for\n"); yylval.node = createNode("for",-1,yytext,"NULL",0,0);  return for_x; }
return { printf("return \n"); yylval.node = createNode("return",-1,yytext,"NULL",0,0);  return return_x; }
printf { printf("printf\n"); yylval.node = createNode("printf",-1,yytext,"NULL",0,0);  return printf_x; }
cout { printf("cout\n"); yylval.node = createNode("cout",-1,yytext,"NULL",0,0);   return cout; }
cin { printf("cin\n"); yylval.node = createNode("cin",-1,yytext,"NULL",0,0);  return cin; }
"<<" { printf("insert\n");  yylval.node = createNode("<<",-1,yytext,"NULL",0,0);  return insert; }
">>" { printf("extract\n"); yylval.node = createNode(">>",-1,yytext,"NULL",0,0);  return extract; }
{assignop} {printf("assignop:%s\n", yytext); yylval.node = createNode("assignop",-1,yytext,"NULL",0,0);  return assignmentop; }
{comparisionop} { ; printf("compop:%s\n", yytext); strcpy(yylval.str,yytext); yylval.node = createNode("comparisionop",-1,yytext,"NULL",0,0);  return comparisionop; }
&& { ; printf("AND:%s\n", yytext); yylval.node = createNode("AND",-1,yytext,"NULL",0,0);  return AND; }
\|\| { ; printf("OR:%s\n", yytext); yylval.node = createNode("OR",-1,yytext,"NULL",0,0);  return OR; }
! { ; printf("NOT:%s\n", yytext); yylval.node = createNode("NOT",-1,yytext,"NULL",0,0);  return NOT; }
int|float|double|char|string|"long long"|short|long { printf("datatype:%s\n", yytext);declared = 1;yylval.node = createNode("datatype",-1,yytext,yytext,0,0);  return datatype; }
{num} { printf("num:%s\n", yytext); yylval.node = createNode("number",atoi(yytext),yytext,"NULL",0,0); return number; }
{increment} {  ; printf("unary:%s\n", yytext); yylval.node = createNode("unary",-1,yytext,"NULL",0,0);  return unary; }
{decrement} {  ; printf("unary:%s\n", yytext); yylval.node = createNode("unary",-1,yytext,"NULL",0,0);  return unary; }
{id} { if(declared == 1) {installID(yytext);}  printf("id:%s\n", yytext); yylval.node = createNode("id",-1,yytext,"NULL",currscope,0); return identifier; }
{character} { printf("character:%s\n", yytext);  yylval.node = createNode("character",-1,yytext,"NULL",0,0); return character;}
{string} { printf("string:%s\n", yytext); yylval.node = createNode("string",-1,yytext,"NULL",0,0);  return string; }
\n* ;
{ws} ;
{plus} { yylval.node = createNode("plus",-1,yytext,"NULL",0,0); return PLUS;}
{minus} { yylval.node = createNode("minus",-1,yytext,"NULL",0,0); return MINUS;}
{mult} { yylval.node = createNode("mult",-1,yytext,"NULL",0,0); return MUL;}
{div} { yylval.node = createNode("div",-1,yytext,"NULL",0,0); return DIV;}

"{" { printf("Lbrace:%s\n",yytext); currscope++; yylval.node = createNode("{",-1,yytext,"NULL",0,0);  return LBRACE; }
"}" { currscope--;printf("Rbrace:%s\n",yytext); yylval.node = createNode("}",-1,yytext,"NULL",0,0); printf("Rbrace:%s\n",yytext);   return RBRACE; }
"(" {printf ("LPAREN: %s, line: %d\n", yytext, yylineno); currscope++; yylval.node = createNode("LPAREN",-1,yytext,"NULL",0,0); return LPAREN;}
")" {printf ("RPAREN: %s, line: %d\n", yytext, yylineno); currscope--; yylval.node = createNode("RPAREN",-1,yytext,"NULL",0,0); return RPAREN;}
"[" {printf ("LBRACKET: %s, line: %d\n", yytext, yylineno); yylval.node = createNode("[",-1,yytext,"NULL",0,0);  return LBRACKET;}
"]" {printf ("RBRACKET: %s, line: %d\n", yytext, yylineno); yylval.node = createNode("]",-1,yytext,"NULL",0,0);  return RBRACKET;}
";" { declared = 0; printf("semicolon :%s,line:%d\n",yytext,yylineno);  yylval.node = createNode(";",-1,yytext,"NULL",0,0);  return SEMICOLON; }
"," { printf("comma :%s,line:%d\n",yytext,yylineno);  yylval.node = createNode(",",-1,yytext,"NULL",0,0);  return COMMA; }
{comment} { };
. { return yytext[0]; }
%%

void installID(char *text)
{
	int present = 0;
	for (int i = 0; i <= up; i++)
	{
		if (strcmp(symbolTable[i].arr, text) == 0 && symbolTable[i].scope == currscope)
		{
			present = 1;
			break;
		}
	}
	if (!present)
	{
		strcpy(symbolTable[up].arr, text);
		symbolTable[up].scope = currscope;
		strcpy(symbolTable[up].dtype, "null");
		up++;
	}
}

void display()
{
	printf("\n--------------------------Symbol Table-------------------------------\n\n");
	printf("Symbol\t\t\t\tscope\t\t\t\tdtype\n");
	printf("-----------------------------------------------------------------------\n");
	for (int i = 0; i < up; i++)
	{
		printf("%s\t\t|\t\t%d\t\t|\t\t%s\n", symbolTable[i].arr,symbolTable[i].scope, symbolTable[i].dtype);
	}
}
int yywrap()
{
	return 1;
}

