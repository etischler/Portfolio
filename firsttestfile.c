#include <sys/syscall.h>
#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

int main(){

pid_t forkpid = fork();

pid_t otherforkpid;

///FIRST SHOW DOWN AND UP WORKING

if(forkpid > 0){
	otherforkpid = fork();

}

if(forkpid > 0 && otherforkpid > 0){
	printf("Starting 3 process test\n");
printf("Testing up and down\n");
	syscall(291, "charlie", 1);
	printf("Semaphore allocated\n");
	printf("Parent downing semaphore\n");
	syscall(292,"charlie");
	printf("Count still not negative downing again (should sleep)\n");
	syscall(292, "charlie");

}
sleep(3);
if(forkpid == 0){
	printf("Child up-ing semaphore owned by parent\n");
	syscall(293,"charlie");

}


if(otherforkpid == 0){
printf("Other child up-ing non existant semaphore\n");
}
printf("process finished 1st test\n");

sleep(3);
//TEST FOR FREE
if(forkpid > 0 && otherforkpid > 0){
	printf("Starting free test(2nd test)\n");
	printf("Parent downing semaphore to sleep\n");
	syscall(292,"charlie");
}

sleep(6);
if(forkpid==0){
	printf("Child freeing parent's semaphore\n");
	syscall(294,"charlie");
}


printf("Process finished 2nd test\n");
sleep(5);


if(forkpid > 0 && otherforkpid > 0){
	printf("Starting automatic destruction test (parent only)\n");
	printf("Allocating semaphore\n");
	syscall(291,"allison",1);
	printf("Results can't be seen but if there is no fault then semaphore destroyed\n");
}

if(forkpid==0){
sleep(2);
}

if(otherforkpid==0){
	sleep(2);
}

printf("Process Finished Test\n");
return 0;

}