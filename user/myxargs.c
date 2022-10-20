// #include "kernel/types.h"
// #include "kernel/stat.h"
// #include "user/user.h"
// #include "kernel/fs.h"
#include "kernel/param.h"


#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int
main(int argc, char* argv[]) {
  if (argc < 3) {
    fprintf(2, "Need at least three argument!\n");
    exit(1);
  }
  char ch;
  char buf[MAXARG][1024] = { 0 };

  // int index = 0;
  // int flag = 0;


  printf("start=========================\n");
  while ((read(0, (char*) &ch, 1)) > 0 && ch != '\n') {
    printf("2 ch[%c]=========================\n", ch);
    // //读到'|'就fork
    // if (ch == '|') {
    //   printf("3=========================\n");
    //   int pid = fork();
    //   if (pid > 0) {
    //     wait(0);
    //     //打印保存的数据参数
    //     buf[++index][0] = 0;
    //     //调用exec
    //     exec(buf[0], (char**) buf);
    //   } else if (pid == 0) {
    //     printf("4=========================\n");
    //     char cmd[512];
    //     memset(cmd, 0, sizeof(cmd));
    //     int flag = 0;
    //     char ch;
    //     while (flag == 0 ||
    //       (ch = read(0, (char*) &ch, 1)) != ' ') {
    //       if (ch == ' ')
    //         continue;
    //       cmd[flag++] = ch;
    //     }
    //     //判断收到的命令是不是xargs
    //     if (strcmp(cmd, "xargs") != 0) {
    //       fprintf(2, "cmd error!\n");
    //       exit(1);
    //     }
    //     //继续读接下来的数据
    //     flag = 0;
    //     int index = 0;
    //     char args[MAXARG][1024];
    //     while (flag == 0 || (ch = read(0, (char*) &ch, 1)) != '\n') {
    //       if (ch == ' ' && flag == 0) {
    //         continue;
    //       } else if (ch == ' ') {
    //         args[index][flag] = '\0';
    //         flag = 0;
    //         ++index;
    //       }
    //       args[index][flag] = ch;
    //     }
    //     args[++index][0] = 0;
    //     //调用exec
    //     exec(args[0], (char**) args);
    //   } else {
    //     fprintf(2, "fork failed!\n");
    //     exit(1);
    //   }
    //   break;
    // } else {
    //   printf("5=========================\n");
    //   if (ch == ' ' && flag == 0) {
    //     continue;
    //   } else if (ch == ' ') {
    //     buf[index][flag] = '\0';
    //     ++index;
    //     flag = 0;
    //   }
    //   buf[index][flag++] = ch;
    // }
  }

  printf("end================[%d]=========\n", sizeof(buf));

  exit(0);
}
