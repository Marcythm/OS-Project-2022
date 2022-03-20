#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

#define STUID "520021910863"

int main() {
  pid_t pid = fork();

  if (pid < 0)
    return -1;
  else if (pid == 0) {
    printf(STUID " Child: PID = %d\n", getpid());
    execl("/data/misc/ptreeTestARM", "ptreeTestARM", NULL);
  } else {
    printf(STUID " Parent: PID = %d\n", getpid());
    wait(NULL);
  }

  return 0;
}
