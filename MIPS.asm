.data
d: .word
a: .word
b: .word


.text
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
