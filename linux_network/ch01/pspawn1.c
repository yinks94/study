#include <spawn.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    int ret_err = 0;
    char buf_err[64];
    char *argv_child[] = {"forkexec_child", NULL};

    pid_t pid_child;
    posix_spawn_file_actions_t posix_faction; /*파일 액션 구조체*/


    printf("Parent[%d]: Start\n", getpid() );

    //초기화
    if( (ret_err = posix_spawn_file_actions_init(&posix_faction)) != 0 )
    {
        strerror_r(ret_err, buf_err, sizeof(buf_err));
        fprintf(stderr, "Fail: file_actions_init: %s\n", buf_err);
        exit(EXIT_FAILURE);
    }


    if( (ret_err = posix_spawn_file_actions_addopen(&posix_faction, 3, "pspawn.log", O_WRONLY|O_CREAT|O_APPEND, 0664)) != 0 )
    {
        strerror_r(ret_err, buf_err, sizeof(buf_err));
        fprintf(stderr, "Fail:file_actions_addopen: %s\n", buf_err);
        exit(EXIT_FAILURE);
    }

    ret_err = posix_spawn( &pid_child, 
                           argv_child[0], 
                           &posix_faction,
                           NULL, 
                           argv_child, 
                           NULL);

    if( (ret_err=posix_spawn_file_actions_destroy(&posix_faction)) != 0 )
    {
        strerror_r(ret_err, buf_err, sizeof(buf_err));
        fprintf(stderr, "Fail: file_actions_destory: %s\n", buf_err);
        exit(EXIT_FAILURE);
    }

    printf("Parent[%d]: Wait for child(%d)\n", getpid(), (int)pid_child);
    (void)wait(NULL); /* 자식 프로세스의 종료 대기 */
    printf("Parent[%d]: Exit\n", getpid());
    return 0;
}
