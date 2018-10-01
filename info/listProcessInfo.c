#include <linux/kernel.h>
#include <linux/init.h>
//The <sched.h> header defines the sched_param structure, which contains the scheduling parameters required for implementation 
//of each supported scheduling policy. This structure contains at least the following member:
#include <linux/sched.h>      //Contains the struct task_struct *proces which can be used to list the various processes
#include <linux/syscalls.h>   //Now to the file include/linux/syscalls.h, add the prototype of the system call.
#include <asm/uaccess.h>      //copy_to_user is defined in this 
#include "processInfo.h"
int myForkCounter;
int myvForkCounter;
int myExecVeCounter;
int myCloneCounter; 
EXPORT_SYMBOL(myForkCounter);
EXPORT_SYMBOL(myvForkCounter);
EXPORT_SYMBOL(myExecVeCounter);
EXPORT_SYMBOL(myCloneCounter);
int init_module(void)
{
    //printk(KERN_INFO "Hello world 1.\n");
    myForkCounter=0;
    myvForkCounter=0;
    myExecVeCounter=0;
    myCloneCounter=0;
	return 0;
}

asmlinkage long sys_listingProcessInfo(void) {

    struct task_struct *proces;
 
    for_each_process(proces) {
 
    printk(
      "Process: %s\n \
       PID_Number: %ld\n \
       Process State: %ld\n \
       Priority: %ld\n \
       RT_Priority: %ld\n \
       Static Priority: %ld\n \
       Normal Priority: %ld\n", \
       proces->comm, \
       (long)task_pid_nr(proces), \
       (long)proces->state, \
       (long)proces->prio, \
       (long)proces->rt_priority, \
       (long)proces->static_prio, \
       (long)proces->normal_prio \
    );
  
  
   if(proces->parent) 
      printk(
        "Parent process: %s, \
         PID_Number: %ld", \ 
         proces->parent->comm, \
         (long)task_pid_nr(proces->parent) \
      );
  
   printk("\n\n");
  
  }
  
  return 0;
}

asmlinkage long sys_listingCountInfo(unsigned long fCounter,unsigned long vFCounter,unsigned long eCounter,unsigned long cCounter)
{
	/*printk(
		"Fork Called:   %d\n \
		 vFork Called:  %d\n \
		 Execve Called: %d\n \
		 Clone Called:  %d\n", \
		 myForkCounter, \
		 myvForkCounter, \
		 myExecVeCounter, \
		 myCloneCounter \
	);*/
	printk("---The value of fCounter:%d\n",(int *) fCounter);
	printk("---The value of vFCounter:%d\n",(int *) vFCounter);
	printk("---The value of eCounter:%d\n",(int *) eCounter);
	printk("---The value of cCounter:%d\n",(int *) cCounter);
	
	/*
	int r1=copy_to_user ((int *) fCounter, &myForkCounter, sizeof(myForkCounter));
	int r2=copy_to_user (vFCounter, &myvForkCounter, sizeof(myvForkCounter));
	int r3=copy_to_user ((int *) eCounter, &myExecVeCounter, sizeof(myExecVeCounter));
	int r4=copy_to_user (cCounter, &myCloneCounter, sizeof(myCloneCounter));
	
	printk("r1=%d, r2=%d, r3=%d, r4=%d\n",r1,r2,r3,r4);
	printk("---The number of various calls\n");
	printk("Fork Called:    %d\n",myForkCounter);
	printk("vFork Called:   %d\n",myvForkCounter);
	printk("Execve Called:  %d\n",myExecVeCounter);
	printk("Clone Called:   %d\n",myCloneCounter);
	*/
	return 0;
}

asmlinkage long sys_resetCountInfo(void)
{
	printk("\n---Resetting the Values of the Counters---\n");
	myForkCounter=0;
    myvForkCounter=0;
    myExecVeCounter=0;
    myCloneCounter=0;
	return 0;
}
