.data
a: .word
b: .word


.text
la $t0, a
addi $sp, $sp, -4
sw $t0, 0($sp)
la $t0, b
addi $sp, $sp, -4
sw $t0, 0($sp)
