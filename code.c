#include "globals.h"
#include "code.h"

int func_compound_mem_size;

DecoNode * newDecoNode(DecoKind deco_kind)
{
    DecoNode * t = (DecoNode *)malloc(sizeof(DecoNode));
    if(t != NULL)
    {
        int i;
        for(i=0; i<MAXCHILDREN; i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->deco_kind = deco_kind;
        t->is_func_com = 0;
    }
    return t;
}

DecoNode * copyTree(TreeNode * t)
{
    DecoNode * dt = NULL;
    int already_child = 0;
    int already_sibling = 0;

    if(t != NULL)
    {
        int i;
        if(t->nodekind == DeclK)
        {
            if(t->kind.decl == VaK)
            {
                if(t->var_type == Global)
                {
                    dt = newDecoNode(DEF_GLOBAL_VAR);
                    dt->type = t->type;
                    dt->name = t->name;
                }
            }
            else if(t->kind.decl == ArrK)
            {
                if(t->var_type == Global)
                {
                    dt = newDecoNode(DEF_GLOBAL_ARR);
                    dt->type = t->type;
                    dt->name = t->name;
                    dt->arr_size = t->arr_size;
                }
            }
            else if(t->kind.decl == FuncK)
            {
                dt = newDecoNode(DEF_FUNC);
                dt->type = t->type;
                dt->name = t->name;
                dt->child[0] = copyTree(t->child[1]);
                already_child = 1;
            }
        }
        else if(t->nodekind == StmtK)
        {
            if(t->kind.stmt == ComK)
            {
                dt = newDecoNode(STMT_COM);
                dt->local_var_size = t->compound_mem_size;
                if(t->func_flag)
                {
                    dt->is_func_com = 1;
                    func_compound_mem_size = t->compound_mem_size;
                }
                dt->child[0] = copyTree(t->child[1]);
                already_child = 1;
            }
            else if(t->kind.stmt == SelK)
            {
                if(!t->else_flag) dt = newDecoNode(STMT_IF);
                else dt = newDecoNode(STMT_IF_ELSE);
            }
            else if(t->kind.stmt == IterK) dt = newDecoNode(STMT_WHILE);
            else if(t->kind.stmt == RetK)
            {
                dt = newDecoNode(STMT_RET);
                dt->local_var_size = func_compound_mem_size;
            }
        }
        else if(t->nodekind == ExpK)
        {
            if(t->kind.exp == OpK)
            {
                dt = newDecoNode(EXP_OP);
                dt->op_kind = t->op;
            }
            else if(t->kind.exp == VarK)
            {
                if(t->var_type == Global)
                {
                    if(t->is_array_name) dt = newDecoNode(GLOBAL_ARR_NAME);
                    else dt = newDecoNode(GLOBAL_VAR);
                }
                else if(t->var_type == Local)
                {
                    if(t->is_array_name) dt = newDecoNode(LOCAL_ARR_NAME);
                    else dt = newDecoNode(LOCAL_VAR);
                }
                else if(t->var_type == Para)
                {
                    if(t->is_array_name) dt = newDecoNode(PARA_ARR_NAME);
                    else dt = newDecoNode(PARA_VAR);
                }
                dt->type = t->type;
                dt->name = t->name;
                dt->offset = t->mem_offset;
            }
            else if(t->kind.exp == ArrrK)
            {
                if(t->var_type == Global) dt = newDecoNode(GLOBAL_ARR);
                else if(t->var_type == Local) dt = newDecoNode(LOCAL_ARR);
                else if(t->var_type == Para) dt = newDecoNode(PARA_ARR);
                dt->type = t->type;
                dt->name =t->name;
                dt->offset = t->mem_offset;
            }
            else if(t->kind.exp == NumK)
            {
                dt = newDecoNode(EXP_NUM);
                dt->type = t->type;
                dt->val = t->val;
            }
            else if(t->kind.exp == CallK)
            {
                TreeNode * t_cur = t->child[0];
                DecoNode * dt_cur = NULL;
                DecoNode * dt_prev = NULL;

                dt = newDecoNode(EXP_CALL);
                dt->type = t->type;
                dt->name = t->name;
                
                while(t_cur != NULL)
                {
                    dt_cur = copyTree(t_cur);
                    dt_cur->sibling = dt_prev;
                    dt_prev = dt_cur;
                    t_cur = t_cur->sibling;
                }
                dt->child[0] = dt_cur;
                already_child = 1;
            }
            else if(t->kind.exp == AssignK)
            {
                dt = newDecoNode(EXP_ASSIGN);
                dt->type = t->type;
            }
        }
        if(!already_child)
            for(i=0; i<MAXCHILDREN; i++)
                dt->child[i] = copyTree(t->child[i]);
        if(!already_sibling)
            dt->sibling = copyTree(t->sibling);
    }
    return dt;
}

void printDecoTree(DecoNode * t, int level)
{
    int i;
    if(t == NULL) return;
    for(int i=0; i<level; i++) printf("  ");
    switch(t->deco_kind)
    {
        case DEF_GLOBAL_VAR:
            printf("[DEF_GLOBAL_VAR] type: %d name: %s", t->type, t->name);
            break;
        case DEF_GLOBAL_ARR:
            printf("[DEF_GLOBAL_ARR] type: %d name: %s arr_size: %d", t->type, t->name, t->arr_size);
            break;
        case DEF_FUNC:
            printf("[DEF_FUNC] type: %d name: %s", t->type, t->name);
            break;

        case GLOBAL_VAR:
            printf("[GLOBAL_VAR] type: %d name: %s", t->type, t->name);
            break;
        case GLOBAL_ARR:
            printf("[GLOBAL_ARR] type: %d name: %s", t->type, t->name);
            break;
        case GLOBAL_ARR_NAME:
            printf("[GLOBAL_ARR_NAME] type: %d name: %s", t->type, t->name);
            break;
        case LOCAL_VAR:
            printf("[LOCAL_VAR] type: %d name: %s offset: %d", t->type, t->name, t->offset);
            break;
        case LOCAL_ARR:
            printf("[LOCAL_ARR] type: %d name: %s offset: %d", t->type, t->name, t->offset);
            break;
        case LOCAL_ARR_NAME:
            printf("[LOCAL_ARR_NAME] type: %d name: %s offset: %d", t->type, t->name, t->offset);
            break;
        case PARA_VAR:
            printf("[PARA_VAR] type: %d name: %s offset: %d", t->type, t->name, t->offset);
            break;
        case PARA_ARR:
            printf("[PARA_ARR] type: %d name: %s offset: %d", t->type, t->name, t->offset);
            break;
        case PARA_ARR_NAME:
            printf("[PARA_ARR_NAME] type: %d name: %s offset: %d", t->type, t->name, t->offset);
            break;

        case EXP_OP:
            printf("[EXP_OP] op: %d", t->op_kind);
            break;
        case EXP_CALL:
            printf("[EXP_CALL] type: %d name: %s", t->type, t->name);
            break;
        case EXP_ASSIGN:
            printf("[EXP_ASSIGN] type: %d", t->type);
            break;
        case EXP_NUM:
            printf("[EXP_NUM] type: %d val: %d", t->type, t->val);
            break;

        case STMT_COM:
            printf("[STMT_COM] is_func_com: %d size: %d", t->is_func_com, t->local_var_size);
            break;
        case STMT_IF:
            printf("[STMT_IF]");
            break;
        case STMT_IF_ELSE:
            printf("[STMT_IF_ELSE]");
            break;
        case STMT_WHILE:
            printf("[STMT_WHILE]");
            break;
        case STMT_RET:
            printf("[STMT_RET]");
            break;
    }
    printf("\n");
    for(i=0; i<MAXCHILDREN; i++)
        printDecoTree(t->child[i], level+1);
    printDecoTree(t->sibling, level);
}