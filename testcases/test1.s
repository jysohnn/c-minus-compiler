.data

newline: .asciiz "\n"
output_str: .asciiz "Output : "
input_str: .asciiz "Input : "
.align 2

.text
.globl main

gcd:
# COM STMT
move $fp, $sp
addiu $sp, $sp, -4
sw $ra, 0($sp)
addiu $sp, $sp, 0
# IF
# PARA VAR y
lw $v0, 4($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 0
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
beq $t0, $t1, L1
li $v0, 0
b L2
L1:
li $v0, 1
L2:
beq $v0, $zero, L0
# RETURN
# PARA VAR x
lw $v0, 8($fp)
move $sp, $fp
lw $ra, -4($sp)
jr $ra
L0:
# RETURN
# CALL gcd
# PARA 0
# PARA VAR y
lw $v0, 4($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
# PARA 1
# PARA VAR x
lw $v0, 8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
# PARA VAR x
lw $v0, 8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
# PARA VAR y
lw $v0, 4($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
div $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
# PARA VAR y
lw $v0, 4($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
mul $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sub $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
addiu $sp, $sp, -4
sw $fp, 0($sp)
jal gcd
lw $fp, 0($sp)
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
move $sp, $fp
lw $ra, -4($sp)
jr $ra
addiu $sp, $sp, 0
lw $ra, 0($sp)
addiu $sp, $sp, 4
jr $ra
main:
# COM STMT
move $fp, $sp
addiu $sp, $sp, -4
sw $ra, 0($sp)
addiu $sp, $sp, -8
# ASSIGN
# LOCAL VAR a
addiu $v0, $fp, -8
addiu $sp, $sp, -4
sw $v0, 0($sp)
# CALL input
li $v0, 4
la $a0, input_str
syscall
li $v0, 5
syscall
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
# ASSIGN
# LOCAL VAR b
addiu $v0, $fp, -12
addiu $sp, $sp, -4
sw $v0, 0($sp)
# CALL input
li $v0, 4
la $a0, input_str
syscall
li $v0, 5
syscall
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
# CALL output
# CALL gcd
# PARA 0
# LOCAL VAR a
lw $v0, -8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
# PARA 1
# LOCAL VAR b
lw $v0, -12($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
addiu $sp, $sp, -4
sw $fp, 0($sp)
jal gcd
lw $fp, 0($sp)
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
move $t0, $v0
li $v0, 4
la $a0, output_str
syscall
move $a0, $t0
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall
addiu $sp, $sp, 8
lw $ra, 0($sp)
addiu $sp, $sp, 4
jr $ra
