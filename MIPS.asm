.data
b: .word 0
a: .word 0
str1: .asciiz "here"
str2: .asciiz "%d"
newline: .asciiz "\n" 


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
li $a0, 2
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
lw $a0, a
sw $a0, 0($sp)
addi $sp, $sp, -4
lw $a0, b
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sne $a0, $a0, $t0
sw $a0, 4($sp)
addi $sp, $sp, 4
lw $t0, 0($sp)
beqz $t0, L0
la $a0, str1
li $v0, 4
syscall
la $a0, newline
li $v0, 4
syscall
L0:
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
