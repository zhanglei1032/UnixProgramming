/* more第二版
 * 读取并打印24行然后暂停
 * 改善了第一版执行 ls /bin | more 时，数据显示24后，继续打印的bug
 */

#include <stdio.h>
#define PAGELEN 24
#define LINELEN 512
void do_more(FILE *);
int see_more();

//主程序没变
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
  int see_more(FILE*), reply;
  FILE *fp_tty;
  //  /dev/tty是键盘和显示器的设备描述文件
  fp_tty = fopen("/dev/tty", "r");

  if ( fp_tty == NULL) {
    exit(1);
  }
  //从fp指向的文件中读取LINELEN个字符到line数组中
  while ( fgets(line, LINELEN, fp)) {
    //输出pagelen行后，执行see_more,等待输入参数，
   //此处see_more从第一版的标准输入（可能是管道前命令的输出）变成了指定输入（此时为键盘）
    if (num_of_lines == PAGELEN) {
      //see_more只能从键盘读取输入，修正了从管道输入数据时的bug
      reply = see_more(fp_tty);
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


int see_more(FILE *cmd){
  int c;
  //反白显示more？
  printf("\033[7m more? \033[m");
  while ((c = getc(cmd)) != EOF) {
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
