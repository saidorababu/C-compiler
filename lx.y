%{
    /* definitions */
    #include "parser.tab.h"
%}

/* rules */
%%

[0-9]+ { yylval.num=atoi(yytext);  return NUMBER;}
"+" { return PLUS; }
\n { return EOL;}
. {}

%%

yywrap(){}