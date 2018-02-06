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
 li	$t7,1000
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
 # the register $t7 stands for the ms the program runs for
 #
delay:
 # frees up the variables $s0, $t0 and $s1
 PUSH($s0)
 PUSH($t0)
 PUSH($s1)
 li	$s1, 2		# sets $s1 to a constant, in this case 2

delayloop1:
 # checks if $t7 is less than or equal to 0 and if so moves to delayend
 sle	$t0, $t7, $0
 bne	$t0, 0, delayend
 nop			# delay slot filler (just in case)

 subi	$t7, $t7, 1	# subtracts 1 from $t7
 li	$s0, 0		# sets $s0 to 0

delayloop2:
 # checks if $s0 is less than or equal to $s1 and if so moves to delayend
 slt	$t0, $s0, $s1
 beq	$t0, 0, delayloop1
 nop			# delay slot filler (just in case)
 nop			# extra delay to make delayloop2 take 1 ms

 addi	$s0, $s0, 1	# adds 1 to $s0
 j	delayloop2	# begins the loop again
 nop			# delay slot filler (just in case)


delayend:
 # restores registers $s1, $t0 and $s0
 POP($s1)
 POP($t0)
 POP($s0)
 jr 	$ra		# jumps using the return adress
 nop			# delay slot filler (just in case)

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
 PUSH($t3)
 li	$t3, 9
 andi	$a0, $a1, 0x000f
 beq	$t3, $a0, ifNINE
 POP($t3)
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
 
ifNINE:
 li	$t1, 0x4e
 sb	$t1, 4($t0)

 li	$t1, 0x49
 sb	$t1, 5($t0)
 
 li	$t1, 0x4e
 sb	$t1, 6($t0)
 
 li	$t1, 0x45
 sb	$t1, 7($t0)
 
 sb 	$0, 8($t0)
 
 POP($t3)
 POP($ra)		# restore $t0, $t1 and $ra
 POP($t1)
 POP($t0)

 jr	$ra		# jumps using returnadress
 nop			# delay slot filler (just in case)
 

