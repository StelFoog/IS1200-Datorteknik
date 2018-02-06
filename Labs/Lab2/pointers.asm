
        # pointers.asm
# By David Broman, 2015-09-14
# This file is in the public domain


.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

.data


text1: 	  .asciiz "This is a string."
text2:	  .asciiz "Yet another thing."

.align 2
list1: 	.space 80
list2: 	.space 80
count:	.word  0

.text
main:
	jal	work
stop:	j	stop

# function work()
work:
	PUSH	($ra)
	la 	$a0,text1	# takes adress of text1 as agrument
	la	$a1,list1	# takes adress of list1 as argument
	la	$a2,count	# takes adress of count as argument
	jal	copycodes	# executes copycodes
	
	la 	$a0,text2	# takes adress of text2 as agrument
	la	$a1,list2	# takes adress of list2 as agrument
	la	$a2,count	# takes adress of count as agrument
	jal	copycodes	# executes copycodes
	POP	($ra)
	
	
# function copycodes()
copycodes:
loop:
	lb	$t0,0($a0)	# saves the byte at adress $a0 to $t0 
	beq	$t0,$0,done	# checks if the byte is equal to 0
	sw	$t0,0($a1)	# stores the word in $t0 to the adress of $a1

	addi	$a0,$a0,1	# adds one to $a0
	addi	$a1,$a1,4	# adds four to $a1 (word)
	
	# adds one to count
	lw	$t1,0($a2)
	addi	$t1,$t1,1
	sw	$t1,0($a2)
	j	loop
done:
	jr	$ra
		



