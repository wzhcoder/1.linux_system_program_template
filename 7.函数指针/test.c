#include <signal.h>
#include <stdio.h>

typedef void (*test_handle_t)(int );  /* 定义了一个函数指针类型 test_handle_t ，这个函数指针类型
										可以定义 函数，输入参数类型为int，返回值为void *类型 */

void test_handle(int num)
{
    printf("test = %d\r\n", num);
}

void test(int num, test_handle_t fuc) 
{
    fuc(num);
}


void test2(int num, void *fuc(int a)) //等价于test
{
    fuc(num);
}


int main(void)
{
    test(23, test_handle);	
	test2(14, test_handle);
}


