	.data
str_0: .asciiz "\n"
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
YangHuiTriangle:
	addi $sp, $sp, -324
	sw $fp, 0($sp)
	sw $ra, 4($sp)
	move $fp, $sp
YangHuiTriangle0:
	li $8, 0
	sw $8, 60($fp)
	j YangHuiTriangle1
YangHuiTriangle1:
	lw $9, 60($fp)
	slti $10, $9, 8
	bgtz $10, YangHuiTriangle2
	j YangHuiTriangle8
	move $11, $12
	mul $13, $13,8
	mul $13, $13,4
	add $11, $11, $13
YangHuiTriangle2:
	li $14, 0
	sw $14, 64($fp)
	j YangHuiTriangle3
YangHuiTriangle3:
	lw $15, 64($fp)
	slti $3, $15, 8
	bgtz $3, YangHuiTriangle4
	j YangHuiTriangle6
	move $11, $6
	mul $7, $7,6
	mul $7, $7,4
	add $11, $11, $7
YangHuiTriangle4:
	lw $24, 60($fp)
	add $25, $zero, $fp
	add $25, $25, 68
	mul $24, $24,8
	mul $24, $24,4
	add $25, $25, $24
	lw $8, 64($fp)
	move $9, $25
	mul $8, $8,1
	mul $8, $8,4
	add $9, $9, $8
	li $10, 1
	sw $10, ($9)
	j YangHuiTriangle5
YangHuiTriangle5:
	lw $12, 64($fp)
	add $13, $12, 1
	sw $13, 64($fp)
	j YangHuiTriangle3
YangHuiTriangle6:
	j YangHuiTriangle7
YangHuiTriangle7:
	lw $14, 60($fp)
	add $15, $14, 1
	sw $15, 60($fp)
	j YangHuiTriangle1
YangHuiTriangle8:
	li $3, 2
	sw $3, 60($fp)
	j YangHuiTriangle9
YangHuiTriangle9:
	lw $6, 60($fp)
	slti $7, $6, 8
	bgtz $7, YangHuiTriangle10
	j YangHuiTriangle16
	move $11, $24
	mul $25, $25,16
	mul $25, $25,4
	add $11, $11, $25
YangHuiTriangle10:
	li $8, 1
	sw $8, 64($fp)
	j YangHuiTriangle11
YangHuiTriangle11:
	lw $9, 64($fp)
	lw $10, 60($fp)
	slt $12, $9, $10
	bgtz $12, YangHuiTriangle12
	j YangHuiTriangle14
	move $11, $13
	mul $14, $14,14
	mul $14, $14,4
	add $11, $11, $14
YangHuiTriangle12:
	lw $15, 60($fp)
	add $3, $zero, $fp
	add $3, $3, 68
	mul $15, $15,8
	mul $15, $15,4
	add $3, $3, $15
	lw $6, 64($fp)
	move $7, $3
	mul $6, $6,1
	mul $6, $6,4
	add $7, $7, $6
	lw $24, 60($fp)
	sub $25, $24, 1
	add $8, $zero, $fp
	add $8, $8, 68
	mul $25, $25,8
	mul $25, $25,4
	add $8, $8, $25
	lw $9, 64($fp)
	move $10, $8
	mul $9, $9,1
	mul $9, $9,4
	add $10, $10, $9
	lw $12, ($10)
	lw $13, 60($fp)
	sub $14, $13, 1
	add $15, $zero, $fp
	add $15, $15, 68
	mul $14, $14,8
	mul $14, $14,4
	add $15, $15, $14
	lw $3, 64($fp)
	sub $6, $3, 1
	move $24, $15
	mul $6, $6,1
	mul $6, $6,4
	add $24, $24, $6
	lw $25, ($24)
	add $8, $12, $25
	sw $8, ($7)
	j YangHuiTriangle13
YangHuiTriangle13:
	lw $9, 64($fp)
	add $10, $9, 1
	sw $10, 64($fp)
	j YangHuiTriangle11
YangHuiTriangle14:
	j YangHuiTriangle15
YangHuiTriangle15:
	lw $13, 60($fp)
	add $14, $13, 1
	sw $14, 60($fp)
	j YangHuiTriangle9
YangHuiTriangle16:
	li $3, 0
	sw $3, 60($fp)
	j YangHuiTriangle17
YangHuiTriangle17:
	lw $15, 60($fp)
	slti $6, $15, 8
	bgtz $6, YangHuiTriangle18
	j YangHuiTriangle24
	move $11, $24
	mul $25, $25,24
	mul $25, $25,4
	add $11, $11, $25
YangHuiTriangle18:
	li $12, 0
	sw $12, 64($fp)
	j YangHuiTriangle19
YangHuiTriangle19:
	lw $7, 64($fp)
	lw $8, 60($fp)
	sle $9, $7, $8
	bgtz $9, YangHuiTriangle20
	j YangHuiTriangle22
	move $11, $10
	mul $13, $13,22
	mul $13, $13,4
	add $11, $11, $13
YangHuiTriangle20:
	lw $14, 60($fp)
	add $3, $zero, $fp
	add $3, $3, 68
	mul $14, $14,8
	mul $14, $14,4
	add $3, $3, $14
	lw $15, 64($fp)
	move $6, $3
	mul $15, $15,1
	mul $15, $15,4
	add $6, $6, $15
	lw $24, ($6)
	sw $11, 20($fp)
	sw $24, 40($fp)
	move $a0, $24
	jal Mars_PrintInt
	lw $11, 20($fp)
	lw $24, 40($fp)
	nop
	j YangHuiTriangle21
YangHuiTriangle21:
	lw $3, 64($fp)
	add $6, $3, 1
	sw $6, 64($fp)
	j YangHuiTriangle19
YangHuiTriangle22:
	sw $11, 20($fp)
	sw $24, 40($fp)
	la $a0, str_0
	jal Mars_PrintStr
	lw $11, 20($fp)
	lw $24, 40($fp)
	nop
	j YangHuiTriangle23
YangHuiTriangle23:
	lw $3, 60($fp)
	add $6, $3, 1
	sw $6, 60($fp)
	j YangHuiTriangle17
YangHuiTriangle24:
	move $sp, $fp
	lw $ra, 4($sp)
	lw $fp, 0($sp)
	addi $sp, $sp, 324
	jr $ra
	nop
main:
	addi $sp, $sp, -60
	sw $fp, 0($sp)
	sw $ra, 4($sp)
	move $fp, $sp
main0:
	jal YangHuiTriangle
	nop
	li $v0, 0
	move $sp, $fp
	lw $ra, 4($sp)
	lw $fp, 0($sp)
	addi $sp, $sp, 60
	jr $ra
	nop
