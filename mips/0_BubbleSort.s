	.data
str_0: .asciiz "please input ten int number for bubble sort:\n"
str_1: .asciiz "before bubble sort:\n"
str_2: .asciiz "\n"
str_3: .asciiz "after bubble sort:\n"
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
main:
	addi $sp, $sp, -124
	sw $fp, 0($sp)
	sw $ra, 4($sp)
	move $fp, $sp
main0:
	la $a0, str_0
	jal Mars_PrintStr
	nop
	li $3, 0
	sw $3, 120($fp)
	j main1
main1:
	lw $6, 120($fp)
	slti $7, $6, 10
	bgtz $7, main2
	j main4
	move $8, $9
	mul $10, $10,4
	mul $10, $10,4
	add $8, $8, $10
main2:
	lw $11, 120($fp)
	add $12, $zero, $fp
	add $12, $12, 60
	mul $11, $11,1
	mul $11, $11,4
	add $12, $12, $11
	sw $8, 8($fp)
	sw $12, 24($fp)
	jal Mars_GetInt
	move $3, $v0
	lw $8, 8($fp)
	lw $12, 24($fp)
	nop
	sw $3, ($12)
	j main3
main3:
	lw $6, 120($fp)
	add $7, $6, 1
	sw $7, 120($fp)
	j main1
main4:
	sw $8, 8($fp)
	la $a0, str_1
	jal Mars_PrintStr
	lw $8, 8($fp)
	nop
	li $3, 0
	sw $3, 120($fp)
	j main5
main5:
	lw $6, 120($fp)
	slti $7, $6, 10
	bgtz $7, main6
	j main8
	move $8, $9
	mul $10, $10,8
	mul $10, $10,4
	add $8, $8, $10
main6:
	lw $11, 120($fp)
	add $12, $zero, $fp
	add $12, $12, 60
	mul $11, $11,1
	mul $11, $11,4
	add $12, $12, $11
	lw $13, ($12)
	sw $8, 8($fp)
	sw $13, 28($fp)
	move $a0, $13
	jal Mars_PrintInt
	lw $8, 8($fp)
	lw $13, 28($fp)
	nop
	j main7
main7:
	lw $3, 120($fp)
	add $6, $3, 1
	sw $6, 120($fp)
	j main5
main8:
	sw $8, 8($fp)
	sw $13, 28($fp)
	la $a0, str_2
	jal Mars_PrintStr
	lw $8, 8($fp)
	lw $13, 28($fp)
	nop
	li $3, 0
	sw $3, 120($fp)
	j main9
main9:
	lw $6, 120($fp)
	slti $7, $6, 10
	bgtz $7, main10
	j main18
	move $8, $9
	mul $10, $10,18
	mul $10, $10,4
	add $8, $8, $10
main10:
	li $11, 0
	sw $11, 112($fp)
	j main11
main11:
	lw $12, 112($fp)
	lw $14, 120($fp)
	li $24, 10
	sub $15, $24, $14
	sub $25, $15, 1
	slt $3, $12, $25
	bgtz $3, main12
	j main16
	move $8, $6
	mul $7, $7,16
	mul $7, $7,4
	add $8, $8, $7
main12:
	lw $9, 112($fp)
	add $10, $zero, $fp
	add $10, $10, 60
	mul $9, $9,1
	mul $9, $9,4
	add $10, $10, $9
	lw $11, ($10)
	lw $24, 112($fp)
	add $14, $24, 1
	add $15, $zero, $fp
	add $15, $15, 60
	mul $14, $14,1
	mul $14, $14,4
	add $15, $15, $14
	lw $12, ($15)
	sgt $25, $11, $12
	bgtz $25, main13
	j main14
	move $8, $3
	mul $6, $6,14
	mul $6, $6,4
	add $8, $8, $6
main13:
	lw $7, 112($fp)
	add $9, $zero, $fp
	add $9, $9, 60
	mul $7, $7,1
	mul $7, $7,4
	add $9, $9, $7
	lw $10, ($9)
	sw $10, 116($fp)
	lw $24, 112($fp)
	add $14, $zero, $fp
	add $14, $14, 60
	mul $24, $24,1
	mul $24, $24,4
	add $14, $14, $24
	lw $15, 112($fp)
	add $12, $15, 1
	add $11, $zero, $fp
	add $11, $11, 60
	mul $12, $12,1
	mul $12, $12,4
	add $11, $11, $12
	lw $25, ($11)
	sw $25, ($14)
	lw $3, 112($fp)
	add $6, $3, 1
	add $7, $zero, $fp
	add $7, $7, 60
	mul $6, $6,1
	mul $6, $6,4
	add $7, $7, $6
	lw $9, 116($fp)
	sw $9, ($7)
	j main14
main14:
	j main15
main15:
	lw $10, 112($fp)
	add $24, $10, 1
	sw $24, 112($fp)
	j main11
main16:
	j main17
main17:
	lw $15, 120($fp)
	add $12, $15, 1
	sw $12, 120($fp)
	j main9
main18:
	sw $8, 8($fp)
	sw $13, 28($fp)
	la $a0, str_3
	jal Mars_PrintStr
	lw $8, 8($fp)
	lw $13, 28($fp)
	nop
	li $3, 0
	sw $3, 120($fp)
	j main19
main19:
	lw $6, 120($fp)
	slti $7, $6, 10
	bgtz $7, main20
	j main22
	move $8, $9
	mul $10, $10,22
	mul $10, $10,4
	add $8, $8, $10
main20:
	lw $11, 120($fp)
	add $12, $zero, $fp
	add $12, $12, 60
	mul $11, $11,1
	mul $11, $11,4
	add $12, $12, $11
	lw $14, ($12)
	sw $8, 8($fp)
	sw $13, 28($fp)
	sw $14, 32($fp)
	move $a0, $14
	jal Mars_PrintInt
	lw $8, 8($fp)
	lw $13, 28($fp)
	lw $14, 32($fp)
	nop
	j main21
main21:
	lw $3, 120($fp)
	add $6, $3, 1
	sw $6, 120($fp)
	j main19
main22:
	li $v0, 0
	move $sp, $fp
	lw $ra, 4($sp)
	lw $fp, 0($sp)
	addi $sp, $sp, 124
	jr $ra
	nop
