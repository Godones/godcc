	.data
a_0: .word 1, 4, 7, 2, 3, 0, 8, 5, 9, 6
str_0: .asciiz "Before quicksort:\n"
str_1: .asciiz "\nAfter quicksort:\n"
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
partion:
	addi $sp, $sp, -72
	sw $a0, 0($sp)
	sw $a1, 4($sp)
	sw $fp, 8($sp)
	sw $ra, 12($sp)
	move $fp, $sp
partion0:
	lw $8, 0($fp)
	la $9, a_0
	mul $8, $8,1
	mul $8, $8,4
	add $9, $9, $8
	lw $10, ($9)
	sw $10, 68($fp)
	j partion1
partion1:
	lw $11, 0($fp)
	lw $12, 4($fp)
	slt $13, $11, $12
	bgtz $13, partion2
	j partion18
	move $14, $15
	mul $3, $3,18
	mul $3, $3,4
	add $14, $14, $3
partion2:
	j partion3
partion3:
	lw $6, 0($fp)
	lw $7, 4($fp)
	slt $24, $6, $7
	lw $25, 4($fp)
	la $8, a_0
	mul $25, $25,1
	mul $25, $25,4
	add $8, $8, $25
	lw $9, ($8)
	lw $10, 68($fp)
	sgt $11, $9, $10
	and $12, $24, $11
	bgtz $12, partion4
	j partion6
	move $14, $13
	mul $15, $15,6
	mul $15, $15,4
	add $14, $14, $15
partion4:
	lw $3, 4($fp)
	sub $6, $3, 1
	sw $6, 4($fp)
	j partion5
partion5:
	j partion3
partion6:
	lw $7, 0($fp)
	lw $25, 4($fp)
	sge $8, $7, $25
	bgtz $8, partion7
	j partion8
	move $14, $10
	mul $9, $9,8
	mul $9, $9,4
	add $14, $14, $9
partion7:
	j partion13
	j partion9
partion8:
	lw $11, 0($fp)
	la $24, a_0
	mul $11, $11,1
	mul $11, $11,4
	add $24, $24, $11
	lw $12, 4($fp)
	la $13, a_0
	mul $12, $12,1
	mul $12, $12,4
	add $13, $13, $12
	lw $15, ($13)
	sw $15, ($24)
	j partion9
partion9:
	j partion10
partion10:
	lw $3, 0($fp)
	lw $6, 4($fp)
	slt $25, $3, $6
	lw $7, 0($fp)
	la $8, a_0
	mul $7, $7,1
	mul $7, $7,4
	add $8, $8, $7
	lw $10, ($8)
	lw $9, 68($fp)
	slt $11, $10, $9
	and $12, $25, $11
	bgtz $12, partion11
	j partion13
	move $14, $13
	mul $24, $24,13
	mul $24, $24,4
	add $14, $14, $24
partion11:
	lw $15, 0($fp)
	add $3, $15, 1
	sw $3, 0($fp)
	j partion12
partion12:
	j partion10
partion13:
	lw $6, 0($fp)
	lw $7, 4($fp)
	sge $8, $6, $7
	bgtz $8, partion14
	j partion15
	move $14, $10
	mul $9, $9,15
	mul $9, $9,4
	add $14, $14, $9
partion14:
	j partion18
	j partion16
partion15:
	lw $11, 4($fp)
	la $25, a_0
	mul $11, $11,1
	mul $11, $11,4
	add $25, $25, $11
	lw $12, 0($fp)
	la $13, a_0
	mul $12, $12,1
	mul $12, $12,4
	add $13, $13, $12
	lw $24, ($13)
	sw $24, ($25)
	j partion16
partion16:
	j partion17
partion17:
	j partion1
partion18:
	lw $15, 0($fp)
	la $3, a_0
	mul $15, $15,1
	mul $15, $15,4
	add $3, $3, $15
	lw $7, 68($fp)
	sw $7, ($3)
	lw $6, 0($fp)
	move $v0, $6
	move $sp, $fp
	lw $ra, 12($sp)
	lw $fp, 8($sp)
	addi $sp, $sp, 72
	jr $ra
	nop
quick:
	addi $sp, $sp, -72
	sw $a0, 0($sp)
	sw $a1, 4($sp)
	sw $fp, 8($sp)
	sw $ra, 12($sp)
	move $fp, $sp
quick0:
	lw $8, 0($fp)
	lw $9, 4($fp)
	sw $8, 16($fp)
	sw $9, 20($fp)
	move $a0, $8
	move $a1, $9
	jal partion
	move $3, $v0
	lw $8, 16($fp)
	lw $9, 20($fp)
	nop
	sw $3, 68($fp)
	lw $6, 68($fp)
	lw $7, 0($fp)
	add $10, $7, 1
	sgt $11, $6, $10
	bgtz $11, quick1
	j quick2
	move $8, $12
	mul $9, $9,2
	mul $9, $9,4
	add $8, $8, $9
quick1:
	lw $13, 0($fp)
	lw $14, 68($fp)
	sub $15, $14, 1
	sw $8, 16($fp)
	sw $13, 36($fp)
	sw $15, 44($fp)
	move $a0, $13
	move $a1, $15
	jal quick
	lw $8, 16($fp)
	lw $13, 36($fp)
	lw $15, 44($fp)
	nop
	j quick2
quick2:
	lw $3, 68($fp)
	lw $6, 4($fp)
	sub $7, $6, 1
	slt $9, $3, $7
	bgtz $9, quick3
	j quick4
	move $8, $10
	mul $11, $11,4
	mul $11, $11,4
	add $8, $8, $11
quick3:
	lw $12, 68($fp)
	add $14, $12, 1
	lw $24, 4($fp)
	sw $8, 16($fp)
	sw $13, 36($fp)
	sw $14, 40($fp)
	sw $15, 44($fp)
	sw $24, 48($fp)
	move $a0, $14
	move $a1, $24
	jal quick
	lw $8, 16($fp)
	lw $13, 36($fp)
	lw $14, 40($fp)
	lw $15, 44($fp)
	lw $24, 48($fp)
	nop
	j quick4
quick4:
	move $sp, $fp
	lw $ra, 12($sp)
	lw $fp, 8($sp)
	addi $sp, $sp, 72
	jr $ra
	nop
quickSort:
	addi $sp, $sp, -64
	sw $a0, 0($sp)
	sw $fp, 4($sp)
	sw $ra, 8($sp)
	move $fp, $sp
quickSort0:
	lw $8, 0($fp)
	sub $9, $8, 1
	sw $9, 16($fp)
	li $a0, 0
	move $a1, $9
	jal quick
	lw $9, 16($fp)
	nop
	move $sp, $fp
	lw $ra, 8($sp)
	lw $fp, 4($sp)
	addi $sp, $sp, 64
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
	li $3, 0
	sw $3, 64($fp)
	j main1
main1:
	lw $6, 64($fp)
	slti $7, $6, 10
	bgtz $7, main2
	j main4
	move $8, $9
	mul $10, $10,4
	mul $10, $10,4
	add $8, $8, $10
main2:
	lw $11, 64($fp)
	la $12, a_0
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
	j main3
main3:
	lw $3, 64($fp)
	add $6, $3, 1
	sw $6, 64($fp)
	j main1
main4:
	sw $8, 8($fp)
	sw $13, 28($fp)
	li $a0, 10
	jal quickSort
	lw $8, 8($fp)
	lw $13, 28($fp)
	nop
	sw $8, 8($fp)
	sw $13, 28($fp)
	la $a0, str_1
	jal Mars_PrintStr
	lw $8, 8($fp)
	lw $13, 28($fp)
	nop
	li $3, 0
	sw $3, 64($fp)
	j main5
main5:
	lw $6, 64($fp)
	slti $7, $6, 10
	bgtz $7, main6
	j main8
	move $8, $9
	mul $10, $10,8
	mul $10, $10,4
	add $8, $8, $10
main6:
	lw $11, 64($fp)
	la $12, a_0
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
	j main7
main7:
	lw $3, 64($fp)
	add $6, $3, 1
	sw $6, 64($fp)
	j main5
main8:
	li $v0, 0
	move $sp, $fp
	lw $ra, 4($sp)
	lw $fp, 0($sp)
	addi $sp, $sp, 68
	jr $ra
	nop
