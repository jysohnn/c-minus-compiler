#include "globals.h"
#include "util.h"

const char* typeString[2] = {"void", "int"};

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  {
    case ENDFILE: fprintf(listing, "\t%d\t\tEOF\n", lineno); break;
    case ERROR: fprintf(listing, "\t%d\t\tERROR\t\t%s\n", lineno, tokenString); break;
    case COMMENT_ERROR: fprintf(listing, "\t%d\t\tERROR\t\tComment Error\n", lineno); break;
    case ELSE: fprintf(listing, "\t%d\t\tELSE\t\t%s\n", lineno, tokenString); break;
    case IF: fprintf(listing, "\t%d\t\tIF\t\t%s\n", lineno, tokenString); break;
    case INT: fprintf(listing, "\t%d\t\tINT\t\t%s\n", lineno, tokenString); break;
    case RETURN: fprintf(listing, "\t%d\t\tRETURN\t\t%s\n", lineno, tokenString); break;
    case VOID: fprintf(listing, "\t%d\t\tVOID\t\t%s\n", lineno, tokenString); break;
    case WHILE: fprintf(listing, "\t%d\t\tWHILE\t\t%s\n", lineno, tokenString); break;
    case PLUS: fprintf(listing, "\t%d\t\t+\t\t%s\n", lineno, tokenString); break;
    case MINUS: fprintf(listing, "\t%d\t\t-\t\t%s\n", lineno, tokenString); break;
    case TIMES: fprintf(listing, "\t%d\t\t*\t\t%s\n", lineno, tokenString); break;
    case OVER: fprintf(listing, "\t%d\t\t/\t\t%s\n", lineno, tokenString); break;
    case LE: fprintf(listing, "\t%d\t\t<=\t\t%s\n", lineno, tokenString); break;
    case LT: fprintf(listing, "\t%d\t\t<\t\t%s\n", lineno, tokenString); break;
    case GE: fprintf(listing, "\t%d\t\t>=\t\t%s\n", lineno, tokenString); break;
    case GT: fprintf(listing, "\t%d\t\t>\t\t%s\n", lineno, tokenString); break;
    case EQ: fprintf(listing, "\t%d\t\t==\t\t%s\n", lineno, tokenString); break;
    case ASSIGN: fprintf(listing, "\t%d\t\t=\t\t%s\n", lineno, tokenString); break;
    case NE: fprintf(listing, "\t%d\t\t!=\t\t%s\n", lineno, tokenString); break;
    case SEMI: fprintf(listing, "\t%d\t\t;\t\t%s\n", lineno, tokenString); break;
    case COMMA: fprintf(listing, "\t%d\t\t,\t\t%s\n", lineno, tokenString); break;
    case LPAREN: fprintf(listing, "\t%d\t\t(\t\t%s\n", lineno, tokenString); break;
    case RPAREN: fprintf(listing, "\t%d\t\t)\t\t%s\n", lineno, tokenString); break;
    case LBRACK: fprintf(listing, "\t%d\t\t[\t\t%s\n", lineno, tokenString); break;
    case RBRACK: fprintf(listing, "\t%d\t\t]\t\t%s\n", lineno, tokenString); break;
    case LBRACE: fprintf(listing, "\t%d\t\t{\t\t%s\n", lineno, tokenString); break;
    case RBRACE: fprintf(listing, "\t%d\t\t}\t\t%s\n", lineno, tokenString); break;
    case NUM: fprintf(listing, "\t%d\t\tNUM\t\t%s\n", lineno, tokenString); break;
    case ID: fprintf(listing, "\t%d\t\tID\t\t%s\n", lineno, tokenString); break;
    default: /* should never happen */ break;
  }
}

TreeNode * newDeclNode()
{
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->lineno = lineno;
    t->sibling = NULL;
    t->nodekind = DeclK;
    t->type = -1;
    t->arr_size = 0;
    t->else_flag = t->return_flag = t->func_flag = 0;
  }
  return t;
}

TreeNode * newStmtNode(StmtKind kind)
{
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->lineno = lineno;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->else_flag = t->return_flag = t->func_flag = 0;
  }
  return t;
}

TreeNode * newExpNode(ExpKind kind)
{
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->lineno = lineno;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->else_flag = t->return_flag = t->func_flag = 0;
  }
  return t;
}

char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==DeclK)
    {
      switch (tree->kind.decl) {
        case VaK:
          if(tree->var_type == Global) fprintf(listing,"Variable declaration");
          else if(tree->var_type == Local) fprintf(listing,"Variable declaration (Local)");
          else if(tree->var_type == Para)
          {
            if(tree->type != Void) fprintf(listing,"Parameter declaration");
            else
            {
              fprintf(listing,"Parameter declaration (void)\n");
              break;
            }
          }
          fprintf(listing," [Type: %s, Id: %s]\n", typeString[tree->type], tree->name);
          break;
        case ArrK:
          if(tree->var_type == Global) fprintf(listing,"Variable declaration");
          else if(tree->var_type == Local) fprintf(listing,"Variable declaration (Local)");
          else if(tree->var_type == Para) fprintf(listing,"Parameter declaration");
          fprintf(listing," [Type: %s array, Id: %s", typeString[tree->type], tree->name);
          if(tree->var_type != Para) fprintf(listing,", Size: %d]\n", tree->arr_size);
          else fprintf(listing,"]\n");
          break;
        case FuncK:
          fprintf(listing,"Function declaration");
          fprintf(listing," [Type: %s, Id: %s]\n", typeString[tree->type], tree->name);
          break;
        default:
          fprintf(listing,"Unknown DeclNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==StmtK)
    {
      switch (tree->kind.stmt) {
        case ComK:
          fprintf(listing,"Compound Statement\n");
          break;
        case SelK:
          fprintf(listing,"If Statement\n");
          if(tree->else_flag)
          {
            printTree(tree->child[0]);
            printTree(tree->child[1]);
            printSpaces(); fprintf(listing,"Else Statement\n");
            printTree(tree->child[2]);
          }
          break;
        case IterK:
          fprintf(listing,"While Statement\n");
          break;
        case RetK:
          if(tree->return_flag) fprintf(listing,"Return Statement\n");
          else fprintf(listing,"Return Statement (void)\n");
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    {
      switch (tree->kind.exp) {
        case OpK:
          switch(tree->op)
          {
            case PLUS: fprintf(listing, "Op: +\n"); break;
            case MINUS: fprintf(listing, "Op: -\n"); break;
            case TIMES: fprintf(listing, "Op: *\n"); break;
            case OVER: fprintf(listing, "Op: /\n"); break;
            case LE: fprintf(listing, "Op: <=\n"); break;
            case LT: fprintf(listing, "Op: <\n"); break;
            case GE: fprintf(listing, "Op: >=\n"); break;
            case GT: fprintf(listing, "Op: >\n"); break;
            case EQ: fprintf(listing, "Op: ==\n"); break;
            case NE: fprintf(listing, "Op: !=\n"); break;
            default: break;
          }
          break;
        case VarK:
          fprintf(listing,"Id: %s\n", tree->name);
          break;
        case ArrrK:
          fprintf(listing,"Id: %s\n", tree->name);
          break;
        case NumK:
          fprintf(listing,"Const: %d\n", tree->val);
          break;
        case CallK:
          fprintf(listing,"Call: %s\n", tree->name);
          break;
        case AssignK:
          fprintf(listing,"Assign\n");
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
    
    if(!tree->else_flag)
      for(i = 0; i < MAXCHILDREN; i++)
        printTree(tree->child[i]);
    
    tree = tree->sibling;
  }
  UNINDENT;
}