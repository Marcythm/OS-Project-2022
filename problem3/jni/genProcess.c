// the source file of generating a child process
// and call ptree syscall in child process
// to show the relationship between it and its parent

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
    // execute ptree syscall in child process
    execl("/data/misc/ptreeTestARM", "ptreeTestARM", NULL);
  } else {
    printf(STUID " Parent: PID = %d\n", getpid());
    wait(NULL);
  }

  return 0;
}
