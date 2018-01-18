  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0, 15		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0, $v0	# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)


  # You can write your own code for hexasc here
hexasc:
	andi	$v0, $a0, 15	# sets $v0 equal to the 4 least significant bits of $a0
	
	sge	$t0, $v0, 10	# goes to l1 if v0 is greater than or equal to 10
	beq	$t0, 1, l1	
	
	add	$v0, $v0, 0x30	# adds 0x30 to $v0
	
	jr 	$ra		# returns to the part of main where we left
	nop			# delay slot filler (just in case)
	
l1:
	add	$v0, $v0, 0x37	# adds 0x30 to $v0
	
	jr	$ra		# returns to the part of main where we left
	nop			# delay slot filler (just in case)
	
	
	
	
	
	
	
