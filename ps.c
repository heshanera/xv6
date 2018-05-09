#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_STRUCTS 10

struct procdetails {
  int pid;		  // Process ID
  int psize;		  // Size of process memory (bytes)
  char pname[16];	  // Process name
  int priority;		  // Priority of the process
};

int main(void) {

  struct procdetails proc_det_arr[NUM_STRUCTS];
  struct procdetails *p;
  
  int return_val = getprocessinfo(
      NUM_STRUCTS*sizeof(struct procdetails),
      &proc_det_arr
  );

  p = &proc_det_arr[0];

  printf(
    1,"%s    %s    %s    %s\n",
    "PID","MEMORY(Bytes)","PRIORITY","PROCESS"
  );

  while( p != &proc_det_arr[NUM_STRUCTS-1]) {
    if ((p->pid == 0 ) && (p->psize == 0)) break;
    printf(
      1," %d       %d             %d        %s\n",

      p->pid, p->psize, p->priority, p->pname
    );
    p++;
  }

  printf(1,"\nProgram %d \n\n",return_val);
  exit();
}
