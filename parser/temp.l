%option yylineno
%{
#include "temp.tab.h"
#include<stdio.h>
#include <string.h>
int st[100];
int top;
int count;
int currscope;
int up;
int sc_set;
int set;
int in;
char decl[20];
int flag = 0;
void installID(char *text,int nm,int scp);
void display();
struct entry
{
	char arr[20];
	int scope;
	char dtype[10];
	int value;
};
struct entry symbolTable[100];
%}

/* regular definitions */
delim [ \t] 
ws {delim}+ 
letter [a-zA-Z] 
digit [0-9] 
id {letter}({letter}|{digit})* 
relop (<=|>=|==|!=|<|>) 
logicalop (&&|[|][|])
leftshift (<<) 
rightshi (>>) 
plus [+] 
minus [-] 
mult [*] 
div [/] 
num ({digit}+) 
float ({num}\.{num}) 
arithmeticop ({plus}|{minus}|{mult}|{div}) 
increment {plus}{plus} 
decrement {minus}{minus} 
assignop = 
string (\"(\\.|[^\\"])*\") 
character (\'(\\.|[^\\'])*\')
keyword (if|else|const|while|for|int|float|return|void|main|char|"long long"|double|short|long|unsigned|signed|define|struct|enum|typedef|sizeof|sta c|register|auto|break|case|con nue|default|do|goto|switch|cout|cin|endl|bool|using|namespace|std|include|iostream|vector|map|set|queue|stack|push_back|pop_back|pop|push|top|front|priority_queue) 
inval (({digit}+{id})) 
comment (\/\/.*|\/\*([^*]|(\*+[^*/]))*\*+\/[\n]*)

%%
[\n] {printf("newline\n");return EOL;}
^"#include".+ ;
if { printf("if\n"); return if_x; }
else { printf("else\n"); return else_x; }
while { printf("while\n"); return while_x; }
for {printf("for\n"); return for_x; }
return { printf("return \n"); return return_x; }
printf { printf("printf\n"); return printf_x; }
cout { printf("cout\n"); return cout; }
cin { printf("cin\n"); return cin; }
"<<" { printf("insert\n"); return insert; }
">>" { printf("extract\n"); return extract; }
{assignop} {printf("assignop:%s\n", yytext); return assignmentop; }
{relop} { ; printf("compop:%s\n", yytext); return comparisionop; }
{logicalop} { printf("logicalop:%s\n", yytext); return logicalop; }
int|float|double|char|string|"long long"|short|long { currscope++; printf("datatype:%s\n", yytext); strcpy(decl, yytext); return datatype; }
{num} { printf("num:%s\n", yytext); yylval.num = atoi(yytext); return number; }
{increment} {  ; printf("unary:%s\n", yytext); return unary; }
{decrement} {  ; printf("unary:%s\n", yytext); return unary; }
{id} { installID(yytext, yylineno, st[top]);  printf("id:%s\n", yytext);yylval.str = yytext;return identifier; }
{character} { printf("character:%s\n", yytext); return character; }
{string} { printf("string:%s\n", yytext); return string; }
\n* ;
{ws} ;
{plus} {return PLUS;}
{minus} {return MINUS;}
{mult} {return MUL;}
{div} {return DIV;}

"{" { printf("Lbrace:%s\n",yytext); currscope++; return yytext[0]; }
"}" { currscope--;printf("Rbrace:%s\n",yytext);  return yytext[0]; }
"(" {printf ("LPAREN: %s, line: %d\n", yytext, yylineno);return yytext[0];} 
")" {printf ("RPAREN: %s, line: %d\n", yytext, yylineno);return yytext[0];} 
"[" {printf ("LBRACKET: %s, line: %d\n", yytext, yylineno); return yytext[0];} 
"]" {printf ("RBRACKET: %s, line: %d\n", yytext, yylineno); return yytext[0];}
";" { printf("semicolon :%s,line:%d\n",yytext,yylineno); return yytext[0]; }
{comment} { };
. { return yytext[0]; }
%%

void installID(char *text, int nm, int scp)
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
	if (present == 0)
	{
		strcpy(symbolTable[up].arr, text);
		// symbolTable[up].scope = currscope;
		strcpy(symbolTable[up].dtype, decl);
		// symbolTable[up].value = up;
		up++;
	}
}

void display()
{
	printf("\nSymbol Table\n");
	printf("Symbol\t\tdtype\n");
	for (int i = 0; i < up; i++)
	{
		printf("%s\t\t%s\n", symbolTable[i].arr, symbolTable[i].dtype);
	}
}
int yywrap()
{
	return 1;
}

