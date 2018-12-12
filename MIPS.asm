.data
a: .word 0
str1: .asciiz "%d"
tab: .asciiz "\t" 


.text
la $a0, a
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 10
sw $a0, 0($sp)
addi $sp, $sp, -4
li $a0, 1
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
add $a0, $t0, $a0
sw $a0, 4($sp)
li $a0, 2
sw $a0, 0($sp)
addi $sp, $sp, -4
addi $sp, $sp, 4
lw $t0, 4($sp)
rem $a0, $t0, $a0
sw $a0, 4($sp)
addi $sp, $sp, 4
lw $t0, 4($sp)
sw $a0, 0($t0)
la $a0, str1
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
li $v0, 10
syscall
