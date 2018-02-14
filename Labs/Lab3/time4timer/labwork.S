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
	.align 2
	
  	.globl hexasc
  	.globl time2string
  	.globl delay
  
 	.text
hexasc:
	PUSH	$t0
	andi	$v0,$a0,15	#Keep the 4 least significant bits
	slti	$t0,$v0,0x0a	#if a < 10 t0 = 1 else 0
	bne	$t0,$0,if	#if t0 != 0 go to if
	nop
	addi	$v0,$v0,0x07	#Add the amount of elements between 9 and A in ASCII table
if:
	addi	$v0,$v0,0x30	#Add the index of '0' in the ASCII table
	POP	$t0
	jr	$ra		#Return to main
	nop

# Delay function
delay:
	#PUSH temps to not delete their initial value
	PUSH	$t0
	PUSH	$t1
	PUSH	$s0
	li	$s0, 3400
while:
	sgt	$t1,$a0,0	# If ms is more than 0 return 1, else 0
	beq	$t1,$0,endDelay	# If ms is not more than 0, end delay
	nop
	addi	$a0,$a0,-1	# Decrement with one
	li	$t0,0		# index (t0) = 0
for:
	sge	$t1,$t0,$s0	# If index is more than 1, return 0
	bne	$t1,$0,while	# Jump to loop if 0 is returned 
	nop
	addi	$t0, $t0,1	# Increment index with one (i++)
	j	for		# Jump back to begining of for loop
	nop
endDelay:
	# POP the initial temp registers
	POP	$s0
	POP	$t1
	POP	$t0
	jr 	$ra
	nop
	
# To String function
time2string:
	PUSH    $t0
	PUSH    $t1
	PUSH    $ra	# PUSH the reutrn address to stack

	move	$t0,$a0		# adressen
	#move	$t1,$a1		# Tiden som ska lagras
	
	# Get the first digit in ascii and add it to the first byte 
	andi	$t1,$a1,0xf000
	srl	$a0,$t1,12
	jal	hexasc
	nop
	sb	$v0,0($t0)
	
	# Get the second digit in ascii and add it to the second byte 
	andi	$t1,$a1,0xf00
	srl	$a0,$t1,8
	jal	hexasc
	nop
	sb	$v0,1($t0)
	
	# Add a ascii colon to the third byte
	li	$v0,0x3A
	sb	$v0,2($t0)
	
	# Get the third digit in ascii and add it to the fourh byte 
	andi	$t1,$a1,0xf0
	srl	$a0,$t1,4
	jal	hexasc
	nop
	sb	$v0,3($t0)
	
	# Get the fourth digit in ascii and add it to the fifth byte 
	andi	$a0,$a1,0xf
	jal	hexasc
	nop
	sb	$v0,4($t0)
	
	# Add null byte at end
	li	$v0,0x00
	sb	$v0,5($t0)
	
	# POP back the used variables so they return to their initial value 
	POP 	$ra
	POP   	$t1
	POP   	$t0	# POP back the return adress	
	jr	$ra
	nop
