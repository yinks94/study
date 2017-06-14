#include <spawn.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <wait.h>

char file_log[64]; //로그릴 기록할 파일명
void cat_logfile(); //로그 파일을 출력하는 함수

int main(int argc, char *argv[])
{

    int fd0, fd1;
    FILE *fp0;
    char buf[64];

    snprintf(file_log, sizeof(file_log), "%s.log", argv[0]);
    if( (fd0=open(file_log, O_CREAT|O_TRUNC|O_RDWR, 0644)) == -1 )
    {
        //error !!!
    }


    write(fd0, "1234567890abcdefghij", 20);
    cat_logfile();

    if( (fd1 = dup(fd0)) == -1 )
    {
        // error !!!
    }

    write(fd1, "OPQRSTU", 7);
    cat_logfile();


    //파일기술자로부터 고수준 파일 처리 구조체 생성
    if( (fp0=fdopen(fd1, "r+")) == NULL )
    {
        // error !!
    }

    printf("\tfd0(%d) fd1(%d)\n", fd0, fd1);
    lseek(fd1, 2, SEEK_SET);    //fd1의 현재 오프셋 위치 변경
    write(fd1, ",fd1,", 5);
    cat_logfile();
    write(fd0, ",fd0,", 5);
    cat_logfile();
    fread(buf, 5, 1, fp0);      //fp0로부터 파일읽기
    printf("\tread buf=%.5s\n", buf);
    fwrite("(^o^)",5, 1, fp0);
    fflush(fp0);
    cat_logfile();
    fclose(fp0);
    close(fd1);
    close(fd0);
    return 0;
}

void cat_logfile()
{
    static int cnt;
    char *argv_child[] = {"cat", file_log, NULL};
    printf("%d={", cnt++);
    fflush(stdout);
    posix_spawnp(NULL, argv_child[0], NULL, NULL, argv_child, NULL);
    (void)wait(NULL);
    printf("}\n");
    fflush(stdout);
}
