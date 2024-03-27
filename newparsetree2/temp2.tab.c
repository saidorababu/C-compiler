
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "temp2.y"

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
				if(strcmp(symbolTable[i].dtype,dtype) == 0){
					printf("Variable %s is already declared\n",name); 
					yyerror("Variable already declared");
					return;
				}
				strcpy(symbolTable[i].dtype,dtype);
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


/* Line 189 of yacc.c  */
#line 197 "temp2.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EOL = 258,
     PLUS = 259,
     MINUS = 260,
     MUL = 261,
     DIV = 262,
     number = 263,
     if_x = 264,
     else_x = 265,
     while_x = 266,
     for_x = 267,
     return_x = 268,
     printf_x = 269,
     main_x = 270,
     assignmentop = 271,
     comparisionop = 272,
     logicalop = 273,
     datatype = 274,
     unary = 275,
     identifier = 276,
     string = 277,
     character = 278,
     cout = 279,
     cin = 280,
     insert = 281,
     extract = 282,
     header = 283,
     LBRACE = 284,
     RBRACE = 285,
     LPAREN = 286,
     RPAREN = 287,
     SEMICOLON = 288,
     COMMA = 289
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 124 "temp2.y"

    int num;
    char *str;
	struct TreeNode *node;



/* Line 214 of yacc.c  */
#line 275 "temp2.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 287 "temp2.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  49
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   265

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNRULES -- Number of states.  */
#define YYNSTATES  139

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     7,    10,    13,    15,    16,    18,    22,
      25,    27,    37,    42,    45,    47,    48,    51,    54,    56,
      57,    59,    62,    64,    66,    68,    70,    72,    74,    76,
      79,    81,    89,    95,    98,   103,   106,   109,   112,   120,
     131,   135,   138,   142,   146,   150,   153,   156,   160,   164,
     167,   171,   175,   176,   181,   183,   185,   189,   193,   197,
     201,   205,   209,   211,   215,   219,   221,   223,   225,   229,
     231,   234
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    37,    38,    36,    -1,    40,    36,    -1,
       3,    36,    -1,     3,    -1,    -1,    28,    -1,    37,     3,
      37,    -1,     3,    37,    -1,     3,    -1,    19,    21,    31,
      39,    32,    29,    40,    30,    40,    -1,    19,    21,    34,
      39,    -1,    19,    21,    -1,     3,    -1,    -1,    41,    40,
      -1,     3,    40,    -1,     3,    -1,    -1,    52,    -1,    56,
      33,    -1,    46,    -1,    42,    -1,    44,    -1,    45,    -1,
      48,    -1,    50,    -1,    47,    -1,     1,    33,    -1,     3,
      -1,     9,    31,    57,    32,    29,    40,    30,    -1,     9,
      31,    57,    32,    41,    -1,    42,     3,    -1,    10,    29,
      40,    30,    -1,    10,    41,    -1,    43,     3,    -1,    42,
      43,    -1,    11,    31,    57,    32,    29,    40,    30,    -1,
      12,    31,    52,    57,    33,    57,    32,    29,    40,    30,
      -1,    13,    57,    33,    -1,    13,    33,    -1,    24,    49,
      33,    -1,    26,    57,    49,    -1,    26,    22,    49,    -1,
      26,    57,    -1,    26,    22,    -1,    25,    51,    33,    -1,
      27,    21,    51,    -1,    27,    21,    -1,    19,    53,    33,
      -1,    53,    34,    21,    -1,    -1,    53,    54,    34,    55,
      -1,    55,    -1,    21,    -1,    21,    16,    57,    -1,    21,
      16,    57,    -1,    21,    16,    57,    -1,    57,    17,    57,
      -1,    57,     4,    58,    -1,    57,     5,    58,    -1,    58,
      -1,    58,     6,    59,    -1,    58,     7,    59,    -1,    59,
      -1,     8,    -1,    23,    -1,    31,    57,    32,    -1,    21,
      -1,    20,    21,    -1,    21,    20,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   138,   138,   139,   140,   141,   142,   144,   145,   146,
     147,   149,   151,   152,   153,   154,   158,   159,   160,   161,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   177,   178,   179,   182,   183,   184,   187,   189,   191,
     194,   195,   197,   199,   200,   201,   202,   204,   206,   207,
     210,   212,   218,   218,   222,   226,   233,   241,   248,   249,
     267,   268,   269,   273,   274,   275,   279,   280,   281,   282,
     286,   287
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EOL", "PLUS", "MINUS", "MUL", "DIV",
  "number", "if_x", "else_x", "while_x", "for_x", "return_x", "printf_x",
  "main_x", "assignmentop", "comparisionop", "logicalop", "datatype",
  "unary", "identifier", "string", "character", "cout", "cin", "insert",
  "extract", "header", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "SEMICOLON",
  "COMMA", "$accept", "program", "headers", "function_declaration",
  "parameter_list", "statement_list", "statement", "if_statement",
  "else_statement", "if_else_statement", "while_statement",
  "for_statement", "return_statement", "cout_statement",
  "insert_statement", "cin_statement", "extract_statement",
  "declaration_statement", "id_list", "$@1", "dec_assignment",
  "assignment_statement", "E", "T", "F", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    36,    36,    36,    36,    37,    37,    37,
      37,    38,    39,    39,    39,    39,    40,    40,    40,    40,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    42,    42,    42,    43,    43,    43,    44,    45,    46,
      47,    47,    48,    49,    49,    49,    49,    50,    51,    51,
      52,    53,    54,    53,    53,    53,    55,    56,    57,    57,
      57,    57,    57,    58,    58,    58,    59,    59,    59,    59,
      59,    59
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     1,     0,     1,     3,     2,
       1,     9,     4,     2,     1,     0,     2,     2,     1,     0,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     7,     5,     2,     4,     2,     2,     2,     7,    10,
       3,     2,     3,     3,     3,     2,     2,     3,     3,     2,
       3,     3,     0,     4,     1,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     1,     1,     3,     1,
       2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     0,     0,     0,     0,    23,    24,    25,    22,
      28,    26,    27,    20,     0,    29,     4,     0,     0,     0,
       0,     0,    66,     0,    69,    67,     0,    41,     0,    62,
      65,    55,     0,    54,     0,     0,     0,     0,     0,     1,
       0,     0,     0,     3,     0,    16,    33,     0,    37,    21,
       0,     0,     0,    70,     0,    71,     0,     0,     0,     0,
      40,     0,     0,     0,    50,     0,     0,    57,    46,    45,
      42,    49,    47,    10,     8,     0,     2,    17,    30,     0,
      35,    36,     0,     0,     0,    58,    68,    69,    60,    61,
      59,    63,    64,    56,    51,     0,    44,    43,    48,     9,
      15,     0,     0,    32,     0,     0,     0,    53,    14,     0,
       0,    34,     0,     0,     0,    13,     0,    31,    38,     0,
      15,     0,     0,    12,     0,     0,     0,    39,    11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    53,    13,    52,   120,    14,    15,    16,    58,    17,
      18,    19,    20,    21,    46,    22,    48,    23,    42,    76,
      43,    24,    38,    39,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -53
static const yytype_int16 yypact[] =
{
     132,   -26,   158,   -21,   -15,   -12,   168,     1,    31,    25,
      26,   -53,    55,     5,   132,    20,    59,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,    28,   -53,   -53,     5,   132,    52,
      52,    40,   -53,    46,    14,   -53,    52,   -53,    10,    57,
     -53,    81,    47,   -53,    52,   194,    38,    78,    70,   -53,
       8,    84,   132,   -53,    65,   -53,   -53,   210,   106,   -53,
      53,    96,    52,   -53,    52,   -53,   122,    71,    71,    52,
     -53,    71,    71,    52,   -53,    90,    97,   119,    25,   239,
     -53,    26,   -53,     8,   112,   109,   -53,   -53,   -53,    95,
     -53,   -53,   229,   113,    21,   119,   -53,   128,    57,    57,
     119,   -53,   -53,   119,   -53,   131,   -53,   -53,   -53,   112,
       9,   125,    95,   -53,    95,    52,    81,   -53,   -53,   141,
     117,   -53,   134,   136,   133,   129,   139,   -53,   -53,   143,
       9,    95,    95,   -53,   144,   145,   184,   -53,   -53
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -53,     4,    -1,   -53,    43,    -2,   -52,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,    39,   -53,    99,   147,   -53,   -53,
      76,   -53,   -27,    54,    75
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -20
static const yytype_int16 yytable[] =
{
      28,    27,    60,    61,    12,    90,    26,    25,    50,    66,
      29,    83,   118,    55,    67,    68,    30,    77,    79,    31,
     -19,     1,    41,    54,    51,    67,    68,    69,   119,     3,
      64,     4,     5,     6,    65,    94,    11,    95,    69,     7,
     113,     8,   100,    70,     9,    10,   103,    44,   -19,    84,
     -19,    45,    87,    47,   115,    49,    86,    67,    68,     7,
      32,    59,    56,    71,    72,   -18,     1,    63,    54,    57,
      69,    80,    33,    34,     3,    35,     4,     5,     6,    32,
      74,    75,   109,    36,     7,    92,     8,   111,   124,     9,
      10,    33,    97,   -18,    35,   -18,     1,    73,    54,    81,
      67,    68,    36,    82,     3,    85,     4,     5,     6,    91,
     122,   104,   123,    69,     7,    50,     8,   106,   107,     9,
      10,    98,    99,    67,    68,   -19,    67,    68,    93,   134,
     135,   105,    -6,     1,   138,     2,    69,    67,    68,    69,
     110,     3,   114,     4,     5,     6,   101,   102,    65,   126,
      69,     7,   116,     8,    96,   121,     9,    10,    -5,     1,
      11,     2,   125,   130,   127,   129,   128,     3,   131,     4,
       5,     6,   132,   133,   136,   137,    32,     7,    62,     8,
     108,   117,     9,    10,   -19,     1,    11,    54,    33,    34,
       0,    35,     0,     3,     0,     4,     5,     6,     0,    36,
       0,    37,    32,     7,     0,     8,     0,     0,     9,    10,
       0,     1,   -19,    88,    33,    34,    78,    35,     0,     3,
       0,     4,     5,     6,     0,    36,     0,     0,     0,     7,
       1,     8,    88,     0,     9,    10,     0,     0,     3,    89,
       4,     5,     6,    67,    68,     0,     0,     0,     7,     0,
       8,     0,     0,     9,    10,     0,    69,     0,   112,     0,
       0,     0,     0,     0,     0,    45
};

static const yytype_int16 yycheck[] =
{
       2,     2,    29,    30,     0,    57,     2,    33,     3,    36,
      31,     3,     3,    15,     4,     5,    31,    44,    45,    31,
       0,     1,    21,     3,    19,     4,     5,    17,    19,     9,
      16,    11,    12,    13,    20,    62,    28,    64,    17,    19,
      92,    21,    69,    33,    24,    25,    73,    16,    28,    50,
      30,    26,    54,    27,    33,     0,    52,     4,     5,    19,
       8,    33,     3,     6,     7,     0,     1,    21,     3,    10,
      17,    33,    20,    21,     9,    23,    11,    12,    13,     8,
      33,    34,    83,    31,    19,    32,    21,    89,   115,    24,
      25,    20,    21,    28,    23,    30,     1,    16,     3,    21,
       4,     5,    31,    33,     9,    21,    11,    12,    13,     3,
     112,    21,   114,    17,    19,     3,    21,    78,    79,    24,
      25,    67,    68,     4,     5,    30,     4,     5,    32,   131,
     132,    34,     0,     1,   136,     3,    17,     4,     5,    17,
      31,     9,    29,    11,    12,    13,    71,    72,    20,    32,
      17,    19,    21,    21,    32,    30,    24,    25,     0,     1,
      28,     3,    21,    34,    30,    32,    30,     9,    29,    11,
      12,    13,    29,   130,    30,    30,     8,    19,    31,    21,
      81,   105,    24,    25,     0,     1,    28,     3,    20,    21,
      -1,    23,    -1,     9,    -1,    11,    12,    13,    -1,    31,
      -1,    33,     8,    19,    -1,    21,    -1,    -1,    24,    25,
      -1,     1,    28,     3,    20,    21,    22,    23,    -1,     9,
      -1,    11,    12,    13,    -1,    31,    -1,    -1,    -1,    19,
       1,    21,     3,    -1,    24,    25,    -1,    -1,     9,    29,
      11,    12,    13,     4,     5,    -1,    -1,    -1,    19,    -1,
      21,    -1,    -1,    24,    25,    -1,    17,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    26
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     9,    11,    12,    13,    19,    21,    24,
      25,    28,    36,    37,    40,    41,    42,    44,    45,    46,
      47,    48,    50,    52,    56,    33,    36,    37,    40,    31,
      31,    31,     8,    20,    21,    23,    31,    33,    57,    58,
      59,    21,    53,    55,    16,    26,    49,    27,    51,     0,
       3,    19,    38,    36,     3,    40,     3,    10,    43,    33,
      57,    57,    52,    21,    16,    20,    57,     4,     5,    17,
      33,     6,     7,    16,    33,    34,    54,    57,    22,    57,
      33,    21,    33,     3,    37,    21,    36,    40,     3,    29,
      41,     3,    32,    32,    57,    57,    32,    21,    58,    58,
      57,    59,    59,    57,    21,    34,    49,    49,    51,    37,
      31,    40,    29,    41,    29,    33,    21,    55,     3,    19,
      39,    30,    40,    40,    57,    21,    32,    30,    30,    32,
      34,    29,    29,    39,    40,    40,    30,    30,    40
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 138 "temp2.y"
    { printf("program No: %d\n",(yyval.node)); (yyval.node) = create_Node("program", -1, "NULL","NULL", 3,(yyvsp[(1) - (3)].node),(yyvsp[(2) - (3)].node),(yyvsp[(3) - (3)].node));if(!head) head = (yyval.node);;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 139 "temp2.y"
    {(yyval.node) = create_Node("program", -1, "NULL","NULL", 2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); head = (yyval.node);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 140 "temp2.y"
    {(yyval.node) = create_Node("program", -1, "NULL","NULL", 1,(yyvsp[(2) - (2)].node)); head = (yyval.node);;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 141 "temp2.y"
    {(yyval.node) = NULL;;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 144 "temp2.y"
    {(yyval.node) = create_Node("headers", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node));;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 145 "temp2.y"
    { (yyval.node) = create_Node("headers", -1,"NULL","NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 146 "temp2.y"
    { (yyval.node) = create_Node("headers", -1, "NULL","NULL",1, (yyvsp[(2) - (2)].node));;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 147 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 149 "temp2.y"
    {printf("Function NO: %d\n",(yyval.node)); (yyvsp[(2) - (9)].node)->dtype = (yyvsp[(1) - (9)].node)->value_str; (yyval.node) = create_Node("function_declaration", -1, "NULL","NULL", 9, (yyvsp[(1) - (9)].node),(yyvsp[(2) - (9)].node),(yyvsp[(3) - (9)].node), (yyvsp[(4) - (9)].node), (yyvsp[(5) - (9)].node), (yyvsp[(6) - (9)].node), (yyvsp[(7) - (9)].node), (yyvsp[(8) - (9)].node), (yyvsp[(9) - (9)].node)); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 151 "temp2.y"
    { (yyval.node) = create_Node("parameter_list", -1, "NULL","NULL",4, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node)); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 152 "temp2.y"
    { (yyval.node) = create_Node("parameter_list", -1, "NULL","NULL",2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 153 "temp2.y"
    {(yyval.node) = NULL;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 154 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 158 "temp2.y"
    { (yyval.node) = create_Node("statement_list", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 159 "temp2.y"
    { (yyval.node) = create_Node("statement_list", -1, "NULL","NULL", 1, (yyvsp[(2) - (2)].node));;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 160 "temp2.y"
    {(yyval.node) = NULL;;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 165 "temp2.y"
    { (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 166 "temp2.y"
    {printf("assignment_statement\n"); (yyval.node) = create_Node("statement", -1,"NULL","NULL",2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 167 "temp2.y"
    {printf("for_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 168 "temp2.y"
    {printf("if_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 169 "temp2.y"
    {printf("if_else_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 170 "temp2.y"
    {printf("while_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 171 "temp2.y"
    {printf("cout_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 172 "temp2.y"
    {printf("cin_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 173 "temp2.y"
    {printf("return_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 174 "temp2.y"
    { (yyval.node) = create_Node("error", -1, "NULL","NULL",0); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 175 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 177 "temp2.y"
    { (yyval.node) = create_Node("if_statement", -1,"NULL","NULL", 7,(yyvsp[(1) - (7)].node),(yyvsp[(2) - (7)].node),(yyvsp[(3) - (7)].node),(yyvsp[(4) - (7)].node),(yyvsp[(5) - (7)].node),(yyvsp[(6) - (7)].node),(yyvsp[(7) - (7)].node));;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 178 "temp2.y"
    { (yyval.node) = create_Node("if_statement", -1,"NULL","NULL", 5,(yyvsp[(1) - (5)].node),(yyvsp[(2) - (5)].node),(yyvsp[(3) - (5)].node),(yyvsp[(4) - (5)].node),(yyvsp[(5) - (5)].node));;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 179 "temp2.y"
    { (yyval.node) = create_Node("if_statement", -1,"NULL","NULL", 1,(yyvsp[(1) - (2)].node));;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 182 "temp2.y"
    { (yyval.node) = create_Node("else_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 183 "temp2.y"
    { (yyval.node) = create_Node("else_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 184 "temp2.y"
    { (yyval.node) = create_Node("else_statement", -1, "NULL","NULL", 1, (yyvsp[(1) - (2)].node)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 187 "temp2.y"
    { (yyval.node) = create_Node("if_else_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 189 "temp2.y"
    { (yyval.node) = create_Node("while_statement", -1, "NULL","NULL", 7, (yyvsp[(1) - (7)].node), (yyvsp[(2) - (7)].node), (yyvsp[(3) - (7)].node), (yyvsp[(4) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(6) - (7)].node), (yyvsp[(7) - (7)].node)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 191 "temp2.y"
    { (yyval.node) = create_Node("for_statement", -1, "NULL","NULL", 9, (yyvsp[(1) - (10)].node), (yyvsp[(2) - (10)].node), (yyvsp[(3) - (10)].node), (yyvsp[(4) - (10)].node), (yyvsp[(5) - (10)].node), (yyvsp[(6) - (10)].node), (yyvsp[(7) - (10)].node), (yyvsp[(8) - (10)].node), (yyvsp[(9) - (10)].node)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 194 "temp2.y"
    { (yyval.node) = create_Node("return_statement", -1,"NULL","NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 195 "temp2.y"
    { (yyval.node) = create_Node("return_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 197 "temp2.y"
    { (yyval.node) = create_Node("cout_statement", -1,"NULL","NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 199 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1,"NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 200 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 201 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 202 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 204 "temp2.y"
    { (yyval.node) = create_Node("cin_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 206 "temp2.y"
    { (yyval.node) = create_Node("extract_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 207 "temp2.y"
    { (yyval.node) = create_Node("extract_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 210 "temp2.y"
    { (yyvsp[(2) - (3)].node)->dtype = (yyvsp[(1) - (3)].node)->dtype;  (yyval.node) = create_Node("declaration_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 212 "temp2.y"
    {
	(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); 
	(yyvsp[(3) - (3)].node)->dtype = (yyvsp[(0) - (3)].node)->dtype;
	(yyvsp[(1) - (3)].node)->dtype = (yyvsp[(0) - (3)].node)->dtype;
	addEntry((yyvsp[(3) - (3)].node)->value_str,(yyvsp[(3) - (3)].node)->dtype,(yyvsp[(3) - (3)].node)->scope);
;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 218 "temp2.y"
    {(yyvsp[(1) - (1)].node)->dtype = (yyvsp[(0) - (1)].node)->dtype;;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 218 "temp2.y"
    {
	(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 3, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
	(yyvsp[(3) - (4)].node)->dtype = (yyvsp[(0) - (4)].node)->dtype;
;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 222 "temp2.y"
    {
	(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));
	(yyvsp[(1) - (1)].node)->dtype = (yyvsp[(0) - (1)].node)->dtype; 
;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 226 "temp2.y"
    { 
	(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));
	(yyvsp[(1) - (1)].node)->dtype = (yyvsp[(-1) - (1)].node)->dtype;
	addEntry((yyvsp[(1) - (1)].node)->value_str,(yyvsp[(1) - (1)].node)->dtype,(yyvsp[(1) - (1)].node)->scope); 
;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 233 "temp2.y"
    { 
		(yyval.node) = create_Node("dec_assignment", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); 
		(yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value;
		(yyvsp[(1) - (3)].node)->dtype = (yyvsp[(0) - (3)].node)->dtype; 
		addEntry((yyvsp[(1) - (3)].node)->value_str,(yyvsp[(1) - (3)].node)->dtype,(yyvsp[(1) - (3)].node)->scope);
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 241 "temp2.y"
    {
		(yyval.node) = create_Node("assignment_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));
		(yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value;
		checkid((yyvsp[(1) - (3)].node));
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 248 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); (yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value;  checkid((yyvsp[(2) - (3)].node)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 249 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); 

		if (strcmp((yyvsp[(2) - (3)].node)->value_str, "<=") == 0) {
			(yyval.node)->value = (yyvsp[(1) - (3)].node)->value <= (yyvsp[(3) - (3)].node)->value;
		} else if (strcmp((yyvsp[(2) - (3)].node)->value_str, ">=") == 0) {
			(yyval.node)->value = (yyvsp[(1) - (3)].node)->value >= (yyvsp[(3) - (3)].node)->value;
		} else if (strcmp((yyvsp[(2) - (3)].node)->value_str, "==") == 0) {
			(yyval.node)->value = (yyvsp[(1) - (3)].node)->value == (yyvsp[(3) - (3)].node)->value;
		} else if (strcmp((yyvsp[(2) - (3)].node)->value_str, "!=") == 0) {
			(yyval.node)->value = (yyvsp[(1) - (3)].node)->value != (yyvsp[(3) - (3)].node)->value;
		}
		else if (strcmp((yyvsp[(2) - (3)].node)->value_str, "<") == 0) {
			(yyval.node)->value = (yyvsp[(1) - (3)].node)->value < (yyvsp[(3) - (3)].node)->value;
		}
		else if (strcmp((yyvsp[(2) - (3)].node)->value_str, ">") == 0) {
			(yyval.node)->value = (yyvsp[(1) - (3)].node)->value > (yyvsp[(3) - (3)].node)->value;
		}
;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 267 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (3)].node)->value+(yyvsp[(3) - (3)].node)->value, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 268 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (3)].node)->value-(yyvsp[(3) - (3)].node)->value, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 269 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (1)].node)->value, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 273 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (3)].node)->value*(yyvsp[(3) - (3)].node)->value, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 274 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (3)].node)->value/(yyvsp[(3) - (3)].node)->value, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 275 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (1)].node)->value, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 279 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 280 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 281 "temp2.y"
    { (yyval.node) = create_Node("F",(yyvsp[(2) - (3)].node)->value, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 282 "temp2.y"
    { 
		(yyval.node) = create_Node("F", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));
		checkid((yyvsp[(1) - (1)].node));
	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 286 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); checkid((yyvsp[(2) - (2)].node)); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 287 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); checkid((yyvsp[(1) - (2)].node)); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2146 "temp2.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 290 "temp2.y"

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

