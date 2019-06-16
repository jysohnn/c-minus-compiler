#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 6
#define MAXTOKENLEN 40

#ifndef YYPARSER
#include "cm.tab.h"
#endif

typedef int TokenType;

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */
extern FILE* data;
extern FILE* complete;


extern int lineno; /* source line number for listing */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {StmtK,ExpK,DeclK} NodeKind;
typedef enum {VaK,ArrK,FuncK} DeclKind;
typedef enum {ComK,SelK,IterK,RetK} StmtKind;
typedef enum {OpK,VarK,ArrrK,NumK,CallK,AssignK} ExpKind;

typedef enum {Global, Local, Para} VarType;
typedef enum {Void=0,Integer=1} DataType;

#define MAXCHILDREN 3

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     struct treeNode * friend;
     int lineno;
     NodeKind nodekind;
     union { DeclKind decl; StmtKind stmt; ExpKind exp; } kind;
     char* name;
     DataType type;
     VarType var_type;
     int val;
     int array_type;
     int func_type;
     int arr_size;
     int is_array;
     int is_func;
     int op;
     int else_flag, return_flag, func_flag;

     int mem_offset;
     int compound_mem_size;
     int is_array_name;
   } TreeNode;

typedef enum
{
  DEF_GLOBAL_VAR,
  DEF_GLOBAL_ARR,
  DEF_FUNC,

  GLOBAL_VAR,
  GLOBAL_ARR,
  GLOBAL_ARR_NAME,
  LOCAL_VAR,
  LOCAL_ARR,
  LOCAL_ARR_NAME,
  PARA_VAR,
  PARA_ARR,
  PARA_ARR_NAME,

  EXP_OP,
  EXP_CALL,
  EXP_ASSIGN,
  EXP_NUM,

  STMT_COM,
  STMT_IF,
  STMT_IF_ELSE,
  STMT_WHILE,
  STMT_RET

} DecoKind;

typedef struct decoNode
{
  struct decoNode * child[MAXCHILDREN];
  struct decoNode * sibling;
  DecoKind deco_kind;
  
  int type;
  char * name;
  int val;
  int arr_size;
  int op_kind;
  int offset;
  int local_var_size;
  int is_func_com;

} DecoNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error;
#endif