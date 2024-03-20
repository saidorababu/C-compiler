%{ 
    #include <stdio.h> 
    extern int yylex(); 
    extern char *yytext; 
    char *prevtoken; 
    char *tokentobeadded; 
    int idCount = 0; 
    int lineno = 0; 
%}
/* regular defini ons */
delim [ \t] 
ws {delim}+ 
letter [a-zA-Z] 
digit [0-9] 
id {le er}({le er}|{digit})* 
relop (<=|>=|==|!=|<|>) 
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
string (\"(\\.|[^\\"])*\"|\'(\\.|[^\\'])*\') 
keyword (if|else|const|while|for|int|float|return|void|main|char|"long long"|double|short|long|unsigned|signed|define|struct|enum|typedef|sizeof|sta c|register|auto|break|case|con nue|default|do|goto|switch|cout|cin|endl|bool|using|namespace|std|include|iostream|vector|map|set|queue|stack|push_back|pop_back|pop|push|top|front|priority_queue) 
inval (({digit}+{id})) 
%% 
"bits/stdc++.h" {printf ("HEADER: %s\n", yytext);} 
"\n" {lineno++;printf ("\nNEWLINE: %s", yytext);} 
"//".* { /* ignore comments */ } 
"/*".*"*/" { /* ignore comments */ } 
{keyword} { 
    printf ("KEYWORD: %s   line: %d\n", yytext, lineno); 
} 
{id} { 
    prevtoken = "id"; 
    printf ("ID: %s, line: %d\n", yytext, lineno); 
} 
{ws} { /* ignore whitespace */ } 
{leftshift} { 
  printf ("Le Shi : %s, line: %d\n", yytext, lineno); 
} 
{rightshift} { 
  printf ("RightShi : %s, line: %d\n", yytext, lineno); 
} 
{relop} { 
  printf ("RELOP: %s, line: %d\n", yytext, lineno); 
} 
{inval} {printf ("Invalid token: %s\n", yytext);} 
{increment} {printf ("INCREMENT: %s\n", yytext);} 
{decrement} {printf ("DECREMENT: %s\n", yytext);} 
{float} {printf ("FLOAT: %s, line: %d\n", yytext, lineno);} 
{num} { 
  if(tokentobeadded && strcmp(tokentobeadded, "-") == 0) { 
    printf ("Number:-%s, line: %d\n", yytext, lineno); 
    prevtoken = NULL; 
    tokentobeadded = NULL; 
  }else{ 
    printf ("Number: %s, line: %d\n", yytext, lineno); 
  } 
} 
{arithmeticop} { 
  if(strcmp(prevtoken, "assign") == 0 && strcmp(yytext,"-") == 0) { 
    tokentobeadded = "-"; 
  }else{ 
    printf ("ARITHMETICOP: %s, line: %d\n", yytext, lineno); 
  } 
} 
"." {printf("DOT: %s, line: %d\n", yytext, lineno);} 
"#" {printf ("Hash: %s, line: %d\n", yytext, lineno);} 
"(" {printf ("LPAREN: %s, line: %d\n", yytext, lineno);} 
")" {printf ("RPAREN: %s, line: %d\n", yytext, lineno);} 
"[" {printf ("LBRACKET: %s, line: %d\n", yytext, lineno);} 
"]" {printf ("RBRACKET: %s, line: %d\n", yytext, lineno);} 
"{" {printf ("LBRACE: %s, line: %d\n", yytext, lineno);} 
"}" {printf ("RBRACE: %s, line: %d\n", yytext, lineno);} 
"=" {prevtoken = "assign";printf ("ASSIGNOP: %s, line: %d\n", yytext, lineno);} 
";" {printf ("Delimiter: %s, line: %d\n", yytext, lineno);} 
"," {printf ("COMMA: %s, line: %d\n", yytext, lineno);} 
{string} {printf ("string: %s, line: %d\n", yytext, lineno);} 
. {printf ("Invalid token: %s, line: %d\n", yytext, lineno);} 
%% 

int yywrap(){ return 1; } 
