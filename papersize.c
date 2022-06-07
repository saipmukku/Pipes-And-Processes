#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "safe-fork.h"

int main(void) {

  pid_t pid;
  int fd[2];
  int error = 0;

  pipe(fd);
  pid = safe_fork();

  if(pid > 0) {

    int word_count = 0;

    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    scanf("%d", &word_count);
    
    if(word_count >= 200) {

      printf("Long enough!\n");

    } else {

      printf("Too short!\n");
      error = 1;

    }

  } else if(pid == 0) {

    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execl("/usr/bin/wc", "wc", "-w", NULL);

  }

  return error;

}
