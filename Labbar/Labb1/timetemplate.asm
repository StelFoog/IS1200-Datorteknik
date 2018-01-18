  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return


  # you can write your code for subroutine "hexasc" below this line
  #
hexasc:
	andi	$v0,$a0,15	#Keep the 4 least significant bits
	slti	$t3,$v0,0x0a	#if a < 10 t0 = 1 else 0
	bne	$t3,$0,if	#if t0 != 0 go to if
	addi	$v0,$v0,0x07	#Add the amount of elements between 9 and A in ASCII table
if:
	addi	$v0,$v0,0x30	#Add the index of '0' in the ASCII table
	jr	$ra		#Return to main
	nop
# Delay function
delay:
	jr $ra
	nop
# To String function
time2string:

	PUSH    ($ra)           # nested subroutine must store $ra too
	
	add	$t0,$0,$a0	# adressen
	add	$t1,$0,$a1	# Tiden som ska lagras
	
	
	andi	$t2,$t1,0xf000
	srl	$a0,$t2,12
	jal	hexasc
	nop
	sb	$v0,0($t0)
	
	andi	$t2,$t1,0xf00
	srl	$a0,$t2,8
	jal	hexasc
	nop
	sb	$v0,1($t0)
	
	li	$t5,0x3A
	sb	$t5,2($t0)
	
	andi	$t2,$t1,0xf0
	srl	$a0,$t2,4
	jal	hexasc
	nop
	sb	$v0,3($t0)
	
	andi	$a0,$t1,0xf
	jal	hexasc
	nop
	sb	$v0,4($t0)

	POP ($ra)
	
	jr	$ra
	nop
	
	