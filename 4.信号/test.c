#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>

union semun {							/*信号量操作的联合结构*/
	int 				val;			/*整型变量*/
	struct semid_ds 	*buf;			/*semid_ds结构指针*/
	unsigned short 		*array;			/*数组类型*/
} arg;									/*定义一个全局变量*/

typedef int sem_t;

sem_t CreateSem(key_t key, int value);
void  SetvalueSem(sem_t semid, int value);
int   GetvalueSem(sem_t semid);			
void  DestroySem(sem_t semid);					

int Sem_P(sem_t semid);			/*增加信号量值*/			
int Sem_V(sem_t semid);			/*减小信号量值*/			

int progress_test(void);
int main(void)
{

    progress_test();

    // key_t key;
    // int semid;
    // char i;
    // int value = 0;

    // key = ftok("/ipc/sem", 'a');
    // if(key == -1){
    //     printf("创建key错误\r\n");
    // }

    // semid = CreateSem(key, 100);

    // for(i = 0;i <3;i++){
    //     Sem_V(semid);
    // }
    // printf("信号量的值：%d\r\n", GetvalueSem(semid));

    // for(i = 0;i <3;i++){
    //     Sem_P(semid);    
    // }
    // printf("信号量的值：%d\r\n", GetvalueSem(semid));



    // DestroySem(semid);



    return 0;


    

}

int progress_test(void)
{
    pid_t pid, ppid;
    int count = 0;

    key_t key;
    int semid;
    char i;
    int value = 0;

    key = ftok("/ipc/sem", 'a');
    if(key == -1){
        printf("创建key错误\r\n");
    }
    semid = CreateSem(key, 100);

    pid = fork();
    
    if(pid ==  -1){
        printf("创建进程失败\r\n");
        perror("进程");
        return -1;
    }else if(pid == 0){

        for(i = 0;i <3;i++){
        Sem_P(semid);    
        }
        printf("子进程，信号量的值：%d\r\n", GetvalueSem(semid));

        DestroySem(semid);

    }else{

        for(i = 0;i <3;i++){
        Sem_V(semid);
        }
        printf("父进程，信号量的值：%d\r\n", GetvalueSem(semid));
    }

}



sem_t CreateSem(key_t key, int value)	/*建立信号量，魔数key和信号量的初始值										   value*/
{
	union semun sem;					/*信号量结构变量*/
	sem_t semid;						/*信号量ID*/
	sem.val = value;					/*设置初始值*/
	
	semid = semget(key,1,IPC_CREAT|0666);	/*获得信号量的ID*/
	if (-1 == semid){						/*获得信号量ID失败*/
		printf("创建信号量错误\n");/*打印信息*/
        perror("reason: ");
		return -1;							/*返回错误*/
	}
	
	semctl(semid,0,SETVAL,sem);		   /*发送命令，建立value初始值的信号量*/
		
	return semid;						/*返回建立的信号量*/
}


void SetvalueSem(sem_t semid, int value)			/*设置信号量的值*/
{
	union semun sem;								/*信号量操作的结构*/
	sem.val = value;								/*值初始化*/
		
	semctl(semid,0,SETVAL,sem);						/*设置信号量的值*/
}

int GetvalueSem(sem_t semid)						/*获得信号量的值*/
{
	union semun sem;								/*信号量操作的结构*/
	return semctl(semid,0,GETVAL,sem);				/*获得信号量的值*/
}

void DestroySem(sem_t semid)							/*销毁信号量*/
{
	union semun sem;									/*信号量操作的结构*/
	sem.val = 0;										/*信号量值的初始化*/
	
	semctl(semid,0,IPC_RMID,sem);						/*设置信号量*/
}



int Sem_P(sem_t semid)							/*增加信号量*/
{
	struct sembuf sops={0,+1,IPC_NOWAIT};		/*建立信号量结构值*/
		
	return (semop(semid,&sops,1));				/*发送命令*/
}
int Sem_V(sem_t semid)							/*减小信号量值*/
{
	struct sembuf sops={0,-1,IPC_NOWAIT};		/*建立信号量结构值*/
	
	return (semop(semid,&sops,1));				/*发送命令*/
}

