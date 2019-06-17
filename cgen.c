#include "globals.h"
#include "cgen.h"
#define VAL 0
#define ADDR 1
#define GC gen_comment

int print_comment = 0;
int label_num = 0;

char * get_label()
{
    char * str = (char *)malloc(sizeof(char) * 20);
    sprintf(str, "L%d", label_num++);
    return str;
}

void initCodeGen()
{
    fprintf(data, ".data\n\n");
    fprintf(data, "newline: .asciiz \"\\n\"\n");
    fprintf(data, "output_str: .asciiz \"Output : \"\n");
    fprintf(data, "input_str: .asciiz \"Input : \"\n");
    fprintf(data, ".align 2\n");

    fprintf(code, ".text\n");
    fprintf(code, ".globl main\n\n");
}

void gen_comment(char * str)
{
    if(print_comment) fprintf(code, "# %s\n", str);
}

void gen_global_var(DecoNode * t, int mode)
{
    if(mode == VAL) fprintf(code, "lw $v0, _%s\n", t->name);
    if(mode == ADDR) fprintf(code, "la $v0, _%s\n", t->name);
}

void gen_local_var(DecoNode * t, int mode)
{
    if(mode == VAL) fprintf(code, "lw $v0, %d($fp)\n", t->offset);
    if(mode == ADDR) fprintf(code, "addiu $v0, $fp, %d\n", t->offset);
}

void gen_para_var(DecoNode * t, int mode)
{
    if(mode == VAL) fprintf(code, "lw $v0, %d($fp)\n", t->offset);
    if(mode == ADDR) fprintf(code, "addiu $v0, $fp, %d\n", t->offset);
}

void gen_global_arr(DecoNode * t, int mode)
{
    codeGen(t->child[0], 0, 0);
    fprintf(code, "li $t0, 4\n");
    fprintf(code, "mul $v0, $v0, $t0\n");
    fprintf(code, "la $t0, _%s\n", t->name);
    fprintf(code, "add $t0, $t0, $v0\n");
    if(mode == VAL) fprintf(code, "lw $v0, 0($t0)\n");
    if(mode == ADDR) fprintf(code, "move $v0, $t0\n");
}

void gen_local_arr(DecoNode * t, int mode)
{
    codeGen(t->child[0], 0, 0);
    fprintf(code, "li $t0, 4\n");
    fprintf(code, "mul $v0, $v0, $t0\n");
    fprintf(code, "addiu $t0, $fp, %d\n", t->offset);
    fprintf(code, "add $t0, $t0, $v0\n");
    if(mode == VAL) fprintf(code, "lw $v0, 0($t0)\n");
    if(mode == ADDR) fprintf(code, "move $v0, $t0\n");
}

void gen_para_arr(DecoNode * t, int mode)
{
    codeGen(t->child[0], 0, 0);
    fprintf(code, "li $t0, 4\n");
    fprintf(code, "mul $v0, $v0, $t0\n");
    fprintf(code, "lw $t0, %d($fp)\n", t->offset);
    fprintf(code, "add $t0, $t0, $v0\n");
    if(mode == VAL) fprintf(code, "lw $v0, 0($t0)\n");
    if(mode == ADDR) fprintf(code, "move $v0, $t0\n");
}

void gen_compare_op(char* op)
{
    char * label = get_label();
    char * label2 = get_label();
    fprintf(code, "%s $t0, $t1, %s\n", op, label);
    fprintf(code, "li $v0, 0\n");
    fprintf(code, "b %s\n", label2);
    fprintf(code, "%s:\n", label);
    fprintf(code, "li $v0, 1\n");
    fprintf(code, "%s:\n", label2);
}

void codeGen(DecoNode * t, int ac, int as)
{
    int i;
    int already_child = ac;
    int already_sibling = as;
    char * label;
    char * label2;
    char tmp_str[100];

    if(t == NULL) return;
    switch(t->deco_kind)
    {
        case DEF_GLOBAL_VAR:
            fprintf(data, "_%s: .space 4\n", t->name);
            break;
        case DEF_GLOBAL_ARR:
            fprintf(data, "_%s: .space %d\n", t->name, t->arr_size * 4);
            break;
        case DEF_FUNC:
            fprintf(code, "%s:\n", t->name);
            break;
            
        case GLOBAL_VAR:
            sprintf(tmp_str, "GLOBAL VAR %s", t->name);
            GC(tmp_str);
            gen_global_var(t, VAL);
            break;
        case GLOBAL_ARR:
            sprintf(tmp_str, "GLOBAL ARR %s", t->name);
            GC(tmp_str);
            already_child = 1;
            gen_global_arr(t, VAL);
            break;
        case GLOBAL_ARR_NAME:
            sprintf(tmp_str, "GLOBAL ARR NAME %s", t->name);
            GC(tmp_str);
            gen_global_var(t, ADDR);
            break;
        case LOCAL_VAR:
            sprintf(tmp_str, "LOCAL VAR %s", t->name);
            GC(tmp_str);
            gen_local_var(t, VAL);
            break;
        case LOCAL_ARR:
            sprintf(tmp_str, "LOCAL ARR %s", t->name);
            GC(tmp_str);
            already_child = 1;
            gen_local_arr(t, VAL);
            break;
        case LOCAL_ARR_NAME:
            sprintf(tmp_str, "LOCAL ARR NAME %s", t->name);
            GC(tmp_str);
            gen_local_var(t, ADDR);
            break;
        case PARA_VAR:
            sprintf(tmp_str, "PARA VAR %s", t->name);
            GC(tmp_str);
            gen_para_var(t, VAL);
            break;
        case PARA_ARR:
            sprintf(tmp_str, "PARA ARR %s", t->name);
            GC(tmp_str);
            already_child = 1;
            gen_para_arr(t, VAL);
            break;
        case PARA_ARR_NAME:
            sprintf(tmp_str, "PARA ARR NAME %s", t->name);
            GC(tmp_str);
            fprintf(code, "lw $v0, %d($fp)\n", t->offset);
            break;

        case EXP_OP:
            already_child = 1;
            codeGen(t->child[0], 0, 0);
            fprintf(code, "addiu $sp, $sp, -4\n");
            fprintf(code, "sw $v0, 0($sp)\n");
            codeGen(t->child[1], 0, 0);
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
                    gen_compare_op("ble");
                    break;
                case LT:
                    gen_compare_op("blt");
                    break;
                case GE:
                    gen_compare_op("bge");
                    break;
                case GT:
                    gen_compare_op("bgt");
                    break;
                case EQ:
                    gen_compare_op("beq");
                    break;
                case NE:
                    gen_compare_op("bne");
                    break;
            }
            break;
        case EXP_CALL:
            sprintf(tmp_str, "CALL %s", t->name);
            GC(tmp_str);
            already_child = 1;

            if(!strcmp(t->name, "input"))
            {
                fprintf(code, "li $v0, 4\n");
                fprintf(code, "la $a0, input_str\n");
                fprintf(code, "syscall\n");

                fprintf(code, "li $v0, 5\n");
                fprintf(code, "syscall\n");
                break;
            }
            if(!strcmp(t->name, "output"))
            {
                codeGen(t->child[0], 0, 0);
                fprintf(code, "move $t0, $v0\n");
                fprintf(code, "li $v0, 4\n");
                fprintf(code, "la $a0, output_str\n");
                fprintf(code, "syscall\n");
                fprintf(code, "move $a0, $t0\n");
                fprintf(code, "li $v0, 1\n");
                fprintf(code, "syscall\n");
                fprintf(code, "li $v0, 4\n");
                fprintf(code, "la $a0, newline\n");
                fprintf(code, "syscall\n");
                break;
            }

            DecoNode * s = t->child[0];
            i = 0;
            while(s != NULL)
            {
                sprintf(tmp_str, "PARA %d", i);
                GC(tmp_str);

                codeGen(s, 0, 1);
                fprintf(code, "addiu $sp, $sp, -4\n");
                fprintf(code, "sw $v0, 0($sp)\n");
                s = s->sibling;
                i++;
            }

            fprintf(code, "addiu $sp, $sp, -4\n");
            fprintf(code, "sw $fp, 0($sp)\n");
            fprintf(code, "jal %s\n", t->name);
            fprintf(code, "lw $fp, 0($sp)\n");
            fprintf(code, "addiu $sp, $sp, 4\n");

            s = t->child[0];
            while(s != NULL)
            {
                fprintf(code, "addiu $sp, $sp, 4\n");
                s = s->sibling;
            }
            break;
        case EXP_ASSIGN:
            GC("ASSIGN");
            already_child = 1;
            switch(t->child[0]->deco_kind)
            {
                case GLOBAL_VAR:
                    sprintf(tmp_str, "GLOBAL VAR %s", t->child[0]->name);
                    GC(tmp_str);
                    gen_global_var(t->child[0], ADDR);
                    break;
                case GLOBAL_ARR:
                    sprintf(tmp_str, "GLOBAL ARR %s", t->child[0]->name);
                    GC(tmp_str);
                    gen_global_arr(t->child[0], ADDR);
                    break;
                case LOCAL_VAR:
                    sprintf(tmp_str, "LOCAL VAR %s", t->child[0]->name);
                    GC(tmp_str);
                    gen_local_var(t->child[0], ADDR);
                    break;
                case LOCAL_ARR:
                    sprintf(tmp_str, "LOCAL ARR %s", t->child[0]->name);
                    GC(tmp_str);
                    gen_local_arr(t->child[0], ADDR);
                    break;
                case PARA_VAR:
                    sprintf(tmp_str, "PARA VAR %s", t->child[0]->name);
                    GC(tmp_str);
                    gen_para_var(t->child[0], ADDR);
                    break;
                case PARA_ARR:
                    sprintf(tmp_str, "PARA ARR %s", t->child[0]->name);
                    GC(tmp_str);
                    gen_para_arr(t->child[0], ADDR);
                    break;
            }
            fprintf(code, "addiu $sp, $sp, -4\n");
            fprintf(code, "sw $v0, 0($sp)\n");
            codeGen(t->child[1], 0, 0);
            fprintf(code, "lw $t0, 0($sp)\n");
            fprintf(code, "addiu $sp, $sp, 4\n");
            fprintf(code, "move $t1, $v0\n");
            fprintf(code, "sw $t1, 0($t0)\n");
            break;
        case EXP_NUM:
            fprintf(code, "li $v0, %d\n", t->val);
            break;

        case STMT_COM:
            GC("COM STMT");
            already_child = 1;
            if(t->is_func_com)
            {
                fprintf(code, "move $fp, $sp\n");
                fprintf(code, "addiu $sp, $sp, -4\n");
                fprintf(code, "sw $ra, 0($sp)\n");
            }
            fprintf(code, "addiu $sp, $sp, %d\n", t->local_var_size);
            codeGen(t->child[0], 0, 0);
            fprintf(code, "addiu $sp, $sp, %d\n", -1 * t->local_var_size);
            if(t->is_func_com)
            {
                fprintf(code, "lw $ra, 0($sp)\n");
                fprintf(code, "addiu $sp, $sp, 4\n");
                fprintf(code, "jr $ra\n");
            }
            break;
        case STMT_IF:
            GC("IF");
            already_child = 1;
            label = get_label();
            codeGen(t->child[0], 0, 0);
            fprintf(code, "beq $v0, $zero, %s\n", label);
            codeGen(t->child[1], 0, 0);
            fprintf(code, "%s:\n", label);
            break;
        case STMT_IF_ELSE:
            GC("IF ELSE");
            already_child = 1;
            label = get_label();
            label2 = get_label();
            codeGen(t->child[0], 0, 0);
            fprintf(code, "beq $v0, $zero, %s\n", label);
            codeGen(t->child[1], 0, 0);
            fprintf(code, "b %s\n", label2);
            fprintf(code, "%s:\n", label);
            codeGen(t->child[2], 0, 0);
            fprintf(code, "%s:\n", label2);
            break;
        case STMT_WHILE:
            GC("WHILE");
            already_child = 1;
            label = get_label();
            label2 = get_label();
            fprintf(code, "%s:\n", label);
            codeGen(t->child[0], 0, 0);
            fprintf(code, "beq $v0, $zero, %s\n", label2);
            codeGen(t->child[1], 0, 0);
            fprintf(code, "b %s\n", label);
            fprintf(code, "%s:\n", label2);
            break;
        case STMT_RET:
            GC("RETURN");
            already_child = 1;
            codeGen(t->child[0], 0, 0);
            fprintf(code, "move $sp, $fp\n");
            fprintf(code, "lw $ra, -4($sp)\n");
            fprintf(code, "jr $ra\n");
            break;
    }
    if(!already_child)
        for(i=0; i<MAXCHILDREN; i++)
            codeGen(t->child[i], 0, 0);
    if(!already_sibling)
        codeGen(t->sibling, 0, 0);
}