#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <linux/msg.h>
#include <stdarg.h>

int demo(char* msg,...);
int pipe_test(void);

int main(void)
{
    // pipe_test();
    demo("demo", "This ", "is ","a ", "demo!", "");
    return 0;
}

int pipe_test(void)
{
    int result = -1;
    int fd[2];
    pid_t pid;
    char str[] = "你好，管道";
    char r_buf[20];
    int i = 0;

    int *write_fd, *read_fd;

    write_fd = &fd[1];
    read_fd  = &fd[0];
    printf("%d\r\n", sizeof(r_buf));

    result = pipe(fd);
    if(result == -1){
        printf("建立管道失败\r\n");
        return -1;
    }

    pid = fork();
    if(pid == -1){
        printf("建立进程失败\r\n");
        return -1;        
    }else if(pid == 0){
        close(*read_fd);

        result = write(*write_fd, str,strlen(str));

    }else{
        close(*write_fd);
        read(*read_fd, r_buf, sizeof(r_buf));
        printf("\t\t\t\t接受到的数据：%s\r\n", r_buf);
    }

    return 0;

}


int demo(char* msg,...)
{
    if (!msg)
    {
        return 0;
    }

    int count = 0;

    va_list p;
    va_start(p, msg);

    while (1)
    {
        count++;
        char* s = va_arg(p, char*);

        if (strcmp(s, "") == 0)
        {
            printf("\n");
            break;
        }

        printf("%s", s);
    }

    va_end(p);

    return count;
}