	.data
str_0: .asciiz "Please Input 16 numbers:\n"
str_1: .asciiz "Array A:\n"
str_2: .asciiz "\n"
str_3: .asciiz "Array B:\n"
str_4: .asciiz "\n"
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
array4_4:
	addi $sp, $sp, -196
	sw $fp, 0($sp)
	sw $ra, 4($sp)
	move $fp, $sp
array4_40:
	la $a0, str_0
	jal Mars_PrintStr
	nop
	li $3, 0
	sw $3, 188($fp)
	j array4_41
array4_41:
	lw $6, 188($fp)
	slti $7, $6, 4
	bgtz $7, array4_42
	j array4_48
	move $8, $9
	mul $10, $10,8
	mul $10, $10,4
	add $8, $8, $10
array4_42:
	li $11, 0
	sw $11, 192($fp)
	j array4_43
array4_43:
	lw $12, 192($fp)
	slti $13, $12, 4
	bgtz $13, array4_44
	j array4_46
	move $8, $14
	mul $15, $15,6
	mul $15, $15,4
	add $8, $8, $15
array4_44:
	lw $24, 188($fp)
	add $25, $zero, $fp
	add $25, $25, 60
	mul $24, $24,4
	mul $24, $24,4
	add $25, $25, $24
	lw $3, 192($fp)
	move $6, $25
	mul $3, $3,1
	mul $3, $3,4
	add $6, $6, $3
	sw $6, 52($fp)
	sw $8, 8($fp)
	jal Mars_GetInt
	move $3, $v0
	lw $6, 52($fp)
	lw $8, 8($fp)
	nop
	sw $3, ($6)
	lw $7, 192($fp)
	li $10, 3
	sub $9, $10, $7
	add $11, $zero, $fp
	add $11, $11, 124
	mul $9, $9,4
	mul $9, $9,4
	add $11, $11, $9
	lw $12, 188($fp)
	move $13, $11
	mul $12, $12,1
	mul $12, $12,4
	add $13, $13, $12
	lw $14, 188($fp)
	add $15, $zero, $fp
	add $15, $15, 60
	mul $14, $14,4
	mul $14, $14,4
	add $15, $15, $14
	lw $24, 192($fp)
	move $25, $15
	mul $24, $24,1
	mul $24, $24,4
	add $25, $25, $24
	lw $6, ($25)
	sw $6, ($13)
	j array4_45
array4_45:
	lw $3, 192($fp)
	add $10, $3, 1
	sw $10, 192($fp)
	j array4_43
array4_46:
	j array4_47
array4_47:
	lw $7, 188($fp)
	add $9, $7, 1
	sw $9, 188($fp)
	j array4_41
array4_48:
	sw $8, 8($fp)
	la $a0, str_1
	jal Mars_PrintStr
	lw $8, 8($fp)
	nop
	li $3, 0
	sw $3, 188($fp)
	j array4_49
array4_49:
	lw $6, 188($fp)
	slti $7, $6, 4
	bgtz $7, array4_410
	j array4_416
	move $8, $9
	mul $10, $10,16
	mul $10, $10,4
	add $8, $8, $10
array4_410:
	li $11, 0
	sw $11, 192($fp)
	j array4_411
array4_411:
	lw $12, 192($fp)
	slti $13, $12, 4
	bgtz $13, array4_412
	j array4_414
	move $8, $14
	mul $15, $15,14
	mul $15, $15,4
	add $8, $8, $15
array4_412:
	lw $24, 188($fp)
	add $25, $zero, $fp
	add $25, $25, 60
	mul $24, $24,4
	mul $24, $24,4
	add $25, $25, $24
	lw $3, 192($fp)
	move $6, $25
	mul $3, $3,1
	mul $3, $3,4
	add $6, $6, $3
	lw $7, ($6)
	sw $7, 56($fp)
	sw $8, 8($fp)
	move $a0, $7
	jal Mars_PrintInt
	lw $7, 56($fp)
	lw $8, 8($fp)
	nop
	j array4_413
array4_413:
	lw $3, 192($fp)
	add $6, $3, 1
	sw $6, 192($fp)
	j array4_411
array4_414:
	sw $7, 56($fp)
	sw $8, 8($fp)
	la $a0, str_2
	jal Mars_PrintStr
	lw $7, 56($fp)
	lw $8, 8($fp)
	nop
	j array4_415
array4_415:
	lw $3, 188($fp)
	add $6, $3, 1
	sw $6, 188($fp)
	j array4_49
array4_416:
	sw $7, 56($fp)
	sw $8, 8($fp)
	la $a0, str_3
	jal Mars_PrintStr
	lw $7, 56($fp)
	lw $8, 8($fp)
	nop
	li $3, 0
	sw $3, 188($fp)
	j array4_417
array4_417:
	lw $6, 188($fp)
	slti $9, $6, 4
	bgtz $9, array4_418
	j array4_424
	move $8, $10
	mul $11, $11,24
	mul $11, $11,4
	add $8, $8, $11
array4_418:
	li $12, 0
	sw $12, 192($fp)
	j array4_419
array4_419:
	lw $13, 192($fp)
	slti $14, $13, 4
	bgtz $14, array4_420
	j array4_422
	move $8, $15
	mul $24, $24,22
	mul $24, $24,4
	add $8, $8, $24
array4_420:
	lw $25, 188($fp)
	add $3, $zero, $fp
	add $3, $3, 124
	mul $25, $25,4
	mul $25, $25,4
	add $3, $3, $25
	lw $6, 192($fp)
	move $9, $3
	mul $6, $6,1
	mul $6, $6,4
	add $9, $9, $6
	lw $10, ($9)
	sw $7, 56($fp)
	sw $8, 8($fp)
	sw $10, 16($fp)
	move $a0, $10
	jal Mars_PrintInt
	lw $7, 56($fp)
	lw $8, 8($fp)
	lw $10, 16($fp)
	nop
	j array4_421
array4_421:
	lw $3, 192($fp)
	add $6, $3, 1
	sw $6, 192($fp)
	j array4_419
array4_422:
	sw $7, 56($fp)
	sw $8, 8($fp)
	sw $10, 16($fp)
	la $a0, str_4
	jal Mars_PrintStr
	lw $7, 56($fp)
	lw $8, 8($fp)
	lw $10, 16($fp)
	nop
	j array4_423
array4_423:
	lw $3, 188($fp)
	add $6, $3, 1
	sw $6, 188($fp)
	j array4_417
array4_424:
	move $sp, $fp
	lw $ra, 4($sp)
	lw $fp, 0($sp)
	addi $sp, $sp, 196
	jr $ra
	nop
main:
	addi $sp, $sp, -60
	sw $fp, 0($sp)
	sw $ra, 4($sp)
	move $fp, $sp
main0:
	jal array4_4
	nop
	li $v0, 0
	move $sp, $fp
	lw $ra, 4($sp)
	lw $fp, 0($sp)
	addi $sp, $sp, 60
	jr $ra
	nop
