#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
  int status;
  pid_t pid, tcpid;
  pid_t cpid = fork();
  if (cpid > 0){
    pid = getpid();
    printf("[%d] parent of [%d]\n", pid, cpid);
    tcpid = wait(&status);
    printf("[%d] bye %d(%d)\n", pid, cpid, status);
  }
  else if (cpid == 0) {
    pid = getpid();
    printf("[%d] child\n", pid);
    exit(1);
  }

  return 0;
}
