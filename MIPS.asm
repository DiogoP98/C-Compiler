.data
b: .word 0
a: .word 0
str1: .asciiz "%d"
str2: .asciiz "%d"
newline: .asciiz "\n" 


.text
la $a0, a
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 10
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
la $a0, b
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 5
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
L0:
lw $t0, a
sw $t0, 0($sp)
addi $sp, $sp, -4
li $a0, 1
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sgt $a0, $t0, $a0
sw $a0, 4($sp)
addi $sp, $sp, 4
lw $t0, 0($sp)
beqz $t0, L1
lw $t0, b
sw $t0, 0($sp)
addi $sp, $sp, -4
li $a0, 3
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
seq $a0, $t0, $a0
sw $a0, 4($sp)
addi $sp, $sp, 4
lw $t0, 0($sp)
beqz $t0, L2
la $a0, a
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 0
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
j L3
L2:
la $a0, a
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 20
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
L3:
la $a0, str1
li $v0, 4
syscall
la $a0, newline
li $v0, 4
syscall
lw $a0, a
li $v0, 1
syscall
la $a0, newline
li $v0, 4
syscall
la $a0, a
sw $a0, 0($sp)
addi $sp, $sp, -4
lw $t0, a
sw $t0, 0($sp)
addi $sp, $sp, -4
li $a0, 1
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sub $a0, $t0, $a0
sw $a0, 4($sp)
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
la $a0, b
sw $a0, 0($sp)
addi $sp, $sp, -4
lw $t0, b
sw $t0, 0($sp)
addi $sp, $sp, -4
li $a0, 1
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sub $a0, $t0, $a0
sw $a0, 4($sp)
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
j L0
L1:
la $a0, str2
li $v0, 4
syscall
la $a0, newline
li $v0, 4
syscall
lw $a0, a
li $v0, 1
syscall
la $a0, newline
li $v0, 4
syscall
li $v0, 10
syscall
