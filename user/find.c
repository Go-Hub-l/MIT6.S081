#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char* path) {
  // static char buf[DIRSIZ + 1];
  char* p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  // if (strlen(p) >= DIRSIZ)
  return p;
// memmove(buf, p, strlen(p));
// memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
// return buf;
}

void find(char* path, char* pattern) {
  //打开文件/目录
  // printf("[%s]===[%s]\n", path, pattern);
  int fd;
  char buf[512], * p;
  struct dirent de;
  struct stat st;

  memset(buf, 0, sizeof(buf));
  memcpy(buf, path, strlen(path));


  //打开文件/目录
  if ((fd = open(path, 0)) < 0) {
    // printf("[%s]===[%s]\n", path, pattern);
    fprintf(2, "find: cannot open %s\n", path);
    exit(1);
  }

  //查看打开地文件/目录信息
  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", path);
    exit(1);
  }

  switch (st.type) {
  case T_FILE:
    // printf("FILE==path[%s]===subPath[%s]=======\n", path, fmtname(path));
    //检查是否和pattern相同
    if (strcmp(fmtname(path), pattern) == 0) {
      printf("%s\n", path);
    }
    break;
  case T_DIR:
    // printf("DIR============\n");
    //打开目录
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0 ||
        strcmp(de.name, ".") == 0 ||
        strcmp(de.name, "..") == 0)
        continue;
      //将目录路径添加到buf中
      p = buf + strlen(buf);
      *p++ = '/';
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = '\0';
      // printf("buf=====[%s]----[%s]\n", buf, de.name);
      //递归下一层目录
      find(buf, pattern);
      *(--p) = '\0';
    }
    break;

  default:
    break;
  }
  close(fd);

}

int
main(int argc, char* argv[]) {
  if (argc < 3) {
    fprintf(2, "inut error! Need 3 argument\n");
    exit(1);
  }
  find(argv[1], argv[2]);

  exit(0);
}
