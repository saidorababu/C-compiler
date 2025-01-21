
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PLUS = 258,
     MINUS = 259,
     MUL = 260,
     DIV = 261,
     number = 262,
     swap = 263,
     size = 264,
     using = 265,
     namespace = 266,
     std = 267,
     vector = 268,
     AND = 269,
     OR = 270,
     NOT = 271,
     if_x = 272,
     else_x = 273,
     while_x = 274,
     for_x = 275,
     return_x = 276,
     printf_x = 277,
     main_x = 278,
     assignmentop = 279,
     comparisionop = 280,
     logicalop = 281,
     datatype = 282,
     unary = 283,
     identifier = 284,
     string = 285,
     character = 286,
     cout = 287,
     cin = 288,
     insert = 289,
     extract = 290,
     header = 291,
     LBRACE = 292,
     RBRACE = 293,
     LPAREN = 294,
     RPAREN = 295,
     LBRACKET = 296,
     RBRACKET = 297,
     SEMICOLON = 298,
     COMMA = 299
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 509 "temp2.y"

    int num;
    char *str;
	struct TreeNode *node;



/* Line 1676 of yacc.c  */
#line 104 "temp2.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


