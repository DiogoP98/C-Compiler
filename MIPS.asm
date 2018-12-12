.data
a: .word 0
b: .word 0
str1: .asciiz "here"
str2: .asciiz "%d %d"
tab: .asciiz "\t" 


.text
la $a0, a
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 2
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
la $a0, b
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 3
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
lw $t0, a
sw $t0, 0($sp)
addi $sp, $sp, -4
li $a0, 5
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
seq $a0, $a0, $t0
sw $a0, 4($sp)
lw $t0, b
sw $t0, 0($sp)
addi $sp, $sp, -4
li $a0, 4
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
seq $a0, $a0, $t0
sw $a0, 4($sp)
addi $sp, $sp, 4
lw $t0, 4($sp)
sne $t0, $t0, $zero
sne $a0, $a0, $zero
or $a0, $a0, $t0
sw $a0, 4($sp)
addi $sp, $sp, 4
lw $t0, 0($sp)
beqz $t0, L0
la $a0, str1
li $v0, 4
syscall
la $a0, tab
li $v0, 4
syscall
la $a0, a
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 5
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
j L1
L0:
la $a0, b
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 10
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
L1:
la $a0, str2
li $v0, 4
syscall
la $a0, tab
li $v0, 4
syscall
lw $a0, a
li $v0, 1
syscall
la $a0, tab
li $v0, 4
syscall
lw $a0, b
li $v0, 1
syscall
la $a0, tab
li $v0, 4
syscall
li $v0, 10
syscall
