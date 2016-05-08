/*
 * COP4600 Adding Syscall assignment.
 * Edward Tischler
 *
 * Defines the project sys calls and kernel variables.
 *   + Process-scoped named semaphores (limited to 64 globally).
 */ 

#ifndef _SYS_COP4600_H_
#define _SYS_COP4600_H_



int cop4600_sema_init(void);

// The COP4600 process extension structure.
struct cop4600_pes;

struct cop4600_sema;

struct myslock;


int cop4600_pes_init(void);


int cop4600_pes_create(struct cop4600_pes **pes, struct proc *p);

 
int cop4600_pes_destroy(struct cop4600_pes **pes);


int sys_allocate_semaphore(struct proc *p, void *v, register_t *retval);


int sys_free_semaphore(struct proc *p, void *v, register_t *retval);


int sys_down_semaphore(struct proc *p, void *v, register_t *retval);


int sys_up_semaphore(struct proc *p, void *v, register_t *retval);

#endif _SYS_COP4600_H_