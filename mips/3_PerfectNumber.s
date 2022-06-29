	.data
str_0: .asciiz " "
str_1: .asciiz "The sum is :\n"
str_2: .asciiz "All perfect numbers within 100:\n"
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
perfectNumber:
	addi $sp, $sp, -404
	sw $a0, 0($sp)
	sw $fp, 4($sp)
	sw $ra, 8($sp)
	move $fp, $sp
perfectNumber0:
	li $8, 0
	sw $8, 400($fp)
	li $9, 2
	sw $9, 388($fp)
	j perfectNumber1
perfectNumber1:
	lw $10, 388($fp)
	lw $11, 0($fp)
	slt $12, $10, $11
	bgtz $12, perfectNumber2
	j perfectNumber12
	move $13, $14
	mul $15, $15,12
	mul $15, $15,4
	add $13, $13, $15
perfectNumber2:
	li $3, 0
	sw $3, 392($fp)
	lw $6, 388($fp)
	sw $6, 396($fp)
	li $7, 1
	sw $7, 384($fp)
	j perfectNumber3
perfectNumber3:
	lw $24, 384($fp)
	lw $25, 388($fp)
	div $8, $25, 2
	add $9, $8, 1
	slt $10, $24, $9
	bgtz $10, perfectNumber4
	j perfectNumber8
	move $13, $11
	mul $12, $12,8
	mul $12, $12,4
	add $13, $13, $12
perfectNumber4:
	lw $14, 388($fp)
	lw $15, 384($fp)
	rem $3, $14, $15
	seq $6, $3, 0
	bgtz $6, perfectNumber5
	j perfectNumber6
	move $13, $7
	mul $25, $25,6
	mul $25, $25,4
	add $13, $13, $25
perfectNumber5:
	lw $8, 392($fp)
	add $24, $8, 1
	sw $24, 392($fp)
	add $9, $zero, $fp
	add $9, $9, 64
	mul $10, $10,1
	mul $10, $10,4
	add $9, $9, $10
	lw $11, 384($fp)
	sw $11, ($9)
	lw $12, 396($fp)
	lw $15, 384($fp)
	sub $14, $12, $15
	sw $14, 396($fp)
	j perfectNumber6
perfectNumber6:
	j perfectNumber7
perfectNumber7:
	lw $3, 384($fp)
	add $6, $3, 1
	sw $6, 384($fp)
	j perfectNumber3
perfectNumber8:
	lw $7, 396($fp)
	seq $25, $7, 0
	bgtz $25, perfectNumber9
	j perfectNumber10
	move $13, $8
	mul $24, $24,10
	mul $24, $24,4
	add $13, $13, $24
perfectNumber9:
	lw $10, 388($fp)
	sw $10, 20($fp)
	sw $13, 32($fp)
	move $a0, $10
	jal Mars_PrintInt
	lw $10, 20($fp)
	lw $13, 32($fp)
	nop
	sw $10, 20($fp)
	sw $13, 32($fp)
	la $a0, str_0
	jal Mars_PrintStr
	lw $10, 20($fp)
	lw $13, 32($fp)
	nop
	lw $3, 400($fp)
	add $6, $3, 1
	sw $6, 400($fp)
	j perfectNumber10
perfectNumber10:
	j perfectNumber11
perfectNumber11:
	lw $7, 388($fp)
	add $8, $7, 1
	sw $8, 388($fp)
	j perfectNumber1
perfectNumber12:
	sw $10, 20($fp)
	sw $13, 32($fp)
	la $a0, str_1
	jal Mars_PrintStr
	lw $10, 20($fp)
	lw $13, 32($fp)
	nop
	lw $3, 400($fp)
	sw $3, 52($fp)
	sw $10, 20($fp)
	sw $13, 32($fp)
	move $a0, $3
	jal Mars_PrintInt
	lw $3, 52($fp)
	lw $10, 20($fp)
	lw $13, 32($fp)
	nop
	move $sp, $fp
	lw $ra, 8($sp)
	lw $fp, 4($sp)
	addi $sp, $sp, 404
	jr $ra
	nop
main:
	addi $sp, $sp, -60
	sw $fp, 0($sp)
	sw $ra, 4($sp)
	move $fp, $sp
main0:
	la $a0, str_2
	jal Mars_PrintStr
	nop
	li $a0, 100
	jal perfectNumber
	nop
	li $v0, 0
	move $sp, $fp
	lw $ra, 4($sp)
	lw $fp, 0($sp)
	addi $sp, $sp, 60
	jr $ra
	nop
