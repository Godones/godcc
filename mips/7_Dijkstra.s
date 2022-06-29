	.data
maxint_0: .word 999999
dist_0: .space 200
prev_0: .space 200
cc_0: .space 10000
n_0: .word 0
line_0: .word 0
str_0: .asciiz "->"
str_1: .asciiz "\n"
str_2: .asciiz " "
str_3: .asciiz "\n"
str_4: .asciiz "Shortest path length from source point to last vertex:"
str_5: .asciiz "\nThe path is:\n"
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
Dijkskra:
	addi $sp, $sp, -296
	sw $a0, 0($sp)
	sw $a1, 4($sp)
	sw $fp, 8($sp)
	sw $ra, 12($sp)
	move $fp, $sp
Dijkskra0:
	li $8, 1
	sw $8, 272($fp)
	j Dijkskra1
Dijkskra1:
	lw $9, 272($fp)
	lw $10, 0($fp)
	sle $11, $9, $10
	bgtz $11, Dijkskra2
	j Dijkskra7
	move $12, $13
	mul $14, $14,7
	mul $14, $14,4
	add $12, $12, $14
Dijkskra2:
	lw $15, 272($fp)
	la $3, dist_0
	mul $15, $15,1
	mul $15, $15,4
	add $3, $3, $15
	lw $6, 4($fp)
	la $7, cc_0
	mul $6, $6,50
	mul $6, $6,4
	add $7, $7, $6
	lw $24, 272($fp)
	move $25, $7
	mul $24, $24,1
	mul $24, $24,4
	add $25, $25, $24
	lw $8, ($25)
	sw $8, ($3)
	lw $10, 272($fp)
	add $9, $zero, $fp
	add $9, $9, 68
	mul $10, $10,1
	mul $10, $10,4
	add $9, $9, $10
	li $11, 0
	sw $11, ($9)
	lw $13, 272($fp)
	la $14, dist_0
	mul $13, $13,1
	mul $13, $13,4
	add $14, $14, $13
	lw $15, ($14)
	lw $6, maxint_0
	seq $7, $15, $6
	bgtz $7, Dijkskra3
	j Dijkskra4
	move $12, $24
	mul $25, $25,4
	mul $25, $25,4
	add $12, $12, $25
Dijkskra3:
	lw $3, 272($fp)
	la $8, prev_0
	mul $3, $3,1
	mul $3, $3,4
	add $8, $8, $3
	li $10, 0
	sw $10, ($8)
	j Dijkskra5
Dijkskra4:
	lw $9, 272($fp)
	la $11, prev_0
	mul $9, $9,1
	mul $9, $9,4
	add $11, $11, $9
	lw $13, 4($fp)
	sw $13, ($11)
	j Dijkskra5
Dijkskra5:
	j Dijkskra6
Dijkskra6:
	lw $14, 272($fp)
	add $6, $14, 1
	sw $6, 272($fp)
	j Dijkskra1
Dijkskra7:
	lw $15, 4($fp)
	la $7, dist_0
	mul $15, $15,1
	mul $15, $15,4
	add $7, $7, $15
	li $24, 0
	sw $24, ($7)
	lw $25, 4($fp)
	add $3, $zero, $fp
	add $3, $3, 68
	mul $25, $25,1
	mul $25, $25,4
	add $3, $3, $25
	li $8, 1
	sw $8, ($3)
	li $10, 2
	sw $10, 272($fp)
	j Dijkskra8
Dijkskra8:
	lw $9, 272($fp)
	lw $11, 0($fp)
	sle $13, $9, $11
	bgtz $13, Dijkskra9
	j Dijkskra25
	move $12, $14
	mul $6, $6,25
	mul $6, $6,4
	add $12, $12, $6
Dijkskra9:
	lw $15, maxint_0
	sw $15, 276($fp)
	lw $7, 4($fp)
	sw $7, 280($fp)
	li $24, 1
	sw $24, 288($fp)
	j Dijkskra10
Dijkskra10:
	lw $25, 288($fp)
	lw $3, 0($fp)
	sle $8, $25, $3
	bgtz $8, Dijkskra11
	j Dijkskra15
	move $12, $10
	mul $11, $11,15
	mul $11, $11,4
	add $12, $12, $11
Dijkskra11:
	lw $9, 288($fp)
	add $13, $zero, $fp
	add $13, $13, 68
	mul $9, $9,1
	mul $9, $9,4
	add $13, $13, $9
	lw $14, ($13)
	seq $6, $14, 0
	lw $15, 288($fp)
	la $7, dist_0
	mul $15, $15,1
	mul $15, $15,4
	add $7, $7, $15
	lw $24, ($7)
	lw $3, 276($fp)
	slt $25, $24, $3
	and $8, $6, $25
	bgtz $8, Dijkskra12
	j Dijkskra13
	move $12, $10
	mul $11, $11,13
	mul $11, $11,4
	add $12, $12, $11
Dijkskra12:
	lw $9, 288($fp)
	sw $9, 280($fp)
	lw $13, 288($fp)
	la $14, dist_0
	mul $13, $13,1
	mul $13, $13,4
	add $14, $14, $13
	lw $15, ($14)
	sw $15, 276($fp)
	j Dijkskra13
Dijkskra13:
	j Dijkskra14
Dijkskra14:
	lw $7, 288($fp)
	add $24, $7, 1
	sw $24, 288($fp)
	j Dijkskra10
Dijkskra15:
	lw $3, 280($fp)
	add $25, $zero, $fp
	add $25, $25, 68
	mul $3, $3,1
	mul $3, $3,4
	add $25, $25, $3
	li $6, 1
	sw $6, ($25)
	li $8, 1
	sw $8, 288($fp)
	j Dijkskra16
Dijkskra16:
	lw $10, 288($fp)
	lw $11, 0($fp)
	sle $9, $10, $11
	bgtz $9, Dijkskra17
	j Dijkskra23
	move $12, $13
	mul $14, $14,23
	mul $14, $14,4
	add $12, $12, $14
Dijkskra17:
	lw $15, 288($fp)
	add $7, $zero, $fp
	add $7, $7, 68
	mul $15, $15,1
	mul $15, $15,4
	add $7, $7, $15
	lw $24, ($7)
	seq $3, $24, 0
	lw $25, 280($fp)
	la $6, cc_0
	mul $25, $25,50
	mul $25, $25,4
	add $6, $6, $25
	lw $8, 288($fp)
	move $11, $6
	mul $8, $8,1
	mul $8, $8,4
	add $11, $11, $8
	lw $10, ($11)
	lw $9, maxint_0
	slt $13, $10, $9
	and $14, $3, $13
	bgtz $14, Dijkskra18
	j Dijkskra21
	move $12, $15
	mul $7, $7,21
	mul $7, $7,4
	add $12, $12, $7
Dijkskra18:
	lw $24, 280($fp)
	la $25, dist_0
	mul $24, $24,1
	mul $24, $24,4
	add $25, $25, $24
	lw $6, ($25)
	lw $8, 280($fp)
	la $11, cc_0
	mul $8, $8,50
	mul $8, $8,4
	add $11, $11, $8
	lw $10, 288($fp)
	move $9, $11
	mul $10, $10,1
	mul $10, $10,4
	add $9, $9, $10
	lw $13, ($9)
	add $3, $6, $13
	sw $3, 292($fp)
	lw $14, 292($fp)
	lw $15, 288($fp)
	la $7, dist_0
	mul $15, $15,1
	mul $15, $15,4
	add $7, $7, $15
	lw $24, ($7)
	slt $25, $14, $24
	bgtz $25, Dijkskra19
	j Dijkskra20
	move $12, $8
	mul $11, $11,20
	mul $11, $11,4
	add $12, $12, $11
Dijkskra19:
	lw $10, 288($fp)
	la $9, dist_0
	mul $10, $10,1
	mul $10, $10,4
	add $9, $9, $10
	lw $13, 292($fp)
	sw $13, ($9)
	lw $6, 288($fp)
	la $3, prev_0
	mul $6, $6,1
	mul $6, $6,4
	add $3, $3, $6
	lw $15, 280($fp)
	sw $15, ($3)
	j Dijkskra20
Dijkskra20:
	j Dijkskra21
Dijkskra21:
	j Dijkskra22
Dijkskra22:
	lw $7, 288($fp)
	add $14, $7, 1
	sw $14, 288($fp)
	j Dijkskra16
Dijkskra23:
	j Dijkskra24
Dijkskra24:
	lw $24, 272($fp)
	add $25, $24, 1
	sw $25, 272($fp)
	j Dijkskra8
Dijkskra25:
	move $sp, $fp
	lw $ra, 12($sp)
	lw $fp, 8($sp)
	addi $sp, $sp, 296
	jr $ra
	nop
searchPath:
	addi $sp, $sp, -280
	sw $a0, 0($sp)
	sw $a1, 4($sp)
	sw $fp, 8($sp)
	sw $ra, 12($sp)
	move $fp, $sp
searchPath0:
	li $8, 1
	sw $8, 268($fp)
	lw $9, 268($fp)
	add $10, $zero, $fp
	add $10, $10, 68
	mul $9, $9,1
	mul $9, $9,4
	add $10, $10, $9
	lw $11, 4($fp)
	sw $11, ($10)
	lw $12, 268($fp)
	add $13, $12, 1
	sw $13, 268($fp)
	lw $14, 4($fp)
	la $15, prev_0
	mul $14, $14,1
	mul $14, $14,4
	add $15, $15, $14
	lw $3, ($15)
	sw $3, 272($fp)
	j searchPath1
searchPath1:
	lw $6, 272($fp)
	lw $7, 0($fp)
	sne $24, $6, $7
	bgtz $24, searchPath2
	j searchPath4
	move $25, $8
	mul $9, $9,4
	mul $9, $9,4
	add $25, $25, $9
searchPath2:
	lw $10, 268($fp)
	add $11, $zero, $fp
	add $11, $11, 68
	mul $10, $10,1
	mul $10, $10,4
	add $11, $11, $10
	lw $12, 272($fp)
	sw $12, ($11)
	lw $13, 268($fp)
	add $14, $13, 1
	sw $14, 268($fp)
	lw $15, 272($fp)
	la $3, prev_0
	mul $15, $15,1
	mul $15, $15,4
	add $3, $3, $15
	lw $7, ($3)
	sw $7, 272($fp)
	j searchPath3
searchPath3:
	j searchPath1
searchPath4:
	lw $6, 268($fp)
	add $24, $zero, $fp
	add $24, $24, 68
	mul $6, $6,1
	mul $6, $6,4
	add $24, $24, $6
	lw $8, 0($fp)
	sw $8, ($24)
	lw $9, 268($fp)
	sw $9, 276($fp)
	j searchPath5
searchPath5:
	lw $10, 276($fp)
	sge $11, $10, 1
	bgtz $11, searchPath6
	j searchPath11
	move $25, $12
	mul $13, $13,11
	mul $13, $13,4
	add $25, $25, $13
searchPath6:
	lw $14, 276($fp)
	add $15, $zero, $fp
	add $15, $15, 68
	mul $14, $14,1
	mul $14, $14,4
	add $15, $15, $14
	lw $3, ($15)
	sw $3, 56($fp)
	sw $25, 52($fp)
	move $a0, $3
	jal Mars_PrintInt
	lw $3, 56($fp)
	lw $25, 52($fp)
	nop
	lw $6, 276($fp)
	sne $7, $6, 1
	bgtz $7, searchPath7
	j searchPath8
	move $25, $8
	mul $9, $9,8
	mul $9, $9,4
	add $25, $25, $9
searchPath7:
	sw $3, 56($fp)
	sw $25, 52($fp)
	la $a0, str_0
	jal Mars_PrintStr
	lw $3, 56($fp)
	lw $25, 52($fp)
	nop
	j searchPath9
searchPath8:
	sw $3, 56($fp)
	sw $25, 52($fp)
	la $a0, str_1
	jal Mars_PrintStr
	lw $3, 56($fp)
	lw $25, 52($fp)
	nop
	j searchPath9
searchPath9:
	j searchPath10
searchPath10:
	lw $6, 276($fp)
	sub $7, $6, 1
	sw $7, 276($fp)
	j searchPath5
searchPath11:
	move $sp, $fp
	lw $ra, 12($sp)
	lw $fp, 8($sp)
	addi $sp, $sp, 280
	jr $ra
	nop
main:
	addi $sp, $sp, -96
	sw $fp, 0($sp)
	sw $ra, 4($sp)
	move $fp, $sp
main0:
	jal Mars_GetInt
	move $3, $v0
	nop
	sw $3, n_0
	jal Mars_GetInt
	move $3, $v0
	nop
	sw $3, line_0
	li $6, 1
	sw $6, 88($fp)
	j main1
main1:
	lw $7, 88($fp)
	lw $8, n_0
	sle $9, $7, $8
	bgtz $9, main2
	j main8
	move $10, $11
	mul $12, $12,8
	mul $12, $12,4
	add $10, $10, $12
main2:
	li $13, 1
	sw $13, 92($fp)
	j main3
main3:
	lw $14, 92($fp)
	lw $15, n_0
	sle $24, $14, $15
	bgtz $24, main4
	j main6
	move $10, $25
	mul $3, $3,6
	mul $3, $3,4
	add $10, $10, $3
main4:
	lw $6, 88($fp)
	la $8, cc_0
	mul $6, $6,50
	mul $6, $6,4
	add $8, $8, $6
	lw $7, 92($fp)
	move $9, $8
	mul $7, $7,1
	mul $7, $7,4
	add $9, $9, $7
	lw $11, maxint_0
	sw $11, ($9)
	j main5
main5:
	lw $12, 92($fp)
	add $13, $12, 1
	sw $13, 92($fp)
	j main3
main6:
	j main7
main7:
	lw $15, 88($fp)
	add $14, $15, 1
	sw $14, 88($fp)
	j main1
main8:
	li $24, 1
	sw $24, 88($fp)
	j main9
main9:
	lw $25, 88($fp)
	lw $3, line_0
	sle $6, $25, $3
	bgtz $6, main10
	j main14
	move $10, $8
	mul $7, $7,14
	mul $7, $7,4
	add $10, $10, $7
main10:
	sw $10, 16($fp)
	jal Mars_GetInt
	move $3, $v0
	lw $10, 16($fp)
	nop
	sw $3, 60($fp)
	sw $10, 16($fp)
	jal Mars_GetInt
	move $3, $v0
	lw $10, 16($fp)
	nop
	sw $3, 64($fp)
	sw $10, 16($fp)
	jal Mars_GetInt
	move $3, $v0
	lw $10, 16($fp)
	nop
	sw $3, 68($fp)
	lw $6, 68($fp)
	lw $7, 60($fp)
	la $8, cc_0
	mul $7, $7,50
	mul $7, $7,4
	add $8, $8, $7
	lw $9, 64($fp)
	move $11, $8
	mul $9, $9,1
	mul $9, $9,4
	add $11, $11, $9
	lw $12, ($11)
	slt $13, $6, $12
	bgtz $13, main11
	j main12
	move $10, $14
	mul $15, $15,12
	mul $15, $15,4
	add $10, $10, $15
main11:
	lw $24, 60($fp)
	la $25, cc_0
	mul $24, $24,50
	mul $24, $24,4
	add $25, $25, $24
	lw $3, 64($fp)
	move $7, $25
	mul $3, $3,1
	mul $3, $3,4
	add $7, $7, $3
	lw $8, 68($fp)
	sw $8, ($7)
	lw $9, 64($fp)
	la $11, cc_0
	mul $9, $9,50
	mul $9, $9,4
	add $11, $11, $9
	lw $6, 60($fp)
	move $12, $11
	mul $6, $6,1
	mul $6, $6,4
	add $12, $12, $6
	lw $13, 68($fp)
	sw $13, ($12)
	j main12
main12:
	j main13
main13:
	lw $14, 88($fp)
	add $15, $14, 1
	sw $15, 88($fp)
	j main9
main14:
	li $24, 1
	sw $24, 88($fp)
	j main15
main15:
	lw $25, 88($fp)
	lw $3, n_0
	sle $7, $25, $3
	bgtz $7, main16
	j main18
	move $10, $8
	mul $9, $9,18
	mul $9, $9,4
	add $10, $10, $9
main16:
	lw $11, 88($fp)
	la $6, dist_0
	mul $11, $11,1
	mul $11, $11,4
	add $6, $6, $11
	lw $12, maxint_0
	sw $12, ($6)
	j main17
main17:
	lw $13, 88($fp)
	add $14, $13, 1
	sw $14, 88($fp)
	j main15
main18:
	li $15, 1
	sw $15, 88($fp)
	j main19
main19:
	lw $24, 88($fp)
	lw $3, n_0
	sle $25, $24, $3
	bgtz $25, main20
	j main26
	move $10, $7
	mul $8, $8,26
	mul $8, $8,4
	add $10, $10, $8
main20:
	li $9, 1
	sw $9, 92($fp)
	j main21
main21:
	lw $11, 92($fp)
	lw $6, n_0
	sle $12, $11, $6
	bgtz $12, main22
	j main24
	move $10, $13
	mul $14, $14,24
	mul $14, $14,4
	add $10, $10, $14
main22:
	lw $15, 88($fp)
	la $3, cc_0
	mul $15, $15,50
	mul $15, $15,4
	add $3, $3, $15
	lw $24, 92($fp)
	move $25, $3
	mul $24, $24,1
	mul $24, $24,4
	add $25, $25, $24
	lw $7, ($25)
	sw $7, 56($fp)
	sw $10, 16($fp)
	move $a0, $7
	jal Mars_PrintInt
	lw $7, 56($fp)
	lw $10, 16($fp)
	nop
	sw $7, 56($fp)
	sw $10, 16($fp)
	la $a0, str_2
	jal Mars_PrintStr
	lw $7, 56($fp)
	lw $10, 16($fp)
	nop
	j main23
main23:
	lw $3, 92($fp)
	add $6, $3, 1
	sw $6, 92($fp)
	j main21
main24:
	sw $7, 56($fp)
	sw $10, 16($fp)
	la $a0, str_3
	jal Mars_PrintStr
	lw $7, 56($fp)
	lw $10, 16($fp)
	nop
	j main25
main25:
	lw $3, 88($fp)
	add $6, $3, 1
	sw $6, 88($fp)
	j main19
main26:
	lw $8, n_0
	sw $7, 56($fp)
	sw $8, 8($fp)
	sw $10, 16($fp)
	move $a0, $8
	li $a1, 1
	jal Dijkskra
	lw $7, 56($fp)
	lw $8, 8($fp)
	lw $10, 16($fp)
	nop
	sw $7, 56($fp)
	sw $8, 8($fp)
	sw $10, 16($fp)
	la $a0, str_4
	jal Mars_PrintStr
	lw $7, 56($fp)
	lw $8, 8($fp)
	lw $10, 16($fp)
	nop
	lw $3, n_0
	la $6, dist_0
	mul $3, $3,1
	mul $3, $3,4
	add $6, $6, $3
	lw $9, ($6)
	sw $7, 56($fp)
	sw $8, 8($fp)
	sw $9, 12($fp)
	sw $10, 16($fp)
	move $a0, $9
	jal Mars_PrintInt
	lw $7, 56($fp)
	lw $8, 8($fp)
	lw $9, 12($fp)
	lw $10, 16($fp)
	nop
	sw $7, 56($fp)
	sw $8, 8($fp)
	sw $9, 12($fp)
	sw $10, 16($fp)
	la $a0, str_5
	jal Mars_PrintStr
	lw $7, 56($fp)
	lw $8, 8($fp)
	lw $9, 12($fp)
	lw $10, 16($fp)
	nop
	lw $3, n_0
	sw $3, 48($fp)
	sw $7, 56($fp)
	sw $8, 8($fp)
	sw $9, 12($fp)
	sw $10, 16($fp)
	li $a0, 1
	move $a1, $3
	jal searchPath
	lw $3, 48($fp)
	lw $7, 56($fp)
	lw $8, 8($fp)
	lw $9, 12($fp)
	lw $10, 16($fp)
	nop
	li $v0, 0
	move $sp, $fp
	lw $ra, 4($sp)
	lw $fp, 0($sp)
	addi $sp, $sp, 96
	jr $ra
	nop
