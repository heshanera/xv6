#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
  printf(1,"Background service started... \n");
  setpriority(1);
  while(1){
    //printf(1,".");
    sleep(5);
  }
}
