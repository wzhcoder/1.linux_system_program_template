#include <signal.h>
#include <stdio.h>


void sig_handle(int signo)			/*信号处理函数*/
{
	if( SIGSTOP == signo)					/*为SIGSTOP信号*/
	{
		printf("接收到信号SIGSTOP\n");		/*打印信息*/
	}	
	else if(SIGKILL==signo)					/*为SIGKILL信号*/
	{
		printf("接收到信号SIGKILL\n");		/*打印信息*/
	}
	else									/*其他信号*/
	{
		printf("接收到信号:%d\n",signo);		/*打印信息*/
	}
	
	return;
}





int main(void)
{
	__sighandler_t ret;
	ret = signal(SIGQUIT, sig_handle);		
	if(SIG_ERR == ret)						/*挂接失败*/
	{
        perror("reason: ");
		return -1;							/*返回*/
	}	
	
	ret = signal(SIGINT, sig_handle);		
	if(SIG_ERR == ret)						/*挂接失败*/
	{
        perror("reason: ");
		return -1;							/*返回*/
	}
	
	while(1);								/*等待程序退出*/
	
}


