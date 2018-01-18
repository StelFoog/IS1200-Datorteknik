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
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
hexasc:
	PUSH($t0)		# saves $t0 in memory so it can be used properly in time2string subroutine
	andi	$v0, $a0, 15	# sets $v0 equal to the 4 least significant bits of $a0
	
	sge	$t0, $v0, 10	# goes to l1 if v0 is greater than or equal to 10
	beq	$t0, 1, l1	
	
	add	$v0, $v0, 0x30	# adds 0x30 to $v0
	
	POP($t0)		# retrives $t0 from memory
	jr 	$ra		# returns to the part of main where we left
	nop			# delay slot filler (just in case)
	
l1:
	add	$v0, $v0, 0x37	# adds 0x30 to $v0
	
	jr	$ra		# jumps using the returnadress
	nop			# delay slot filler (just in case)
  
  
  # "delay" subroutine
  #
delay:
	jr $ra
	nop
	
  # "time2string" subroutine
  #
time2string:
	PUSH($t0)		# free up $t0, $t1 and $ra
	PUSH($t1)
	PUSH($ra)
	
	move	$t0, $a0	# save $a0 to $t0
	
	# save the first minute nibble to $a0, shift it to the right, activate hexasc and store the result ($v0)
	andi	$t1, $a1, 0xf000
	srl	$a0, $t1, 12
	jal	hexasc
	nop
	sb	$v0, 0($t0)
	
	# save the second minute nibble to $a0, shift it to the right, activate hexasc and store the result ($v0)
	andi	$t1, $a1, 0x0f00
	srl	$a0, $t1, 8
	jal	hexasc
	nop
	sb	$v0, 1($t0)
	
	# store the hexvalue for ':' in $v0 and store it	
	li	$v0, 0x3A
	sb	$v0, 2($t0)
	
	# save the first second nibble to $a0, shift it to the right, activate hexasc and store the result ($v0)	
	andi	$t1, $a1, 0x00f0
	srl	$a0, $t1, 4
	jal	hexasc
	nop
	sb	$v0, 3($t0)
	
	
	# save the second minute nibble to $a0, activate hexasc and store the result ($v0)	
	andi	$a0, $a1, 0x000f
	jal	hexasc
	nop
	sb	$v0, 4($t0)
	
	# store the hexvalue for a null byte in $v0 and store it	
	li	$v0, 0x0
	sb	$v0, 5($t0)
	
	POP($ra)		# restore $t0, $t1 and $ra
	POP($t1)
	POP($t0)
	
	jr	$ra		# jumps using returnadress
	nop			# delay slot filler (just in case)
				
	
