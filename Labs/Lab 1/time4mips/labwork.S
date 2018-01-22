  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
 #
 # Please add your own code below this line
 #
 
 .data
 .globl hexasc
 .globl delay
 .globl time2string
 .align 2
 .text
 # hexasc subroutine
 #
hexasc:
 PUSH $t0		# saves $t0 in memory so it can be used properly in time2string subroutine
 andi	$v0, $a0, 15	# sets $v0 equal to the 4 least significant bits of $a0

 sge	$t0, $v0, 10	# goes to l1 if v0 is greater than or equal to 10
 beq	$t0, 1, l1

 add	$v0, $v0, 0x30	# adds 0x30 to $v0

 POP $t0		# retrives $t0 from memory
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
 PUSH $s0
 PUSH $t0
 PUSH $s1
 li	$s1, 2		# sets $s1 to a constant, in this case 2

delayloop1:
 # checks if $t7 is less than or equal to 0 and if so moves to delayend
 sle	$t0, $t7, $0
 bne	$t0, 0, delayend
 nop			# delay slot filler (just in case)

 sub	$t7, $t7, 1	# subtracts 1 from $t7
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
 POP $s1
 POP $t0
 POP $s0
 jr 	$ra		# jumps using the return adress
 nop			# delay slot filler (just in case)
 
 
 # "time2string" subroutine
 #
time2string:
 PUSH $t0		# free up $t0, $t1 and $ra
 PUSH $t1
 PUSH $ra

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

 POP $ra		# restore $t0, $t1 and $ra
 POP $t1
 POP $t0

 jr	$ra		# jumps using returnadress
 nop			# delay slot filler (just in case)

