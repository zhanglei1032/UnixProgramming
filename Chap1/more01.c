/* more
 * 读取并打印24行然后暂停
 */

#include <stdio.h>
#define PAGELEN 24
#define LINELEN 512
void do_more(FILE *);
int see_more();

int main(int argc, char const *argv[]) {
  FILE *fp;
  //more后面不加参数
  if (argc == 1) {
    do_more(stdin);
  } else {
    //循环打开more命令后面跟着的所有文件，执行do_more
    while (--argc) {
      if ((fp = fopen(* ++argv, "r")) != NULL) {
        do_more(fp);
        fclose(fp);
      } else {
        exit(1);
      }
    }
  }
  return 0;
}


void do_more(FILE *fp) {
  char line[LINELEN];
  int num_of_lines = 0;
  int see_more(), reply;
  //从fp指向的文件中读取LINELEN个字符到line数组中
  while ( fgets(line, LINELEN, fp)) {
    //输出pagelen行后，执行see_more,等待输入参数
    if (num_of_lines == PAGELEN) {
      reply = see_more();
      if ( reply == 0) {
        break;
      }
      num_of_lines -= reply;
    }
    //每次循环都把line的内容输出，遇到错误退出
    if (fputs(line, stdout) == EOF) {
      //fputs返回EOF写入失败
      exit(1);
    }
    num_of_lines++;
  }
}


int see_more(){
  int c;
  //反白显示more？]
  printf("\033[7m more?]\033[m");
  while ((c = getchar()) != EOF) {
  //按q退出，按空格再显示PAGELEN行，回车多显示一行
    if ( c == 'q') {
      return 0;
    }
    if ( c == ' '){
      return PAGELEN;
    }
    if ( c == '\n') {
      return 1;
    }
  }
  return 0;
}
