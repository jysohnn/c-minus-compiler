%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */
static int yyerror(char * message);
static int yylex(void);

%}

%token ENDFILE ERROR COMMENT_ERROR
%token ELSE IF INT RETURN VOID WHILE
%token ID NUM
%token PLUS MINUS TIMES OVER
%token LE LT GE GT EQ ASSIGN
%token NE SEMI COMMA LPAREN RPAREN
%token LBRACK RBRACK LBRACE RBRACE

%nonassoc RPAREN 
%nonassoc ELSE

%% /* Grammar for C- */

program             : declaration_list
                    {
                        savedTree = $1;
                    } 
                    ;
declaration_list    : declaration_list declaration
                    {
                        YYSTYPE t = $1;
                        if (t != NULL)
                        {
                            while (t->sibling != NULL) t = t->sibling;
                            t->sibling = $2;
                            $$ = $1;
                        }
                        else $$ = $2;
                    }
                    | declaration
                    {
                        $$ = $1;
                    }
                    ;
declaration         : var_declaration
                    {
                        $$ = $1;
                    }
                    | fun_declaration
                    {
                        $$ = $1;
                    }
                    ;
var_declaration     : type_specifier ID
                    {
                        $$ = $1;
                        $$->name = savedName;
                        $$->kind.decl = VaK;
                        $$->var_type = Global;
                    }
                    SEMI
                    {
                        $$ = $1;
                    }
                    | type_specifier ID
                    {
                        $$ = $1;
                        $$->name = savedName;
                        $$->kind.decl = ArrK;
                        $$->var_type = Global;
                    }
                    LBRACK NUM
                    {
                        $$ = $1;
                        $$->arr_size = atoi(tokenString);
                    }
                    RBRACK SEMI
                    {
                        $$ = $1;
                    }
                    ;
type_specifier      : INT
                    {
                        $$ = newDeclNode();
                        $$->type = Integer;
                    }
type_specifier      : VOID
                    {
                        $$ = newDeclNode();
                        $$->type = Void;
                    }
                    ;
fun_declaration     : type_specifier ID
                    {
                        $$ = $1;
                        $$->name = savedName;
                        $$->kind.decl = FuncK;
                    }
                    LPAREN params RPAREN compound_stmt
                    {
                        $$ = $1;
                        $$->child[0] = $5;
                        $$->child[1] = $7;
                    }
                    ;
params              : param_list
                    {
                        $$ = $1;
                    }
                    | VOID
                    {
                        $$ = newDeclNode();
                        $$->kind.decl = VaK;
                        $$->var_type = Para;
                        $$->type = Void;
                        $$->name = NULL;
                    }
                    ;
param_list          : param_list COMMA param
                    {
                        YYSTYPE t = $1;
                        if (t != NULL)
                        {
                            while (t->sibling != NULL) t = t->sibling;
                            t->sibling = $3;
                            $$ = $1;
                        }
                        else $$ = $3;
                    }
                    | param
                    {
                        $$ = $1;
                    }
                    ;
param               : type_specifier ID
                    {
                        $$ = $1;
                        $$->name = savedName;
                        $$->kind.decl = VaK;
                        $$->var_type = Para;
                    }
                    | type_specifier ID
                    {
                        $$ = $1;
                        $$->name = savedName;
                        $$->kind.decl = ArrK;
                        $$->var_type = Para;
                    }
                    LBRACK RBRACK
                    {
                        $$ = $1;
                    }
                    ;
compound_stmt       : LBRACE local_declarations statement_list RBRACE
                    {
                        $$ = newStmtNode(ComK);
                        $$->child[0] = $2;
                        $$->child[1] = $3;
                    }
                    ;
local_declarations  : local_declarations var_declaration
                    {
                        $2->var_type = Local;
                        YYSTYPE t = $1;
                        if (t != NULL)
                        {
                            while (t->sibling != NULL) t = t->sibling;
                            t->sibling = $2;
                            $$ = $1;
                        }
                        else $$ = $2;
                    }
                    |
                    {
                        $$ = NULL;
                    }
                    ;
statement_list      : statement_list statement
                    {
                        YYSTYPE t = $1;
                        if (t != NULL)
                        {
                            while (t->sibling != NULL) t = t->sibling;
                            t->sibling = $2;
                            $$ = $1;
                        }
                        else $$ = $2;
                    }
                    |
                    {
                        $$ = NULL;
                    }
                    ;
statement           : expression_stmt
                    {
                        $$ = $1;
                    }
                    | compound_stmt
                    {
                        $$ = $1;
                    }
                    | selection_stmt
                    {
                        $$ = $1;
                    }
                    | iteration_stmt
                    {
                        $$ = $1;
                    }
                    | retrun_stmt
                    {
                        $$ = $1;
                    }
                    ;
expression_stmt     : expression SEMI
                    {
                        $$ = $1;
                    }
                    | SEMI
                    {
                        $$ = NULL;
                    }
                    ;
selection_stmt     : IF LPAREN expression RPAREN statement
                    {
                        $$ = newStmtNode(SelK);
                        $$->child[0] = $3;
                        $$->child[1] = $5;
                    }
                    | IF LPAREN expression RPAREN statement ELSE statement
                    {
                        $$ = newStmtNode(SelK);
                        $$->else_flag = 1;
                        $$->child[0] = $3;
                        $$->child[1] = $5;
                        $$->child[2] = $7;
                    }
                    ;
iteration_stmt      : WHILE LPAREN expression RPAREN statement
                    {
                        $$ = newStmtNode(IterK);
                        $$->child[0] = $3;
                        $$->child[1] = $5;
                    }
                    ;
retrun_stmt         : RETURN SEMI
                    {
                        $$ = newStmtNode(RetK);
                    }
                    | RETURN expression SEMI
                    {
                        $$ = newStmtNode(RetK);
                        $$->return_flag = 1;
                        $$->child[0] = $2;
                    }
                    ;
expression          : var ASSIGN expression
                    {
                        $$ = newExpNode(AssignK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                    }
                    | simple_expression
                    {
                        $$ = $1;
                    }
                    ;
var                 : ID
                    {
                        $$ = newExpNode(VarK);
                        $$->name = savedName;
                    }
                    | ID
                    {
                        $$ = newExpNode(VarK);
                        $$->name = savedName;
                    }
                    LBRACK expression RBRACK
                    {
                        $$ = $2;
                        $$->child[0] = $4;
                    }
                    ;
simple_expression   : additive_expression relop additive_expression
                    {
                        $$ = $2;
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                    }
                    | additive_expression
                    {
                        $$ = $1;
                    }
                    ;
relop               : LE
                    {
                        $$ = newExpNode(OpK);
                        $$->op = LE;
                    }
                    | LT
                    {
                        $$ = newExpNode(OpK);
                        $$->op = LT;
                    }
                    | GT
                    {
                        $$ = newExpNode(OpK);
                        $$->op = GT;
                    }
                    | GE
                    {
                        $$ = newExpNode(OpK);
                        $$->op = GE;
                    }
                    | EQ
                    {
                        $$ = newExpNode(OpK);
                        $$->op = EQ;
                    }
                    | NE
                    {
                        $$ = newExpNode(OpK);
                        $$->op = NE;
                    }
                    ;
additive_expression : additive_expression addop term
                    {
                        $$ = $2;
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                    }
                    | term
                    {
                        $$ = $1;
                    }
                    ;
addop               : PLUS
                    {
                        $$ = newExpNode(OpK);
                        $$->op = PLUS;
                    }
                    | MINUS
                    {
                        $$ = newExpNode(OpK);
                        $$->op = MINUS;
                    }
                    ;
term                : term mulop factor
                    {
                        $$ = $2;
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                    }
                    | factor
                    {
                        $$ = $1;
                    }
                    ;
mulop               : TIMES
                    {
                        $$ = newExpNode(OpK);
                        $$->op = TIMES;
                    }
                    | OVER
                    {
                        $$ = newExpNode(OpK);
                        $$->op = OVER;
                    }
                    ;
factor              : LPAREN expression RPAREN
                    {
                        $$ = $2;
                    }
                    | var
                    {
                        $$ = $1;
                    }
                    | call
                    {
                        $$ = $1;
                    }
                    | NUM
                    {
                        $$ = newExpNode(NumK);
                        $$->val = atoi(tokenString);
                    }
                    ;
call                : ID
                    {
                        $$ = newExpNode(CallK);
                        $$->name = savedName;
                    }
                    LPAREN args RPAREN
                    {
                        $$ = $2;
                        $$->child[0] = $4;
                    }
                    ;
args                : arg_list
                    {
                        $$ = $1;
                    }
                    |
                    {
                        $$ = NULL;
                    }
                    ;
arg_list            : arg_list COMMA expression
                    {
                        YYSTYPE t = $1;
                        if (t != NULL)
                        {
                            while (t->sibling != NULL) t = t->sibling;
                            t->sibling = $3;
                            $$ = $1;
                        }
                        else $$ = $3;
                    }
                    | expression
                    {
                        $$ = $1;
                    }
                    ;
%%

int yyerror(char * message)
{
    fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
    fprintf(listing,"Current token: ");
    printToken(yychar,tokenString);
    Error = TRUE;
    return 0;
}

static int yylex(void)
{
    int t;
    savedName = copyString(tokenString);
    t = getToken();
    if(t == ENDFILE) return 0;
    else return t;
}

TreeNode * parse(void)
{
    yyparse();
    return savedTree;
}
