# analyze.asm
  # This file written 2015 by F Lundevall
  # Copyright abandoned - this file is in the public domain.

	.text
main:
	li	$s0,0x30	# stores 0x30 in $s0
loop:
	move	$a0,$s0		# copy from s0 to a0

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window

	addi	$s0,$s0,1	# what happens if the constant is changed?

	sge	$t0,$s0,0x5b	# set t0 as 1 if s0 is greater than 0x5b, otherwise as 0
	beq 	$t0,0,loop	# continue the loop if t0 is equal to 0
	nop			# delay slot filler (just in case)

stop:	j	stop		# loop forever here
	nop			# delay slot filler (just in case)
