.data

newline: .asciiz "\n"
output_str: .asciiz "Output : "
input_str: .asciiz "Input : "
.align 2

.text
.globl main

main:
move $fp, $sp
addiu $sp, $sp, -4
sw $ra, 0($sp)
addiu $sp, $sp, -16
addiu $v0, $fp, -8
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -12
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 2
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -16
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 3
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -20
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 4
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -8
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -12($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -16($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -20($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 5
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 6
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 7
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 8
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 9
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
mul $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
lw $v0, -8($fp)
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
addiu $v0, $fp, -12
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -16($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -20($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
mul $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -12($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sub $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
lw $v0, -12($fp)
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
addiu $v0, $fp, -16
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -20($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -16($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sub $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
div $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
lw $v0, -16($fp)
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
addiu $v0, $fp, -20
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -12($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
div $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -16($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -16($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
mul $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sub $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
lw $v0, -20($fp)
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
addiu $sp, $sp, 16
lw $ra, 0($sp)
addiu $sp, $sp, 4
jr $ra
