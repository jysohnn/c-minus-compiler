#include "globals.h"
#include "cgen.h"
#define VAL 0
#define ADDR 1
#define GC gen_comment

int print_comment = 1;
int label_num = 0;

void get_label()
{
    char * str = (char *)malloc(sizeof(char) * 20);
    sprintf(str, "L%d", label_num++);
    return str;
}

void gen_comment(char * str)
{
    if(print_comment) fprintf(code, "# %s\n", str);
}

void initCodeGen()
{
    fprintf(data, ".data\n\n");
    fprintf(data, "newline: .asciiz \"\\n\"\n");
    fprintf(data, "output_str: .asciiz \"Output : \"\n");
    fprintf(data, "input_str: .asciiz \"Input : \"\n");

    fprintf(code, ".text\n");
    fprintf(code, ".globl main\n\n");
}

void gen_global_var(DecoNode * t, int mode)
{
    if(mode == VAL) fprintf(code, "lw $v0, %s\n", t->name);
    if(mode == ADDR) fprintf(code, "la $v0, %s\n", t->name);
}

void gen_local_var(DecoNode * t, int mode)
{
    if(mode == VAL) fprintf(code, "lw $v0, %d($sp)\n", t->offset);
    if(mode == ADDR) fprintf(code, "addiu $v0, $sp, %d\n", t->offset);
}

void gen_para_var(DecoNode * t, int mode)
{
    if(mode == VAL) fprintf(code, "lw $v0, %d($sp)\n", t->offset);
    if(mode == ADDR) fprintf(code, "addiu $v0, $sp, %d\n", t->offset);
}

void gen_global_arr(DecoNode * t, int mode)
{
    codeGen(t->child[0]);
    fprintf(code, "li $t0, 4\n");
    fprintf(code, "mul $v0, $v0, $t0\n");
    fprintf(code, "la $t0, %s\n", t->name);
    fprintf(code, "add $t0, $t0, $v0\n");
    if(mode == VAL) fprintf(code, "lw $v0, 0($t0)\n");
    if(mode == ADDR) fprintf(code, "move $v0, $t0\n");
}

void gen_local_arr(DecoNode * t, int mode)
{
    codeGen(t->child[0]);
    fprintf(code, "li $t0, 4\n");
    fprintf(code, "mul $v0, $v0, $t0\n");
    fprintf(code, "addiu $t0, $sp, %d\n", t->offset);
    fprintf(code, "add $t0, $t0, $v0\n");
    if(mode == VAL) fprintf(code, "lw $v0, 0($t0)\n");
    if(mode == ADDR) fprintf(code, "move $v0, $t0\n");
}

void gen_para_arr(DecoNode * t, int mode)
{
    codeGen(t->child[0]);
    fprintf(code, "li $t0, 4\n");
    fprintf(code, "mul $v0, $v0, $t0\n");
    fprintf(code, "lw $t0, %d($sp)\n", t->offset);
    fprintf(code, "add $t0, $t0, $v0\n");
    if(mode == VAL) fprintf(code, "lw $v0, 0($t0)\n");
    if(mode == ADDR) fprintf(code, "move $v0, $t0\n");
}

void codeGen(DecoNode * t)
{
    int already_child = 0;
    int already_sibling = 0;

    if(t == NULL) return;
    switch(t->deco_kind)
    {
        case DEF_GLOBAL_VAR:
            fprintf(data, "%s: .space 4\n", t->name);
            break;
        case DEF_GLOBAL_ARR:
            fprintf(data, "%s: .space %d\n", t->name, t->arr_size * 4);
            break;
        case DEF_FUNC:
            fprintf(code, "%s:\n", t->name);
            // todo : function call -> func commpound
            break;
            
        case GLOBAL_VAR:
            GC(t->name)
            gen_global_var(t, VAL);
            break;
        case GLOBAL_ARR:
            GC(t->name)
            already_child = 1;
            gen_global_arr(t, VAL);
            break;
        case GLOBAL_ARR_NAME:
            GC(t->name)
            gen_global_var(t, ADDR);
            break;
        case LOCAL_VAR:
            GC(t->name)
            gen_local_var(t, VAL);
            break;
        case LOCAL_ARR:
            GC(t->name)
            already_child = 1;
            gen_local_arr(t, VAL);
            break;
        case LOCAL_ARR_NAME:
            GC(t->name)
            gen_global_var(t, ADDR);
            break;
        case PARA_VAR:
            GC(t->name)
            gen_para_var(t, VAL);
            break;
        case PARA_ARR:
            GC(t->name)
            already_child = 1;
            gen_para_arr(t, VAL);
            break;
        case PARA_ARR_NAME:
            GC(t->name)
            fprintf(code, "lw $v0, %d($sp)\n", t->offset);
            break;

        case EXP_OP:
            codeGen(t->child[0]);
            fprintf(code, "addiu $sp, $sp, -4\n");
            fprintf(code, "sw $v0, 0($sp)\n");
            codeGen(t->child[1]);
            fprintf(code, "lw $t0, 0($sp)\n");
            fprintf(code, "addiu $sp, $sp, 4\n");
            fprintf(code, "move $t1, $v0\n");

            switch(t->op_kind)
            {
                case PLUS:
                    fprintf(code, "add $v0, $t0, $t1\n");
                    break;
                case MINUS:
                    fprintf(code, "sub $v0, $t0, $t1\n");
                    break;
                case TIMES:
                    fprintf(code, "mul $v0, $t0, $t1\n");
                    break;
                case OVER:
                    fprintf(code, "div $v0, $t0, $t1\n");
                    break;
                case LE:
                    break;
                case LT:
                    break;
                case GE:
                    break;
                case EQ:
                    break;
                case NE:
                    break;
            }
            break;
        case EXP_CALL:
            break;
        case EXP_ASSIGN:
            break;
        case EXP_NUM:
            break;

        case STMT_COM:
            break;
        case STMT_IF:
            break;
        case STMT_IF_ELSE:
            break;
        case STMT_WHILE:
            break;
        case STMT_RET:
            break;
    }
    if(!already_child)
        for(i=0; i<MAXCHILDREN; i++)
            codeGen(t->child[i]);
    if(!already_sibling)
        codeGen(t->sibling);
}