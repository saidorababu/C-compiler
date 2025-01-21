
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

	typedef struct threeAddrCode{
		int index;
		int blockNo;
		char *result;
		char* operation;
		char* op1;
		char* op2;
	} threeAddrCode;


	threeAddrCode* createCode(char* result, char* operation, char* op1, char* op2){
		threeAddrCode* code = (threeAddrCode*)malloc(sizeof(threeAddrCode));
		code->result = (char*)malloc(strlen(result)+1);
		strcpy(code->result, result);
		code->operation = (char*)malloc(strlen(operation)+1);
		strcpy(code->operation, operation);
		code->op1 = (char*)malloc(strlen(op1)+1);
		strcpy(code->op1, op1);
		code->op2 = (char*)malloc(strlen(op2)+1);
		strcpy(code->op2, op2);
		return code;
	}

	void printCode(threeAddrCode* code){
		printf("%s = %s %s %s\n", code->result, code->op1, code->operation, code->op2);
	}

	List* newList(int i){
		List* list = (List*)malloc(sizeof(List));
		list->curr = i;
		list->next = NULL;
		return list;
	}

	List* mergeList(List* list1, List* list2){
		if(list1 == NULL) return list2;
		if(list2 == NULL) return list1;
		struct List *newList = (struct List*)malloc(sizeof(struct List));
		newList->curr = list1->curr;
		newList->next = mergeList(list1->next, list2);
		return newList;
	}
	int tempVarNo = 1;
	struct threeAddrCode* icg[1000];
	int icgIndex = 0;
	void generateCode(char* operation, char* op1, char* op2, char* result){
		icg[icgIndex++] = createCode(result, operation, op1, op2);
	}
	char* new_label(){
		char* label = (char*)malloc(10);
		sprintf(label, "L%d", tempVarNo++);
		return label;
	}
	char* new_temp(){
		char* temp = (char*)malloc(10);
		sprintf(temp, "t%d", tempVarNo++);
		return temp;
	}
	void backpatch(List* list, int label){
		// printf("backpatching %d\n",label);
		List* temp = list;
		while(temp != NULL){
			char* index = (char*)malloc(10);
			sprintf(index, "L%d", label);
			icg[temp->curr]->result = (char*)malloc(10);
			printf("backpatching %d\n",temp->curr);
			strcpy(icg[temp->curr]->result, index);
			temp = temp->next;
		}
	}
	void displayICG(){
		printf("Intermediate Code Generation\n");
		for(int i = 0; i < icgIndex; i++){
			icg[i]->index = i;
			if(icg[i]->operation[0] == 'g'){
				printf("%2d %s %s\n", i, icg[i]->operation, icg[i]->result);
			}else if(icg[i]->operation[0] == '='){
				printf("%2d %s = %s\n", i, icg[i]->result, icg[i]->op1);
			}else if( icg[i]->operation[0] == 'i'){
				printf("%2d %s %s %s %s\n", i, icg[i]->operation, icg[i]->op1,icg[i]->op2, icg[i]->result);
			}else if(icg[i]->operation[0] == 'p'){
				printf("%2d %s %s \n", i, icg[i]->operation, icg[i]->op1);
			}else if(icg[i]->operation[0] == 'c'){
				printf("%2d %s %s %s\n", i, icg[i]->operation , icg[i]->op1 , icg[i]->op2);
			}else{
				printf("%2d %s = %s %s %s\n", i, icg[i]->result, icg[i]->op1, icg[i]->operation, icg[i]->op2);
			}
		}
	}
	void printList(List* list){
		printf("List: ");
		List* temp = list;
		while(temp != NULL){
			printf("%d ", temp->curr);
			temp = temp->next;
		}
		printf("\n");
	}

	typedef struct Block{
		struct Block* next;
		threeAddrCode* code[100];
		int index;
		int start;
		int end;
	}block;

	block* createBlock(){
		block* b = (block*)malloc(sizeof(block));
		b->next = NULL;
		return b;
	}
	block* startBlock = NULL;
	void createBasicBlocks() {
		block* currentBlock = createBlock();
		startBlock = currentBlock;
		int i = 0;
		int blockNo = 1;
		while (i < icgIndex) {
			
			if (strcmp(icg[i]->operation, "if") == 0 || strcmp(icg[i]->operation, "goto") == 0) {
				icg[i]->blockNo = blockNo;
				currentBlock->code[currentBlock->index++] = icg[i];
				currentBlock->end = icg[i]->index;
				currentBlock->next = createBlock();
				blockNo++;
				currentBlock = currentBlock->next;
				currentBlock->start = icg[i]->index + 1;
			} else if (strcmp(icg[i]->result, "return") == 0) {
				icg[i]->blockNo = blockNo;
				currentBlock->code[currentBlock->index++] = icg[i];
				currentBlock->end = icg[i]->index;
				currentBlock->next = createBlock();
				blockNo++;
				currentBlock = currentBlock->next;
				currentBlock->start = icg[i]->index + 1;
			} else {
				icg[i]->blockNo = blockNo;
				currentBlock->code[currentBlock->index++] = icg[i];
			}
			i++;
		}
		currentBlock = startBlock;
		//assigning the next block to each block
		printf("----------------------------------------------------------------------------");
		for(int i = 0;i<icgIndex;i++){
			if(strcmp(icg[i]->operation,"if") == 0){
				// block* temp = startBlock;
				int label = atoi(icg[i]->result+1);
				for(int j = 0;j<icgIndex;j++){
				
					if(icg[j]->index == label){
						sprintf(icg[i]->result,"B%d",icg[j]->blockNo);
						break;
					}
				}
				
			}else if(strcmp(icg[i]->operation,"goto") == 0){
				int label = atoi(icg[i]->result+1);
				for(int j = 0;j<icgIndex;j++){
					if(icg[j]->index == label){
						sprintf(icg[i]->result,"B%d",icg[j]->blockNo);
						break;
					}
				}
			}
		}





		
	}

	
	void printBasicBlocks(block* startBlock) {
		block* currentBlock = startBlock;
		int blockIndex = 1;
		while (currentBlock != NULL) {
			printf("Basic Block %d:\n", blockIndex);
			for (int i = 0; i < currentBlock->index; i++) {
				threeAddrCode* code = currentBlock->code[i];
				// printf("%2d %s %s %s %s\n", currentBlock->code[i]->index, currentBlock->code[i]->operation, currentBlock->code[i]->op1, currentBlock->code[i]->op2, currentBlock->code[i]->result);
				if(code->operation[0] == 'g'){
					printf("%2d %s %s\n", code->index, code->operation, code->result);
				}else if(code->operation[0] == '='){
					printf("%2d %s = %s\n", code->index, code->result, code->op1);
				}else if( code->operation[0] == 'i'){
					printf("%2d %s %s %s %s\n", code->index, code->operation, code->op1,code->op2, code->result);
				}else if(code->operation[0] == 'p'){
					printf("%2d %s %s \n", code->index, code->operation, code->op1);
				}else if(code->operation[0] == 'c'){
					printf("%2d %s %s %s\n", code->index, code->operation , code->op1 , code->op2);
				}else{
					if(code->operation == "eliminated"){
						printf("%2d Dead Code eliminated\n",code->index);
						continue;
					}
					printf("%2d %s = %s %s %s\n", code->index, code->result, code->op1, code->operation, code->op2);
				}
			}
			printf("\n");
			currentBlock = currentBlock->next;
			blockIndex++;
		}
	}


	void constantFolding(block* startBlock) {
		block* currentBlock = startBlock;
		while (currentBlock != NULL) {
			int i = 0;
			while (i < currentBlock->index) {
				threeAddrCode* code = currentBlock->code[i];
				// printf("Constant folding: %s %s %s\n", code->op1, code->operation, code->op2);
				if (code->operation[0] != '=' && code->operation[0] != 'g' && code->operation[0] != 'i' && code->operation[0] != 'p' && code->operation[0] != 'c') {
					int op1_value = atoi(code->op1);
					int op2_value = atoi(code->op2);
					if (isdigit(code->op1[0]) && isdigit(code->op2[0])) {
						printf("Constant folding: %d %s %d------------------------\n", op1_value, code->operation, op2_value);
						int result;
						switch (code->operation[0]) {
							case '+':
								result = op1_value + op2_value;
								break;
							case '-':
								result = op1_value - op2_value;
								break;
							case '*':
								result = op1_value * op2_value;
								break;
							case '/':
								result = op1_value / op2_value;
								break;
							default:
								result = 0;
								break;
						}
						//printf("Result: %d----------------------------------------------\n", result);
						sprintf(code->op1, "%d", result);
						code->operation = "";
						code->op2 = "";
					}
				}
				i++;
			}
			currentBlock = currentBlock->next;
		}
		printf("Constant Folding Completed");
	}
	void commonsubexpression(block* startBlock) {
		block* currentBlock = startBlock;
		while (currentBlock != NULL) {
			int i = 0;
			while (i < currentBlock->index) {
				threeAddrCode* code = currentBlock->code[i];
				if (code->operation[0] != 'g' && code->operation[0] != 'i' && code->operation[0] != 'p' && code->operation[0] != 'c') {
					int j = i + 1;
					while (j < currentBlock->index) {
						if (strcmp(currentBlock->code[j]->op1, code->op1) == 0 && strcmp(currentBlock->code[j]->op2, code->op2) == 0 && strcmp(currentBlock->code[j]->operation, code->operation) == 0) {
							currentBlock->code[j]->operation = "";
							currentBlock->code[j]->op1 = code->result;
							currentBlock->code[j]->op2 = "";
						}
						j++;
					}
				}
				i++;
			}
			currentBlock = currentBlock->next;
		}
	}
	void deadCodeElimination(){
		
		int eliminations[1000];
		for(int i = 0;i<1000;i++){
			eliminations[i] = 0;
		}
		for(int i = 0;i<icgIndex;i++){
			
			if(icg[i]->operation[0] == '='){
				int flag = 0;
				for(int i = 0;i<1000;i++){
					eliminations[i] = 0;
				}
				for(int j = i+1;j<icgIndex;j++){
					
					if(strcmp(icg[j]->op1,icg[i]->result) == 0 || strcmp(icg[j]->op2,icg[i]->result) == 0){
						flag = 1;
						continue;
					}
					if(strcmp(icg[j]->result,icg[i]->result) == 0){
						
						eliminations[j] = 1;
					}
				}
				if(flag == 0){
					for(int x= 0;x<icgIndex;x++){
						if(eliminations[x] == 1){
							icg[x]->result = "";
							icg[x]->op1 = "";
							icg[x]->op2 = "";
							icg[x]->operation = "eliminated";
						}
					}
				}
			}
		}
		
	}
	void copyPropagation(){
		block* currentBlock = startBlock;
		while (currentBlock != NULL) {
			int i = 0;
			while (i < currentBlock->index) {
				threeAddrCode* code = currentBlock->code[i];
				if (code->operation[0] != 'g' && code->operation[0] != 'i' && code->operation[0] != 'p' && code->operation[0] != 'c') {
					int j = i + 1;
					while (j < currentBlock->index) {
						if (strcmp(currentBlock->code[j]->op1, code->result) == 0) {
							currentBlock->code[j]->op1 = code->op1;
						}
						if (strcmp(currentBlock->code[j]->op2, code->result) == 0) {
							currentBlock->code[j]->op2 = code->op1;
						}
						j++;
					}
				}
				i++;
			}
			currentBlock = currentBlock->next;
		}
		
	}
	// void printTree(struct Node* node, int level);
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
		if(root->value ==-1 && strcmp(root->dtype,"NULL") == 0){
			if(strcmp(root->value_str,"NULL") == 0){
				printf("|--%d.%s\n",level, root->label);
			}else{
				printf("|--%d.%s\n",level, root->value_str);
			}
		}
		else{
			printf("|--%d.(%s,%d,%s,%s)\n",level, root->label,root->value,root->value_str,root->dtype);
		}
		
		for(int i = 0;i<root->num_children;i++){
			printTree(root->children[i],level+1);
		}
	}
	void addEntry(char *name, char *dtype,int scope,int value){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,name) == 0 && symbolTable[i].scope == scope){
				//printf("Variable: %s, dtype:%s  \n",name,symbolTable[i].dtype);

				if(strcmp(symbolTable[i].dtype,"null") != 0 ){
					printf("Variable %s is already declared\n",name); 
					yyerror("Variable already declared");
					break;
					return;
				}
				symbolTable[i].value = value;
				strcpy(symbolTable[i].dtype,dtype);
				// printf("Variable: %s, dtype: %s \n",name,symbolTable[i].dtype);
				break;
			}
		}
	}
	void addFunctionValue(char *name, int value){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,name) == 0){
				symbolTable[i].value = value ;
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
	int checkEntry(char *name,char *dtype,int scope,int value){
		for(int i = 0;i<100;i++){
			
			if(strcmp(symbolTable[i].arr,name) == 0 && symbolTable[i].scope <= scope && strcmp(symbolTable[i].dtype,dtype) == 0){
				symbolTable[i].value = value;
				return 1;
			}
		}
		return 0;
	}
	void checkid(TreeNode *root){
		char x = root->value_str[0];
		if(x == 't') return;
		struct Pair p = checkIdentifier(root->value_str);
		if(p.dtype == "keyword"){
			printf("variable %s using the keyword declare again\n",root->value_str);
			yyerror("Variable using keyword");
			return;
		}

		if(p.dtype == "NULL"){
			printf("Variable %s is not declared\n",root->value_str); 
			yyerror("Variable not declared");
			return ;
		}else{
			root->dtype = p.dtype;
		}
		if(checkEntry(root->value_str,root->dtype,root->scope,root->value) == 0){
			
			printf("Variable %s,%s,%d is not declared\n",root->value_str,root->dtype,root->scope); 
			yyerror("Variable not declared");
			return;
		};
	}
	void checkType(TreeNode* a, TreeNode* b){
		if((a->dtype != b->dtype) && (strcmp(a->dtype, "string") == 0 || strcmp(b->dtype, "string") == 0)){
			yyerror("Type mismatch");
			return;
		}
	}
	int checkfnArguments(TreeNode* a){
		int flag = 0;
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,a->value_str) == 0){
				if(symbolTable[i].value != a->value){
					yyerror("Number of arguments mismatch");
					return 0;
				}else{
					flag == 1;
					return 1;
				}
			}
		}
		if(flag == 0){
			yyerror("Function not declared");
			return 0;
		}
		return 1;
	}


/* Line 189 of yacc.c  */
#line 582 "temp2.tab.c"

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

/* Line 214 of yacc.c  */
#line 509 "temp2.y"

    int num;
    char *str;
	struct TreeNode *node;



/* Line 214 of yacc.c  */
#line 670 "temp2.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 682 "temp2.tab.c"

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   284

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNRULES -- Number of states.  */
#define YYNSTATES  194

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    45,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    11,    13,    16,    17,    18,
      27,    31,    33,    36,    39,    40,    44,    46,    50,    52,
      53,    54,    55,    57,    60,    62,    64,    66,    68,    70,
      72,    75,    78,    81,    84,    87,    90,    97,   102,   107,
     111,   113,   117,   124,   135,   143,   154,   158,   161,   165,
     169,   173,   176,   179,   183,   187,   190,   194,   201,   208,
     213,   214,   219,   221,   226,   228,   230,   234,   236,   240,
     244,   251,   255,   259,   264,   269,   272,   276,   280,   282,
     286,   290,   292,   294,   296,   300,   302,   305,   308,   310,
     315,   317
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    49,    62,    48,    -1,    50,    48,    -1,
      -1,    36,    -1,    36,    49,    -1,    -1,    -1,    27,    29,
      51,    39,    53,    52,    40,    55,    -1,    54,    44,    53,
      -1,    54,    -1,    27,    29,    -1,    74,    29,    -1,    -1,
      37,    56,    38,    -1,    59,    -1,    56,    57,    59,    -1,
      59,    -1,    -1,    -1,    -1,    73,    -1,    80,    43,    -1,
      67,    -1,    65,    -1,    66,    -1,    69,    -1,    71,    -1,
      68,    -1,    63,    43,    -1,    60,    43,    -1,    61,    43,
      -1,     1,    43,    -1,    28,    29,    -1,    29,    28,    -1,
       8,    39,    81,    44,    81,    40,    -1,    10,    11,    12,
      43,    -1,    29,    39,    64,    40,    -1,    29,    39,    40,
      -1,    81,    -1,    81,    44,    64,    -1,    17,    39,    81,
      40,    57,    55,    -1,    17,    39,    81,    40,    57,    55,
      18,    58,    57,    55,    -1,    19,    57,    39,    81,    40,
      57,    55,    -1,    20,    57,    39,    73,    81,    43,    57,
      81,    40,    55,    -1,    21,    81,    43,    -1,    21,    43,
      -1,    32,    70,    43,    -1,    34,    81,    70,    -1,    34,
      30,    70,    -1,    34,    81,    -1,    34,    30,    -1,    33,
      72,    43,    -1,    35,    29,    72,    -1,    35,    29,    -1,
      27,    75,    43,    -1,    74,    29,    37,    78,    38,    43,
      -1,    74,    29,    39,     7,    40,    43,    -1,    13,    25,
      27,    25,    -1,    -1,    75,    76,    44,    77,    -1,    77,
      -1,    29,    41,     7,    42,    -1,    79,    -1,    29,    -1,
      78,    44,     7,    -1,     7,    -1,    29,    24,    81,    -1,
      29,    24,    81,    -1,    29,    41,    81,    42,    24,    81,
      -1,    29,    24,    81,    -1,    81,    25,    81,    -1,    81,
      14,    57,    81,    -1,    81,    15,    57,    81,    -1,    16,
      81,    -1,    81,     3,    82,    -1,    81,     4,    82,    -1,
      82,    -1,    82,     5,    83,    -1,    82,     6,    83,    -1,
      83,    -1,     7,    -1,    31,    -1,    39,    81,    40,    -1,
      29,    -1,    28,    29,    -1,    29,    28,    -1,    30,    -1,
      29,    41,    81,    42,    -1,    63,    -1,    29,    45,     9,
      39,    40,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   523,   523,   525,   526,   528,   529,   531,   531,   531,
     536,   540,   543,   549,   555,   557,   558,   561,   569,   570,
     572,   573,   575,   576,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   588,   589,   591,   593,   595,   609,
     612,   616,   619,   624,   631,   641,   651,   652,   654,   656,
     657,   658,   659,   661,   663,   664,   668,   669,   674,   679,
     681,   681,   687,   693,   698,   702,   709,   710,   714,   728,
     735,   748,   749,   768,   774,   780,   781,   782,   783,   786,
     787,   788,   791,   792,   793,   794,   795,   796,   797,   798,
     807,   808
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PLUS", "MINUS", "MUL", "DIV", "number",
  "swap", "size", "using", "namespace", "std", "vector", "AND", "OR",
  "NOT", "if_x", "else_x", "while_x", "for_x", "return_x", "printf_x",
  "main_x", "assignmentop", "comparisionop", "logicalop", "datatype",
  "unary", "identifier", "string", "character", "cout", "cin", "insert",
  "extract", "header", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "LBRACKET",
  "RBRACKET", "SEMICOLON", "COMMA", "'.'", "$accept", "program",
  "function_declarations", "headers", "function_declaration", "$@1", "$@2",
  "parameter_list", "parameter", "combined_stmt", "statement_list", "M",
  "N", "statement", "unary_statement", "swap_statement",
  "namespace_statement", "function_call", "arg_list", "if_statement",
  "while_statement", "for_statement", "return_statement", "cout_statement",
  "insert_statement", "cin_statement", "extract_statement",
  "declaration_statement", "vectordatatype", "id_list", "$@3", "decl_id",
  "list", "dec_assignment", "assignment_statement", "E", "T", "F", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    51,    52,    50,
      53,    53,    54,    54,    54,    55,    55,    56,    56,    56,
      57,    58,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    60,    60,    61,    62,    63,    63,
      64,    64,    65,    65,    66,    67,    68,    68,    69,    70,
      70,    70,    70,    71,    72,    72,    73,    73,    73,    74,
      76,    75,    75,    77,    77,    77,    78,    78,    79,    80,
      80,    81,    81,    81,    81,    81,    81,    81,    81,    82,
      82,    82,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     0,     1,     2,     0,     0,     8,
       3,     1,     2,     2,     0,     3,     1,     3,     1,     0,
       0,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     6,     4,     4,     3,
       1,     3,     6,    10,     7,    10,     3,     2,     3,     3,
       3,     2,     2,     3,     3,     2,     3,     6,     6,     4,
       0,     4,     1,     4,     1,     1,     3,     1,     3,     3,
       6,     3,     3,     4,     4,     2,     3,     3,     1,     3,
       3,     1,     1,     1,     3,     1,     2,     2,     1,     4,
       1,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     0,     6,     1,     0,     4,     0,     0,
       2,     4,     0,     7,     3,    37,     0,    14,     0,     0,
       8,    11,     0,     0,    12,     0,    14,    13,     0,     0,
      10,    59,     0,     0,     0,    20,    20,     0,     0,     0,
       0,     0,     0,     0,     9,    16,     0,     0,     0,    25,
      26,    24,    29,    27,    28,    22,     0,     0,    33,     0,
       0,     0,     0,    82,     0,     0,    85,    88,    83,     0,
      47,    90,     0,    78,    81,    65,    60,    62,    64,    34,
       0,    35,     0,     0,     0,     0,     0,     0,    20,    18,
      31,    32,    30,     0,    23,     0,     0,     0,     0,    75,
      86,     0,    87,     0,     0,     0,     0,     0,    20,    20,
       0,    46,     0,     0,     0,     0,    56,     0,    69,    39,
       0,    40,     0,    88,    51,    48,    55,    53,    15,     0,
       0,     0,     0,    20,     0,     0,    71,     0,     0,    84,
      85,    76,    77,     0,     0,    72,    79,    80,    68,     0,
       0,    38,     0,     0,    50,    49,    54,    17,    67,     0,
       0,     0,     0,    20,     0,    89,     0,    73,    74,    63,
      61,    41,     0,     0,     0,     0,    36,    42,     0,    20,
      91,    70,    57,    66,    58,    21,    44,     0,    20,     0,
       0,     0,    43,    45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    10,     3,    11,    16,    25,    20,    21,    44,
      88,    61,   188,    45,    46,    47,     7,    71,   120,    49,
      50,    51,    52,    53,    85,    54,    87,    55,    56,    76,
     117,    77,   159,    78,    57,   121,    73,    74
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -115
static const yytype_int16 yypact[] =
{
     -15,   -15,    32,    24,  -115,  -115,    51,    39,    66,    55,
    -115,    39,    46,  -115,  -115,  -115,    64,    15,    84,    87,
    -115,    75,    93,    98,  -115,    89,    15,  -115,   116,   191,
    -115,  -115,    99,   107,   134,  -115,  -115,   186,   126,   128,
      -4,   140,   143,   139,  -115,  -115,   141,   142,   144,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,   153,   145,  -115,   225,
     225,   150,   151,  -115,   225,   168,   155,  -115,  -115,   225,
    -115,  -115,    40,    53,  -115,   -11,   152,  -115,  -115,  -115,
     225,  -115,   206,   225,   245,   160,   169,   162,   171,  -115,
    -115,  -115,  -115,   -34,  -115,     4,    90,   225,   118,    57,
    -115,   225,  -115,   225,   198,    92,    10,    10,  -115,  -115,
     225,  -115,    10,    10,   225,   214,  -115,   182,    57,  -115,
     187,     8,    72,   -28,   109,  -115,   143,  -115,  -115,   230,
     223,   226,   225,  -115,   123,   225,    57,    76,   200,  -115,
     238,    53,    53,   225,   225,    57,  -115,  -115,    57,   202,
     126,  -115,   225,   216,  -115,  -115,  -115,  -115,  -115,    25,
     208,   161,   191,  -115,    42,  -115,   220,    57,    57,  -115,
    -115,  -115,   225,   199,   258,   224,  -115,   250,   191,  -115,
    -115,    57,  -115,  -115,  -115,  -115,  -115,   225,  -115,   166,
     191,   191,  -115,  -115
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -115,  -115,   259,   268,  -115,  -115,  -115,   246,  -115,   -70,
    -115,   -35,  -115,   -41,  -115,  -115,  -115,   -29,   119,  -115,
    -115,  -115,  -115,  -115,  -114,  -115,   154,   180,    -1,  -115,
    -115,   131,  -115,  -115,  -115,   -33,    29,    38
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -53
static const yytype_int16 yytable[] =
{
      48,    62,    89,   130,    72,   131,    84,   106,   107,   154,
     155,   106,   107,   114,    48,   -52,    22,    63,   108,   109,
      80,     1,   108,   109,    81,    22,    95,    96,    18,   110,
     115,    99,     5,   110,     6,    82,   105,    83,    65,   140,
      67,    68,    19,   106,   107,   106,   107,   118,   132,    69,
     122,   124,   152,   129,   108,   109,   108,   109,   112,   113,
     106,   107,     8,   173,   134,   110,     9,   110,   136,   174,
     137,   108,   109,   143,   144,   106,   107,   145,    12,   106,
     107,   148,   110,   111,    13,   179,   108,   109,   157,    15,
     108,   109,   177,   106,   107,   106,   107,   110,   162,   161,
      48,   110,   164,    17,   108,   109,   108,   109,   186,    23,
     167,   168,   106,   107,   153,   110,    24,   110,   165,    26,
     192,   193,    27,   108,   109,    28,   106,   107,   178,    29,
     133,    18,   139,    48,   110,   141,   142,   108,   109,   181,
      32,    31,    58,    84,   187,    38,    59,    33,   110,    48,
     146,   147,    18,   190,   189,    75,    34,    79,    35,    36,
      37,    48,    48,   163,   106,   107,    38,    39,    40,   106,
     107,    41,    42,    60,    84,   108,   109,   -19,    86,   101,
     108,   109,    93,   102,    90,    91,   110,    92,    94,    97,
      98,   110,    32,    63,    82,   116,   103,   100,   126,    33,
     104,   176,    64,   125,    18,   127,   191,   138,    34,   128,
      35,    36,    37,    63,    65,    66,    67,    68,    38,    39,
      40,   149,    64,    41,    42,    69,   150,   151,    43,    70,
     158,    32,    63,   160,    65,    66,    67,    68,    33,   166,
     172,    64,   182,    18,   169,    69,   119,    34,   175,    35,
      36,    37,    63,    65,    66,    67,    68,    38,    39,    40,
     180,    64,    41,    42,    69,   183,   102,   184,   185,     4,
      14,   171,    30,    65,    66,   123,    68,    82,   135,   103,
     156,   170,     0,   104,    69
};

static const yytype_int16 yycheck[] =
{
      29,    36,    43,    37,    37,    39,    34,     3,     4,   123,
     124,     3,     4,    24,    43,    43,    17,     7,    14,    15,
      24,    36,    14,    15,    28,    26,    59,    60,    13,    25,
      41,    64,     0,    25,    10,    39,    69,    41,    28,    29,
      30,    31,    27,     3,     4,     3,     4,    80,    44,    39,
      83,    84,    44,    88,    14,    15,    14,    15,     5,     6,
       3,     4,    11,    38,    97,    25,    27,    25,   101,    44,
     103,    14,    15,   108,   109,     3,     4,   110,    12,     3,
       4,   114,    25,    43,    29,    43,    14,    15,   129,    43,
      14,    15,   162,     3,     4,     3,     4,    25,   133,   132,
     129,    25,   135,    39,    14,    15,    14,    15,   178,    25,
     143,   144,     3,     4,    42,    25,    29,    25,    42,    44,
     190,   191,    29,    14,    15,    27,     3,     4,   163,    40,
      40,    13,    40,   162,    25,   106,   107,    14,    15,   172,
       1,    25,    43,    34,   179,    27,    39,     8,    25,   178,
     112,   113,    13,   188,   187,    29,    17,    29,    19,    20,
      21,   190,   191,    40,     3,     4,    27,    28,    29,     3,
       4,    32,    33,    39,    34,    14,    15,    38,    35,    24,
      14,    15,    29,    28,    43,    43,    25,    43,    43,    39,
      39,    25,     1,     7,    39,    43,    41,    29,    29,     8,
      45,    40,    16,    43,    13,    43,    40,     9,    17,    38,
      19,    20,    21,     7,    28,    29,    30,    31,    27,    28,
      29,     7,    16,    32,    33,    39,    44,    40,    37,    43,
       7,     1,     7,     7,    28,    29,    30,    31,     8,    39,
      24,    16,    43,    13,    42,    39,    40,    17,    40,    19,
      20,    21,     7,    28,    29,    30,    31,    27,    28,    29,
      40,    16,    32,    33,    39,     7,    28,    43,    18,     1,
      11,   152,    26,    28,    29,    30,    31,    39,    98,    41,
     126,   150,    -1,    45,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    47,    49,    49,     0,    10,    62,    11,    27,
      48,    50,    12,    29,    48,    43,    51,    39,    13,    27,
      53,    54,    74,    25,    29,    52,    44,    29,    27,    40,
      53,    25,     1,     8,    17,    19,    20,    21,    27,    28,
      29,    32,    33,    37,    55,    59,    60,    61,    63,    65,
      66,    67,    68,    69,    71,    73,    74,    80,    43,    39,
      39,    57,    57,     7,    16,    28,    29,    30,    31,    39,
      43,    63,    81,    82,    83,    29,    75,    77,    79,    29,
      24,    28,    39,    41,    34,    70,    35,    72,    56,    59,
      43,    43,    43,    29,    43,    81,    81,    39,    39,    81,
      29,    24,    28,    41,    45,    81,     3,     4,    14,    15,
      25,    43,     5,     6,    24,    41,    43,    76,    81,    40,
      64,    81,    81,    30,    81,    43,    29,    43,    38,    57,
      37,    39,    44,    40,    81,    73,    81,    81,     9,    40,
      29,    82,    82,    57,    57,    81,    83,    83,    81,     7,
      44,    40,    44,    42,    70,    70,    72,    59,     7,    78,
       7,    81,    57,    40,    81,    42,    39,    81,    81,    42,
      77,    64,    24,    38,    44,    40,    40,    55,    57,    43,
      40,    81,    43,     7,    43,    18,    55,    57,    58,    81,
      57,    40,    55,    55
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
#line 523 "temp2.y"
    {  (yyval.node) = create_Node("program", -1, "NULL","NULL", 3,(yyvsp[(1) - (3)].node),(yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));if(!head) head = (yyval.node);;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 525 "temp2.y"
    { (yyval.node) = create_Node("function_declarations", -1, "NULL","NULL", 2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 528 "temp2.y"
    {(yyval.node) = create_Node("headers", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node));;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 529 "temp2.y"
    { (yyval.node) = create_Node("headers", -1,"NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 531 "temp2.y"
    {(yyvsp[(2) - (2)].node)->dtype = (yyvsp[(1) - (2)].node)->dtype;;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 531 "temp2.y"
    { addEntry((yyvsp[(2) - (5)].node)->value_str,(yyvsp[(2) - (5)].node)->dtype,(yyvsp[(2) - (5)].node)->scope,(yyvsp[(5) - (5)].node)->value);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 531 "temp2.y"
    {
	(yyval.node) = create_Node("function_declaration", -1, "NULL","NULL", 4, (yyvsp[(1) - (8)].node), (yyvsp[(2) - (8)].node), (yyvsp[(5) - (8)].node), (yyvsp[(8) - (8)].node));
;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 536 "temp2.y"
    { 
		(yyval.node) = create_Node("parameter_list", -1, "NULL","NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		(yyval.node)->value = (yyvsp[(3) - (3)].node)->value + 1;
	 ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 540 "temp2.y"
    { (yyval.node) = create_Node("parameter_list", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); (yyval.node)->value = 1; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 543 "temp2.y"
    {
		(yyvsp[(2) - (2)].node)->dtype = (yyvsp[(1) - (2)].node)->dtype;
		(yyval.node) = create_Node("parameter", -1, "NULL","NULL",2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		(yyval.node)->value = 1;
		// addEntry($2->value_str,$2->dtype,$2->scope,$2->value);
	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 549 "temp2.y"
    {
		(yyvsp[(2) - (2)].node)->dtype = (yyvsp[(1) - (2)].node)->dtype;
		(yyval.node) = create_Node("parameter", -1, "NULL","NULL",2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		(yyval.node)->value = 1;
		// addEntry($2->value_str,$2->dtype,$2->scope,$2->value);
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 555 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 557 "temp2.y"
    { (yyval.node) = create_Node("combined_stmt", -1,"NULL","NULL", 3,(yyvsp[(1) - (3)].node),(yyvsp[(2) - (3)].node),(yyvsp[(3) - (3)].node)); (yyval.node)->nextList = (yyvsp[(2) - (3)].node)->nextList; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 558 "temp2.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node);  ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 561 "temp2.y"
    { 
			(yyval.node) = (yyvsp[(1) - (3)].node);
			// printf("2222222222backpatching %d\n",$2->nextList->curr);
			backpatch((yyvsp[(1) - (3)].node)->nextList,(yyvsp[(2) - (3)].node)->nextList->curr);
			// printf("PRINTING AFTER STMT\n");
			// printList($1->nextList);
			(yyval.node)->nextList = (yyvsp[(3) - (3)].node)->nextList;
		;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 569 "temp2.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); (yyval.node)->nextList = (yyvsp[(1) - (1)].node)->nextList; ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 572 "temp2.y"
    {(yyval.node) = create_Node("M", -1, "st_if","NULL", 0);(yyval.node)->nextList = newList(icgIndex);;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 573 "temp2.y"
    {(yyval.node) = create_Node("N", -1, "st_if","NULL", 0);(yyval.node)->nextList = newList(icgIndex);generateCode("goto","","","");;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 575 "temp2.y"
    { (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 576 "temp2.y"
    {printf("assignment_statement\n"); (yyval.node) = create_Node("statement", -1,"NULL","NULL",2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 577 "temp2.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 578 "temp2.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 579 "temp2.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 580 "temp2.y"
    {printf("cout_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 581 "temp2.y"
    {printf("cin_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 582 "temp2.y"
    {printf("return_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 583 "temp2.y"
    {printf("function_call\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 584 "temp2.y"
    {printf("unary_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 585 "temp2.y"
    {printf("swap_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 586 "temp2.y"
    { (yyval.node) = create_Node("error", -1, "NULL","NULL",0); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 588 "temp2.y"
    { (yyval.node) = create_Node("unary_statement", -1, "NULL","NULL",2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node));  (yyval.node)->dtype = (yyvsp[(2) - (2)].node)->dtype; generateCode("+", (yyvsp[(2) - (2)].node)->value_str, "1", (yyvsp[(2) - (2)].node)->value_str); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 589 "temp2.y"
    { (yyval.node) = create_Node("unary_statement", -1, "NULL","NULL",2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); (yyval.node)->dtype = (yyvsp[(1) - (2)].node)->dtype; generateCode("+", (yyvsp[(1) - (2)].node)->value_str, "1", (yyvsp[(1) - (2)].node)->value_str); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 591 "temp2.y"
    { (yyval.node) = create_Node("swap_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (6)].node), (yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node)); checkid((yyvsp[(3) - (6)].node)); checkid((yyvsp[(5) - (6)].node)); generateCode("swap", (yyvsp[(3) - (6)].node)->value_str, (yyvsp[(5) - (6)].node)->value_str, ""); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 593 "temp2.y"
    { (yyval.node) = create_Node("namespace_statement", -1, "NULL","NULL", 1, (yyvsp[(1) - (4)].node)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 595 "temp2.y"
    { 
		(yyval.node) = create_Node("function_call", -1, "function_call","NULL", 4, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node)); 
		(yyvsp[(1) - (4)].node)->value = (yyvsp[(3) - (4)].node)->value;
		printf("Function is being called-------------------- %s;Arguments:%d\n",(yyvsp[(1) - (4)].node)->value_str,(yyvsp[(3) - (4)].node)->value);
		int x = checkfnArguments((yyvsp[(1) - (4)].node));
		if(x){
			// printf("arguments %d\n",$3->value);
			// for(int i = 0;i<$3->value;i++){
			// 	printf("arguments %s\n",$3->children[i]->value_str);
			// 	//generateCode("param", $3->children[i]->value_str, "", "");
			// }
			generateCode("call", (yyvsp[(1) - (4)].node)->value_str, "", "");
		}
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 609 "temp2.y"
    { (yyval.node) = create_Node("function_call", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 612 "temp2.y"
    { 
		(yyval.node) = create_Node("arg_list", -1, (yyvsp[(1) - (1)].node)->value_str,"NULL", 1, (yyvsp[(1) - (1)].node)); (yyval.node)->value = 1; 
		generateCode("param", (yyvsp[(1) - (1)].node)->value_str, "", "");
	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 616 "temp2.y"
    { (yyval.node) = create_Node("arg_list", -1, "NULL","NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); (yyval.node)->value = (yyvsp[(3) - (3)].node)->value + 1; generateCode("param", (yyvsp[(1) - (3)].node)->value_str, "", ""); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 619 "temp2.y"
    { 
		(yyval.node) = create_Node("if_statement", -1,"NULL","NULL", 5,(yyvsp[(1) - (6)].node),(yyvsp[(2) - (6)].node),(yyvsp[(3) - (6)].node),(yyvsp[(4) - (6)].node),(yyvsp[(6) - (6)].node));
		backpatch((yyvsp[(3) - (6)].node)->trueList,(yyvsp[(5) - (6)].node)->nextList->curr);
		(yyval.node)->nextList = mergeList((yyvsp[(3) - (6)].node)->falseList,(yyvsp[(6) - (6)].node)->nextList);
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 624 "temp2.y"
    {
		(yyval.node) = create_Node("if_statement", -1,"NULL","NULL", 9,(yyvsp[(1) - (10)].node),(yyvsp[(2) - (10)].node),(yyvsp[(3) - (10)].node),(yyvsp[(4) - (10)].node),(yyvsp[(6) - (10)].node),(yyvsp[(7) - (10)].node),(yyvsp[(8) - (10)].node),(yyvsp[(9) - (10)].node),(yyvsp[(10) - (10)].node));
		backpatch((yyvsp[(3) - (10)].node)->trueList,(yyvsp[(5) - (10)].node)->nextList->curr);
		backpatch((yyvsp[(3) - (10)].node)->falseList,(yyvsp[(9) - (10)].node)->nextList->curr);
		(yyval.node)->nextList = mergeList(mergeList((yyvsp[(6) - (10)].node)->nextList,(yyvsp[(8) - (10)].node)->nextList),(yyvsp[(10) - (10)].node)->nextList);
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 631 "temp2.y"
    {
	(yyval.node) = create_Node("while_statement", -1, "NULL","NULL", 7, (yyvsp[(1) - (7)].node), (yyvsp[(2) - (7)].node), (yyvsp[(3) - (7)].node), (yyvsp[(4) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(6) - (7)].node), (yyvsp[(7) - (7)].node));
	backpatch((yyvsp[(4) - (7)].node)->trueList,(yyvsp[(6) - (7)].node)->nextList->curr);
	backpatch((yyvsp[(7) - (7)].node)->nextList,(yyvsp[(2) - (7)].node)->nextList->curr);
	(yyval.node)->nextList = (yyvsp[(4) - (7)].node)->falseList;
	char* x = malloc(10);
	sprintf(x,"L%d",(yyvsp[(2) - (7)].node)->nextList->curr);
	generateCode("goto", "", "", x);
 ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 641 "temp2.y"
    { 
	(yyval.node) = create_Node("for_statement", -1, "NULL","NULL", 9, (yyvsp[(1) - (10)].node), (yyvsp[(3) - (10)].node), (yyvsp[(4) - (10)].node), (yyvsp[(5) - (10)].node), (yyvsp[(6) - (10)].node), (yyvsp[(7) - (10)].node), (yyvsp[(8) - (10)].node), (yyvsp[(9) - (10)].node),(yyvsp[(10) - (10)].node));
	backpatch((yyvsp[(5) - (10)].node)->trueList,(yyvsp[(7) - (10)].node)->nextList->curr);
	backpatch((yyvsp[(10) - (10)].node)->nextList,(yyvsp[(2) - (10)].node)->nextList->curr);
	(yyval.node)->nextList = (yyvsp[(5) - (10)].node)->falseList;
	char* x = malloc(10);
	sprintf(x,"L%d",(yyvsp[(2) - (10)].node)->nextList->curr);
	generateCode("goto", "", "", x);
	// backpatch($4->falseList,$9->nextList->curr);
;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 651 "temp2.y"
    { (yyval.node) = create_Node("return_statement", -1,"NULL","NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node)); generateCode((yyvsp[(2) - (3)].node)->value_str, "", "", "return") ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 652 "temp2.y"
    { (yyval.node) = create_Node("return_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); generateCode("return", "","", "");}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 654 "temp2.y"
    { (yyval.node) = create_Node("cout_statement", -1,"NULL","NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 656 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1,"NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 657 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 658 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 659 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 661 "temp2.y"
    { (yyval.node) = create_Node("cin_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 663 "temp2.y"
    { (yyval.node) = (yyvsp[(3) - (3)].node); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 664 "temp2.y"
    { (yyval.node) = create_Node("extract_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 668 "temp2.y"
    { (yyvsp[(2) - (3)].node)->dtype = (yyvsp[(1) - (3)].node)->dtype;  (yyval.node) = create_Node("declaration_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 669 "temp2.y"
    {
		(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 3, (yyvsp[(1) - (6)].node), (yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node));
		(yyvsp[(2) - (6)].node)->dtype = (yyvsp[(1) - (6)].node)->dtype;
		addEntry((yyvsp[(2) - (6)].node)->value_str,(yyvsp[(2) - (6)].node)->dtype,(yyvsp[(2) - (6)].node)->scope,(yyvsp[(4) - (6)].node)->value);
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 674 "temp2.y"
    {
		(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 3, (yyvsp[(1) - (6)].node), (yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node));
		(yyvsp[(2) - (6)].node)->dtype = (yyvsp[(1) - (6)].node)->dtype;
		addEntry((yyvsp[(2) - (6)].node)->value_str,(yyvsp[(2) - (6)].node)->dtype,(yyvsp[(2) - (6)].node)->scope,(yyvsp[(4) - (6)].node)->value);
	;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 679 "temp2.y"
    {(yyval.node) = create_Node("vectordatatype", -1, "NULL","NULL", 2, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node)); (yyval.node)->dtype = (yyvsp[(3) - (4)].node)->dtype;;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 681 "temp2.y"
    {(yyvsp[(1) - (1)].node)->dtype = (yyvsp[(0) - (1)].node)->dtype;;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 681 "temp2.y"
    {
		(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 3, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node)); 
		(yyvsp[(4) - (4)].node)->dtype = (yyvsp[(0) - (4)].node)->dtype;
		(yyvsp[(1) - (4)].node)->dtype = (yyvsp[(0) - (4)].node)->dtype;
		addEntry((yyvsp[(4) - (4)].node)->value_str,(yyvsp[(4) - (4)].node)->dtype,(yyvsp[(4) - (4)].node)->scope,(yyvsp[(4) - (4)].node)->value);
	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 687 "temp2.y"
    {
		(yyval.node) = (yyvsp[(1) - (1)].node);
		(yyvsp[(1) - (1)].node)->dtype = (yyvsp[(0) - (1)].node)->dtype;
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 693 "temp2.y"
    {
		(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 4, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
		(yyvsp[(1) - (4)].node)->dtype = (yyvsp[(0) - (4)].node)->dtype;
		addEntry((yyvsp[(1) - (4)].node)->value_str,(yyvsp[(1) - (4)].node)->dtype,(yyvsp[(1) - (4)].node)->scope,(yyvsp[(1) - (4)].node)->value);
	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 698 "temp2.y"
    {
		(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));
		(yyvsp[(1) - (1)].node)->dtype = (yyvsp[(0) - (1)].node)->dtype; 
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 702 "temp2.y"
    { 
		(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));
		(yyvsp[(1) - (1)].node)->dtype = (yyvsp[(0) - (1)].node)->dtype;
		//printf("dtype %s %s %s %s\n",$<node>0->dtype,$<node>-1->dtype,$<node>-2->dtype,$<node>-3->dtype);
		addEntry((yyvsp[(1) - (1)].node)->value_str,(yyvsp[(1) - (1)].node)->dtype,(yyvsp[(1) - (1)].node)->scope,(yyvsp[(1) - (1)].node)->value); 
	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 709 "temp2.y"
    { (yyval.node) = create_Node("list", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 710 "temp2.y"
    { (yyval.node) = create_Node("list", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 714 "temp2.y"
    { 
		(yyval.node) = create_Node("dec_assignment", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); 
		checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));
		(yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value;
		if((yyvsp[(0) - (3)].node)->dtype != (yyvsp[(-1) - (3)].node)->dtype) (yyvsp[(1) - (3)].node)->dtype = (yyvsp[(0) - (3)].node)->dtype;
		else (yyvsp[(1) - (3)].node)->dtype = (yyvsp[(-3) - (3)].node)->dtype;
		// printf("dtype %s %s %s %s\n",$<node>0->dtype,$<node>-1->dtype,$<node>-2->dtype,$<node>-3->dtype);
		addEntry((yyvsp[(1) - (3)].node)->value_str,(yyvsp[(1) - (3)].node)->dtype,(yyvsp[(1) - (3)].node)->scope,(yyvsp[(1) - (3)].node)->value);
		char *x = malloc(10);
		sprintf(x,"%s",(yyvsp[(3) - (3)].node)->value_str);
		generateCode("=", x,"", (yyvsp[(1) - (3)].node)->value_str);
	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 728 "temp2.y"
    {
		(yyval.node) = create_Node("assignment_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));
		(yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value;
		checkid((yyvsp[(1) - (3)].node));
		checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));
		generateCode("=", (yyvsp[(3) - (3)].node)->value_str, "", (yyvsp[(1) - (3)].node)->value_str);
	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 735 "temp2.y"
    {
		(yyval.node) = create_Node("assignment_statement", -1, "NULL","NULL", 5, (yyvsp[(1) - (6)].node), (yyvsp[(2) - (6)].node), (yyvsp[(3) - (6)].node), (yyvsp[(4) - (6)].node), (yyvsp[(5) - (6)].node));
		checkid((yyvsp[(1) - (6)].node));
		checkType((yyvsp[(1) - (6)].node),(yyvsp[(5) - (6)].node));
		char *t = new_temp();
		generateCode("*", (yyvsp[(3) - (6)].node)->value_str, "4", t);
		char *x = malloc(strlen((yyvsp[(1) - (6)].node)->value_str)+strlen(t)+1);
		sprintf(x,"(%s)",(yyvsp[(1) - (6)].node)->value_str);
		generateCode("+", t, x, t);
		generateCode("=", (yyvsp[(5) - (6)].node)->value_str, "", t);
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 748 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); (yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value;  checkid((yyvsp[(1) - (3)].node)); checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 749 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); 
			(yyval.node)->trueList = newList(icgIndex);
			(yyval.node)->falseList = newList(icgIndex+1);
			printList((yyval.node)->trueList);
			printList((yyval.node)->falseList);
			char *x = malloc(strlen((yyvsp[(2) - (3)].node)->value_str)+strlen((yyvsp[(1) - (3)].node)->value_str)+strlen((yyvsp[(3) - (3)].node)->value_str)+1);
			int k = 0;
			for(int i = 0;i<strlen((yyvsp[(1) - (3)].node)->value_str);i++){
				x[k++] = (yyvsp[(1) - (3)].node)->value_str[i];
			}
			for(int i = 0;i<strlen((yyvsp[(2) - (3)].node)->value_str);i++){
				x[k++] = (yyvsp[(2) - (3)].node)->value_str[i];
			}
			for(int i = 0;i<strlen((yyvsp[(3) - (3)].node)->value_str);i++){
				x[k++] = (yyvsp[(3) - (3)].node)->value_str[i];
			}
			generateCode("if", x,"goto","");
			generateCode("goto","","","");
	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 768 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL","NULL", 3, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node)); checkType((yyvsp[(1) - (4)].node),(yyvsp[(4) - (4)].node)); 
		
		backpatch((yyvsp[(1) - (4)].node)->trueList, (yyvsp[(3) - (4)].node)->nextList->curr);
		(yyval.node)->trueList = (yyvsp[(4) - (4)].node)->trueList;
		(yyval.node)->falseList = mergeList((yyvsp[(1) - (4)].node)->falseList, (yyvsp[(4) - (4)].node)->falseList);
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 774 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL","NULL", 3, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node)); checkType((yyvsp[(1) - (4)].node),(yyvsp[(4) - (4)].node)); 

		backpatch((yyvsp[(1) - (4)].node)->falseList, (yyvsp[(3) - (4)].node)->nextList->curr);
		(yyval.node)->falseList = (yyvsp[(4) - (4)].node)->falseList;
		(yyval.node)->trueList = mergeList((yyvsp[(1) - (4)].node)->trueList, (yyvsp[(4) - (4)].node)->trueList);
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 780 "temp2.y"
    { (yyval.node) = create_Node("E", !(yyvsp[(2) - (2)].node)->value,  new_temp(),"NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); (yyval.node)->value = !(yyvsp[(2) - (2)].node)->value; (yyval.node)->trueList = (yyvsp[(2) - (2)].node)->falseList; (yyval.node)->falseList = (yyvsp[(2) - (2)].node)->trueList; ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 781 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (3)].node)->value+(yyvsp[(3) - (3)].node)->value, new_temp(),"NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));  generateCode("+", (yyvsp[(1) - (3)].node)->value_str, (yyvsp[(3) - (3)].node)->value_str, (yyval.node)->value_str); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 782 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (3)].node)->value-(yyvsp[(3) - (3)].node)->value, new_temp(),"NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); generateCode("-", (yyvsp[(1) - (3)].node)->value_str, (yyvsp[(3) - (3)].node)->value_str, (yyval.node)->value_str);;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 783 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (1)].node)->value, (yyvsp[(1) - (1)].node)->value_str,"NULL", 1, (yyvsp[(1) - (1)].node));  (yyval.node)->value = (yyvsp[(1) - (1)].node)->value; (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->dtype; ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 786 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (3)].node)->value*(yyvsp[(3) - (3)].node)->value, new_temp(),"NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); generateCode("*",  (yyvsp[(1) - (3)].node)->value_str, (yyvsp[(3) - (3)].node)->value_str, (yyval.node)->value_str);;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 787 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (3)].node)->value/(yyvsp[(3) - (3)].node)->value, new_temp(),"NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); generateCode("/", (yyvsp[(1) - (3)].node)->value_str, (yyvsp[(3) - (3)].node)->value_str, (yyval.node)->value_str);;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 788 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (1)].node)->value, (yyvsp[(1) - (1)].node)->value_str,"NULL", 1, (yyvsp[(1) - (1)].node)); (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->dtype;  (yyval.node)->value = (yyvsp[(1) - (1)].node)->value;;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 791 "temp2.y"
    { (yyval.node) = create_Node(new_temp(), -1, (yyvsp[(1) - (1)].node)->value_str,"NULL", 1, (yyvsp[(1) - (1)].node));  (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->dtype; (yyval.node)->value = (yyvsp[(1) - (1)].node)->value;  ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 792 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));  (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->dtype;  ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 793 "temp2.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node);  (yyval.node)->dtype = (yyvsp[(2) - (3)].node)->dtype;  ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 794 "temp2.y"
    { (yyval.node) = create_Node("F", -1, (yyvsp[(1) - (1)].node)->value_str,"NULL", 1, (yyvsp[(1) - (1)].node)); checkid((yyvsp[(1) - (1)].node));  (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->dtype; ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 795 "temp2.y"
    { (yyval.node) = create_Node("F", -1, (yyvsp[(1) - (2)].node)->value_str,"NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); checkid((yyvsp[(2) - (2)].node));  (yyval.node)->dtype = (yyvsp[(2) - (2)].node)->dtype; generateCode("+", (yyvsp[(2) - (2)].node)->value_str, "1", (yyvsp[(2) - (2)].node)->value_str); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 796 "temp2.y"
    { (yyval.node) = create_Node("F", -1, (yyvsp[(1) - (2)].node)->value_str,"NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); checkid((yyvsp[(1) - (2)].node));  (yyval.node)->dtype = (yyvsp[(1) - (2)].node)->dtype; generateCode("+", (yyvsp[(1) - (2)].node)->value_str, "1", (yyvsp[(1) - (2)].node)->value_str); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 797 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->label;;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 798 "temp2.y"
    {
		(yyval.node) = create_Node("F", -1, new_temp(),"NULL", 4, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node)); (yyval.node)->dtype = (yyvsp[(1) - (4)].node)->dtype;
		checkid((yyvsp[(1) - (4)].node));
		char *t = new_temp();
		generateCode("*", (yyvsp[(3) - (4)].node)->value_str, "4", t);
		char *x = malloc(strlen((yyvsp[(1) - (4)].node)->value_str)+strlen(t)+1);
		sprintf(x,"(%s)",(yyvsp[(1) - (4)].node)->value_str);
		generateCode("+", t, x, (yyval.node)->value_str);
	;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 807 "temp2.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 808 "temp2.y"
    { (yyval.node) = create_Node("F", -1, (yyvsp[(3) - (5)].node)->value_str,"NULL", 1, (yyvsp[(1) - (5)].node)); (yyval.node)->dtype = "int";;}
    break;



/* Line 1455 of yacc.c  */
#line 2838 "temp2.tab.c"
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
#line 811 "temp2.y"

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
	// initializeSymbolTable()
	extern char *yytext;
	yyin=fp;
	yyparse();
	// yyparse();
	printf("---------------\n");
	printTree(head,0);
	printf("---------------\n");
	display();

	printf("---------------\n");
	displayICG();
	printf("---------------\n");
	createBasicBlocks();
	printf("--------------Blocks--------------\n");
	printBasicBlocks(startBlock);
	// deadCodeElimination(startBlock);
	deadCodeElimination();
	printf("--------------Dead Code Eliminated-------------------\n");
	constantFolding(startBlock);
	printf("---------------\n");
	commonsubexpression(startBlock);
	printf("--------------common sub Expression done------------------");
	printf("--------------Blocks After Optimization--------------\n");
	printBasicBlocks(startBlock);
	
}
