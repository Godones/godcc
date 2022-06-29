	.data
str_0: .asciiz "Please input a number:\n"
str_1: .asciiz "This number's fibonacci value is :\n"
	.text
init:
	jal main
	li $v0, 10
	syscall
Mars_PrintInt:
	li $v0, 1
	syscall
	jr $ra
Mars_GetInt:
	li $v0, 5
	syscall
	jr $ra
Mars_PrintStr:
	li $v0, 4
	syscall
	jr $ra
fibonacci:
	addi $sp, $sp, -68
	sw $a0, 0($sp)
	sw $fp, 4($sp)
	sw $ra, 8($sp)
	move $fp, $sp
fibonacci0:
	lw $8, 0($fp)
	slti $9, $8, 1
	bgtz $9, fibonacci1
	j fibonacci2
	move $10, $11
	mul $12, $12,2
	mul $12, $12,4
	add $10, $10, $12
fibonacci1:
	li $13, 0
	sw $13, 64($fp)
	j fibonacci6
fibonacci2:
	lw $14, 0($fp)
	sle $15, $14, 2
	bgtz $15, fibonacci3
	j fibonacci4
	move $10, $3
	mul $6, $6,4
	mul $6, $6,4
	add $10, $10, $6
fibonacci3:
	li $7, 1
	sw $7, 64($fp)
	j fibonacci5
fibonacci4:
	lw $24, 0($fp)
	sub $25, $24, 1
	sw $10, 20($fp)
	sw $25, 48($fp)
	move $a0, $25
	jal fibonacci
	move $3, $v0
	lw $10, 20($fp)
	lw $25, 48($fp)
	nop
	lw $6, 0($fp)
	sub $7, $6, 2
	sw $3, 52($fp)
	sw $7, 60($fp)
	sw $10, 20($fp)
	sw $25, 48($fp)
	move $a0, $7
	jal fibonacci
	move $6, $v0
	lw $3, 52($fp)
	lw $7, 60($fp)
	lw $10, 20($fp)
	lw $25, 48($fp)
	nop
	add $8, $3, $6
	sw $8, 64($fp)
	j fibonacci5
fibonacci5:
	j fibonacci6
fibonacci6:
	lw $9, 64($fp)
	move $v0, $9
	move $sp, $fp
	lw $ra, 8($sp)
	lw $fp, 4($sp)
	addi $sp, $sp, 68
	jr $ra
	nop
get:
	addi $sp, $sp, -60
	sw $fp, 0($sp)
	sw $ra, 4($sp)
	move $fp, $sp
get0:
	li $v0, 1
	move $sp, $fp
	lw $ra, 4($sp)
	lw $fp, 0($sp)
	addi $sp, $sp, 60
	jr $ra
	nop
main:
	addi $sp, $sp, -68
	sw $fp, 0($sp)
	sw $ra, 4($sp)
	move $fp, $sp
main0:
	la $a0, str_0
	jal Mars_PrintStr
	nop
	jal Mars_GetInt
	move $3, $v0
	nop
	sw $3, 60($fp)
	lw $6, 60($fp)
	sw $6, 52($fp)
	move $a0, $6
	jal fibonacci
	move $3, $v0
	lw $6, 52($fp)
	nop
	sw $3, 64($fp)
	sw $6, 52($fp)
	la $a0, str_1
	jal Mars_PrintStr
	lw $6, 52($fp)
	nop
	lw $3, 64($fp)
	sw $3, 48($fp)
	sw $6, 52($fp)
	move $a0, $3
	jal Mars_PrintInt
	lw $3, 48($fp)
	lw $6, 52($fp)
	nop
	li $v0, 0
	move $sp, $fp
	lw $ra, 4($sp)
	lw $fp, 0($sp)
	addi $sp, $sp, 68
	jr $ra
	nop
