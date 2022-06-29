	.data
str_0: .asciiz " "
str_1: .asciiz "Please input a number:\n"
str_2: .asciiz "The number of prime numbers within n is:\n"
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
prime:
	addi $sp, $sp, -80
	sw $a0, 0($sp)
	sw $fp, 4($sp)
	sw $ra, 8($sp)
	move $fp, $sp
prime0:
	li $8, 0
	sw $8, 64($fp)
	li $9, 1
	sw $9, 76($fp)
	li $10, 2
	sw $10, 68($fp)
	j prime1
prime1:
	lw $11, 68($fp)
	lw $12, 0($fp)
	sle $13, $11, $12
	bgtz $13, prime2
	j prime12
	move $14, $15
	mul $3, $3,12
	mul $3, $3,4
	add $14, $14, $3
prime2:
	li $6, 1
	sw $6, 76($fp)
	li $7, 2
	sw $7, 72($fp)
	j prime3
prime3:
	lw $24, 72($fp)
	lw $25, 72($fp)
	mul $8, $24, $25
	lw $9, 68($fp)
	sle $10, $8, $9
	bgtz $10, prime4
	j prime8
	move $14, $12
	mul $11, $11,8
	mul $11, $11,4
	add $14, $14, $11
prime4:
	lw $13, 68($fp)
	lw $15, 72($fp)
	rem $3, $13, $15
	seq $6, $3, 0
	bgtz $6, prime5
	j prime6
	move $14, $7
	mul $25, $25,6
	mul $25, $25,4
	add $14, $14, $25
prime5:
	li $24, 0
	sw $24, 76($fp)
	j prime8
	j prime6
prime6:
	j prime7
prime7:
	lw $9, 72($fp)
	add $8, $9, 1
	sw $8, 72($fp)
	j prime3
prime8:
	lw $10, 76($fp)
	seq $12, $10, 1
	bgtz $12, prime9
	j prime10
	move $14, $11
	mul $15, $15,10
	mul $15, $15,4
	add $14, $14, $15
prime9:
	lw $13, 64($fp)
	add $3, $13, 1
	sw $3, 64($fp)
	lw $6, 68($fp)
	sw $6, 56($fp)
	sw $14, 36($fp)
	move $a0, $6
	jal Mars_PrintInt
	lw $6, 56($fp)
	lw $14, 36($fp)
	nop
	sw $6, 56($fp)
	sw $14, 36($fp)
	la $a0, str_0
	jal Mars_PrintStr
	lw $6, 56($fp)
	lw $14, 36($fp)
	nop
	j prime10
prime10:
	j prime11
prime11:
	lw $3, 68($fp)
	add $7, $3, 1
	sw $7, 68($fp)
	j prime1
prime12:
	lw $8, 64($fp)
	move $v0, $8
	move $sp, $fp
	lw $ra, 8($sp)
	lw $fp, 4($sp)
	addi $sp, $sp, 80
	jr $ra
	nop
main:
	addi $sp, $sp, -68
	sw $fp, 0($sp)
	sw $ra, 4($sp)
	move $fp, $sp
main0:
	la $a0, str_1
	jal Mars_PrintStr
	nop
	jal Mars_GetInt
	move $3, $v0
	nop
	sw $3, 60($fp)
	lw $6, 60($fp)
	sw $6, 52($fp)
	move $a0, $6
	jal prime
	move $3, $v0
	lw $6, 52($fp)
	nop
	sw $3, 64($fp)
	sw $6, 52($fp)
	la $a0, str_2
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
