#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST

int main(int argc, char const *argv[]) {
  /* code */
  struct utmp current_record;
  int utmpfd;
  int reclen = sizeof(current_record)

  //打开UTMP_FILE, 有错误就输出；UTMP_FILE在utmp.h中定义；
  if ( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
    perror(UTMP_FILE);
    exit(1);
  }
  //从utmpfd读取reclean个字符到current_record,执行show_info
  while (read(utmpfd, &current_record, reclen) == reclen){
    show_info(&current_record);
  }
  close(utmpfd);
  return 0;
}


show_info(struct utmp *utbufp){
  printf("% -8.8s", utbufp->ut_name);
  printf(" ");
  printf("% -8.8s", utbufp->ut_line);
  printf(" ");
  printf("% -10ld", utbufp->ut_time);
  printf(" ");
# ifdef SHOWHOST
  printf("( %s)", utbufp->ut_host);
# endif
  printf("\n");
}
