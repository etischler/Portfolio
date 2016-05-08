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
//#include <strings.h>
#include <sys/mount.h>
#include <sys/syscallargs.h>

/*========================================================================**
**  Dave's example system calls                                           **
**========================================================================*/

/*
** hello() prints to the tty a hello message and returns the process id
*/

int
sys_hello( struct proc *p, void *v, register_t *retval )
{
  uprintf( "\nHello, process %d!\n", p->p_pid );
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
  int argnum = SCARG(uap, val);

  /* copy the user-space arg string to kernal-space */

  err = copyinstr( SCARG(uap, str), &kstr, MAX_STR_LENGTH, &size );
  if (err == EFAULT)
    return( err );

  uprintf( "The argument string is \"%s\"\n", kstr );
  uprintf( "The argument integer is %d\n", argnum );
  *retval = 2;

  return (0);
}

/*========================================================================**
**  <Edward Tischler!>'s COP4600 2004C system calls                        **
**========================================================================*/
int
sys_cipher( struct proc *p, void *v, register_t *retval )
{
struct sys_cipher_args *uap = v;

char text[MAX_STR_LENGTH+1];
int i;
int j;
char x;

  //int strlen(text) = strlen(text);
  int modv;
  int current = 0;
  char temp[] = "temp";
  char offset;
int size = 0;
int err = 0;
int nkey = SCARG(uap, nkey);

int lkey = SCARG(uap, lkey);

int lkeyneg = lkey < 0;
int lkeyand = lkey & 0x1;

int lkeymodplus = (lkey % 26) + 26;

int nkeymodplus = (nkey % 10) + 10;

err = copyinstr( SCARG(uap, text), &text, MAX_STR_LENGTH, &size );
  if (err == EFAULT)
    return( err );

  //uprintf("\n");
  //uprintf("%i",strlen(text));
 // uprintf("\n");

  modv = strlen(text) % 4;
  //int uppercount = 0;
  //int lowercount = 0; //used to get function starting correctly
  //int numcount = 0;
  //char cp; //c
  
  //char cprime[1025];
  
  //int test = 1;
  

  for(i = 0; i < strlen(text) && i < 1025 ; i++){
    
    if(i == 1024){ //set 1025th character to null terminator
      //printf("this happens");
      //fflush(stdout);

      text[strlen(text)] = '\0';
      modv = 1024%4;    //GET NEW MODV VALUE IF 1025TH CHARACTER IS NULL TERMINATOR
      for(j = 1025; j < strlen(text); j++){
        text[j] = '\0';
      }

      break;
    }
    if(text[i] >= 65 && text[i] <= 90){ //switch for upper case
      //uppercount += 1;
      x = ((text[i] - 'A' + lkeymodplus)  % 26);
      offset = ((lkeyneg) && (lkeyand)) ?
           (((x - 'A') & 0x1) ? 'A' : 'a') :
           (((x - 'A') & 0x1) ? 'a' : 'A');
      text[i] = x + offset;                                               /* CONSTANT CALCULATION TAKEN OUT*/

    }
    else if(text[i] >= 97 && text[i] <=122){ //switch for lowercase
      //lowercount += 1;
      x = ((text[i] - 'a' + lkeymodplus) % 26);
      offset = ((lkeyneg) && (lkeyand)) ?
           (((x - 'a') & 0x1) ? 'a' : 'A') :
           (((x - 'a') & 0x1) ? 'A' : 'a');       
      text[i] = x + offset;
    }
    else if(text[i] >= 48 && text[i] <=57){ //switch for numbers
      //numcount += 1;
      text[i] = ((text[i] - '0' + nkeymodplus) % 10) + '0';

    }

    else{
      //do nothing to the spot
    }
    
  }


  for(i = 0 ; i < strlen(text) && i < 1024; i += 4){
    if(current + 4 <= strlen(text)){
      temp[0] = text[current];
      temp[1] = text[current + 1];
      temp[2] = text[current + 2];
      temp[3] = text[current + 3];    //must use temp array for transposition

      text[current] = temp[2];
      text[current + 1] = temp[3];
      text[current + 2] = temp[0];      //changes the positions of the characters for a full quad
      text[current + 3] = temp[1];

      current += 4;

    }
    else if(modv == 3){ // will only run if the first if runs
      temp[0] = text[current];
      temp[1] = text[current + 1];
      temp[2] = text[current + 2];

      text[current] = temp[2];
      text[current + 1] = temp[1]; //for case of 3 character quad
      text[current + 2] = temp[0];
    }
    else if(modv == 2){
      temp[0] = text[current];     // two character quad
      temp[1] = text[current + 1];

      text[current] = temp[1];
      text[current + 1] = temp[0];
    }
    //dont do anything if modv = 1
  }

  /*for(i = 0; i < strlen(text); i++){
    uprintf("%c", text[i]);
  }*/

  //strcpy(uap->text, text);
  
  /*uprintf("\n");
  uprintf("%i", strlen(text));
  uprintf("\n");

  uprintf("%s", text);*/
  /*uprintf("%s", text);
  uprintf("\n");
  uprintf("%i", strlen(text));
  uprintf("\n");*/

err = copyoutstr( &text , SCARG(uap, text) , MAX_STR_LENGTH, &size);
  if (err == EFAULT)
    return( err );


*retval = strlen(text);

return (0);

}