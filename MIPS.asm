.data
a: .word
d: .word


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
la $t0, d
addi $sp, $sp, -4
sw $t0, 0($sp)
addi $sp, $sp, -4
li $t0, 10
sw $t0, 0($sp)
lw $t0, 0($sp)
lw $t1, 4($sp)
sw $t0, 0($t1)
addi $sp, $sp, 8
