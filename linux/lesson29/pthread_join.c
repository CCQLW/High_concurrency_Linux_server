#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int value = 199;
void *callback(void *arg)
{
    printf("child thread...\n");
    printf("arg value : %d \n", *(int *)arg);
    return (void *)&value;
}

int main()
{
    pthread_t tid;

    int num = 10;

    int ret = pthread_create(&tid, NULL, callback, (void *)&num);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error : %s \n", errstr);
    }
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    }
    printf("tid : %ld, main thread id : %ld\n", tid, pthread_self());

    int *thread_retval;

    ret = pthread_join(tid, (void *)&thread_retval);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error : %s \n", errstr);
    }
    printf("thread_rerturn %d\n",*thread_retval);

    printf("回收子线程成功！！\n");

    pthread_exit(NULL);

    return 0;
}