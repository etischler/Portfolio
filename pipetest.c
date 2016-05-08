#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
int main(){
  //get ready
  pid_t receiver;
  pid_t sender;
  pid_t pidnumber;

  // char buffer[26];
  int turn = 0;
  // int z = "z";
  int senderterminate = 0;
  int receiverterminate = 0;
 char phrase[] = "ZYXWVUTSRQPONMLKJIHGFEDCBA\n";
  char buffer[50];
  int fd[2];
  int count = 0;
  int othercount = 0;
  char z = 'Z';
  const void * newbuf;
   pipe(fd);
   
   receiver = fork();
   //you are in main
   if(receiver > 0){
    
     sender = fork();
   }

   //main process
   if(receiver > 0 && sender > 0){
     
     close(fd[0]);
     close(fd[1]);
     sleep(30);
     pidnumber = getpid();
     printf("Your pal, Process_");
     printf("%i",pidnumber);
     printf(" says, \"Auf Wiedersehen.\"\n");
     
   }
  
  
   if(sender == 0 && senderterminate == 0){
  
     close(fd[0]);
    
      while(count < 26){
	
       write(fd[1],phrase+count,sizeof(char));
       
       count += 1;
       sleep(1);
    
      }
      close(fd[1]);
      senderterminate = 1;
       pidnumber = getpid();
     printf("Your pal, Process_");
     printf("%i",pidnumber);
     printf(" says, \"Auf Wiedersehen.\"\n");
     
   }

  if(receiver == 0 && receiverterminate == 0){
     
  close(fd[1]);
   while(othercount<26){
    
    
  read(fd[0], buffer+othercount, sizeof(char));
  write(1,buffer+othercount,sizeof(char));
  
   othercount+=1;
     }
 
    printf("\n");
   close(fd[0]);
    pidnumber = getpid();
     printf("Your pal, Process_");
     printf("%i",pidnumber);
     printf(" says, \"Auf Wiedersehen.\"\n");
   receiverterminate = 1;
   
  }
  return 0;

}
