#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int isPrime(int val) {
  for (int i = 2; i < val; ++i) {
    if (val % i == 0)
      return 0;
  }
  return 1;
}
int
main(int argc, char* argv[]) {
  int fd[2];

  pipe(fd);

  int pid = fork();
  if (pid == 0) {
    close(fd[1]);
    int val;
    int childFd[2];
    while (read(fd[0], (int*) &val, 4) > 0) {
      if (isPrime(val) == 1) {
        pipe(childFd);
        int p = fork();
        if (p > 0) {
          close(childFd[0]);
        //向管道里写
          write(childFd[1], (const int*) &val, 4);//29  31 写入出错
          wait(0);
        } else if (p == 0) {
          //关闭子进程的写端
          close(childFd[1]);
          int v;
          if (read(childFd[0], (int*) &v, 4) < 0) {
            fprintf(2, "read failed\n");
            exit(1);
          }
          fprintf(1, "prime %d\n", v);
            //关闭子进程的读端
          close(childFd[0]);
          exit(0);
        } else {
          fprintf(2, "child fork failed\n");
          exit(1);
        }

      }
      // wait(0);
    }
    close(fd[0]);
    close(childFd[1]);
    exit(0);
  } else if (pid > 0) {
    close(fd[0]);
    for (int i = 2; i <= 35; ++i) {
      write(fd[1], (const int*) &i, 4);
    }
    close(fd[1]);
    wait(0);
  } else {
    fprintf(2, "fork failed\n");
    exit(1);
  }
  exit(0);
}
