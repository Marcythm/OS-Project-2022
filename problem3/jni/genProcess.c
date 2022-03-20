#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

#define STUID 520021910863

int main() {
  pid_t pid = fork();
  if (pid < 0)
    return -1;

  if (pid > 0) {
    printf("%d Parent: PID = %d\n", STUID, pid);
  } else {
    printf("%d Child: PID = %d\n", STUID, getpid());
    execl("/data/misc/ptreeTestARM", "ptreeTestARM", NULL);
  }

  return 0;
}
