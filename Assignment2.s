#Edward Tischler
#Spring 2015 Program Assignment 2
#note to grader, some code reused from 1st assignment

.data               # data declaration section specifies values to be stored
                    
EnterFirstIntegerN1: .asciiz "Enter first integer n1: "

EnterSecondIntegerN2: .asciiz "Enter second integer n2: "

GCDtext: .asciiz "The greatest common divisor of n1 and n2 is "

LCMtext: .asciiz "\nThe least common multiple of n1 and n2 is "





.text               # Neccessary to start code section
main:              #beginning of execution of code

li $v0, 4            # string call code
la $a0, EnterFirstIntegerN1    # obtain address of string to put into new register
syscall    

li $v0, 5			# read int call code. this is 1st int variable
syscall
move $t0,$v0		#return value of syscall stored in $t0

#li	$v0,1			# print integer call code
	#move	$a0, $t0	# must load into $a0 before print		#this was used to print values to make sure they were being stored correctly in registers
	#syscall

li $v0, 4            # string call code
la $a0, EnterSecondIntegerN2    # obtain address of string to put into new register
syscall

li $v0, 5			# read int call code. this is 2nd int variable
syscall
move $t1,$v0		#return value of syscall stored in $t1

#li	$v0,1			# print integer call code
	#move	$a0, $t1	# must load into $a0 before print		#this was used to print values to make sure they were being stored correctly in registers
	#syscall

li $t3, 0 #necessary for branch comparison
move $t4, $t0
move $t5, $t1   #this will make lcm function easier to execute

gcd: 


div $t0, $t1 #number one divided by number 2
mfhi $t2	#remainder stored as remainder
beq $t2, $t3, printoutgcd
bne $t2, $t3, changegcdvalues


changegcdvalues:
move $t0, $t1 #number one is now number 2. for first case at least
move $t1, $t2 #number 2 is now remainder. for first case at least

j gcd
printoutgcd:
li $v0, 4           
la $a0, GCDtext    # prints text before gcd integer is outputted
syscall   

li	$v0,1			# print integer call code
	move	$a0, $t1	# must load into $a0 before print		#being used to print gcd
	syscall


lcm:
mult $t4, $t5 #num 1 copy * num 2 copy
mflo $t6 #stores into new register
div $t6,$t1 #multiplication divided by gcd
mflo $t7

li $v0, 4           
la $a0, LCMtext    # prints text before lcm integer is outputted
syscall   

li	$v0,1			# print integer call code
	move	$a0, $t7	# must load into $a0 before print		#being used to print lcm
	syscall



jr $ra                    # needs to be at end of code. says system function called
                    # syscall takes $v0 (and opt arguments)

                    			#variables:
                    			#$t0 = number 1
                    			#$t1 = number 2
                    			#$t2  = remainder
                    			#$t3 = 0
                    			#$t4 = number 1 copy
                    			#$t5 = number 2 copy
                    			#$t6 = num 1 * num 2
                    			#$t7 = lcm
