#Edward Tischler
#Spring 2015 Program Assignment 1

.data               # data declaration section specifies values to be stored
                    
FirstStatements: .asciiz "Programming assignment 1 for CDA3101\nThis palindrome checker only deals with positive integer number.\nEnter a number to check if it is a palindrome or not.\n"

YouHaveReachedTheEnd: .asciiz "You have reached the end" #this was used to help me know when i reached the end of the loop

IsPalindrome: .asciiz " is a palidrome number "
Not: .asciiz " is not a palidrome number"




.text               # Neccessary to start code section
main:              #beginning of execution of code

li $v0, 4            # string call code
la $a0, FirstStatements    # obtain address of string to put into new register
syscall             # call operating system to perform operation

li $v0, 5			# read int call code. this is num variable
syscall
move $t0,$v0		#return value of syscall stored in $t0
move $t2,$v0		#same for $t2


li $t1, 0			#stores initial reverse value
li $t3, 0			#necessary for branch comparison
li $t8, 10			#necessary to divide by 10

#li	$v0,1			# print integer call code
	#move	$a0, $t2	# must load into $a0 before print		#this was used to print values to make sure they were being stored correctly in registers
	#syscall

whilestatement:
	beq	$t2, $t3, exit	#if temp = 0 it exits. basically the same thing rewritten
	mult $t1, $t8	#mutliplies reverse by 10
	mflo $t1		#stores result into reverse register and therefore updates value
	div $t2, $t8	#temp/10
	mfhi $t7		#temp%10
	mflo $t2		#temp/10
	add $t1, $t1, $t7  #reverse = reverse + temp%10




 #bne $t2, $t3, exit # used for test purposes. i wanted to exit after 1 loop to test execution of code

	
	
	j	whilestatement	#jumps to whilestatement
exit:
bne $t0, $t1, else	#if reverse!=num jump to else



j true #if the statement is true jump to true

else:
li	$v0,1			# print integer call code
	move	$a0, $t0	# must load into $a0 before print		#this prints the number before the rest of the statement is printed
	syscall

li $v0, 4            # string call code
la $a0, Not    # obtain address of string to put into new register
syscall             # call operating system to perform operation

j over	#jump to over to bypass true

true:
li	$v0,1			# print integer call code
	move	$a0, $t0	# must load into $a0 before print		#this prints the number before the rest of the statement is printed
	syscall
li $v0, 4            # string call code
la $a0, IsPalindrome    # obtain address of string to put into new register
syscall             # call operating system to perform operation

over:


jr $ra                    # needs to be at end of code. says system function called
                    # syscall takes $v0 (and opt arguments)


                    #$t0 is num
                    #$t1 is reverse
                    #$t2 is temp
                    #$t3 is just 0 used for comparison			#helped me keep my variables straight with registers
                    #$t6 is temp lo
                    #$t7 is temp hi
                    #$t8 is 10


