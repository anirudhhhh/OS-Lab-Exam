#include "kernel/types.h"
#include "user/user.h"

#define PGSIZE 4096

int
main(void)
{
  char *page = sbrk(PGSIZE);
  int status;

  if (page == (char *)-1) {
    printf("prottest: sbrk failed\n");
    exit(1);
  }

  page[0] = 'A';
  printf("read after mprotect: %c\n", page[0]);
  if (mprotect(page, 1) < 0) {
    printf("prottest: mprotect failed\n");
    exit(1);
  }
  printf("read-only page still reads: %c\n", page[0]);

  int pid = fork();
  if (pid < 0) {
    printf("prottest: fork failed\n");
    exit(1);
  }
  if (pid == 0) {
    page[0] = 'B';
    printf("prottest: child write unexpectedly succeeded\n");
    exit(1);
  }
  wait(&status);
  printf("parent after child fault still sees: %c\n", page[0]);

  if (munprotect(page, 1) < 0) {
    printf("prottest: munprotect failed\n");
    exit(1);
  }
  page[0] = 'C';
  printf("write after munprotect: %c\n", page[0]);

  printf("unaligned mprotect: %d\n", mprotect(page + 1, 1));
  printf("zero-length mprotect: %d\n", mprotect(page, 0));
  printf("out-of-range mprotect: %d\n", mprotect(page, 2));
  exit(0);
}
