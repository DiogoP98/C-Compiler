.data
a: .word 0
b: .word 0
str1: .asciiz "%d"
newline: .asciiz "\n" 


.text
la $a0, a
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 3
sw $a0, -4($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
la $a0, b
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 5
sw $a0, -4($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
la $a0, str1
sw $a0, 0($sp)
addi $sp, $sp, -4
la $a0, sp
li $v0, 4
syscall
addi $sp, $sp, 4
lw $a0, 0($a)
sw $a0, 0($sp)
addi $sp, $sp, -4
lw $a0, 0($sp)
li $v0, 1
syscall
addi $sp, $sp, 4
li $v0, 10
syscall
