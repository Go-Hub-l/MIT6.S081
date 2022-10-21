#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char* argv[]) {
  int fd[2];
  pipe(fd);
  int pid = fork();
  if (pid == 0) {
    char ch;
    if (read(fd[0], &ch, 1) > 0) {
      fprintf(1, "%d: received ping\n", getpid());
    }
    close(fd[0]);
    char buf = 'T';
    write(fd[1], &buf, 1);
    close(fd[1]);
  } else if (pid > 0) {
    //向管道写
    char buf = 'T';
    write(fd[1], &buf, 1);
    close(fd[1]);
    char ch;
    if (read(fd[0], &ch, 1) > 0) {
      fprintf(1, "%d: received pong\n", getpid());
    }
    close(fd[0]);
    wait(0);
  } else {
    fprintf(2, "fork failed\n");
    exit(1);
  }
  exit(0);
}
