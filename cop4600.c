/*	$OpenBSD: cop4600.c,v 1.00 2003/07/12 01:33:27 dts Exp $	*/

#include <sys/param.h>
#include <sys/acct.h>
#include <sys/systm.h>
#include <sys/ucred.h>
#include <sys/proc.h>
#include <sys/timeb.h>
#include <sys/times.h>
#include <sys/malloc.h>
#include <sys/filedesc.h>
#include <sys/pool.h>

#include <sys/mount.h>
#include <sys/syscallargs.h>

//added by ed
#include <sys/cop4600.h>
#include <sys/queue.h>
#include <sys/types.h>
#include <sys/lock.h>

/*========================================================================**
**  Dave's example system calls                                           **
**========================================================================*/

/*
** hello() uprints to the tty a hello message and returns the process id
*/

int
sys_hello( struct proc *p, void *v, register_t *retval )
{
  //uprintf( "\nHello, process %d!\n", p->p_pid );

  //uprintf("number of processes: %i \n", nprocs);

  *retval = p->p_pid;

  return (0);
}

/*
** showargs() demonstrates passing arguments to the kernel
*/

#define MAX_STR_LENGTH  1024

int
sys_showargs( struct proc *p, void *v, register_t *retval )
{
  /* The arguments are passed in a structure defined as:
  **
  **  struct sys_showargs_args
  **  {
  **      syscallarg(char *) str;
  **      syscallarg(int)    val;
  **  }
  */

  struct sys_showargs_args *uap = v;

  char kstr[MAX_STR_LENGTH+1]; /* will hold kernal-space copy of uap->str */
  int err = 0;
  int size = 0;

  /* copy the user-space arg string to kernal-space */

  err = copyinstr( SCARG(uap, str), &kstr, MAX_STR_LENGTH, &size );
  if (err == EFAULT)
    return( err );

  //uprintf( "The argument string is \"%s\"\n", kstr );
  //uprintf( "The argument integer is %d\n", SCARG(uap, val) );
  *retval = 0;

  return (0);
}

/*========================================================================**
**  <Edward Tischler>'s COP4600 20015C system calls                        **
**========================================================================*/
//extra structs for part 5
//this is needed to set up the pools
//struct pool sema_pool;
//struct pool pes_pool;


struct cop4600_sema {

  SIMPLEQ_ENTRY(cop4600_sema) sema_entries;

  char name[32];
  int count;

  struct simplelock myslock;
  /* todo
  q holding waiting process ids that will be woken up as count goes non negative
  add lock
  */

  SIMPLEQ_HEAD(otherlisthead,cop4600_pes) otherhead; //must be proc to hold the process
};

//TODO add a sema create
                          //maybe?
//TODO add a sema destroy

int cop4600_sema_init() {
  
  /*pool_init(&sema_pool, sizeof(struct cop4600_sema), 0, 0, 0, "cop4600semapl", //this will create the pool to hold the structs for semaphores
      &pool_allocator_nointr);*/

  return 0;
}


struct cop4600_pes {

  SIMPLEQ_ENTRY(cop4600_pes) proc_entries;

  /*todo
  q holding semaphores belonging to this process
  */
  SIMPLEQ_HEAD(listhead,cop4600_sema) head;

  struct proc* thisprocess;

  int should_econn_abort;


};


int cop4600_pes_init() {
  
  /*pool_init(&pes_pool, sizeof(struct cop4600_pes), 0, 0, 0, "cop4600pespl",  //this will create the pool to hold the structs for semaphores
      &pool_allocator_nointr);*/



  return 0;
}


int cop4600_pes_create(struct cop4600_pes **pes, struct proc *p) {
  
  /**pes = pool_get(&pes_pool, PR_WAITOK);*/
 // 
  ////uprintf("process create called\n");

  *pes = malloc(sizeof(struct cop4600_pes), M_TEMP, M_NOWAIT);
  SIMPLEQ_INIT(&(*pes)->head);
  (*pes)->thisprocess = p;
  (*pes)->should_econn_abort = 0;
  //(*pes)->myval = 2;

  return 0;
}


int cop4600_pes_destroy(struct cop4600_pes **pes) {
  // TODO: Destroy things internal to pes

  // Put the destroyed process extension back in the pool.
  //pool_put(&pes_pool, *pes);
  // Process extension no longer assigned.
  //pid_t curprocess = (*pes)->thisprocess->p_pid;
  struct cop4600_pes *waiting_queuenodes;
  struct cop4600_sema *np;
  //struct cop4600_sema *othernp;

  np = SIMPLEQ_FIRST(&((*pes)->head));


  if(np!=NULL){
     for(waiting_queuenodes = SIMPLEQ_FIRST(&(np->otherhead));waiting_queuenodes!=NULL;waiting_queuenodes = SIMPLEQ_NEXT(waiting_queuenodes,proc_entries)){

       waiting_queuenodes->should_econn_abort = 1;
       wakeup((waiting_queuenodes));     
       //uprintf("process woken up and returned from free on proc exit\n");

     }
   
   }
   if(np!=NULL){
     while(! SIMPLEQ_EMPTY( &((np)->otherhead) )){
            //uprintf("processes being removed from wait queue when semaphore freed from proc exit\n");
            SIMPLEQ_REMOVE_HEAD( &((np)->otherhead), (waiting_queuenodes = SIMPLEQ_FIRST(&((np)->otherhead))), proc_entries );


      }
    }


    
if(! SIMPLEQ_EMPTY( &((*pes)->head))){
SIMPLEQ_REMOVE_HEAD( &((*pes)->head), (np = SIMPLEQ_FIRST(&((*pes)->head))), sema_entries );
    free(np, M_TEMP);
    //uprintf("semaphore freed from a process upon process exit \n");
}

 

if(! SIMPLEQ_EMPTY( &((*pes)->head))){
  cop4600_pes_destroy((pes));
}



////uprintf("9\n");
else{
  free(*pes,M_TEMP);
  ////uprintf("10\n");
  *pes = NULL;
}
  return 0;
}


int sys_allocate_semaphore(struct proc *p, void *v, register_t *retval) {
  
  struct sys_allocate_semaphore_args *uap = v;

  char kstr[MAX_STR_LENGTH+1]; /* will hold kernal-space copy of uap->str */
  int err = 0;
  int size = 0;
  int samename = 0;

  struct cop4600_sema *np;

  struct cop4600_sema *sema_pointer = /*pool_get(&sema_pool, PR_WAITOK);*/ malloc(sizeof(struct cop4600_sema), M_TEMP, M_NOWAIT);
  /* copy the user-space arg string to kernal-space */

  err = copyinstr( SCARG(uap, name), &kstr, MAX_STR_LENGTH, &size );
  if (err == EFAULT)
    return( err );

if(strlen(kstr) > 31){
  free(sema_pointer, M_TEMP);
  return (ENAMETOOLONG);
}

else{

//check to see if there is already a semaphore with that name
for(np = SIMPLEQ_FIRST(&(p->pes->head));np!=NULL;np = SIMPLEQ_NEXT(np,sema_entries)){
  if(strcmp(kstr, np->name) == 0){
    //uprintf("same name sorry\n");
    samename = 1;
    free(sema_pointer, M_TEMP);
    return (EEXIST);
  }
}

  //add characteristics
//WONT GET HERE IF SAME NAME BECAUSE OF PREVIOUS RETURN
  strncpy(sema_pointer->name, kstr, 32);
  sema_pointer->name[31] = '\0';
  sema_pointer->count = SCARG(uap, initial_count);
  //sema_pointer->lock = malloc(sizeof(struct myslock), M_TEMP, M_NOWAIT); NOT ACCURATE
  simple_lock_init(&(sema_pointer->myslock));
  SIMPLEQ_INIT(&(sema_pointer)->otherhead);
  //uprintf("semaphore created in a process \n");
  SIMPLEQ_INSERT_TAIL(&(p->pes->head), sema_pointer, sema_entries);
}


  /*for(np = SIMPLEQ_FIRST(&(p->pes->head));np!=NULL; np = SIMPLEQ_NEXT(np,sema_entries)){
    //uprintf("this is the name: %s", np->name);
    //uprintf("\n");
    ////uprintf("%i",size);
  }*/


  *retval = 0;
  return (0);
}


int sys_down_semaphore(struct proc *p, void *v, register_t *retval) {
int parentend = 0;
int foundsemaphore = 0;
struct cop4600_sema *np;
struct proc *pcheck;
//int i = 0;

struct sys_allocate_semaphore_args *uap = v;
  char kstr[MAX_STR_LENGTH+1]; /* will hold kernal-space copy of uap->str */
  int err = 0;
  int size = 0;
 // pid_t currentpid;
  //int i = 0;

   err = copyinstr( SCARG(uap, name), &kstr, MAX_STR_LENGTH, &size );
  if (err == EFAULT)
    return( err );
pcheck = p;
//first begin with seeing if the semaphore exists
  while(parentend == 0){
//for( i = 0; i < 35; i++){
    for(np = SIMPLEQ_FIRST(&(pcheck->pes->head));np!=NULL;np = SIMPLEQ_NEXT(np,sema_entries)){

      if(strcmp(kstr, np->name) == 0){
        
        //need to start lock
        simple_lock(&(np->myslock));
        np->count -= 1;
        foundsemaphore = 1;
        parentend = 1; //this will ensure it does not try to search the parent
        //uprintf("new semaphore count: %i \n", np->count);
        //free(sema_pointer, M_TEMP);
        //now if it is negative I will need to add this process to the waiting queue
        if(np->count < 0){
          //SIMPLEQ_INSERT_TAIL(&(p->pes->head), sema_pointer, sema_entries);  ------ for reference
         
          SIMPLEQ_INSERT_TAIL(&(np->otherhead), p->pes , proc_entries);

          

          //make process wait now
          //uprintf("putting to sleep\n");
          //uprintf("name of semaphore going to sleep: %s\n", np->name);
         // //uprintf("value of tsleep address %p\n", (p->pes));
          tsleep((p->pes),0, "tsleeping" , 0);
          ////uprintf("value of tsleep address %s\n", &(p->pes));

          //wakeup(p);
          //uprintf("process has been woken up\n");

          if(p->pes->should_econn_abort == 1){
            p->pes->should_econn_abort = 0;
            return (ECONNABORTED);
          }

          ////uprintf("this happens");
          simple_unlock(&(np->myslock));
          //need to end lock
        }
      }

    }
    //currentpid = getpid();
    if(foundsemaphore == 0){
      if(pcheck->p_pid == 1){
        ////uprintf("1\n");
        parentend = 1; //this will prevent faulting
      }
      else{
       // //uprintf("2\n");
        pcheck = pcheck->p_pptr; //will change process to parent to find
      }
    }
    
  }

  if(foundsemaphore == 0){
    //uprintf("semaphore not found for down\n");
    return (ENOENT);
  }


  
  *retval = 0;
  return (0);
}


int sys_up_semaphore(struct proc *p, void *v, register_t *retval) {
  // TODO
int parentend = 0;
int foundsemaphore = 0;
struct cop4600_sema *np;

struct cop4600_pes *waiting_queuenodes;
struct proc *pcheck;
struct sys_allocate_semaphore_args *uap = v;
  char kstr[MAX_STR_LENGTH+1]; /* will hold kernal-space copy of uap->str */
  int err = 0;
  int size = 0;
 // pid_t currentpid;
  //int i = 0;

   err = copyinstr( SCARG(uap, name), &kstr, MAX_STR_LENGTH, &size );
  if (err == EFAULT)
    return( err );
pcheck = p;
//first begin with seeing if the semaphore exists
  while(parentend == 0){
//for( i = 0; i < 35; i++){
    for(np = SIMPLEQ_FIRST(&(pcheck->pes->head));np!=NULL;np = SIMPLEQ_NEXT(np,sema_entries)){

      if(strcmp(kstr, np->name) == 0){
        /*for(waiting_queuenodes = SIMPLEQ_FIRST(&(np->otherhead));waiting_queuenodes!=NULL;waiting_queuenodes = SIMPLEQ_NEXT(waiting_queuenodes,proc_entries)){
          //uprintf("addresses in the queue for wakeup: %p\n", waiting_queuenodes);
        }*/
        //need to start lock
        simple_lock(&(np->myslock));
        np->count += 1;
        foundsemaphore = 1;
        parentend = 1; //this will ensure it does not try to search the parent
        //uprintf("new semaphore count: %i \n", np->count);
        //free(sema_pointer, M_TEMP);
        //now if it is negative I will need to add this process to the waiting queue
        if(np->count <= 0){
          ////uprintf("first\n");
          if(!SIMPLEQ_EMPTY(&(np->otherhead)) ){ //if there is a waiting process wake it up fifo
            ////uprintf("sencond\n");
            wakeup((SIMPLEQ_FIRST(&(np->otherhead))));
            ////uprintf("wake up address %p\n", (SIMPLEQ_FIRST(&(np->otherhead))));
            //TODO
           // //uprintf("thrid\n");
                SIMPLEQ_REMOVE_HEAD( &((np)->otherhead), (waiting_queuenodes = SIMPLEQ_FIRST(&((np)->otherhead))), proc_entries );
               // SIMPLEQ_REMOVE_HEAD( &((*pes)->head), (np = SIMPLEQ_FIRST(&((*pes)->head))), sema_entries ); ----- for reference
                ////uprintf("fourth\n");
              simple_unlock(&(np->myslock));
          }
          else{
            //uprintf("wait queue is empty\n");
          }

        }
      }

    }
    //currentpid = getpid();
    if(foundsemaphore == 0){
      if(pcheck->p_pid == 1){
        ////uprintf("1\n");
        parentend = 1; //this will prevent faulting
      }
      else{
       // //uprintf("2\n");
        pcheck = pcheck->p_pptr; //will change process to parent to find
      }
    }
    
  }

  if(foundsemaphore == 0){
    //uprintf("semaphore not found in up\n");
    return (ENOENT);
  }

  




  *retval = 0;
  return (0);
}

int sys_free_semaphore(struct proc *p, void *v, register_t *retval) {
  
int parentend = 0;
int foundsemaphore = 0;
struct cop4600_sema *np;
struct cop4600_sema *othernp;
struct proc *pcheck;
// curprocess = p->p_pid;

struct cop4600_pes *waiting_queuenodes;

struct sys_allocate_semaphore_args *uap = v;
  char kstr[MAX_STR_LENGTH+1]; /* will hold kernal-space copy of uap->str */
  int err = 0;
  int size = 0;
 // pid_t currentpid;
  //int i = 0;

   err = copyinstr( SCARG(uap, name), &kstr, MAX_STR_LENGTH, &size );
  if (err == EFAULT)
    return( err );
pcheck = p;
//first begin with seeing if the semaphore exists
  while(parentend == 0){
//for( i = 0; i < 35; i++){
    for(np = SIMPLEQ_FIRST(&(pcheck->pes->head));np!=NULL;np = SIMPLEQ_NEXT(np,sema_entries)){

      if(strcmp(kstr, np->name) == 0){

        simple_lock(&(np->myslock));
        othernp = np;
        parentend = 1;
        foundsemaphore = 1;

        for(waiting_queuenodes = SIMPLEQ_FIRST(&(np->otherhead));waiting_queuenodes!=NULL;waiting_queuenodes = SIMPLEQ_NEXT(waiting_queuenodes,proc_entries)){

        // //uprintf("wake up called. count this for number of processes in wait queue, address %p\n", waiting_queuenodes);
         waiting_queuenodes->should_econn_abort = 1;
          wakeup((waiting_queuenodes));

          //if(waiting_queuenodes->thisprocess->p_pid != curprocess){
            //uprintf("process woken up and returned from free\n");
            //return (ECONNABORTED);
          //}

        }

        while(! SIMPLEQ_EMPTY( &((np)->otherhead) )){
          //uprintf("processes being removed from wait queue when semaphore freed\n");
          SIMPLEQ_REMOVE_HEAD( &((np)->otherhead), (waiting_queuenodes = SIMPLEQ_FIRST(&((np)->otherhead))), proc_entries );

        }

        simple_unlock(&(np->myslock));       

      }
    }

    if(foundsemaphore == 0){
      if(pcheck->p_pid == 1){
        ////uprintf("1\n");
        parentend = 1; //this will prevent faulting
      }
      else{
        ////uprintf("2\n");
        pcheck = pcheck->p_pptr; //will change process to parent to find
      }
    }
      if(foundsemaphore == 1){
       // //uprintf("semaphore freed count should be 0\n");
        SIMPLEQ_REMOVE_HEAD( &(pcheck->pes->head), SIMPLEQ_FIRST(&(pcheck->pes->head)), sema_entries );
        free(othernp, M_TEMP);
        //othernp = SIMPLEQ_NEXT()
      }
  

  }
    //currentpid = getpid();
    

  
////uprintf("number of semaphores after free: %i\n", i);
  if(foundsemaphore == 0){
    //uprintf("semaphore not found in free semaphore\n");
    return (ENOENT);
  }




  *retval = 0;
  return (0);
}


