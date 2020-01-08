#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
			

int main(void)
{

    pid_t pid, ppid;
    int count = 0;

    key_t key;
    int semid, shmid;
    char i;
    char *shms, *shmc;
    int value = 0;

    char msg[] = "234234";

    printf("%d\r\n",strlen(msg)+1);

    key = ftok("/ipc/sem", 'a');
    if(key == -1){
        printf("创建key错误\r\n");
    }

    shmid = shmget(key, 1024, IPC_CREAT|0666);//获得1024个字节大小的内存

    pid = fork();
    
    if(pid ==  -1){
        printf("创建进程失败\r\n");
        perror("进程");
        return -1;
    }else if(pid > 0){
        shms = (char *)shmat(shmid, 0, 0); //获得共享内存的首地址

        memcpy(shms, msg, strlen(msg)+1);

        sleep(3);
        shmdt(shms);
        
    }else if(pid == 0){
        shms = (char *)shmat(shmid, 0, 0);
        
        printf("共享内存的值是:%s\r\n ", shms);
        shmdt(shms);
    }
    return 0;
}