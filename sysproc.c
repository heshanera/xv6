#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// change the priority of the current process
int sys_setpriority(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  proc->priority = (int)n;
  return n;
}

int sys_getprocessinfo(void)
{
  int size;
  char * buf;
  char * s;
  int i = 0;
  struct proc * process;

  if (argint(0, &size) < 0) {
    return -1;
  }

  if (argptr(1, &buf,size) < 0) {
    return -1;
  }

  s = buf;
  process = getptable();

  while(buf + size > s) {
    *(int *)s = process->pid;
    s += 4;
    *(int *)s = process->sz;
    s += 4;
    i =  0;
    while( i < 16){
      *s = *(process->name+i);
      s++; i++;
    }
    *(int *)s = process->priority;
    s += 4;
    *(int *)s = process->state;
    s += 4;
    process++;
  }

  return 1;
}
