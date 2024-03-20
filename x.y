%{
    /definitions/
%}

%union {
    int num;
    char sym;
}

%token EOL
%token<num> NUMBER
%type<num> exp
%token PLUS


/* rules */
%%

input:
|   line input
;

line: 
    exp EOL
|   EOL
;

exp: 
    NUMBER { $$ = $1; printf("this is a number\n");}
|   exp PLUS exp { $$ = $1 + $3; printf("this is an expression whose value is %d\n",$$);}
;

%%

int main(){
    yyparse();

    return 0;
}
int yyerror(char *s){
    printf("error %s",s);
    return 0;
}