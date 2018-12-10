.data
d: .word
a: .word
b: .word


.text
la $t0, a
addi $sp, $sp, -4
sw $t0, 0($sp)
addi $sp, $sp, -4
li $t0, 3
sw $t0, 0($sp)
lw $t0, 0($sp)
lw $t1, 4($sp)
sw $t0, 0($t1)
addi $sp, $sp, 8
la $t0, b
addi $sp, $sp, -4
sw $t0, 0($sp)
li $v0, 5
syscall
addi $sp, $sp, -4
sw $v0, 0($sp)
lw $t0, 0($sp)
lw $t1, 4($sp)
sw $t0, 0($t1)
addi $sp, $sp, 8
la $t0, a
addi $sp, $sp, -4
sw $t0, 0($sp)
li $v0, 5
syscall
addi $sp, $sp, -4
sw $v0, 0($sp)
lw $t0, 0($sp)
lw $t1, 4($sp)
sw $t0, 0($t1)
addi $sp, $sp, 8
la $t0, d
addi $sp, $sp, -4
sw $t0, 0($sp)
addi $sp, $sp, -4
li $t0, 2
sw $t0, 0($sp)
la $t0, a
lw $t1, 0($t0)
addi $sp, $sp, -4
sw $t1, 0($sp)
lw $t0, 0($sp)
lw $t1, 4($sp)
add $t2, $t0, $t1
addi $sp, $sp, 4
sw $t2, 0($sp)
lw $t0, 0($sp)
lw $t1, 4($sp)
sw $t0, 0($t1)
addi $sp, $sp, 8
addi $sp, $sp, -4
li $t0, 0
sw $t0, 0($sp)
lw $t0, 0($sp)
addi $sp, $sp, 4
li $t1, 0
beq $t0, $t1, L0
la $t0, a
addi $sp, $sp, -4
sw $t0, 0($sp)
addi $sp, $sp, -4
li $t0, 3
sw $t0, 0($sp)
lw $t0, 0($sp)
lw $t1, 4($sp)
sw $t0, 0($t1)
addi $sp, $sp, 8
j L1
L0:
la $t0, b
addi $sp, $sp, -4
sw $t0, 0($sp)
addi $sp, $sp, -4
li $t0, 2
sw $t0, 0($sp)
lw $t0, 0($sp)
lw $t1, 4($sp)
sw $t0, 0($t1)
addi $sp, $sp, 8
L1:
