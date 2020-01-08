#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int  fork_create(void);

int main(void)
{
    fork_create();
    return 0;
}

int  fork_create(void)
{
    pid_t pid, ppid;

    pid = fork();
    
    if(pid ==  -1){
        printf("创建进程失败\r\n");
        perror("进程");
        return -1;
    }else if(pid == 0){
        int count = 0;
        printf("这是子进程\r\n");
        printf("当前进程ID:%d\n",getpid());
        printf("该进程的父进程ID:%d\n",getppid());
        while(1){
            count++;
            printf("open\r\n");
            sleep(1);
            printf("close\r\n");
            sleep(1);
            printf("%d\r\n",count);
        }
    }else{
        int count = 0;
        printf("\r\n这是父进程\r\n");
        printf("当前进程ID:%d\n",getpid());
        printf("该进程父进程ID:%d\n",getppid());
        while(1){
            count += 2;
            printf("\t on \r\n");
            usleep(500000);
            printf("\t off\r\n");
            usleep(500000);
            printf("\t%d\r\n",count);
        }
    }

}