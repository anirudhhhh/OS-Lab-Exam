#include "kernel/types.h"
#include "user/user.h"

#define NCHILDREN 3
#define WORK 20000000

int
main(void)
{
  int priorities[NCHILDREN] = {5, 10, 15};
  int parent = getpid();

  set_priority(parent, 1);
  for (int i = 0; i < NCHILDREN; i++) {
    int pid = fork();
    if (pid < 0)
      exit(1);
    if (pid == 0) {
      int mypid = getpid();
      if (set_priority(mypid, priorities[i]) < 0)
        exit(1);

      for (volatile int j = 0; j < WORK; j++)
        ;

      printf("priority %d finished\n", priorities[i]);
      exit(0);
    }
  }

  for (int i = 0; i < NCHILDREN; i++)
    wait(0);
  printf("Done\n");
  exit(0);
}
