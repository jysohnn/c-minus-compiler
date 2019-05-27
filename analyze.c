#include "globals.h"
#include "symtab.h"
#include "analyze.h"

static TreeNode * mt = NULL;
static int symbol_table_print = 0;
static int main_decl = 0;
static int ret_exist = 0;
static int ret_type = 0;

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
    case 4:
      fprintf(listing, "Variable and parameter declarations can not be declared 'void' type.\n");
      break;
    case 5:
      fprintf(listing, "The value should be 'int' type.\n");
      break;
    case 6:
      fprintf(listing, "'%s' is not array variable.\n", t->name);
      break;
    case 7:
      fprintf(listing, "'%s' is not function.\n", t->name);
      break;
    case 8:
      fprintf(listing, "The r-value of 'Assign' should be 'int' type.\n");
      break;
    case 9:
      fprintf(listing, "The l-value of 'Assign' should be variable.\n");
      break;
    case 10:
      fprintf(listing, "The 'main' function should return a void type.\n");
      break;
    case 11:
      fprintf(listing, "The 'void' type function should not have return.\n");
      break;
    case 12:
      fprintf(listing, "The 'int' type function should have return integer value.\n");
      break;
    case 13:
      fprintf(listing, "The parameter and argument are different (Number or Type).\n");
      break;
    case 14:
      fprintf(listing, "The index value should be 'int' type.\n");
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

static void symbol_pre(TreeNode * t)
{
  BucketList l;
  switch (t->nodekind)
  {
    case DeclK:
      if(!(t->var_type == Para && t->type == Void && t->name == NULL) && symbol_lookup(t->name) != NULL)
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
              symbol_insert(t->name, global_location, V, 0, 0, 1, t->lineno, t);
              break;
            case Local:
              local_location -= 4;
              cur_scope->local_location_using -= 4;
              symbol_insert(t->name, local_location, V, 0, 0, 1, t->lineno, t);
              break;
            case Para:
              if(!(t->type == Void && t->name == NULL))
              {
                para_location += 4;
                symbol_insert(t->name, para_location, P, 0, 0, 1, t->lineno, t);
              }
              break;
          }
          break;
        case ArrK:
          switch (t->var_type)
          {
            case Global:
              global_location += 4 * t->arr_size;
              symbol_insert(t->name, global_location, V, 1, t->arr_size, 1, t->lineno, t);
              break;
            case Local:
              local_location -= 4 * t->arr_size;
              cur_scope->local_location_using -= 4 * t->arr_size;
              symbol_insert(t->name, local_location, V, 1, t->arr_size, 1, t->lineno, t);
              break;
            case Para:
              para_location += 4;
              symbol_insert(t->name, para_location, P, 1, t->arr_size, 1, t->lineno, t);
              break;
          }
          break;
        case FuncK:
          if(main_decl)
          {
            printError(mt, 2);
            return;
          }
          if(strcmp(t->name, "main") == 0)
          {
            main_decl = 1;
            mt = t;
            if(t->child[0]->type != Void)
            {
              printError(t, 3);
              return;
            }
            if(t->type != Void)
            {
              printError(t, 10);
              return;
            }
          }
          local_location = -4;
          para_location = 0;
          if(t->type == Integer) symbol_insert(t->name, func_num++, F, 0, 0, 1, t->lineno, t);
          else symbol_insert(t->name, func_num++, F, 0, 0, 0, t->lineno, t);
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
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      {
        case VarK:
          l = symbol_lookup_global(t->name);
          if(l == NULL)
          {
            printError(t, 0);
            return;
          }
          t->type = l->type;
          if(l->node->kind.decl == ArrK) t->array_type = 1;
          if(l->node->kind.decl == FuncK) t->func_type = 1;
          symbol_insert_global(t->name, t->lineno);
          break;
        case ArrrK:
          l = symbol_lookup_global(t->name);
          if(l == NULL)
          {
            printError(t, 0);
            return;
          }
          else if(l->is_array == 0)
          {
            printError(t, 6);
            return;
          }
          t->type = l->type;
          symbol_insert_global(t->name, t->lineno);
          break;
        case NumK:
          t->type = Integer;
          break;
        case CallK:
          l = symbol_lookup_global(t->name);
          if(l == NULL)
          {
            printError(t, 0);
            return;
          }
          else if(l->var_type != F)
          {
            printError(t, 7);
            return;
          }
          t->type = l->type;
          t->friend = l->node;
          symbol_insert_global(t->name, t->lineno);
          break;
      }
      break;
  }
}

static void symbol_post(TreeNode * t)
{
  if(t != NULL)
  {
    if(t->nodekind == StmtK && t->kind.stmt == ComK)
    {
      local_location -= cur_scope->local_location_using;
      if(TraceAnalyze && symbol_table_print) print_table(listing);
      scope_pop();
    }
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
  mt = NULL;
  symbol_table_print = 1;
  main_decl = 0;
  ret_exist = 0;
  ret_type = 0;

  global_location = 0;
  local_location = -4;
  para_location = 0;
  func_num = 0;

  scope_push();
  if (TraceAnalyze) fprintf(listing,"\nSymbol table:\n\n");
  traverse(syntaxTree, symbol_pre, symbol_post);
  if (TraceAnalyze) print_table(listing);
  scope_pop();
}

static void check_pre(TreeNode * t)
{
  int i;
  switch (t->nodekind)
  {
    case DeclK:
      switch (t->kind.decl)
      {
        case VaK:
        case ArrK:
          if(!(t->var_type == Para && t->type == Void && t->name == NULL) && t->type == Void)
          {
            printError(t, 4);
            return;
          }
          break;
        case FuncK:
          ret_exist = 0;
          ret_type = t->type;
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      {
        case AssignK:
          if(!((t->child[0]->kind.exp == VarK && !t->child[0]->array_type && !t->child[0]->func_type) || (t->child[0]->kind.exp == ArrrK)))
          {
            printError(t, 9);
            return;
          }
          break;
      }
      break;
  }
}

static void check_post(TreeNode * t)
{
  int i;
  TreeNode * ft;
  switch (t->nodekind)
  {
    case DeclK:
      switch (t->kind.decl)
      {
        case FuncK:
          if(t->type == Integer && !ret_exist)
          {
            printError(t, 12);
            return;
          }
          ret_exist = 0;
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      {
        case SelK:
          if(!(t->child[0]->type == Integer && !t->child[0]->array_type && !t->child[0]->func_type))
          {
            printError(t->child[0], 5);
            return;
          }
          break;
        case IterK:
          if(!(t->child[0]->type == Integer && !t->child[0]->array_type && !t->child[0]->func_type))
          {
            printError(t->child[0], 5);
            return;
          }
          break;
        case RetK:
          if(ret_type == Void)
          {
            printError(t, 11);
            return;
          }
          if(ret_type == Integer)
          {
            if(t->child[0] == NULL)
            {
              printError(t, 12);
              return;
            }
            if(!(t->child[0]->type == Integer && !t->child[0]->array_type && !t->child[0]->func_type))
            {
              printError(t, 12);
              return;
            }
            ret_exist = 1;
          }
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      {
        case OpK:
          for(i=0; i<MAXCHILDREN; i++)
            if(t->child[i] != NULL)
            {
              if(!(t->child[i]->type == Integer && !t->child[i]->array_type && !t->child[i]->func_type))
              {
                printError(t, 5);
                return;
              }
            }
          t->type = Integer;
          break;
        case ArrrK:
          if(!(t->child[0]->type == Integer && !t->child[0]->array_type && !t->child[0]->func_type))
          {
            printError(t, 14);
            return;
          }
          break;
        case CallK:
          ft = t->friend;
          if(ft->child[0]->type == Void)
          {
            if(t->child[0] != NULL)
            {
              printError(t, 13);
              return;
            }
          }
          else
          {
            TreeNode * s = t->child[0];
            TreeNode * fs = ft->child[0];
            while(s != NULL && fs != NULL)
            {
              if(fs->kind.decl == VaK)
              {
                if(!(s->type == Integer && !s->array_type && !s->func_type))
                {
                  printError(t, 13);
                  return;
                }
              }
              if(fs->kind.decl == ArrK)
              {
                if(!(s->type == Integer && s->array_type))
                {
                  printError(t, 13);
                  return;
                }
              }
              s = s->sibling;
              fs = fs->sibling;
            }
            if(!(s == NULL && fs == NULL))
            {
              printError(t, 13);
              return;
            }
          }
          break;
        case AssignK:
          if(t->child[1]->type != Integer)
          {
            printError(t, 8);
            return;
          }
          t->type = t->child[0]->type;
          break;
      }
      break;
  }
}

void typeCheck(TreeNode * syntaxTree)
{
  traverse(syntaxTree,check_pre,check_post);
}