#include "types.h"
#include "riscv.h"
#include "param.h"
#include "defs.h"
#include "date.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;


  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}


#ifdef LAB_PGTBL
int
sys_pgaccess(void)
{
  uint64 p1;
  uint64 p2;
  int num;
  if (argaddr(0, &p1) < 0) {
    printf("explain address one failed!\n");
    return -1;
  }
  if (argint(1, &num) < 0 || num > 64) {
    printf("explain num two failed!\n");
    return -1;
  }
  if (argaddr(2, &p2) < 0) {
    printf("explain address two failed!\n");
    return -1;
  }
  struct proc* p = myproc();
  uint64 bitmap = 0;
  uint64 clr = PTE_A;
  clr = ~clr;
  int count = 0;
  for (uint64 page = p1; page < p1 + num * PGSIZE; page += PGSIZE) {
    pte_t* pte = walk(p->pagetable, page, 0);
    if (*pte & PTE_A) {
      bitmap |= (1 << count);
        //获得页置零
      *pte = (*pte) & clr;
    }
    ++count;
  }
  copyout(p->pagetable, p2, (char*) &bitmap, sizeof(bitmap));
  return 0;
}
#endif

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
