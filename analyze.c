#include "globals.h"
#include "symtab.h"
#include "analyze.h"

static int symbol_table_print = 0;
static int main_decl = 0;

/* counter for variable memory locations */
static int global_location = 0;
static int local_location = -4;
static int para_location = 0;
static int func_num = 0;

static void printError(TreeNode * t, int error_type)
{
  fprintf(listing, "ERROR in line %d : ", t->lineno);
  switch(error_type)
  {
    case 0:
      fprintf(listing, "'%s' is undeclared.\n", t->name);
      break;
    case 1:
      fprintf(listing, "'%s' is duplicated.\n", t->name);
      break;
    case 2:
      fprintf(listing, "The 'main' function must be declared at the end.\n");
      break;
    case 3:
      fprintf(listing, "The 'main' function should not have parameters.\n");
      break;
    default:
      break;
  }
  Error = TRUE;
}

static void traverse(TreeNode * t, void (* preProc) (TreeNode *), void (* postProc) (TreeNode *))
{
  if(Error) return;
  if (t != NULL)
  {
    int i;
    preProc(t);
    if(Error) return;
    for (i=0; i < MAXCHILDREN; i++)
    {
      traverse(t->child[i],preProc,postProc);
      if(Error) return;
    }
    postProc(t);
    if(Error) return;
    traverse(t->sibling,preProc,postProc);
  }
}

static void nullProc(TreeNode * t)
{
  if (t==NULL) return;
  else return;
}

static void symbol_post(TreeNode * t)
{
  if(t != NULL)
  {
    if(t->nodekind == StmtK && t->kind.stmt == ComK)
    {
      if(TraceAnalyze && symbol_table_print) print_table(listing);
      scope_pop();
    }
  }
}

static void symbol_pre(TreeNode * t)
{
  switch (t->nodekind)
  {
    case DeclK:
      if(!(t->var_type == Para && t->type == Void) && symbol_lookup(t->name) != NULL)
      {
        printError(t, 1);
        return;
      }
      switch (t->kind.decl)
      {
        case VaK:
          switch (t->var_type)
          {
            case Global:
              global_location += 4;
              symbol_insert(t->name, global_location, V, 0, 0, INT, t->lineno);
              break;
            case Local:
              local_location -= 4;
              symbol_insert(t->name, local_location, V, 0, 0, INT, t->lineno);
              break;
            case Para:
              if(t->type != Void)
              {
                para_location += 4;
                symbol_insert(t->name, para_location, P, 0, 0, INT, t->lineno);
              }
              break;
            default:
              break;
          }
          break;
        case ArrK:
          switch (t->var_type)
          {
            case Global:
              global_location += 4 * t->arr_size;
              symbol_insert(t->name, global_location, V, 1, t->arr_size, INT, t->lineno);
              break;
            case Local:
              local_location -= 4 * t->arr_size;
              symbol_insert(t->name, local_location, V, 1, t->arr_size, INT, t->lineno);
              break;
            case Para:
              para_location += 4;
              symbol_insert(t->name, para_location, P, 1, t->arr_size, INT, t->lineno);
              break;
            default:
              break;
          }
          break;
        case FuncK:
          if(main_decl)
          {
            printError(t, 2);
            return;
          }
          if(strcmp(t->name, "main") == 0)
          {
            main_decl = 1;
            if(!t->child[0]->type == Void)
            {
              printError(t, 3);
              return;
            }
          }

          local_location = -4;
          para_location = 0;
          if(t->type == Integer) symbol_insert(t->name, func_num++, F, 0, 0, INT, t->lineno);
          else symbol_insert(t->name, func_num++, F, 0, 0, VOID, t->lineno);
          scope_push();
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      {
        case ComK:
          if(t->func_flag == 0) scope_push();
          break;
        default:
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      {
        case VarK:
        case ArrrK:
        case CallK:
          if(symbol_lookup_global(t->name) == NULL)
          {
            printError(t, 0);
            return;
          }
          symbol_insert_global(t->name, t->lineno);
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void buildSymtab(TreeNode * syntaxTree)
{
  scope_push();
  traverse(syntaxTree, symbol_pre, symbol_post);
  scope_pop();
}

void printSymtab(TreeNode * syntaxTree)
{
  global_location = 0;
  local_location = -4;
  para_location = 0;
  func_num = 0;
  main_decl = 0;
  symbol_table_print = 1;
  scope_push();
  if (TraceAnalyze) fprintf(listing,"\nSymbol table:\n\n");
  traverse(syntaxTree, symbol_pre, symbol_post);
  if (TraceAnalyze) print_table(listing);
  scope_pop();
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
/* static void checkNode(TreeNode * t)
{ switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case OpK:
          if ((t->child[0]->type != Integer) ||
              (t->child[1]->type != Integer))
            typeError(t,"Op applied to non-integer");
          if ((t->attr.op == EQ) || (t->attr.op == LT))
            t->type = Boolean;
          else
            t->type = Integer;
          break;
        case ConstK:
        case IdK:
          t->type = Integer;
          break;
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { case IfK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"if test is not Boolean");
          break;
        case AssignK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"assignment of non-integer value");
          break;
        case WriteK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"write of non-integer value");
          break;
        case RepeatK:
          if (t->child[1]->type == Integer)
            typeError(t->child[1],"repeat test is not Boolean");
          break;
        default:
          break;
      }
      break;
    default:
      break;

  }
}

void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree,nullProc,checkNode);
}
*/