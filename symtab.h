#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include "globals.h"

#define V 0
#define P 1
#define F 2

#define SIZE 211

typedef struct LineListRec
   { int lineno;
     struct LineListRec * next;
   } * LineList;

typedef struct BucketListRec
   { char * name;
     int memloc;
     int var_type;
     int is_array;
     int arr_size;
     int type;
     TreeNode * node;
     LineList lines;
     struct BucketListRec * next;
   } * BucketList;

typedef struct ScopeListRec
{
  int level;
  struct BucketListRec * hashTable[SIZE];
  struct ScopeListRec * next;
} * ScopeList;

void scope_push();

void scope_pop();

void symbol_insert(char * name, int memloc, int var_type, int is_array, int arr_size, int type, int lineno, TreeNode * node);

void symbol_insert_global(char * name, int lineno);

BucketList symbol_lookup(char * name);

BucketList symbol_lookup_global(char * name);

void print_table(FILE * listing);

#endif