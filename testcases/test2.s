.data

newline: .asciiz "\n"
output_str: .asciiz "Output : "
input_str: .asciiz "Input : "
.align 2
_sol: .space 4

.text
.globl main

fibonacci:
move $fp, $sp
addiu $sp, $sp, -4
sw $ra, 0($sp)
addiu $sp, $sp, 0
lw $v0, 4($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 0
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
ble $t0, $t1, L2
li $v0, 0
b L3
L2:
li $v0, 1
L3:
beq $v0, $zero, L0
li $v0, 0
move $sp, $fp
lw $ra, -4($sp)
jr $ra
b L1
L0:
lw $v0, 4($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
beq $t0, $t1, L6
li $v0, 0
b L7
L6:
li $v0, 1
L7:
beq $v0, $zero, L4
li $v0, 1
move $sp, $fp
lw $ra, -4($sp)
jr $ra
b L5
L4:
lw $v0, 4($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 2
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
beq $t0, $t1, L10
li $v0, 0
b L11
L10:
li $v0, 1
L11:
beq $v0, $zero, L8
li $v0, 1
move $sp, $fp
lw $ra, -4($sp)
jr $ra
b L9
L8:
lw $v0, 4($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sub $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
addiu $sp, $sp, -4
sw $fp, 0($sp)
jal fibonacci
lw $fp, 0($sp)
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 4($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 2
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sub $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
addiu $sp, $sp, -4
sw $fp, 0($sp)
jal fibonacci
lw $fp, 0($sp)
addiu $sp, $sp, 4
addiu $sp, $sp, 4
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
move $sp, $fp
lw $ra, -4($sp)
jr $ra
L9:
L5:
L1:
addiu $sp, $sp, 0
lw $ra, 0($sp)
addiu $sp, $sp, 4
jr $ra
main:
move $fp, $sp
addiu $sp, $sp, -4
sw $ra, 0($sp)
addiu $sp, $sp, -4
addiu $v0, $fp, -8
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 4
la $a0, input_str
syscall
li $v0, 5
syscall
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
la $v0, _sol
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
addiu $sp, $sp, -4
sw $fp, 0($sp)
jal fibonacci
lw $fp, 0($sp)
addiu $sp, $sp, 4
addiu $sp, $sp, 4
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
lw $v0, _sol
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
addiu $sp, $sp, 4
lw $ra, 0($sp)
addiu $sp, $sp, 4
jr $ra
