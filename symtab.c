#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

#define SHIFT 4

static int hash ( char * key )
{
  int temp = 0;
  int i = 0;
  while (key[i] != '\0')
  { temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}

ScopeList cur_scope = NULL;

void scope_push()
{

  int i;
  ScopeList new_scope = (ScopeList)malloc(sizeof(struct ScopeListRec));
  for(i=0; i<SIZE; i++) new_scope->hashTable[i] = NULL;
  new_scope->local_location_using = 0;
  new_scope->next = NULL;
  
  if(cur_scope == NULL)
  {
    new_scope->level = 0;
    cur_scope = new_scope;
  }
  else
  {
    new_scope->level = cur_scope->level + 1;
    new_scope->next = cur_scope;
    cur_scope = new_scope;
  }
}

void scope_pop()
{
  if(cur_scope != NULL)
  {
    int i;
    for(i=0; i<SIZE; i++)
    {
      BucketList l =  cur_scope->hashTable[i];
      if(l != NULL)
      {
        LineList t = l->lines;
        while(t != NULL)
        {
          LineList tmp = t;
          t = t->next;
          free(tmp);
        }
        free(l);
      }
    }
    ScopeList tmp = cur_scope;
    cur_scope = cur_scope->next;
    free(tmp);
  }
}

void symbol_insert(char * name, int memloc, int var_type, int is_array, int arr_size, int type, int lineno, TreeNode * node)
{
  int h = hash(name);
  BucketList l =  cur_scope->hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0)) l = l->next;
  if (l == NULL)
  {
    l = (BucketList) malloc(sizeof(struct BucketListRec));
    l->name = name;
    l->lines = (LineList) malloc(sizeof(struct LineListRec));
    l->lines->lineno = lineno;
    l->memloc = memloc;
    l->lines->next = NULL;
    l->var_type = var_type;
    l->is_array = is_array;
    l->arr_size = arr_size;
    l->type = type;
    l->node = node;
    l->next = cur_scope->hashTable[h];
    cur_scope->hashTable[h] = l;
  }
}

void symbol_insert_global(char * name, int lineno)
{
  ScopeList s = cur_scope;
  while(s != NULL)
  {
    int h = hash(name);
    BucketList l = s->hashTable[h];
    while ((l != NULL) && (strcmp(name,l->name) != 0)) l = l->next;
    if(l != NULL)
    {
      LineList t = l->lines;
      LineList nt = (LineList) malloc(sizeof(struct LineListRec));
      nt->lineno = lineno;
      nt->next = NULL;
      while(t->next != NULL) t = t->next;
      t->next = nt;
      return;
    }
    s = s->next;
  }
}

BucketList symbol_lookup(char * name)
{
  int h = hash(name);
  if(cur_scope != NULL)
  {
    BucketList l = cur_scope->hashTable[h];
    while ((l != NULL) && (strcmp(name,l->name) != 0)) l = l->next;
    return l;
  }
  return NULL;
}

BucketList symbol_lookup_global(char * name)
{
  ScopeList s = cur_scope;
  while(s != NULL)
  {
    int h = hash(name);
    BucketList l = s->hashTable[h];
    while ((l != NULL) && (strcmp(name,l->name) != 0)) l = l->next;
    if(l != NULL) return l;
    s = s->next;
  }
  return NULL;
}

void print_table(FILE * listing)
{
  int i;
  fprintf(listing,"Name\tScope\tLoc\tV/P/F\tArray?\tArrSize\ttype\tLine Numbers\n");
  fprintf(listing,"------------------------------------------------------------------------\n");
  for(i=0; i<SIZE; i++)
  {
    if(cur_scope->hashTable[i] != NULL)
    {
      BucketList l = cur_scope->hashTable[i];
      while(l != NULL)
      {
        int prev_lineno = -1;
        LineList t = l->lines;
        fprintf(listing, "%s\t", l->name);
        fprintf(listing, "%d\t", cur_scope->level);
        fprintf(listing, "%d\t", l->memloc);
        switch (l->var_type)
        {
        case V:
          fprintf(listing, "Var\t");
          break;
        case P:
          fprintf(listing, "Par\t");
          break;
        case F:
          fprintf(listing, "Func\t");
          break;
        }
        if(l->is_array)
        {
          fprintf(listing, "Array\t");
          fprintf(listing, "%d\t", l->arr_size);
          fprintf(listing, "array\t");
        }
        else
        {
          fprintf(listing, "No\t");
          fprintf(listing, "-\t");
          if(l->type == 0) fprintf(listing, "void\t");
          else fprintf(listing, "int\t");
        }
        while (t != NULL)
        {
          if(t->lineno != prev_lineno) fprintf(listing,"%d\t",t->lineno);
          prev_lineno = t->lineno;
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }
  fprintf(listing,"\n");
}