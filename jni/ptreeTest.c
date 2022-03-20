#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>

#define __NR_ptreecall 356
#define BUFFERSIZE 1000

struct prinfo{
  pid_t parent_pid; /* process id of parent, set 0 if it has no parent*/
  pid_t pid; /* process id */
  pid_t first_child_pid; /* pid of youngest child, set 0 if it has no child */
  pid_t next_sibling_pid; /* pid of older sibling, set 0 if it has no sibling*/
  long state; /* current state of process */
  long uid; /* user id of process owner */
  char comm[64]; /* name of program executed */
};

int main() {
  int *nr = malloc(sizeof(int));
  struct prinfo *buf = malloc(BUFFERSIZE * sizeof(struct prinfo));

  if(buf == NULL || nr == NULL)
    return -1;

  if (syscall(__NR_ptreecall, buf, nr) == -1)
    return -1;

  printf("%d processes totally\n", *nr);
  int indent = 0, i = 0, j = 0;
  for (i = 0; i < *nr; i++) {
    if (i != 0 && buf[i-1].pid == buf[i].parent_pid)
      indent++;
    else if (buf[i-1].parent_pid != buf[i].parent_pid)
      indent--;

    for (j = 0; j < indent; j++)
      printf("  ");

    printf("%s,%d,%ld,%d,%d,%d,%d\n",
      buf[i].comm, buf[i].pid, buf[i].state, buf[i].parent_pid,
      buf[i].first_child_pid, buf[i].next_sibling_pid, buf[i].uid);
  }

  free(buf);
  free(nr);

  return 0;
}
