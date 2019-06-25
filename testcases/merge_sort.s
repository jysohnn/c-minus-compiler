.data

newline: .asciiz "\n"
output_str: .asciiz "Output : "
input_str: .asciiz "Input : "
.align 2
_sorted: .space 40

.text
.globl main

merge:
move $fp, $sp
addiu $sp, $sp, -4
sw $ra, 0($sp)
addiu $sp, $sp, -24
addiu $v0, $fp, -8
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 12($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -12
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -16
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 12($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -24
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -28
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
L0:
lw $v0, -24($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -28($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
mul $v0, $t0, $t1
beq $v0, $zero, L1
addiu $sp, $sp, 0
lw $v0, -8($fp)
li $t0, 4
mul $v0, $v0, $t0
lw $t0, 16($fp)
add $t0, $t0, $v0
lw $v0, 0($t0)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -12($fp)
li $t0, 4
mul $v0, $v0, $t0
lw $t0, 16($fp)
add $t0, $t0, $v0
lw $v0, 0($t0)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
ble $t0, $t1, L4
li $v0, 0
b L5
L4:
li $v0, 1
L5:
beq $v0, $zero, L2
addiu $sp, $sp, 0
lw $v0, -16($fp)
li $t0, 4
mul $v0, $v0, $t0
la $t0, _sorted
add $t0, $t0, $v0
move $v0, $t0
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -8($fp)
li $t0, 4
mul $v0, $v0, $t0
lw $t0, 16($fp)
add $t0, $t0, $v0
lw $v0, 0($t0)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -16
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -16($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
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
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $sp, $sp, 0
b L3
L2:
addiu $sp, $sp, 0
lw $v0, -16($fp)
li $t0, 4
mul $v0, $v0, $t0
la $t0, _sorted
add $t0, $t0, $v0
move $v0, $t0
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -12($fp)
li $t0, 4
mul $v0, $v0, $t0
lw $t0, 16($fp)
add $t0, $t0, $v0
lw $v0, 0($t0)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -16
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -16($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -12
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -12($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $sp, $sp, 0
L3:
lw $v0, -8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 8($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
ble $t0, $t1, L8
li $v0, 0
b L9
L8:
li $v0, 1
L9:
beq $v0, $zero, L6
addiu $v0, $fp, -24
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
b L7
L6:
addiu $v0, $fp, -24
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 0
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
L7:
lw $v0, -12($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 4($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
ble $t0, $t1, L12
li $v0, 0
b L13
L12:
li $v0, 1
L13:
beq $v0, $zero, L10
addiu $v0, $fp, -28
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
b L11
L10:
addiu $v0, $fp, -28
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 0
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
L11:
addiu $sp, $sp, 0
b L0
L1:
lw $v0, -8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 8($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
bgt $t0, $t1, L16
li $v0, 0
b L17
L16:
li $v0, 1
L17:
beq $v0, $zero, L14
addiu $sp, $sp, 0
addiu $v0, $fp, -20
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -12($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
L18:
lw $v0, -20($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 4($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
ble $t0, $t1, L20
li $v0, 0
b L21
L20:
li $v0, 1
L21:
beq $v0, $zero, L19
addiu $sp, $sp, 0
lw $v0, -16($fp)
li $t0, 4
mul $v0, $v0, $t0
la $t0, _sorted
add $t0, $t0, $v0
move $v0, $t0
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -20($fp)
li $t0, 4
mul $v0, $v0, $t0
lw $t0, 16($fp)
add $t0, $t0, $v0
lw $v0, 0($t0)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -16
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -16($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -20
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -20($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $sp, $sp, 0
b L18
L19:
addiu $sp, $sp, 0
b L15
L14:
addiu $sp, $sp, 0
addiu $v0, $fp, -20
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -8($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
L22:
lw $v0, -20($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 8($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
ble $t0, $t1, L24
li $v0, 0
b L25
L24:
li $v0, 1
L25:
beq $v0, $zero, L23
addiu $sp, $sp, 0
lw $v0, -16($fp)
li $t0, 4
mul $v0, $v0, $t0
la $t0, _sorted
add $t0, $t0, $v0
move $v0, $t0
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -20($fp)
li $t0, 4
mul $v0, $v0, $t0
lw $t0, 16($fp)
add $t0, $t0, $v0
lw $v0, 0($t0)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -16
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -16($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -20
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -20($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $sp, $sp, 0
b L22
L23:
addiu $sp, $sp, 0
L15:
addiu $v0, $fp, -20
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 12($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
L26:
lw $v0, -20($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 4($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
ble $t0, $t1, L28
li $v0, 0
b L29
L28:
li $v0, 1
L29:
beq $v0, $zero, L27
addiu $sp, $sp, 0
lw $v0, -20($fp)
li $t0, 4
mul $v0, $v0, $t0
lw $t0, 16($fp)
add $t0, $t0, $v0
move $v0, $t0
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -20($fp)
li $t0, 4
mul $v0, $v0, $t0
la $t0, _sorted
add $t0, $t0, $v0
lw $v0, 0($t0)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -20
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -20($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $sp, $sp, 0
b L26
L27:
addiu $sp, $sp, 24
lw $ra, 0($sp)
addiu $sp, $sp, 4
jr $ra
mergesort:
move $fp, $sp
addiu $sp, $sp, -4
sw $ra, 0($sp)
addiu $sp, $sp, -4
lw $v0, 8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 4($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
blt $t0, $t1, L31
li $v0, 0
b L32
L31:
li $v0, 1
L32:
beq $v0, $zero, L30
addiu $sp, $sp, 0
addiu $v0, $fp, -8
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 4($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
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
li $v0, 2
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
div $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
lw $v0, 12($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
addiu $sp, $sp, -4
sw $fp, 0($sp)
jal mergesort
lw $fp, 0($sp)
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
lw $v0, 12($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 4($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
addiu $sp, $sp, -4
sw $fp, 0($sp)
jal mergesort
lw $fp, 0($sp)
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
lw $v0, 12($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -8($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, 4($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
addiu $sp, $sp, -4
sw $fp, 0($sp)
jal merge
lw $fp, 0($sp)
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 0
L30:
addiu $sp, $sp, 4
lw $ra, 0($sp)
addiu $sp, $sp, 4
jr $ra
main:
move $fp, $sp
addiu $sp, $sp, -4
sw $ra, 0($sp)
addiu $sp, $sp, -48
addiu $v0, $fp, -52
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 10
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $v0, $fp, -48
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 0
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
L33:
lw $v0, -48($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -52($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
blt $t0, $t1, L35
li $v0, 0
b L36
L35:
li $v0, 1
L36:
beq $v0, $zero, L34
addiu $sp, $sp, 0
lw $v0, -48($fp)
li $t0, 4
mul $v0, $v0, $t0
addiu $t0, $fp, -44
add $t0, $t0, $v0
move $v0, $t0
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
addiu $v0, $fp, -48
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -48($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $sp, $sp, 0
b L33
L34:
addiu $v0, $fp, -44
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 0
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -52($fp)
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
jal mergesort
lw $fp, 0($sp)
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $sp, $sp, 4
addiu $v0, $fp, -48
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 0
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
L37:
lw $v0, -48($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -52($fp)
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
blt $t0, $t1, L39
li $v0, 0
b L40
L39:
li $v0, 1
L40:
beq $v0, $zero, L38
addiu $sp, $sp, 0
lw $v0, -48($fp)
li $t0, 4
mul $v0, $v0, $t0
addiu $t0, $fp, -44
add $t0, $t0, $v0
lw $v0, 0($t0)
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
addiu $v0, $fp, -48
addiu $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -48($fp)
addiu $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
add $v0, $t0, $t1
lw $t0, 0($sp)
addiu $sp, $sp, 4
move $t1, $v0
sw $t1, 0($t0)
addiu $sp, $sp, 0
b L37
L38:
addiu $sp, $sp, 48
lw $ra, 0($sp)
addiu $sp, $sp, 4
jr $ra
