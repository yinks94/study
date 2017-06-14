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
#include <stddef.h>


#define pr_struct(pfix_name) printf("sizeof(MY_ST_"#pfix_name")=%2d ,", sizeof(MY_ST_##pfix_name)); \
        printf("\toffsetof(cnt)=0x%04x\n", offsetof(MY_ST_##pfix_name, cnt));

typedef struct my_st_a {
    char    str[7];
    char    cnt[4];
}MY_ST_A;

typedef struct my_st_b {
    char    str[7];
    int     cnt;
} __attribute__((packed))MY_ST_B;

typedef struct my_st_c {
    char    str[7];
    short   cnt;
} MY_ST_C;

typedef struct my_st_d {
    char    str[9];
    double   cnt;
} MY_ST_D;


int main()
{
    pr_struct(A);
    pr_struct(B);
    pr_struct(C);
    pr_struct(D);
    return 0;
}
